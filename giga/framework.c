// Copyright (c) 2011-2020 <>< Charles Lohr - Under the MIT/x11 or NewBSD License you choose.
//  NO WARRANTY! NO GUARANTEE OF SUPPORT! USE AT YOUR OWN RISK

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "os_generic.h"
#include <GLES3/gl3.h>
#include <asset_manager.h>
#include <asset_manager_jni.h>
#include <android_native_app_glue.h>
#include <android/sensor.h>
#include <android/log.h>
#include <dlfcn.h>
#include "CNFGAndroid.h"

// #include <android/log.h>

#define CNFG_IMPLEMENTATION
#define CNFG3D

#include "CNFG.h"

// bass
#define BASSDEF(f) (*f)
#include "bass.h"

// read image
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

typedef struct
{
	int w;
	int h;
	int c;
	uint32_t *rdimg;
	unsigned int tex;
} image;

void rdimg(image *img, unsigned char *data)
{
	uint32_t *rd;
	rd = malloc(sizeof(int) * img->w * img->h);
	uint32_t current = 0;

	for (int y = 0; y < img->h; y += 1)
	{
		for (int x = 0; x < img->w; x += 1)
		{
			current = 0;
			for (int i = 0; i < img->c; i++)
			{
				current = current << 8;
				current += (uint32_t)data[(y * img->w + x) * img->c + i];
			}
			for (int i = 0; i < 4 - img->c; i++)
			{
				if (current == 1)
				{
					current = 0x00 | current << 8;
					continue;
				}
				current = 0xff | current << 8;
			}
			rd[(y * img->w + x)] = current;
		}
	}
	img->rdimg = rd;
}

image *loadimagefromapk(char *name)
{
	// Logs("> loadimagefromapk -> %s", name);
	int w = 0, h = 0, c = 0;
	unsigned char *pixels = 0;

	AAsset *file = AAssetManager_open(gapp->activity->assetManager, name, AASSET_MODE_BUFFER);
	if (file)
	{
		uint32_t size = AAsset_getLength(file);
		unsigned char *data = (unsigned char *)malloc(size * sizeof(unsigned char));
		AAsset_read(file, data, size);
		AAsset_close(file);
		pixels = stbi_load_from_memory(data, size, &w, &h, &c, STBI_rgb_alpha);
	}
	else
	{
		// Logs("loadimagefromapk -> %s not found!", name);
	}

	image *img;
	img = malloc(sizeof(image));
	img->w = w;
	img->h = h;
	img->c = c;

	if (pixels == NULL)
	{
		// Logs("pixels is null");
		img->rdimg = NULL;
		return img;
	}

	// Faster way, but it doesn't seem to work. TODO FIXME
	/*if (c == 4) {
		img->rdimg = (unsigned int *)data;
		return img;
	}*/

	rdimg(img, pixels);
	stbi_image_free(pixels);

	return img;
}

// test load image from path
image *loadimage(char *path)
{
	int w, h, c;

	unsigned char *data = stbi_load(path, &w, &h, &c, 0);

	image *img;
	img = malloc(sizeof(image));
	img->w = w;
	img->h = h;
	img->c = c;

	if (data == NULL)
	{
		// char buff[256];
		// sprintf(buff, "could not find image at path %s", path);
		img->rdimg = NULL;
		return img;
	}

	// Faster way, but it doesn't seem to work. TODO FIXME
	/*if (c == 4) {
		img->rdimg = (unsigned int *)data;
		return img;
	}*/

	rdimg(img, data);
	stbi_image_free(data);

	return img;
}

void RenderImage(unsigned int tex, int x, int y, int w, int h)
{
	if (w == 0 || h == 0)
		return;

	CNFGFlushRender();

	glUseProgram(gRDBlitProg);
	glUniform4f(gRDBlitProgUX, 1.f / gRDLastResizeW, -1.f / gRDLastResizeH, -0.5f + x / (float)gRDLastResizeW, 0.5f - y / (float)gRDLastResizeH);
	glUniform1i(gRDBlitProgUT, 0);

	glBindTexture(GL_TEXTURE_2D, tex);

	float zrotx = 0;
	float zroty = 0;
	float brotx = w;
	float broty = h;
	float wrotx = w;
	float wroty = 0;
	float hrotx = 0;
	float hroty = h;

	const float verts[] = {
		zrotx, zroty, wrotx, wroty, brotx, broty,
		zrotx, zroty, brotx, broty, hrotx, hroty};
	static const uint8_t colors[] = {
		0, 0, 255, 0, 255, 255,
		0, 0, 255, 255, 0, 255};

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, verts);
	glVertexAttribPointer(1, 2, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

float mountainangle;
float mountainoffsetx;
float mountainoffsety;

ASensorManager *sm;
const ASensor *as;
bool no_sensor_for_gyro = false;
ASensorEventQueue *aeq;
ALooper *l;

void SetupIMU()
{
	sm = ASensorManager_getInstance();
	as = ASensorManager_getDefaultSensor(sm, ASENSOR_TYPE_GYROSCOPE);
	no_sensor_for_gyro = as == NULL;
	l = ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS);
	aeq = ASensorManager_createEventQueue(sm, (ALooper *)&l, 0, 0, 0); // XXX??!?! This looks wrong.
	if (!no_sensor_for_gyro)
	{
		ASensorEventQueue_enableSensor(aeq, as);
		printf("setEvent Rate: %d\n", ASensorEventQueue_setEventRate(aeq, as, 10000));
	}
}

float accx, accy, accz;
int accs;

void AccCheck()
{
	if (no_sensor_for_gyro)
	{
		return;
	}

	ASensorEvent evt;
	do
	{
		ssize_t s = ASensorEventQueue_getEvents(aeq, &evt, 1);
		if (s <= 0)
			break;
		accx = evt.vector.v[0];
		accy = evt.vector.v[1];
		accz = evt.vector.v[2];
		mountainangle /*degrees*/ -= accz; // * 3.1415 / 360.0;// / 100.0;
		mountainoffsety += accy;
		mountainoffsetx += accx;
		accs++;
	} while (1);
}

unsigned frames = 0;
unsigned long iframeno = 0;

void AndroidDisplayKeyboard(int pShow);

int lastbuttonx = 0;
int lastbuttony = 0;
int lastmotionx = 0;
int lastmotiony = 0;
int lastbid = 0;
int lastmask = 0;
int lastkey, lastkeydown;
int lastbdown;

static int keyboard_up;

void HandleKey(int keycode, int bDown)
{
	lastkey = keycode;
	lastkeydown = bDown;
	// if (keycode == 10 && !bDown)
	// {
	// 	keyboard_up = 0;
	// 	AndroidDisplayKeyboard(keyboard_up);
	// }

	printf("The keycode is %d", keycode);
	if (keycode == 4)
	{
		exit(0);
		AndroidSendToBack(1);
	} // Handle Physical Back Button.
	else if (keycode == 3)
	{
		exit(0);
		AndroidSendToBack(1);
	}

	// press any key, Gone boom

	// exit(0);
	// AndroidSendToBack(1);
}

void HandleButton(int x, int y, int button, int bDown)
{
	lastbid = button;
	lastbuttonx = x;
	lastbuttony = y;
	lastbdown = bDown;
	// if( bDown ) { keyboard_up = !keyboard_up; AndroidDisplayKeyboard( keyboard_up ); }
}

void HandleMotion(int x, int y, int mask)
{
	lastmask = mask;
	lastmotionx = x;
	lastmotiony = y;
}

#define HMX 162
#define HMY 162
short screenx, screeny;
float Heightmap[HMX * HMY];
void *g_libBASS = NULL;

extern struct android_app *gapp;

void HandleDestroy()
{
	printf("Destroying\n");
	exit(10);
}

volatile int suspended;

uint32_t randomtexturedata[256 * 256];

HSTREAM curr_sample;

void PlaySound(const char *filename, int loop)
{
	AAsset *asset = AAssetManager_open(gapp->activity->assetManager, filename, AASSET_MODE_BUFFER);
	const void *data = AAsset_getBuffer(asset);
	size_t size = AAsset_getLength(asset);
	unsigned char *m_EncodedBuffer = (unsigned char *)malloc(size);
	memcpy(m_EncodedBuffer, data, size);
	size_t m_EncodedBufferSize = size;
	AAsset_close(asset);

	BASS_SetConfig(BASS_CONFIG_GVOL_STREAM, 10000);
	BASS_SetConfig(BASS_CONFIG_NET_PLAYLIST, 1);
	BASS_SetConfig(BASS_CONFIG_NET_TIMEOUT, 10000); // ms

	HSTREAM hSample;
	if (loop == 1)
	{
		hSample = BASS_StreamCreateFile(TRUE, m_EncodedBuffer, 0, m_EncodedBufferSize, BASS_SAMPLE_LOOP);
	}
	else
	{
		hSample = BASS_StreamCreateFile(TRUE, m_EncodedBuffer, 0, m_EncodedBufferSize, BASS_SAMPLE_MONO);
	}
	curr_sample = hSample;

	BASS_ChannelPlay(hSample, true);
}

void StopSound()
{
	BASS_StreamFree(curr_sample);
}

#include "helper.c"

int run(void init(), void gameloop())
{
	int x, y;
	double ThisTime;
	double LastFPSTime = OGGetAbsoluteTime();
	int linesegs = 0;

	CNFGBGColor = 0x000040ff;
	CNFGSetupFullscreen("Test Bench", 0);
	// CNFGSetup( "Test Bench", 0, 0 );

	SetupIMU();

	g_libBASS = dlopen("libbass.so", RTLD_NOW | RTLD_GLOBAL);
	if (g_libBASS == NULL)
	{
		// Logs("[libBASS] Error loading libbass.so");
		// Logs("Error: %s\n", dlerror());
		return -1;
	}
	else
	{
		// Logs("[libBASS] libbass.so loaded...");

#define LOADBASSFUNCTION(f) *((void **)&f) = dlsym(g_libBASS, #f)
		LOADBASSFUNCTION(BASS_SetConfig);
		LOADBASSFUNCTION(BASS_GetConfig);
		LOADBASSFUNCTION(BASS_GetVersion);
		LOADBASSFUNCTION(BASS_ErrorGetCode);
		LOADBASSFUNCTION(BASS_Init);
		LOADBASSFUNCTION(BASS_SetVolume);
		LOADBASSFUNCTION(BASS_GetVolume);
		LOADBASSFUNCTION(BASS_SetDevice);
		LOADBASSFUNCTION(BASS_GetDevice);
		LOADBASSFUNCTION(BASS_GetDeviceInfo);
		LOADBASSFUNCTION(BASS_Free);
		LOADBASSFUNCTION(BASS_GetInfo);
		LOADBASSFUNCTION(BASS_Update);
		LOADBASSFUNCTION(BASS_GetCPU);
		LOADBASSFUNCTION(BASS_Start);
		LOADBASSFUNCTION(BASS_Stop);
		LOADBASSFUNCTION(BASS_Pause);
		LOADBASSFUNCTION(BASS_PluginLoad);
		LOADBASSFUNCTION(BASS_PluginFree);
		LOADBASSFUNCTION(BASS_PluginGetInfo);
		LOADBASSFUNCTION(BASS_Set3DFactors);
		LOADBASSFUNCTION(BASS_Get3DFactors);
		LOADBASSFUNCTION(BASS_Set3DPosition);
		LOADBASSFUNCTION(BASS_Get3DPosition);
		LOADBASSFUNCTION(BASS_Apply3D);
		LOADBASSFUNCTION(BASS_MusicLoad);
		LOADBASSFUNCTION(BASS_MusicFree);
		LOADBASSFUNCTION(BASS_SampleLoad);
		LOADBASSFUNCTION(BASS_SampleCreate);
		LOADBASSFUNCTION(BASS_SampleFree);
		LOADBASSFUNCTION(BASS_SampleGetInfo);
		LOADBASSFUNCTION(BASS_SampleSetInfo);
		LOADBASSFUNCTION(BASS_SampleGetChannel);
		LOADBASSFUNCTION(BASS_SampleStop);
		LOADBASSFUNCTION(BASS_StreamCreate);
		LOADBASSFUNCTION(BASS_StreamCreateFile);
		LOADBASSFUNCTION(BASS_StreamCreateURL);
		LOADBASSFUNCTION(BASS_StreamCreateFileUser);
		LOADBASSFUNCTION(BASS_StreamFree);
		LOADBASSFUNCTION(BASS_StreamGetFilePosition);
		LOADBASSFUNCTION(BASS_RecordInit);
		LOADBASSFUNCTION(BASS_RecordSetDevice);
		LOADBASSFUNCTION(BASS_RecordFree);
		LOADBASSFUNCTION(BASS_RecordGetInfo);
		LOADBASSFUNCTION(BASS_RecordGetInputName);
		LOADBASSFUNCTION(BASS_RecordSetInput);
		LOADBASSFUNCTION(BASS_RecordGetInput);
		LOADBASSFUNCTION(BASS_RecordStart);
		LOADBASSFUNCTION(BASS_ChannelBytes2Seconds);
		LOADBASSFUNCTION(BASS_ChannelSeconds2Bytes);
		LOADBASSFUNCTION(BASS_ChannelGetDevice);
		LOADBASSFUNCTION(BASS_ChannelSetDevice);
		LOADBASSFUNCTION(BASS_ChannelIsActive);
		LOADBASSFUNCTION(BASS_ChannelGetInfo);
		LOADBASSFUNCTION(BASS_ChannelGetTags);
		LOADBASSFUNCTION(BASS_ChannelPlay);
		LOADBASSFUNCTION(BASS_ChannelStop);
		LOADBASSFUNCTION(BASS_ChannelPause);
		LOADBASSFUNCTION(BASS_ChannelIsSliding);
		LOADBASSFUNCTION(BASS_ChannelSet3DAttributes);
		LOADBASSFUNCTION(BASS_ChannelGet3DAttributes);
		LOADBASSFUNCTION(BASS_ChannelSet3DPosition);
		LOADBASSFUNCTION(BASS_ChannelGet3DPosition);
		LOADBASSFUNCTION(BASS_ChannelGetLength);
		LOADBASSFUNCTION(BASS_ChannelSetPosition);
		LOADBASSFUNCTION(BASS_ChannelGetPosition);
		LOADBASSFUNCTION(BASS_ChannelGetLevel);
		LOADBASSFUNCTION(BASS_ChannelGetData);
		LOADBASSFUNCTION(BASS_ChannelSetSync);
		LOADBASSFUNCTION(BASS_ChannelRemoveSync);
		LOADBASSFUNCTION(BASS_ChannelSetDSP);
		LOADBASSFUNCTION(BASS_ChannelRemoveDSP);
		LOADBASSFUNCTION(BASS_ChannelSetLink);
		LOADBASSFUNCTION(BASS_ChannelRemoveLink);
		LOADBASSFUNCTION(BASS_ChannelSetFX);
		LOADBASSFUNCTION(BASS_ChannelRemoveFX);
		LOADBASSFUNCTION(BASS_FXSetParameters);
		LOADBASSFUNCTION(BASS_FXGetParameters);

		// Logs("[libBASS] loading settings..");

		if (BASS_Init(-1, 44100, 0, 0, NULL) != true)
		{
			// Logs("[libBASS] libbass.so is not initialized, error: %i", BASS_ErrorGetCode());
		}
		else
		{
			// Logs("[libBASS] libbass.so successfully initialized");
		}

		init();
	}

	while (1)
	{

		int i, pos;
		iframeno++;

		CNFGHandleInput();
		AccCheck();

		if (suspended)
		{
			usleep(50000);
			continue;
		}

		CNFGClearFrame();
		CNFGColor(0xFFFFFFFF);
		CNFGGetDimensions(&screenx, &screeny);

		// CNFGPenX = 200;
		// CNFGPenY = 500;
		// char st[50];
		// CNFGColor(0xffffffff);

		// sprintf(st, "%d %d %d", backgroud2->w, backgroud2->h, backgroud2->rdimg);
		// CNFGDrawText(st, 10);
		// CNFGSetLineWidth(2);

		gameloop();
		frames++;
		// On Android, CNFGSwapBuffers must be called, and CNFGUpdateScreenWithBitmap does not have an implied framebuffer swap.
		CNFGSwapBuffers();

		ThisTime = OGGetAbsoluteTime();
		if (ThisTime > LastFPSTime + 1)
		{
			printf("FPS: %d\n", frames);
			frames = 0;
			linesegs = 0;
			LastFPSTime += 1;
		}
	}

	return (0);
}

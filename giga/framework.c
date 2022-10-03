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
#include "CNFGAndroid.h"
// #include <android/log.h>

#define CNFG_IMPLEMENTATION
#define CNFG3D

#include "CNFG.h"

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

	// if (keycode == 4)
	// {
	// 	exit(0);
	// 	AndroidSendToBack(1);
	// } // Handle Physical Back Button.
	// if (keycode == 3)
	// {
	// 	exit(0);
	// 	AndroidSendToBack(1);
	// }

	// press any key, Gone boom

		exit(0);
		AndroidSendToBack(1);
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

extern struct android_app *gapp;

void HandleDestroy()
{
	printf("Destroying\n");
	exit(10);
}

volatile int suspended;

uint32_t randomtexturedata[256 * 256];

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
	init();

	SetupIMU();

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

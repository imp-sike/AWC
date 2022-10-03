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
#include "CNFGAndroid.h"

#define CNFG_IMPLEMENTATION
#define CNFG3D

#include "CNFG.h"


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

static int keyboard_up;

void HandleKey(int keycode, int bDown)
{
	lastkey = keycode;
	lastkeydown = bDown;
	// if( keycode == 10 && !bDown ) { keyboard_up = 0; AndroidDisplayKeyboard( keyboard_up );  }

	if (keycode == 4)
	{
		AndroidSendToBack(1);
	} // Handle Physical Back Button.
}

void HandleButton(int x, int y, int button, int bDown)
{
	lastbid = button;
	lastbuttonx = x;
	lastbuttony = y;



	if( bDown ) { keyboard_up = !keyboard_up; AndroidDisplayKeyboard( keyboard_up ); }
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

extern struct android_app *gapp;

void HandleDestroy()
{
	printf("Destroying\n");
	exit(10);
}

volatile int suspended;

void HandleSuspend()
{
	suspended = 1;
}

void HandleResume()
{
	suspended = 0;
}

#include "material.c"

int run(void f())
{
	int x, y;
	double ThisTime;
	double LastFPSTime = OGGetAbsoluteTime();
	int linesegs = 0;

	CNFGBGColor = 0xffffffff;
	CNFGSetupFullscreen("Test Bench", 0);
	// CNFGSetup( "Test Bench", 0, 0 );

	

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

		f();
     	
		
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

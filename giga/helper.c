void Button(void onClick(), const char *title, int backgroundcolor, int textcolor, int xmin, int ymin, int xmax, int ymax)
{

	CNFGGetDimensions(&screenx, &screeny);

	CNFGColor(backgroundcolor);
	CNFGTackRectangle(xmin, ymin, xmax, ymax);

	int distanceX = xmax - xmin;
	int distanceY = ymax - ymin;

	CNFGSetLineWidth(5);
	CNFGPenX = xmin + 0.35 * distanceX;
	CNFGPenY = ymin + 0.3 * distanceY;
	CNFGColor(textcolor);
	CNFGDrawText(title, 15);
	CNFGFlushRender();

	if (lastbdown == true)
	{
		if (lastbuttonx >= xmin && lastbuttonx <= xmax)
		{
			if (lastbuttony >= ymin && lastbuttony <= ymax)
			{
				HandleButton(lastbuttonx, lastbuttony, 0, 0);
				PlaySound("button.wav", 0);
				onClick();
				// StopSound();
			}
		}
	}
}

void ImageButton(void onClick(), image *img, short xmin, short ymin, short xmax, short ymax)
{

	// CNFGGetDimensions(&screenx, &screeny);

	// CNFGColor(0xffffffff);
	// CNFGTackRectangle(xmin, ymin, xmax, ymax);

	// xmin = 0.9 * screenx;
	// ymin = 0.7 * screenx;

	RenderImage(img->tex, xmin, ymin, xmax, ymax);

	xmax = xmin + xmax;
	ymax = ymin + ymax;

	// CNFGSetLineWidth(3);
	// CNFGPenX = 50;
	// CNFGPenY = 50;
	// CNFGColor(textcolor);
	// CNFGDrawText(title, 5);
	CNFGFlushRender();

	if (lastbdown == true)
	{
		if (lastbuttonx >= xmin && lastbuttonx <= xmax)
		{
			if (lastbuttony >= ymin && lastbuttony <= ymax)
			{
				PlaySound("button.wav", 0);

				HandleButton(lastbuttonx, lastbuttony, 0, 0);
				onClick();
			}
		}
	}
}


void OpenUrl(const char* link)
{
	const struct JNINativeInterface * env = 0;
	const struct JNINativeInterface ** envptr = &env;
	const struct JNIInvokeInterface ** jniiptr = gapp->activity->vm;
	const struct JNIInvokeInterface * jnii = *jniiptr;
	
	jobject activity = gapp->activity->clazz;

	jnii->AttachCurrentThread( jniiptr, &envptr, NULL);
	env = (*envptr);

    // Retrieve class information
    jclass activityClass = env->FindClass(envptr,"android/app/Activity");
    jclass intentClass = env->FindClass(envptr,"android/content/Intent");
    jclass uriClass = env->FindClass(envptr,"android/net/Uri");

    // convert URL std::string to jstring
    jstring uriString = env->NewStringUTF(envptr,link);

    // call parse method
    jmethodID uriParse = env->GetStaticMethodID(envptr,uriClass, "parse", "(Ljava/lang/String;)Landroid/net/Uri;");

    // set URL in method
    jobject uri = env->CallStaticObjectMethod(envptr,uriClass, uriParse, uriString);

    // intent action
    jstring actionString = env->NewStringUTF(envptr,"android.intent.action.VIEW");

    // call the intent object constructor
    jmethodID newIntent = env->GetMethodID(envptr,intentClass, "<init>", "(Ljava/lang/String;Landroid/net/Uri;)V");

    // create the intent instance
    jobject intent = env->AllocObject(envptr,intentClass);

    // set intent constructor
    env->CallVoidMethod(envptr,intent, newIntent, actionString, uri);

    jmethodID startActivity = env->GetMethodID(envptr,activityClass, "startActivity", "(Landroid/content/Intent;)V");
    env->CallVoidMethod(envptr,activity, startActivity, intent);

    jnii->DetachCurrentThread( jniiptr );	
}


void playBeepSound() {
	
}
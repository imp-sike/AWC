

void TitleBar(const char *title, int backgroundcolor, int textcolor)
{
	// Square behind text

	CNFGGetDimensions(&screenx, &screeny);

	CNFGColor(backgroundcolor);
	CNFGTackRectangle(0, 0, screenx, 170);

	CNFGSetLineWidth(3);
	CNFGPenX = 50;
	CNFGPenY = 50;
	CNFGColor(textcolor);
	CNFGDrawText(title, 15);
	CNFGFlushRender();

	CNFGPenX = 50;
	CNFGPenY = 200;
}

void SetPosition(int x, int y)
{
	CNFGPenX = x;
	CNFGPenY = y;
}

void Text(const char *content)
{
	CNFGPenX += 0;
	CNFGPenY += 50;
	CNFGColor(0x000000ff);
	CNFGDrawText(content, 10);
	CNFGFlushRender();
}

void DisplayAssetText()
{
	const char *assettext = "Not Found";
	AAsset *file = AAssetManager_open(gapp->activity->assetManager, "asset.txt", AASSET_MODE_BUFFER);
	if (file)
	{
		size_t fileLength = AAsset_getLength(file);
		char *temp = malloc(fileLength + 1);
		memcpy(temp, AAsset_getBuffer(file), fileLength);
		temp[fileLength] = 0;
		assettext = temp;
	}
	CNFGPenX = 50;
	CNFGPenY = 180;
	CNFGColor(0x000000ff);
	CNFGDrawText(assettext, 10);
	CNFGFlushRender();
}

void AppBackgroundColor(int color) 
{
	CNFGBGColor = color;
}

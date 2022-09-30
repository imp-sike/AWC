// char *btnText = "START";
short playerCurrentX =  0;
short playerCurrentY;

void onStartBtn()
{
    CURRENT_GAME_STATE = GAME;
}

void onAboutBtn()
{
    CURRENT_GAME_STATE = ABOUT;
}

void onShareBtn()
{
    CURRENT_GAME_STATE = SHARE;
}

void menu_screen()
{
    // MENU SCREEN

    // title
    CNFGPenX = screenx * 0.27;
    CNFGPenY = 100;
    CNFGSetLineWidth(10);
    CNFGDrawText("YOU WILL EVENTUALLY DIE!", 15);

    // background running animation

    double Now3 = OGGetAbsoluteTime();
    if (Now3 > EventTimeBackground)
    {
        jtemp++;

        playerCurrentX += 10;
        if(playerCurrentX > screenx) playerCurrentX = 0; 


        if(jtemp == 10) jtemp = 0;

        EventTimeBackground += 0.07;
    }

    RenderImage(runAnimation[jtemp]->tex, playerCurrentX, playerPositionYmin, playerPositionXmax, playerPositionYmax);

    // play button
    // ImageButton(onMenuBtnClick, "PLAY", 0x000000ff, 0xffffffff);
    Button(onStartBtn, "START", 0xDC143Cff, 0xffffffff, screenx * 0.37, 300, screenx * 0.63, 450); // edit
    Button(onAboutBtn, "ABOUT", 0xF15381ff, 0xffffffff, screenx * 0.37, 500, screenx * 0.63, 650); // edit
    Button(onShareBtn, "LINKS", 0x272727ff, 0xffffffff, screenx * 0.37, 700, screenx * 0.63, 850); // edit
}
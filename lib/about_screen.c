void onBackBtn()
{
    CURRENT_GAME_STATE = MENU;
}

void about_screen()
{
    // MENU SCREEN

    // title
    CNFGPenX = screenx * 0.27;
    CNFGPenY = 100;
    CNFGSetLineWidth(10);
    CNFGDrawText("YOU WILL EVENTUALLY DIE!", 15);

    // description
    CNFGPenX = screenx * 0.23;
    CNFGPenY = 200;
    CNFGSetLineWidth(7);
    CNFGDrawText("\n An endless casual game created with the power\n   of C programming Language (Java sucks?)!\n\n        Created by: SULAV PARAJULI", 10);

    // background running animation

    double Now3 = OGGetAbsoluteTime();
    if (Now3 > EventTimeBackground)
    {
        jtemp++;

        playerCurrentX += 10;
        if (playerCurrentX > screenx)
            playerCurrentX = 0;

        if (jtemp == 10)
            jtemp = 0;

        EventTimeBackground += 0.07;
    }

    RenderImage(runAnimation[jtemp]->tex, playerCurrentX, playerPositionYmin, playerPositionXmax, playerPositionYmax);

    // play button
    // ImageButton(onMenuBtnClick, "PLAY", 0x000000ff, 0xffffffff);
    Button(onBackBtn, "Back", 0xDC143Cff, 0xffffffff, screenx * 0.37, 600, screenx * 0.63, 750); // edit
}
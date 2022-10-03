void onBackBtn2()
{
    CURRENT_GAME_STATE = MENU;
}

void openFacebook()
{
    // CURRENT_GAME_STATE = MENU;
    
    OpenUrl("http://www.facebook.com/thesulav");
    exit(0);
}

void share_screen()
{
    // MENU SCREEN

    // vibrate(2000);

    // title
    CNFGPenX = screenx * 0.27;
    CNFGPenY = 100;
    CNFGSetLineWidth(10);
    CNFGDrawText("YOU WILL EVENTUALLY DIE!", 15);

    // description
    CNFGPenX = screenx * 0.35;
    CNFGPenY = 200;
    CNFGSetLineWidth(7);
    CNFGDrawText("\nCONNECT & SHARE THE GAME", 10);

    // play button
    // ImageButton(onMenuBtnClick, "PLAY", 0x000000ff, 0xffffffff);
    ImageButton(openFacebook, facebook, screenx * 0.37, 400, 220, 150);
    ImageButton(openFacebook, playstore, screenx * 0.37 + 200, 400, 150, 150);
    ImageButton(openFacebook, playstore, screenx * 0.37 + 380, 400, 150, 150);

    // ImageButton(openFacebook, "F", 0x3b5998ff, 0xffffffff, screenx * 0.37, 400, screenx * 0.43, 550); // edit
    Button(onBackBtn2, "Back", 0xDC143Cff, 0xffffffff, screenx * 0.37, 700, screenx * 0.63, 850); // edit
}
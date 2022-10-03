
void onBackPress()
{
    CURRENT_GAME_STATE = GAME;
}

void onMenuPress() {
    scorePoint = 0;
    CURRENT_GAME_STATE = MENU;
}


void onExitPress() {
    scorePoint = 0;
    // CURRENT_GAME_STATE = MENU;
    exit(0);
}

void pause_screen()
{
    // title
    CNFGPenX = screenx * 0.38;
    CNFGPenY = 100;
    CNFGSetLineWidth(10);
    CNFGDrawText("Game Paused!", 15);

    // play button
    // ImageButton(onMenuBtnClick, "PLAY", 0x000000ff, 0xffffffff);
    Button(onBackPress, "PLAY", 0x4bb543ff, 0xffffffff, screenx * 0.37, 300, screenx * 0.63, 450); // edit
    Button(onExitPress, "EXIT", 0x272727ff, 0xffffffff, screenx * 0.37, 500, screenx * 0.63, 650); // edit
    // Button(onExitPress, "EXIT", 0x272727ff, 0xffffffff, screenx * 0.37, 700, screenx * 0.63, 850); // edit
}
void onHomePress()
{
  scorePoint = 0;
  sprintf(score, "SCORE-%d", scorePoint);

  playerPositionXmin = screenx * 0.2;
  playerPositionYmin = 0.785 * screeny;
  playerPositionYmintemp = playerPositionYmin;
  playerPositionXmax = 120;
  playerPositionYmax = 180;
  screenxdecrementfactor = 0;
  CURRENT_GAME_STATE = MENU;
}

void onExitCalled()
{
  exit(0);
}

void game_over_screen()
{


  // game over screen
  // title
  CNFGPenX = screenx * 0.38;
  CNFGPenY = 100;
  CNFGSetLineWidth(10);
  CNFGDrawText("YOU ARE DEAD!", 15);

  CNFGPenX = screenx * 0.45;
  CNFGPenY = 200;
  CNFGSetLineWidth(10);
  CNFGDrawText(score, 15);

  // play button
  // ImageButton(onMenuBtnClick, "PLAY", 0x000000ff, 0xffffffff);
  Button(onHomePress, "HOME", 0x4bb543ff, 0xffffffff, screenx * 0.37, 400, screenx * 0.63, 550);  // edit
  Button(onExitCalled, "EXIT", 0x272727ff, 0xffffffff, screenx * 0.37, 600, screenx * 0.63, 750); // edit
                                                                                                  // Button(onExitPress, "EXIT", 0x272727ff, 0xffffffff, screenx * 0.37, 700, screenx * 0.63, 850); // edit
}

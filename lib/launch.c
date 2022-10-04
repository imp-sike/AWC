#include "framework.c"
#include "declarations.c"
#include "init.c"
#include "player.c"
#include "menu_screen.c"
#include "about_screen.c"
#include "share_screen.c"
#include "game_screen.c"
#include "game_over_screen.c"
#include "render_parallalax_bg.c"
#include "pause_screen.c"

// Reload the assets when the app is resumed from background
void HandleResume()
{
    suspended = 0;
    initialize_assets();
    // exit(0);
}

void HandleSuspend()
{
    StopSound();
    suspended = 1;
}

// The function `init` is called at the starting of the game
void init()
{
    playerObject = calloc(1, playerObject);
    enemyObject = calloc(1, enemyObject);

    CNFGGetDimensions(&screenx, &screeny);
    finalscreenx = screenx;
    finalscreeny = screeny;
    playerPositionXmin = screenx * 0.2;
    playerPositionYmin = 0.785 * screeny;
    playerPositionYmintemp = playerPositionYmin;
    playerPositionXmax = 120;
    playerPositionYmax = 180;

    render_parallalax_bg_init();

    initialize_assets();

    PlaySound("bg.mp3", 1);

    // init_sound();
}

// Typical Game Loop, Physics actions can be done here
void gameloop()
{
    CNFGBGColor = 0x000000ff;
    CNFGFlushRender();

    render_parallalax_bg();
    player();

    if (CURRENT_GAME_STATE == GAME)
    {
        game_screen();
    }

    else if (CURRENT_GAME_STATE == GAME_OVER)
    {
        game_over_screen();
    }

    else if (CURRENT_GAME_STATE == MENU)
    {
        menu_screen();
    }

    else if (CURRENT_GAME_STATE == ABOUT)
    {
        about_screen();
    }

    else if (CURRENT_GAME_STATE == SHARE)
    {
        share_screen();
    }

    else if (CURRENT_GAME_STATE == PAUSE)
    {
        pause_screen();
    }
}

// Entry Point of the Game
int main()
{
    EventTime = OGGetAbsoluteTime() + 0.04;
    EventTimeEnemySpawn = OGGetAbsoluteTime() + 0.05;
    EventTimeParallalax = OGGetAbsoluteTime() + 0.05;

    run(init, gameloop);
    return 0;
}
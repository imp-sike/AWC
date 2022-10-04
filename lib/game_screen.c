#include "collision_detection.c"

int collision = -1;
float enemyTimeStampInc = 0.001;

// Event Handlers
void jumpPlayer()
{
    if (!jumping)
    {
        // text = "Presses";
        jumping = !jumping;
    }
}

void pauseScreen()
{
    CURRENT_GAME_STATE = PAUSE;
}

void game_screen()
{
    // RenderImage(backgroud1->tex, 0, 0, screenx, screeny);
    // Button(onClick,rocket,text, screenx * 0.85, screeny * 0.7, 150, 150);
    enemyObject->objectXmin = screenx - screenxdecrementfactor;
    enemyObject->objectYmin = playerPositionYmintemp;
    enemyObject->objectXmax = screenx - screenxdecrementfactor + playerPositionXmax;
    enemyObject->objectYmax = playerPositionYmintemp + playerPositionYmax;

    playerObject->objectXmin = playerPositionXmin;
    playerObject->objectYmin = playerPositionYmin;
    playerObject->objectXmax = playerPositionXmin + playerPositionXmax;
    playerObject->objectYmax = playerPositionYmin + playerPositionYmax;

    if (jumping)
        RenderImage(jumpAnimation[jtemp]->tex, playerPositionXmin, playerPositionYmin, playerPositionXmax, playerPositionYmax);
    else
        RenderImage(runAnimation[itemp]->tex, playerPositionXmin, playerPositionYmin, playerPositionXmax, playerPositionYmax);

    // play button
    ImageButton(jumpPlayer, rocket, 0.85 * finalscreenx, 0.7 * finalscreeny, 170, 170); // edit
    ImageButton(pauseScreen, pauseImg, 0.9 * finalscreenx, 50, 150, 150);               // edit

    // if(itemp == 0) RenderImage(runAnimation[0]->tex, screenx * 0.5, 0.785 * screeny, 120, 180);

    // spawnRandomEnemy();
    double NowEnemySpawn = OGGetAbsoluteTime();
    if (NowEnemySpawn > EventTimeEnemySpawn)
    {
        screenxdecrementfactor += 10;

        if (screenx - screenxdecrementfactor <= -10)
        {
            scorePoint += 10;
            sprintf(score, "SCORE-%d", scorePoint);
            screenxdecrementfactor = 0;
        }
        EventTimeEnemySpawn += enemyTimeStampInc;
    }
    RenderImage(enemies[6]->tex, screenx - screenxdecrementfactor, playerPositionYmintemp, playerPositionXmax, playerPositionYmax);

    collision = pleaseCheckCollision(playerObject, enemyObject);
    if (collision == 1)
    {
        // donot know why rendering is off in axis
        // so only SECOND_POINT_COLLISOON works
        PlaySound("dead.wav", 0);

        CURRENT_GAME_STATE = GAME_OVER;
    }
    // sprintf(score, "COLLIDE= %d", scorePoint);

    CNFGPenX = 100;
    CNFGPenY = 100;
    CNFGSetLineWidth(7);
    CNFGDrawText(score, 10);
}
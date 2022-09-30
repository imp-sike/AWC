#include "framework.c"
// #include "physac.h"

enum GameState
{
    MENU,
    GAME,
    GAME_OVER,
    SHARE,
    ABOUT
};

int CURRENT_GAME_STATE = MENU;

// basic global properties that may be required later
// Enemy Class
struct Enemy
{
    short currentXPosition;
};

short screenx, screeny;
short finalscreenx, finalscreeny;
bool jumping = false;
char score[15] = "SCORE-0";
image *backgroud1;
image *rocks1;
image *rocks2;
image *ground;
image *char0;
image *rocket;
image *facebook;
image *playstore;

// current enemy in scenes

// runAnimation arrays
image *runAnimation[10];
image *runAnimation0;

// jumpAnimation arrays
image *jumpAnimation[10];
image *jumpAnimation0;

// enemy arrays
image *enemies[8];
image *enemies0;

int scorePoint = 0;

// all enemy
// struct Enemy *allEnemy[8];
short currentXPositionOfEnemy[8] = {0, 0, 0, 0, 0, 0, 0, 0};

// global player coordinate
short playerPositionXmin;
short playerPositionYmin;
short playerPositionXmax;
short playerPositionYmax;
short playerPositionYmintemp;
const short playerMaxJumpSingle = 500;
const short playerSingleJumpStepping = playerMaxJumpSingle / 5;

// Event Handlers
void onClick()
{
    if (!jumping)
    {
        // text = "Presses";
        jumping = !jumping;
    }
}

void init_jump_animations()
{
    // runAnimation animations
    jumpAnimation0 = loadimagefromapk("jump/Jump__000.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[0] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__001.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[1] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__002.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[2] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__003.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[3] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__004.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[4] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__005.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[5] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__006.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[6] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__007.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[7] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__008.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[8] = jumpAnimation0;

    jumpAnimation0 = loadimagefromapk("jump/Jump__009.png");
    jumpAnimation0->tex = CNFGTexImage(jumpAnimation0->rdimg, jumpAnimation0->w, jumpAnimation0->h);
    jumpAnimation[9] = jumpAnimation0;
}

void init_run_animations()
{
    // runAnimation animations
    runAnimation0 = loadimagefromapk("run/Run__000.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[0] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__001.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[1] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__002.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[2] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__003.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[3] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__004.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[4] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__005.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[5] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__006.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[6] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__007.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[7] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__008.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[8] = runAnimation0;

    runAnimation0 = loadimagefromapk("run/Run__009.png");
    runAnimation0->tex = CNFGTexImage(runAnimation0->rdimg, runAnimation0->w, runAnimation0->h);
    runAnimation[9] = runAnimation0;
}

void init_enemies()
{

    enemies0 = loadimagefromapk("enemy/grass3.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[0] = enemies0;

    enemies0 = loadimagefromapk("enemy/rectangle1.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[1] = enemies0;

    enemies0 = loadimagefromapk("enemy/rocks.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[2] = enemies0;

    enemies0 = loadimagefromapk("enemy/rocks2.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[3] = enemies0;

    enemies0 = loadimagefromapk("enemy/rocks3.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[4] = enemies0;

    enemies0 = loadimagefromapk("enemy/trees1.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[5] = enemies0;

    enemies0 = loadimagefromapk("enemy/trees2.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[6] = enemies0;

    enemies0 = loadimagefromapk("enemy/trees3.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[7] = enemies0;
}

void initialize_assets()
{

    backgroud1 = loadimagefromapk("sky.png");
    backgroud1->tex = CNFGTexImage(backgroud1->rdimg, backgroud1->w, backgroud1->h);

    rocks1 = loadimagefromapk("rocks_1.png");
    rocks1->tex = CNFGTexImage(rocks1->rdimg, rocks1->w, rocks1->h);

    rocks2 = loadimagefromapk("rocks_2.png");
    rocks2->tex = CNFGTexImage(rocks2->rdimg, rocks2->w, rocks2->h);

    ground = loadimagefromapk("tile.png");
    ground->tex = CNFGTexImage(ground->rdimg, ground->w, ground->h);

    char0 = loadimagefromapk("char0.png");
    char0->tex = CNFGTexImage(char0->rdimg, char0->w, char0->h);

    rocket = loadimagefromapk("rocket.png");
    rocket->tex = CNFGTexImage(rocket->rdimg, rocket->w, rocket->h);


    facebook = loadimagefromapk("facebook.png");
    facebook->tex = CNFGTexImage(facebook->rdimg, facebook->w, facebook->h);


    playstore = loadimagefromapk("playstore.png");
    playstore->tex = CNFGTexImage(playstore->rdimg, playstore->w, playstore->h);

    init_run_animations();
    init_jump_animations();
    init_enemies();
}

// The function `init` is called at the starting of the game
void init()
{
    CNFGGetDimensions(&screenx, &screeny);
    finalscreenx = screenx;
    finalscreeny = screeny;
    playerPositionXmin = screenx * 0.2;
    playerPositionYmin = 0.785 * screeny;
    playerPositionYmintemp = playerPositionYmin;
    playerPositionXmax = 120;
    playerPositionYmax = 180;

    initialize_assets();
}

// Reload the assets when the app is resumed from background
void HandleResume()
{
    suspended = 0;
    initialize_assets();
}

double EventTime;
double EventTimeEnemySpawn;
double EventTimeBackground;
int itemp = 0;
int jtemp = 0;
int enemytemp = 0;
short screenxdecrementfactor = 0;

#include "menu_screen.c"
#include "about_screen.c"
#include "share_screen.c"

// Typical Game Loop, Physics actions can be done here
void gameloop()
{
    CNFGBGColor = 0x000000ff;
    CNFGFlushRender();
    RenderImage(backgroud1->tex, 0, 0, screenx, screeny);
    RenderImage(rocks1->tex, 0, screeny * 0.05, screenx, screeny);
    RenderImage(rocks2->tex, 0, screeny * 0.2, screenx, screeny);
    RenderImage(ground->tex, 0, 0.95 * screeny, screenx, screeny);

    if (CURRENT_GAME_STATE == GAME)
    {

        // RenderImage(backgroud1->tex, 0, 0, screenx, screeny);
        // Button(onClick,rocket,text, screenx * 0.85, screeny * 0.7, 150, 150);

        ImageButton(onClick, rocket, 0.85 * finalscreenx, 0.7 * finalscreeny, 170, 170); // edit

        // if(itemp == 0) RenderImage(runAnimation[0]->tex, screenx * 0.5, 0.785 * screeny, 120, 180);

        if (jumping)
        {
            double Now2 = OGGetAbsoluteTime();
            if (Now2 > EventTime)
            {

                jtemp++;
                playerPositionYmin -= playerSingleJumpStepping;
                if (jtemp == 4)
                    playerPositionYmin += playerSingleJumpStepping;
                if (jtemp > 9)
                {
                    jtemp = 0;
                    jumping = false;
                    playerPositionYmin = playerPositionYmintemp;
                }
                EventTime += 0.07;
            }

            RenderImage(jumpAnimation[jtemp]->tex, playerPositionXmin, playerPositionYmin, playerPositionXmax, playerPositionYmax);
        }
        else
        {
            // Not jumping
            double Now = OGGetAbsoluteTime();
            if (Now > EventTime)
            {

                itemp++;
                if (itemp > 9)
                    itemp = 0;
                EventTime += 0.04;
            }
            RenderImage(runAnimation[itemp]->tex, playerPositionXmin, playerPositionYmin, playerPositionXmax, playerPositionYmax);
        }

        // spawnRandomEnemy();
        double NowEnemySpawn = OGGetAbsoluteTime();
        if (NowEnemySpawn > EventTimeEnemySpawn)
        {
            screenxdecrementfactor += 10;

            if (screenx - screenxdecrementfactor <= -10)
            {
                //     scorePoint += 10;
                //     sprintf(score, "SCORE-%d", scorePoint);
                screenxdecrementfactor = 0;
            }
            EventTimeEnemySpawn += 0.02;
        }
        RenderImage(enemies[6]->tex, screenx - screenxdecrementfactor, playerPositionYmintemp, playerPositionXmax, playerPositionYmax);

        // TODO Add collision detection  tomoroow
        if ((screenx - screenxdecrementfactor) > playerPositionXmin && (screenx - screenxdecrementfactor) < playerPositionXmax)
        {
            scorePoint = "Collision!!!";
        }
        else if ((screenx - screenxdecrementfactor + playerPositionXmax) < playerPositionXmax && (screenx - screenxdecrementfactor + playerPositionXmax) > playerPositionXmin)
        {
            scorePoint = "Collision!!!";
        }

        CNFGPenX = 100;
        CNFGPenY = 100;
        CNFGSetLineWidth(7);
        CNFGDrawText(score, 10);
    }

    else if (CURRENT_GAME_STATE == GAME_OVER)
    {
        // game over screen
        CNFGPenX = 100;
        CNFGPenY = 100;
        CNFGSetLineWidth(7);
        CNFGDrawText("Game Over", 50);
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
}

// Entry Point of the Game
int main()
{
    EventTime = OGGetAbsoluteTime() + 0.04;
    EventTimeEnemySpawn = OGGetAbsoluteTime() + 0.05;
    EventTimeBackground = OGGetAbsoluteTime() + 0.05;
    run(init, gameloop);
    return 0;
}
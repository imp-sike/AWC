#include "framework.c"
// #include "sound.c"

// #include "physac.h"

enum GameState
{
    MENU,
    GAME,
    GAME_OVER,
    SHARE,
    ABOUT,
    PAUSE
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
image *pauseImg;

struct collisionObject *enemyObject;
struct  collisionObject *playerObject;


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

struct collisionObject
{
    short objectXmin;
    short objectYmin;
    short objectXmax;
    short objectYmax;
};

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
const short playerMaxJumpSingle = 800;
const short playerSingleJumpStepping = playerMaxJumpSingle / 8;

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

    // enemies0 = loadimagefromapk("enemy/grass3.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[0] = enemies0;

    // enemies0 = loadimagefromapk("enemy/rectangle1.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[1] = enemies0;

    // enemies0 = loadimagefromapk("enemy/rocks.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[2] = enemies0;

    // enemies0 = loadimagefromapk("enemy/rocks2.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[3] = enemies0;

    // enemies0 = loadimagefromapk("enemy/rocks3.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[4] = enemies0;

    // enemies0 = loadimagefromapk("enemy/trees1.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[5] = enemies0;

    enemies0 = loadimagefromapk("enemy/trees2.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[6] = enemies0;

    // enemies0 = loadimagefromapk("enemy/trees3.png");
    // enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    // enemies[7] = enemies0;
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

    pauseImg = loadimagefromapk("pause.png");
    pauseImg->tex = CNFGTexImage(pauseImg->rdimg, pauseImg->w, pauseImg->h);

    init_run_animations();
    init_jump_animations();
    init_enemies();
}

double EventTime;
double EventTimeEnemySpawn;
double EventTimeBackground;
double EventTimeParallalax;

int itemp = 0;
int jtemp = 0;
int enemytemp = 0;
int bakitemp = 0;
short screenxdecrementfactor = 0;
char *test = "Loading...";

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
    playerObject = calloc(1,playerObject);
    enemyObject = calloc(1,enemyObject);

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
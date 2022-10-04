
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
struct collisionObject *playerObject;

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
const short playerMaxJumpSingle = 400;
const short playerSingleJumpStepping = playerMaxJumpSingle / 8;



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

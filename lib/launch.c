#include "framework.c"

short screenx, screeny;

bool pressed = false;
char *text = "Button Not Clicked";
image *backgroud1;
image *ground;

void onClick()
{
    if (pressed)
        text = "Button Clicked";
    else
        text = "Button Not Clicked";
    pressed = !pressed;
}

void initialize_assets()
{
    backgroud1 = loadimagefromapk("background.png");
    backgroud1->tex = CNFGTexImage(backgroud1->rdimg, backgroud1->w, backgroud1->h);


    ground = loadimagefromapk("ground.png");
    ground->tex = CNFGTexImage(ground->rdimg, ground->w, ground->h);
}

void init()
{
    initialize_assets();
}

void HandleResume()
{
    suspended = 0;
    initialize_assets();
}

void gameloop()
{
    CNFGGetDimensions(&screenx, &screeny);
    CNFGBGColor = 0x000000ff;
    CNFGFlushRender();
    RenderImage(backgroud1->tex, 0, 0, screenx, screeny);
    // Button(onClick, text, 0xffffffff, 0x000000ff);
    RenderImage(ground->tex, 0, screenx - 0.6 * screenx, screenx, screeny);
}

int main()
{
    run(init, gameloop);
    return 0;
}
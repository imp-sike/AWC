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

    enemies0 = loadimagefromapk("enemy/trees2.png");
    enemies0->tex = CNFGTexImage(enemies0->rdimg, enemies0->w, enemies0->h);
    enemies[6] = enemies0;
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

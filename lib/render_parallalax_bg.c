int screenCurrentXmin[3];

void render_parallalax_bg_init()
{
    screenCurrentXmin[0] = -screenx;
    screenCurrentXmin[1] = 0;
    screenCurrentXmin[2] = screenx;
}

void render_parallalax_bg()
{
    RenderImage(backgroud1->tex, 0, 0, screenx, screeny);
    RenderImage(rocks1->tex, screenCurrentXmin[0], screeny * 0.05, screenx, screeny);
    RenderImage(rocks1->tex, screenCurrentXmin[1], screeny * 0.05, screenx, screeny);
    RenderImage(rocks1->tex, screenCurrentXmin[2], screeny * 0.05, screenx, screeny);

    // parallalax
    RenderImage(rocks2->tex, screenCurrentXmin[0], screeny * 0.2, screenx, screeny);
    RenderImage(rocks2->tex, screenCurrentXmin[1], screeny * 0.2, screenx, screeny);
    RenderImage(rocks2->tex, screenCurrentXmin[2], screeny * 0.2, screenx, screeny);

    // parallalax ground
    RenderImage(ground->tex, screenCurrentXmin[0], 0.95 * screeny, screenx, screeny);
    RenderImage(ground->tex, screenCurrentXmin[1], 0.95 * screeny, screenx, screeny);
    RenderImage(ground->tex, screenCurrentXmin[2], 0.95 * screeny, screenx, screeny);

    double NowBg = OGGetAbsoluteTime();
    if (NowBg > EventTimeParallalax)
    {

        if (!suspended)
        {
            // infinite parallalax background
            if (screenCurrentXmin[0] <= -screenx)
            {
                screenCurrentXmin[0] = screenx - 10;
            }

            if (screenCurrentXmin[1] <= -screenx)
            {
                screenCurrentXmin[1] = screenx - 10;
            }

            if (screenCurrentXmin[2] <= -screenx)
            {
                screenCurrentXmin[2] = screenx - 10;
            }

            // do the parallalax background
            screenCurrentXmin[0] -= 10;
            screenCurrentXmin[1] -= 10;
            screenCurrentXmin[2] -= 10;
        }
        EventTimeParallalax += 0.01;
    }
}
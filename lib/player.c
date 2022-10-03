void player()
{
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
            EventTime += 0.08;
        }

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
    }


}
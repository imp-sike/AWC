

enum CollisionPointDetected {
    FIRST_POINT_COLLISION_DETECTED,
    SECOND_POINT_COLLISION_DETECTED,
    THIRD_POINT_COLLISION_DETECTED,
    FOURTH_POINT_COLLISION_DETECTED
};

int pleaseCheckCollision(struct collisionObject *obj1, struct collisionObject *obj2)
{
    /**
        check if there is collision and return TRUE if collided
        there are 4 points to be checked for collision



        * 1st point [obj1->objectXmin],[obj1->objectYmin]  + + + + + + + + + + +  [obj1->objectXmax],[obj1->objectYmin] 2nd point
                                                           +                   +
                                                           +                   +
                                                           +                   +
                                                           +                   +
                                                           +                   +
        * 3rd point [obj1->objectXmin],[obj1->objectYmax]  + + + + + + + + + + +  [obj1->objectXmax],[obj1->objectYmax] 4th point

    **/

    // checking collision for firstpoint [obj1->objectXmin],[obj1->objectYmin]
    if ((obj1->objectXmin >= obj2->objectXmin && obj1->objectYmin >= obj2->objectYmin) && (obj1->objectXmin >= obj2->objectXmax && obj1->objectYmin >= obj2->objectXmax)) {
        // first point collision detected
        return FIRST_POINT_COLLISION_DETECTED;
    }

    if ((obj1->objectXmax >= obj2->objectXmin && obj1->objectYmin >= obj2->objectYmin) && (obj1->objectXmax >= obj2->objectXmax && obj1->objectYmin >= obj2->objectXmax)) {
        // second point collision detected
        return SECOND_POINT_COLLISION_DETECTED;
    }

    if ((obj1->objectXmin >= obj2->objectXmin && obj1->objectYmax >= obj2->objectYmin) && (obj1->objectXmin >= obj2->objectXmax && obj1->objectYmax >= obj2->objectXmax)) {
        // third point collision detected
        return THIRD_POINT_COLLISION_DETECTED;
    }

    if ((obj1->objectXmax >= obj2->objectXmin && obj1->objectYmax >= obj2->objectYmin) && (obj1->objectXmax >= obj2->objectXmax && obj1->objectYmax >= obj2->objectXmax)) {
        // fourth point collision detected
        return FOURTH_POINT_COLLISION_DETECTED;
    }

    return -1;
}
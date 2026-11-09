#ifndef OBJVIEW_FN_80187410_PRIVATE_H
#define OBJVIEW_FN_80187410_PRIVATE_H

#include "game/objview/path186_private.h"

struct AirShipPathState {
    HSD_JObj *joint[4];
    Vec3f *points;
    int count, index;
    Vec3f control[3];
    float time;
    Vec3f position;
    float yaw;
};

#endif

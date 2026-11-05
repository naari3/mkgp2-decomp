#ifndef KARTMOVE_ROTATION_PRIVATE_H
#define KARTMOVE_ROTATION_PRIVATE_H
#include "game/kartmove/carobject_private.h"
extern const float lbl_806D96D0;
struct MovementQuat {
    float x, y, z, w;
    MovementQuat() { x = y = z = w = lbl_806D96D0; }
    ~MovementQuat() {}
};
#endif

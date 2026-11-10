#ifndef GAME_TYPES_COURSEPROPDATA_H
#define GAME_TYPES_COURSEPROPDATA_H

#include "game/types/Vec3f.h"

typedef struct CoursePropData {
    Vec3f position;
    float yaw;
    int kind;
} CoursePropData;

#endif /* GAME_TYPES_COURSEPROPDATA_H */

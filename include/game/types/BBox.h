#ifndef GAME_TYPES_BBOX_H
#define GAME_TYPES_BBOX_H

#include "game/types/Vec3.h"

typedef struct BBox {
    Vec3 min;
    Vec3 max;
    Vec3 center;
    float radius;
    int x28;
    int x2c;
    int x30;
    int x34;
    int x38;
} BBox;

#endif /* GAME_TYPES_BBOX_H */

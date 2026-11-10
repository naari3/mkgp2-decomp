#ifndef GAME_TYPES_MODELPARAM_H
#define GAME_TYPES_MODELPARAM_H

#include "game/types/Vec3f.h"

typedef struct ModelParam {
    Vec3f pos;
    float rotX;
    float rotY;
    float rotZ;
} ModelParam;

#endif /* GAME_TYPES_MODELPARAM_H */

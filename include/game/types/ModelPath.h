#ifndef GAME_TYPES_MODELPATH_H
#define GAME_TYPES_MODELPATH_H

#include "game/types/Vec3f.h"

typedef struct ModelPath {
    Vec3f *points;
    int count;
    float speed;
} ModelPath;

#endif /* GAME_TYPES_MODELPATH_H */

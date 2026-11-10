#ifndef GAME_TYPES_TERRAINSAMPLE_H
#define GAME_TYPES_TERRAINSAMPLE_H

#include "game/types/TerrainTriangle.h"

typedef struct TerrainSample {
    void *walls;
    TerrainTriangle *triangle;
    float x;
    float y;
    float z;
    unsigned char onTriangle;
    unsigned char pad_15[3];
} TerrainSample;

#endif /* GAME_TYPES_TERRAINSAMPLE_H */

#ifndef GAME_TYPES_TERRAINSTEPPER_H
#define GAME_TYPES_TERRAINSTEPPER_H

#include "game/types/TerrainSample.h"

typedef struct TerrainStepper {
    TerrainSample samples[2];
    float normal[3];
    float x;
    float pad_40;
    float z;
    int index;
    unsigned char pad_4C[4];
    float delta[3];
} TerrainStepper;

#endif /* GAME_TYPES_TERRAINSTEPPER_H */

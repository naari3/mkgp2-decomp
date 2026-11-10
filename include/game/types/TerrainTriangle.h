#ifndef GAME_TYPES_TERRAINTRIANGLE_H
#define GAME_TYPES_TERRAINTRIANGLE_H

#include "game/types/TerrainVertex.h"

typedef struct TerrainTriangle {
    unsigned char pad_00[0x10];
    TerrainVertex verts[3];
    unsigned char pad_34[0x24];
    unsigned int wallEdges;
} TerrainTriangle;

#endif /* GAME_TYPES_TERRAINTRIANGLE_H */

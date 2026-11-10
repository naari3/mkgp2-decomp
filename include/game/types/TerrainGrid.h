#ifndef GAME_TYPES_TERRAINGRID_H
#define GAME_TYPES_TERRAINGRID_H

#include "game/types/TerrainCell.h"

typedef struct TerrainGrid {
    int width;
    int height;
    float cellWidth;
    float cellDepth;
    unsigned char pad_10[0x10];
    float offsetX;
    float offsetZ;
    TerrainCell *cells;
} TerrainGrid;

#endif /* GAME_TYPES_TERRAINGRID_H */

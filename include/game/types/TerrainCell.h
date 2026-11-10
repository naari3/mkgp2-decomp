#ifndef GAME_TYPES_TERRAINCELL_H
#define GAME_TYPES_TERRAINCELL_H

#include "game/types/TerrainTri.h"

typedef struct TerrainCell {
    TerrainTri *tris;
    int triCount;
    void *walls;
    int wallCount;
} TerrainCell;

#endif /* GAME_TYPES_TERRAINCELL_H */

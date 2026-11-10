#ifndef GAME_TYPES_TERRAINSTEPPER_H
#define GAME_TYPES_TERRAINSTEPPER_H

#include "game/types/TerrainSample.h"

/* Merged from 3 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct TerrainStepper TerrainStepper;
struct TerrainStepper {
    /* 0x000 */ TerrainSample samples[2];
    /* 0x030 */ float normal[3];
    /* 0x03C */ float x;
    /* 0x040 */ unsigned char pad_040[0x4];
    /* 0x044 */ float z;
    /* 0x048 */ int index;
    /* 0x04C */ unsigned char pad_04C[0x4];
    /* 0x050 */ float delta[3];
};

#endif /* GAME_TYPES_TERRAINSTEPPER_H */

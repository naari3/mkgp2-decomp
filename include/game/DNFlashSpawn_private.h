#ifndef GAME_DNFLASHSPAWN_PRIVATE_H
#define GAME_DNFLASHSPAWN_PRIVATE_H
#include "game/DNFlash_private.h"

/* The original TU addresses these adjacent tables through one rodata base. */
struct DNFlashSpawnTables {
    unsigned int samples[0x102];
    float scales[3];
    float xLimits[3];
    float zLimits[3];
};

#endif

#ifndef GAME_TYPES_DEBRISBURST_H
#define GAME_TYPES_DEBRISBURST_H

#include "game/types/DebrisParticle.h"

/* Merged from 2 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct DebrisBurst DebrisBurst;
struct DebrisBurst {
    /* 0x000 */ unsigned char active;
    /* 0x001 */ unsigned char pad_001[0x3];
    /* 0x004 */ DebrisParticle particles[15];
};

#endif /* GAME_TYPES_DEBRISBURST_H */

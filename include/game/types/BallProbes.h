#ifndef GAME_TYPES_BALLPROBES_H
#define GAME_TYPES_BALLPROBES_H

#include "game/types/Vec.h"

/* Merged from 1 per-TU views by tools/struct_merge.py: members are
 * the ones some TU accesses; the size is the largest any view declared. */
typedef struct BallProbes BallProbes;
struct BallProbes {
    /* 0x000 */ Vec v[4];
};

#endif /* GAME_TYPES_BALLPROBES_H */

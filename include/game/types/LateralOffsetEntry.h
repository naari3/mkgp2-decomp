#ifndef GAME_TYPES_LATERALOFFSETENTRY_H
#define GAME_TYPES_LATERALOFFSETENTRY_H

#include "game/types/PathCond.h"

typedef struct LateralOffsetEntry {
    PathCond cond;
    int kart;
    float magnitude;
    int unk10;
} LateralOffsetEntry;

#endif /* GAME_TYPES_LATERALOFFSETENTRY_H */

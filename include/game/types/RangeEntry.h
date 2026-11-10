#ifndef GAME_TYPES_RANGEENTRY_H
#define GAME_TYPES_RANGEENTRY_H

#include "game/types/KartCond.h"

typedef struct RangeEntry {
    KartCond cond;
    int minValue;
    int maxValue;
} RangeEntry;

#endif /* GAME_TYPES_RANGEENTRY_H */

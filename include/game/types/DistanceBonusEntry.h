#ifndef GAME_TYPES_DISTANCEBONUSENTRY_H
#define GAME_TYPES_DISTANCEBONUSENTRY_H

#include "game/types/KartCond.h"

typedef struct DistanceBonusEntry {
    KartCond cond;
    float bonus[6][6];
} DistanceBonusEntry;

#endif /* GAME_TYPES_DISTANCEBONUSENTRY_H */

#ifndef GAME_TYPES_ITEMUSEPROBENTRY_H
#define GAME_TYPES_ITEMUSEPROBENTRY_H

#include "game/types/KartCond.h"

typedef struct ItemUseProbEntry {
    KartCond cond;
    int kart;
    float probability;
} ItemUseProbEntry;

#endif /* GAME_TYPES_ITEMUSEPROBENTRY_H */

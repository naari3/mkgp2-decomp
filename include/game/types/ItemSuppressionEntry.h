#ifndef GAME_TYPES_ITEMSUPPRESSIONENTRY_H
#define GAME_TYPES_ITEMSUPPRESSIONENTRY_H

#include "game/types/KartCond.h"

typedef struct ItemSuppressionEntry {
    KartCond cond;
    int item;
    int minValue;
    int maxValue;
} ItemSuppressionEntry;

#endif /* GAME_TYPES_ITEMSUPPRESSIONENTRY_H */

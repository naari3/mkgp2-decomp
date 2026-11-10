#ifndef GAME_TYPES_PATHVARIANTENTRY_H
#define GAME_TYPES_PATHVARIANTENTRY_H

#include "game/types/KartCond.h"

typedef struct PathVariantEntry {
    KartCond cond;
    int kart;
    int variantA;
    int variantB;
} PathVariantEntry;

#endif /* GAME_TYPES_PATHVARIANTENTRY_H */

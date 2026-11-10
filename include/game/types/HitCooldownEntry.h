#ifndef GAME_TYPES_HITCOOLDOWNENTRY_H
#define GAME_TYPES_HITCOOLDOWNENTRY_H

#include "game/types/KartCond.h"

typedef struct HitCooldownEntry {
    KartCond cond;
    int cooldown;
} HitCooldownEntry;

#endif /* GAME_TYPES_HITCOOLDOWNENTRY_H */

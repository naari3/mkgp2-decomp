#ifndef GAME_TYPES_ENEMYITEMLISTENTRY_H
#define GAME_TYPES_ENEMYITEMLISTENTRY_H

#include "game/types/KartCond.h"

typedef struct EnemyItemListEntry {
    KartCond cond;
    int itemIds[8];
} EnemyItemListEntry;

#endif /* GAME_TYPES_ENEMYITEMLISTENTRY_H */

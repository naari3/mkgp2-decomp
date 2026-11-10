#ifndef PLAYER_UNLOCK_TABLES_PENDING_PRIVATE_H
#define PLAYER_UNLOCK_TABLES_PENDING_PRIVATE_H
#include "game/PlayerDataProgressPrivate.h"
/* Read-only tables share the original player-card string/table block. */
#include "game/types/UnlockRemap.h"
#include "game/types/UnlockGrant.h"
typedef struct UnlockTables {
    unsigned char prefix[0x640];
    int baseIds[0x79];
    UnlockRemap remaps[3];
    UnlockGrant grants[120];
} UnlockTables;
extern UnlockTables lbl_8039C718;
#endif

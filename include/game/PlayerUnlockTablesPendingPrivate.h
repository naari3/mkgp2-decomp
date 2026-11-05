#ifndef PLAYER_UNLOCK_TABLES_PENDING_PRIVATE_H
#define PLAYER_UNLOCK_TABLES_PENDING_PRIVATE_H
#include "game/PlayerDataProgressPrivate.h"
/* Read-only tables share the original player-card string/table block. */
typedef struct UnlockRemap { int baseId, flagIdx, resultId; } UnlockRemap;
typedef struct UnlockGrant { int id, flagIdx, extraIdx, unknown0, unknown1; } UnlockGrant;
typedef struct UnlockTables {
    unsigned char prefix[0x640];
    int baseIds[0x79];
    UnlockRemap remaps[3];
    UnlockGrant grants[120];
} UnlockTables;
extern UnlockTables lbl_8039C718;
#endif

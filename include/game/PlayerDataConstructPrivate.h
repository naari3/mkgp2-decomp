#ifndef PLAYER_DATA_CONSTRUCT_PRIVATE_H
#define PLAYER_DATA_CONSTRUCT_PRIVATE_H
#include "game/PlayerDataResetPrivate.h"

/* Read-only view of the shared player-card pool; no data is emitted here. */
typedef struct ThreeModes { int modes[3]; } ThreeModes;
typedef struct ConstructPool {
    unsigned char common[0x1280];
    ThreeModes defaults;
    unsigned char commonAfter[0x1DA4 - 0x128C];
    char mileageError[0x24];
    char grantMessage[0x28];
} ConstructPool;
#endif

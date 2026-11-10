#ifndef GAME_TYPES_SYNCSLOT_H
#define GAME_TYPES_SYNCSLOT_H
#include "game/types/bitfields.h"

typedef struct SyncSlot {
    BITFIELDS2(unsigned char kind:5, unsigned char rest:3)
} SyncSlot;

#endif /* GAME_TYPES_SYNCSLOT_H */

#ifndef GAME_TYPES_COUNTLIST_H
#define GAME_TYPES_COUNTLIST_H

#include "game/types/CountEntry.h"

/* Declare before including (each user already does): whatever the definition below uses */

struct CountList {
    char pad0[0x18];
    unsigned char on;
    char pad19[0x2C - 0x19];
    CountEntry e[6];
};

#endif /* GAME_TYPES_COUNTLIST_H */

#ifndef GAME_TYPES_CDHOLDER_H
#define GAME_TYPES_CDHOLDER_H

#include "game/types/Countdown.h"

typedef struct CdHolder {
    char pad0[0x1C];
    Countdown *cd;
} CdHolder;

#endif /* GAME_TYPES_CDHOLDER_H */

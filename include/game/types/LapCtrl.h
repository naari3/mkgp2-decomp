#ifndef GAME_TYPES_LAPCTRL_H
#define GAME_TYPES_LAPCTRL_H

#include "game/types/LapSlot.h"

typedef struct LapCtrl {
    char pad0[0x18];
    int mode;
    float f1C;
    int cur;
    char pad24[0x24];
    LapSlot slots[2];
    char pad98[0x74 - 0x98 + 0x50];
} LapCtrl;

#endif /* GAME_TYPES_LAPCTRL_H */

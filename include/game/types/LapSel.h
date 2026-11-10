#ifndef GAME_TYPES_LAPSEL_H
#define GAME_TYPES_LAPSEL_H

#include "game/types/Countdown.h"
#include "game/types/SelSlot.h"

typedef struct LapSel {
    char pad0[0x18];
    int mode;
    float f1C;
    int cur;
    SelSlot slots[2];
    int timer;
    Countdown *cd;
    void *p7c;
} LapSel;

#endif /* GAME_TYPES_LAPSEL_H */

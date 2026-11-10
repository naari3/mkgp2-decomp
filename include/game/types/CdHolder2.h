#ifndef GAME_TYPES_CDHOLDER2_H
#define GAME_TYPES_CDHOLDER2_H

#include "game/types/Countdown.h"

/* Include before this header (each user already does): "game/types/VObj14.h" */

typedef struct CdHolder2 {
    char pad0[0x34];
    Countdown *cd;
    char pad38[0x28];
    VObj14 *f60;
    char pad64[4];
    void *f68;
} CdHolder2;

#endif /* GAME_TYPES_CDHOLDER2_H */

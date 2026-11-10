#ifndef GAME_TYPES_KARTMOVE_H
#define GAME_TYPES_KARTMOVE_H

#include "game/types/V3.h"

typedef struct KartMove {
    unsigned char pad0[0x40];
    V3 pos;
    V3 prevPos;
    float mtx[16];
    unsigned char pad98[0x1c8 - 0x98];
    float yaw;
} KartMove;

#endif /* GAME_TYPES_KARTMOVE_H */

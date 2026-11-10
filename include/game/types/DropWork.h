#ifndef GAME_TYPES_DROPWORK_H
#define GAME_TYPES_DROPWORK_H

#include "game/types/Vec.h"

typedef struct DropWork {
    unsigned char pad0[4];
    unsigned int timer;
    unsigned char pad8[0x14 - 8];
    float groundY;
    unsigned char pad18[0x34 - 0x18];
    Vec offset;
    Vec vel;
    unsigned char pad4C[0x9C - 0x4C];
    void *kart;
} DropWork;

#endif /* GAME_TYPES_DROPWORK_H */

#ifndef GAME_TARU_ITEM_DISPATCH_25_PRIVATE_H
#define GAME_TARU_ITEM_DISPATCH_25_PRIVATE_H

#include "game/objview/item_state_private.h"

typedef struct TaruState {
    unsigned char render, hit;
    unsigned char pad2[2];
    unsigned int timer, timer2, timer3, timer4;
    float height, lift;
    unsigned char pad1c[0x34-0x1c];
    Vec3 velocity, offset;
    unsigned char pad4c[0x9c-0x4c];
    void *driver;
} TaruState;

#endif

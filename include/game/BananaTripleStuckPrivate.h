#ifndef BANANA_TRIPLE_STUCK_PRIVATE_H
#define BANANA_TRIPLE_STUCK_PRIVATE_H
#include "game/objview/item_state_private.h"
/* State payload used by the attached-driver movement callback. */
typedef struct BananaDriverState {
    unsigned char count, rebound, dispatchHit, pad3;
    unsigned int timer;
    unsigned char pad8[0x34 - 8];
    Vec3 delta;
    Vec3 offset;
    unsigned char pad4c[0x9c - 0x4c];
    void *driver;
} BananaDriverState;
#endif

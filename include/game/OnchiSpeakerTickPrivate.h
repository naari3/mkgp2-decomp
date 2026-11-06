#ifndef ONCHI_SPEAKER_TICK_PRIVATE_H
#define ONCHI_SPEAKER_TICK_PRIVATE_H
#include "game/objview/item_state_private.h"
typedef struct OnchiSpeakerTickState {
    unsigned char pad0[4];
    unsigned int timer, timer8, timerc, timer10;
    float height, lift;
    unsigned char pad1c[0x34 - 0x1c];
    Vec3 delta;
    unsigned char pad40[0xc];
    void *effect;
} OnchiSpeakerTickState;
#endif

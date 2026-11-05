#ifndef ONCHI_SPEAKER_FLIGHT_PRIVATE_H
#define ONCHI_SPEAKER_FLIGHT_PRIVATE_H
#include "game/objview/item_state_private.h"
typedef struct OnchiFlightState {
    unsigned char pad0[4];
    unsigned int timer;
    unsigned char pad8[0x14 - 8];
    float height;
    unsigned char pad18[0x34 - 0x18];
    Vec3 offset;
    Vec3 delta;
    unsigned char pad4c[0x9c - 0x4c];
    void *driver;
} OnchiFlightState;
#endif

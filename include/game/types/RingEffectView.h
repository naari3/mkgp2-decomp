#ifndef GAME_TYPES_RINGEFFECTVIEW_H
#define GAME_TYPES_RINGEFFECTVIEW_H

#include "game/types/RingKartView.h"
#include "game/types/Vec3.h"

typedef struct RingEffectView {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char active;
    unsigned char pad29[3];
    float lifetime;
    unsigned char pad30[0x5C];
    Vec3 position;
    Vec3 rotation;
    Vec3 velocity;
    float scale;
    signed char state;
    signed char phase;
    unsigned char padB6[0x66];
    RingKartView *kart;
    Vec3 offset;
    unsigned char pad12C[0x24];
    float amount;
    unsigned char pad154[0x2C];
    unsigned int timer0;
    unsigned int timer1;
    unsigned int timer2;
    unsigned int timer3;
} RingEffectView;

#endif /* GAME_TYPES_RINGEFFECTVIEW_H */

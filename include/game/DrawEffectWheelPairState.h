#ifndef GAME_DRAWEFFECTWHEELPAIRSTATE_H
#define GAME_DRAWEFFECTWHEELPAIRSTATE_H

/* Private payload at DrawEffect + 0xCC for the rear-wheel pair callback. */
typedef struct WheelPairState {
    unsigned char pad00[0x10];
    unsigned char *children[2]; /* 0x10 */
    unsigned char pad18[0x50 - 0x18];
    unsigned char *driver;      /* 0x50 */
    unsigned char pad54[0x84 - 0x54];
    float angle;               /* 0x84 */
    float speed;               /* 0x88 */
    unsigned char pad8C[0xB4 - 0x8C];
    unsigned int timers[4];     /* 0xB4 */
} WheelPairState;

#endif

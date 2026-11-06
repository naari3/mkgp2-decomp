#ifndef GAME_STARITEMPRIVATE_H
#define GAME_STARITEMPRIVATE_H
/* Star item payload at item + 0xEC. Vec3 is supplied by item_state_private.h. */
typedef struct StarWork {
    unsigned int unused, timer, timer2, timer3, timer4;
    float height, lift, gravity;
    unsigned char pad20[0x14];
    Vec3 delta, velocity;
    unsigned char pad4c[0x4C];
    void *owner, *target;
    signed char action;
} StarWork;
#endif

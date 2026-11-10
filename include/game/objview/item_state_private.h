#ifndef OBJVIEW_ITEM_STATE_PRIVATE_H
#define OBJVIEW_ITEM_STATE_PRIVATE_H
#include "game/types/Vec3.h"
typedef struct Item {
    unsigned char pad0[8];
    int id;
    unsigned char padc[8];
    unsigned char sprite[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float scale;
    unsigned char pad30[0x3C - 0x30];
    unsigned char x3c;
    unsigned char pad3d[0x8C - 0x3D];
    unsigned char flags8c;
    char tracking;
    char hit;
    unsigned char pad8f;
    Vec3 impulse;
    struct Item *anchor;
    Vec3 pos;
    Vec3 rotation;
    Vec3 velocity;
    float param;
    signed char phase, subphase, step, reason;
} Item;
typedef struct State {
    unsigned char count;
    unsigned char pad1[3];
    unsigned int timer;
    unsigned int x8, xc, x10;
    float height;
    float lift;
    float gravity;
    unsigned char pad20[0x34 - 0x20];
    Vec3 delta;
    unsigned char pad40[0x98 - 0x40];
    void *owner;
    void *target;
    signed char action;
} State;
#endif

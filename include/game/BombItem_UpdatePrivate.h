#ifndef BOMB_ITEM_UPDATE_PRIVATE_H
#define BOMB_ITEM_UPDATE_PRIVATE_H

#include "game/MathInline.h"
typedef Vec3f Vec;

/* Private view of the item payload beginning at item + 0xEC. */
typedef struct BombWork {
    unsigned int unused, timer, timer2, timer3, timer4;
    float tether, tetherScale;
    char pad1c[0x18];
    Vec offset;
    char pad40[0xC];
    void *effect;
    char pad50[0x40];
    unsigned char active;
    char pad91[3];
    unsigned int owner, target;
    char pad9c[0x54];
    unsigned char alias;
    char padf1[3];
    unsigned int context;
} BombWork;

typedef struct BombItem {
    char pad0[0x14];
    unsigned char sprite[0x14];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0xC];
    unsigned char flag;
    char pad3d[0x4F];
    unsigned char spriteMode, spriteFlag;
    char pad8e[0xE];
    struct BombItem *anchor;
    Vec pos, rotation, velocity;
    float scale;
    signed char state, phase;
    unsigned char padca;
    signed char mode;
    char padcc[0x20];
    BombWork work;
} BombItem;

#endif

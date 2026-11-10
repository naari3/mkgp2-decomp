#ifndef SPRITESLOT_WITHRESEED_PRIVATE_H
#define SPRITESLOT_WITHRESEED_PRIVATE_H
#include "game/types/SpriteAnimEntry.h"

#include "game/types/SpriteClassEntry.h"

typedef struct SpriteSlot {
    unsigned char pad0[4];
    void *model;       /* 0x04 */
    unsigned char cls; /* 0x08 */
    signed char anim;  /* 0x09 */
    signed char state; /* 0x0A */
    float frame;       /* 0x0C */
    unsigned char pad10[0x24];
    float matrix[12]; /* 0x34 */
} SpriteSlot;

#endif

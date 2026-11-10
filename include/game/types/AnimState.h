#ifndef GAME_TYPES_ANIMSTATE_H
#define GAME_TYPES_ANIMSTATE_H

#include "game/types/AnimVec3.h"

typedef struct AnimState {
    unsigned char pad00[0x28];
    float weight;
    unsigned char pad2c[0x44 - 0x2C];
    int current;
    AnimVec3 pos[4];
    AnimVec3 rot[4];
    AnimVec3 scale[4];
    float alpha[4];
} AnimState;

#endif /* GAME_TYPES_ANIMSTATE_H */

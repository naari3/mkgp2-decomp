#ifndef GAME_ITEM_BOX_DEBRIS_PARTICLE_PRIVATE_H
#define GAME_ITEM_BOX_DEBRIS_PARTICLE_PRIVATE_H

#include "game/types/Matrix.h"
typedef struct DebrisParticle {
    float position[3];
    unsigned char unknown[0x14];
    float scale;
    float yaw;
    float pitch;
} DebrisParticle;

#endif

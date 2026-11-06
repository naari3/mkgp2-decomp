#ifndef GAME_ITEM_BOX_DEBRIS_PARTICLE_PRIVATE_H
#define GAME_ITEM_BOX_DEBRIS_PARTICLE_PRIVATE_H

typedef struct Matrix { float v[16]; } Matrix;
typedef struct DebrisParticle {
    float position[3];
    unsigned char unknown[0x14];
    float scale;
    float yaw;
    float pitch;
} DebrisParticle;

#endif

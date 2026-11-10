#ifndef GAME_TYPES_PARTICLE_H
#define GAME_TYPES_PARTICLE_H

#include "game/types/Vec3f.h"

typedef struct Particle {
    unsigned char active;
    Vec3f v;
    Vec3f pos;
    float scale;
    float alpha;
    float c[3];
    float speed;
    float grow;
    float dvx;
    float dvy;
    float dvz;
    int delay;
} Particle;

#endif /* GAME_TYPES_PARTICLE_H */

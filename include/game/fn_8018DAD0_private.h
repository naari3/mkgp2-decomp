#ifndef FN_8018DAD0_PRIVATE_H
#define FN_8018DAD0_PRIVATE_H

#include "game/types/Vec3.h"
typedef struct Joint { char pad[0x38]; Vec3 pos; } Joint;
typedef struct Emitter { Joint *joint; unsigned char delay, burst; char pad[2]; } Emitter;
typedef struct Particle {
    unsigned char type; char pad[3]; Vec3 pos;
    float age, scale, speed, frequency, amplitude, offset, alpha;
} Particle;
typedef struct Owner { void *vt; Emitter *emitters; int count; void *models; Particle *parts; int rand64, rand48; } Owner;
typedef struct ParticleTables {
    char prefix[0x3c];
    float scale[3];
    float speed[3];
    float frequency[3];
    float amplitude[3];
    float fadeStart[3];
    float fadeEnd[3];
    char gap[0x18];
    Vec3 nearest;
} ParticleTables;

#endif

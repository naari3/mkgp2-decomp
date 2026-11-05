#ifndef OBJVIEW_PARTICLE_UPDATE_PRIVATE_H
#define OBJVIEW_PARTICLE_UPDATE_PRIVATE_H

typedef struct ParticleUpdateVec { float x, y, z; } ParticleUpdateVec;
typedef struct ViewParticle {
    unsigned char active;
    unsigned char pad[3];
    float x, y, depth, alpha;
    float speed, amplitude, angle, angularSpeed;
} ViewParticle;
typedef struct ViewParticleOwner {
    void *vt;
    void *model;
    void *table;
    ViewParticle *particles;
    int delay;
    unsigned char reset, enabled;
    unsigned char pad16[2];
    ParticleUpdateVec position;
    int randomX, randomY, randomParam, randomDelay;
} ViewParticleOwner;

#endif

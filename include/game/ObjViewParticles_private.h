#ifndef OBJVIEW_PARTICLES_PRIVATE_H
#define OBJVIEW_PARTICLES_PRIVATE_H
#include "game/mapobject/mapobject.h"

struct ParticleDirection {
    Vec3f direction;
    int cooldown;
};
struct ObjParticle {
    float age;
    Vec3f position;
    Vec3f rotation;
    float ageStep;
    float alpha;
    Vec3f velocity;
    Vec3f spin;
    float sway;
    float phase;
    float phaseStep;
};
struct ObjParticleView {
    void *vtable;
    clNormal3D *model;
    ParticleDirection *directions;
    ObjParticle *particles;
    int positionRandom;
    int spinRandom;
    int phaseRandom;
    int cooldownRandom;
    int velocityRandom;
};
struct ParticleEmitter {
    Vec3f start;
    Vec3f end;
};
extern "C" {
extern ParticleEmitter lbl_8037D888[7];
extern float lbl_80495994[64];
extern float lbl_80495A94[49];
extern const float lbl_806D9560;
extern const float lbl_806D956C;
extern const float lbl_806D9570;
extern const float lbl_806D9574;
extern const float lbl_806D9578;
extern const float lbl_806D957C;
extern const float lbl_806D9580;
extern const float lbl_806D9584;
extern const float lbl_806D9588;
extern const float lbl_806D958C;
extern const float lbl_806D9590;
extern const float lbl_806D9594;
extern const float lbl_806D9598;
extern const float lbl_806D959C;
extern const float lbl_806D95A0;
extern const float lbl_806D95A4;
extern const float lbl_806D95A8;
extern const float lbl_806D95AC;
extern const float lbl_806D95B0;
extern const float lbl_806D95B4;
}
#endif

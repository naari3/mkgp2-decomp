#include "game/ObjViewParticles_private.h"

struct ParticleViewBase {
    ParticleViewBase() {}
    virtual ~ParticleViewBase();
};
struct ParticleView : ParticleViewBase {
    clNormal3D *model;
    ParticleDirection *directions;
    ObjParticle *particles;
    int positionRandom, spinRandom, phaseRandom, cooldownRandom, velocityRandom;
    ParticleView();
    virtual ~ParticleView();
};
extern "C" {
extern int g_courseVariantIdx;
extern void clNormal3D_SetFlags(clNormal3D *, unsigned int, int);
extern void *FUN_8003b120(unsigned long);
extern void Vec3_Normalize(const Vec3f *, Vec3f *);
}
ParticleView::ParticleView() {
    ParticleEmitter *emitter = lbl_8037D888;
    DebugPrintf((const char *)emitter + 0xE8);
    model = 0;
    directions = 0;
    particles = 0;
    positionRandom = 0;
    spinRandom = 0;
    phaseRandom = 0;
    cooldownRandom = 0;
    velocityRandom = 0;
    switch (g_courseVariantIdx) {
    case 0: model = new clNormal3D((const char *)emitter + 0x108, 1); break;
    case 1: model = new clNormal3D((const char *)emitter + 0x120, 1); break;
    case 2: model = new clNormal3D((const char *)emitter + 0x13C, 1); break;
    default: model = new clNormal3D((const char *)emitter + 0x108, 1); break;
    }
    clNormal3D_SetFlags(model, 0x40000000, 0);
    directions = (ParticleDirection *)FUN_8003b120(0x70);
    particles = (ObjParticle *)FUN_8003b120(0x13B0);
    for (int i = 0; i < 7; i++, emitter++) {
        Vec3_Subtract(&emitter->end, &emitter->start, &directions[i].direction);
        Vec3_Normalize(&directions[i].direction, &directions[i].direction);
        directions[i].cooldown = 0;
    }
    for (int j = 0; j < 70; j++) {
        particles[j].age = lbl_806D9560;
    }
}

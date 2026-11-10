#include "game/ObjViewParticles_private.h"

#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
#define kEmitters lbl_8037D888
#endif
#ifdef __MWERKS__
static const ParticleEmitter kEmitters[7] = {
#else /* ObjViewParticles_private.h declares it without const */
ParticleEmitter kEmitters[7] = {
#endif
    {{222.0f, 130.0f, -1600.0f}, {100.0f, 70.0f, -1700.0f}},
    {{222.0f, 130.0f, -1300.0f}, {100.0f, 70.0f, -1300.0f}},
    {{222.0f, 130.0f, -998.0f}, {100.0f, 70.0f, -900.0f}},
    {{450.0f, 290.0f, -1482.0f}, {220.0f, 250.0f, -1480.0f}},
    {{450.0f, 290.0f, -1104.0f}, {220.0f, 250.0f, -1100.0f}},
    {{1136.0f, 290.0f, -1432.0f}, {1300.0f, 250.0f, -1380.0f}},
    {{1018.0f, 290.0f, -1074.0f}, {1200.0f, 200.0f, -1000.0f}}
};
SHARED_STATIC const char lbl_8037D930[12] = "clWCBlossom";
SHARED_STATIC const char lbl_8037D93C[17] = "clMapEffectParts";
SHARED_STATIC const char lbl_8037D950[32] = " DeleteMapEffect : clWCBlossom\n";
static const char lbl_8037D970[32] = " CreateMapEffect : clWCBlossom\n";
static const char lbl_8037D990[21] = "ef_cherryblossom.dat";
static const char lbl_8037D9A8[27] = "ef_cherryblossom_night.dat";
static const char lbl_8037D9C4[26] = "ef_cherryblossom_dawn.dat";

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
    int i;
    DebugPrintf(lbl_8037D970);
    model = 0;
    directions = 0;
    particles = 0;
    positionRandom = 0;
    spinRandom = 0;
    phaseRandom = 0;
    cooldownRandom = 0;
    velocityRandom = 0;
    switch (g_courseVariantIdx) {
    case 0: model = new clNormal3D(lbl_8037D990, 1); break;
    case 1: model = new clNormal3D(lbl_8037D9A8, 1); break;
    case 2: model = new clNormal3D(lbl_8037D9C4, 1); break;
    default: model = new clNormal3D(lbl_8037D990, 1); break;
    }
    clNormal3D_SetFlags(model, 0x40000000, 0);
    directions = (ParticleDirection *)FUN_8003b120(0x70);
    particles = (ObjParticle *)FUN_8003b120(0x13B0);
    for (i = 0; i < 7; i++) {
        Vec3_Subtract(&kEmitters[i].end, &kEmitters[i].start, &directions[i].direction);
        Vec3_Normalize(&directions[i].direction, &directions[i].direction);
        directions[i].cooldown = 0;
    }
    for (i = 0; i < 70; i++) {
        particles[i].age = lbl_806D9560;
    }
}

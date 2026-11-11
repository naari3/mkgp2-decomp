/* clWCBlossom: deferred generation, definitions in reverse address order.
 * The compiler emits the vtable, base list, RTTI records and class names. */
#include "game/ObjViewParticles_private.h"
#include "game/types/clMapEffectParts.h"
struct clWCBlossom : clMapEffectParts {
    clNormal3D *model;
    ParticleDirection *directions;
    ObjParticle *particles;
    int positionRandom, spinRandom, phaseRandom, cooldownRandom, velocityRandom;
    clWCBlossom();
    virtual ~clWCBlossom();
    virtual void Update();
    virtual void Draw();
};
extern "C" {
void Object_DtorWithGXSync(void *, int);
void MemoryManager_Free(void *);
}
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

extern "C" {
extern int g_courseVariantIdx;
extern void clNormal3D_SetFlags(clNormal3D *, unsigned int, int);
extern void *FUN_8003b120(unsigned long);
extern void Vec3_Normalize(const Vec3f *, Vec3f *);
}
clWCBlossom::clWCBlossom() {
    int i;
    DebugPrintf(" CreateMapEffect : clWCBlossom\n");
    model = 0;
    directions = 0;
    particles = 0;
    positionRandom = 0;
    spinRandom = 0;
    phaseRandom = 0;
    cooldownRandom = 0;
    velocityRandom = 0;
    switch (g_courseVariantIdx) {
    case 0: model = new clNormal3D("ef_cherryblossom.dat", 1); break;
    case 1: model = new clNormal3D("ef_cherryblossom_night.dat", 1); break;
    case 2: model = new clNormal3D("ef_cherryblossom_dawn.dat", 1); break;
    default: model = new clNormal3D("ef_cherryblossom.dat", 1); break;
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

clWCBlossom::~clWCBlossom() {
    Object_DtorWithGXSync(model, 1);
    MemoryManager_Free(directions);
    MemoryManager_Free(particles);
    DebugPrintf(" DeleteMapEffect : clWCBlossom\n");
}


extern "C" {
void *GetCourseScene3D();
void CObj_LoadProjMatrix(void *, Vec3f *);
float PSVECSquareMag(const Vec3f *);
float Vec3_Dot(const Vec3f *, const Vec3f *);
void PSMTXMultVec(const Mtx, const Vec3f *, Vec3f *);
float LUT_Sin12Bit(float);
float fn_80186960(float);
float Saturate_Double(float, float, float);
}

static inline ObjParticle *FindFreeParticle(clWCBlossom *self) {
    for (ObjParticle *p = self->particles; p < self->particles + 70; p++) {
        if (lbl_806D9560 == p->age) return p;
    }
    return 0;
}
static inline float PositionRandom(clWCBlossom *self, float scale, float base) {
    if (self->positionRandom >= 64) self->positionRandom = 0;
    return scale * lbl_80495994[self->positionRandom++] + base;
}

void clWCBlossom::Update() {
    clWCBlossom *self = this;
    void *scene = GetCourseScene3D();
    if (scene == 0) return;
    Vec3f camera;
    Vec3f delta;
    Mtx rotation;
    CObj_LoadProjMatrix(scene, &camera);
    for (int i = 0; i < 7; i++) {
        if (self->directions[i].cooldown > 0) {
            self->directions[i].cooldown--;
            continue;
        }
        Vec3_Subtract(&camera, &lbl_8037D888[i].start, &delta);
        float distance = PSVECSquareMag(&delta);
        float facing = Vec3_Dot(&delta, &self->directions[i].direction);
        if (distance < lbl_806D956C && facing >= 0.0f) {
            ObjParticle *p = FindFreeParticle(self);
            if (p != 0) {
                p->age = lbl_806D9570;
                p->position.x = PositionRandom(self, lbl_806D9578, lbl_806D9574) + lbl_8037D888[i].start.x;
                p->position.y = PositionRandom(self, lbl_806D9580, lbl_806D957C) + lbl_8037D888[i].start.y;
                p->position.z = PositionRandom(self, lbl_806D9578, lbl_806D9574) + lbl_8037D888[i].start.z;
                p->rotation.x = lbl_806D9570;
                p->rotation.y = lbl_806D9570;
                p->rotation.z = lbl_806D9570;
                p->alpha = lbl_806D9584;
                if (self->velocityRandom >= 48) self->velocityRandom = 0;
                p->ageStep = lbl_806D9588 * lbl_80495A94[self->velocityRandom++] + lbl_806D9588;
                p->velocity.x = p->ageStep * self->directions[i].direction.x;
                p->velocity.y = p->ageStep * self->directions[i].direction.y;
                p->velocity.z = p->ageStep * self->directions[i].direction.z;
                if (self->velocityRandom >= 48) self->velocityRandom = 0;
                PSMTXRotRad(rotation, 'Y', lbl_806D9584 * lbl_80495A94[self->velocityRandom++] + lbl_806D958C);
                PSMTXMultVec(rotation, &p->velocity, &p->velocity);
                if (self->spinRandom >= 48) self->spinRandom = 0;
                p->spin.x = lbl_806D9594 * lbl_80495A94[self->spinRandom++] + lbl_806D9590;
                if (self->spinRandom >= 48) self->spinRandom = 0;
                p->spin.y = lbl_806D9594 * lbl_80495A94[self->spinRandom++] + lbl_806D9590;
                if (self->spinRandom >= 48) self->spinRandom = 0;
                p->spin.z = lbl_806D9594 * lbl_80495A94[self->spinRandom++] + lbl_806D9590;
                if (self->phaseRandom >= 48) self->phaseRandom = 0;
                p->sway = lbl_806D9584 * lbl_80495A94[self->phaseRandom++] + lbl_806D9570;
                if (self->phaseRandom >= 48) self->phaseRandom = 0;
                p->phase = lbl_806D9598 * lbl_80495A94[self->phaseRandom++] + lbl_806D9570;
                if (self->phaseRandom >= 48) self->phaseRandom = 0;
                p->phaseStep = lbl_806D95A0 * lbl_80495A94[self->phaseRandom++] + lbl_806D959C;
            }
            if (self->cooldownRandom >= 64) self->cooldownRandom = 0;
            self->directions[i].cooldown = (int)(lbl_806D959C * lbl_80495994[self->cooldownRandom++] + lbl_806D95A4);
        }
    }
    for (ObjParticle *p = self->particles; p < self->particles + 70; p++) {
        if (lbl_806D9560 != p->age) {
            PSVECAdd(&p->position, &p->velocity, &p->position);
            PSVECAdd(&p->rotation, &p->spin, &p->rotation);
            p->position.x = p->sway * LUT_Sin12Bit(p->phase) + p->position.x;
            p->position.z = p->sway * fn_80186960(p->phase) + p->position.z;
            p->phase = p->phase + p->phaseStep;
            p->age = p->age + p->ageStep;
            if (p->age < lbl_806D95A8) {
                p->alpha = Saturate_Double(lbl_806D95AC * p->age, lbl_806D9570, lbl_806D9584);
            } else {
                p->alpha = Saturate_Double(lbl_806D9584 - lbl_806D95B0 * (p->age - lbl_806D95B4), lbl_806D9570, lbl_806D9584);
            }
            if (p->alpha <= lbl_806D9570) p->age = lbl_806D9560;
        }
    }
}

typedef struct HSD_DObj HSD_DObj;

struct GXChannel {
    GXChannel(HSD_JObj *jobj, HSD_DObj *dobj, unsigned int flags, int n);
    ~GXChannel();
    unsigned char pad[0x14];
};

struct Effect {
    float active;
    Vec3f pos;
    float rx;
    float ry;
    float rz;
    float x1c;
    float alpha;
    unsigned char pad24[0x48 - 0x24];
};

extern "C" {
extern HSD_DObj *HSD_JObjGetDObj(HSD_JObj *jobj);
extern unsigned char fn_801379F0(Vec3f *pos, float radius);
extern void PSMTXScale(Mtx m, float x, float y, float z);
extern void Object_SetColorAlphaOnly(void *model, int idx, float alpha);
extern void GXChannel_PushTransform(GXChannel *ch, Mtx m);
extern const float lbl_806D9560;
extern const float lbl_806D9564;
extern const float lbl_806D9568;
}

void clWCBlossom::Draw() {
    clWCBlossom *o = this;
    GXChannel ch(Archive_GetRootJObj(o->model), HSD_JObjGetDObj(Archive_GetRootJObj(o->model)), 0x40000000, 1);
    Effect *e;
    Mtx tmp;
    Mtx m;

    for (e = (Effect *)o->particles; e < (Effect *)o->particles + 70; e++) {
        if (lbl_806D9560 != e->active && fn_801379F0(&e->pos, lbl_806D9564)) {
            PSMTXScale(m, lbl_806D9568, lbl_806D9568, lbl_806D9568);
            PSMTXRotRad(tmp, 'Z', e->rz);
            PSMTXConcat(m, tmp, m);
            PSMTXRotRad(tmp, 'X', e->rx);
            PSMTXConcat(m, tmp, m);
            PSMTXRotRad(tmp, 'Y', e->ry);
            PSMTXConcat(m, tmp, m);
            m[0][3] = e->pos.x;
            m[1][3] = e->pos.y;
            m[2][3] = e->pos.z;
            Object_SetColorAlphaOnly(o->model, 0, e->alpha);
            GXChannel_PushTransform(&ch, m);
        }
    }
}

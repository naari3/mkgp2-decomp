#include "game/objview/emitter_private.h"
extern "C" {
extern float lbl_80495994[], lbl_80495A94[];
extern const Vec3f lbl_803780EC[12];
extern const float lbl_806D9464, lbl_806D9468, lbl_806D946C;
extern const float lbl_806D9470, lbl_806D9474, lbl_806D9478, lbl_806D947C;
extern char lbl_806D9450[8], lbl_806D9458[8];
void HSD_JObjSetupMatrixSub(ViewJoint *);
}
static inline float variation(ViewEmitter *o) {
    if (o->variationIndex >= 48) o->variationIndex = 0;
    return lbl_80495A94[o->variationIndex++];
}
static inline void setup(ViewJoint *j) {
    if (!j) __assert(lbl_806D9450, 0x47c, lbl_806D9458);
    if (j) {
        if (!j) __assert(lbl_806D9450, 0x25d, lbl_806D9458);
        unsigned char dirty = 0;
        if (!(j->flags & 0x800000) && (j->flags & 0x40)) dirty = 1;
        if (dirty) HSD_JObjSetupMatrixSub(j);
    }
}
static inline ViewBillboardParticle *freeParticle(ViewEmitter *o) {
    for (int i = 0; i < 60; i++) {
        if (o->particles[i].age < 0.0f) return &o->particles[i];
    }
    return 0;
}
static inline void updateParticle(ViewBillboardParticle *q) {
    if (q->age < 0.0f) return;
    q->scale += q->speed;
    if (q->age < 10.0f) q->alpha = q->maxAlpha * (q->age / 10.0f);
    else q->alpha = q->maxAlpha - q->maxAlpha * ((q->age - 10.0f) / 30.0f);
    if ((q->age += 1.0f) > 40.0f) q->age = -1.0f;
}
static inline void initializeMatrix(ViewEmitter *o, void *scene, int index) {
    ViewJoint *joint;
    o->matrices[index].age = 0.0f;
    joint = o->matrices[index].joint;
    setup(joint);
    PSMTXScale(o->matrices[index].matrix, 1.0f + variation(o), 1.0f, 1.0f);
    PSMTXConcat(o->matrices[index].matrix, *CObj_GetProjMatrix_Cached(scene), o->matrices[index].matrix);
    o->matrices[index].matrix[0][3] = joint->matrix[0][3];
    o->matrices[index].matrix[1][3] = joint->matrix[1][3];
    o->matrices[index].matrix[2][3] = joint->matrix[2][3];
    o->delay = (int)(30.0f + 30.0f * variation(o));
}
static inline void updateMatrices(ViewEmitter *o) {
    int i;
    unsigned int matrixOffset;
    ViewBillboardParticle *q;
    ViewMatrixParticle *p;
    for (i = 0, matrixOffset = 0; i < o->count; matrixOffset += sizeof(ViewMatrixParticle), i++) {
        p = (ViewMatrixParticle *)((char *)o->matrices + matrixOffset);
        if (p->age < 0.0f) continue;
        if ((p->age += 1.0f) >= 89.0f) { p->age = -1.0f; continue; }
        if (p->age >= 20.0f) {
            unsigned int point = ((int)(p->age - 20.0f)) >> 1;
            if (point < 12) {
                q = freeParticle(o);
                if (q) {
                    q->age = 0.0f;
                    q->scale = 0.0f;
                    q->alpha = 0.0f;
                    q->speed = 0.025f + 0.05f * variation(o);
                    q->maxAlpha = 0.5f + 0.5f * variation(o);
                    PSMTXMultVec(p->matrix, &lbl_803780EC[point], &q->pos);
                }
            }
        }
    }
}
static inline void updateBillboards(ViewEmitter *o) {
    int k;
    ViewBillboardParticle *q;
    unsigned int particleOffset;
    for (k = 0, particleOffset = 0; k < 60; particleOffset += sizeof(ViewBillboardParticle), k++) {
        q = (ViewBillboardParticle *)((char *)o->particles + particleOffset);
        updateParticle(q);
    }
}
#pragma push
#pragma opt_dead_assignments off
extern "C" void fn_8018E6FC(ViewEmitter *o) {
    int index;
    void *scene;
    if (o->count == 0) return;
    if (o->delay > 0) o->delay--;
    else {
        if (o->randomIndex >= 64) o->randomIndex = 0;
        float random = lbl_80495994[o->randomIndex++];
        index = (int)(o->count * random);
        if (-1.0f == o->matrices[index].age) {
            scene = GetCourseScene3D();
            initializeMatrix(o, scene, index);
        }
    }
    updateMatrices(o);
    updateBillboards(o);
}
#pragma pop


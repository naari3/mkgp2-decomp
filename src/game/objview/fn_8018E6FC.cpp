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
    int index = o->variationIndex++;
    return lbl_80495A94[index];
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
        if (o->particles[i].age < lbl_806D9440) return &o->particles[i];
    }
    return 0;
}
extern "C" void fn_8018E6FC(ViewEmitter *o) {
    ViewJoint *joint;
    int index;
    void *scene;
    if (o->count == 0) return;
    if (o->delay > 0) o->delay--;
    else {
        if (o->randomIndex >= 64) o->randomIndex = 0;
        float random = lbl_80495994[o->randomIndex++];
        index = (int)(o->count * random);
        if (lbl_806D944C == o->matrices[index].age) {
            scene = GetCourseScene3D();
            o->matrices[index].age = lbl_806D9440;
            joint = o->matrices[index].joint;
            setup(joint);
            PSMTXScale(o->matrices[index].matrix, lbl_806D9460 + variation(o), lbl_806D9460, lbl_806D9460);
            PSMTXConcat(o->matrices[index].matrix, *CObj_GetProjMatrix_Cached(scene), o->matrices[index].matrix);
            o->matrices[index].matrix[0][3] = joint->matrix[0][3];
            o->matrices[index].matrix[1][3] = joint->matrix[1][3];
            o->matrices[index].matrix[2][3] = joint->matrix[2][3];
            o->delay = (int)(lbl_806D9464 + lbl_806D9464 * variation(o));
        }
    }
    int i;
    ViewMatrixParticle *p;
    for (i = 0; i < o->count; i++) {
        p = &o->matrices[i];
        if (p->age < lbl_806D9440) continue;
        p->age += lbl_806D9460;
        if (p->age >= lbl_806D9468) { p->age = lbl_806D944C; continue; }
        if (p->age >= lbl_806D946C) {
            unsigned int point = ((int)(p->age - lbl_806D946C)) >> 1;
            if (point < 12) {
                ViewBillboardParticle *q = freeParticle(o);
                if (q) {
                    q->age = lbl_806D9440;
                    q->scale = lbl_806D9440;
                    q->alpha = lbl_806D9440;
                    q->speed = lbl_806D9470 + lbl_806D9474 * variation(o);
                    q->maxAlpha = lbl_806D9478 + lbl_806D9478 * variation(o);
                    PSMTXMultVec(p->matrix, &lbl_803780EC[point], &q->pos);
                }
            }
        }
    }
    ViewBillboardParticle *q;
    for (i = 0; i < 60; i++) {
        q = &o->particles[i];
        if (!(q->age < lbl_806D9440)) {
        q->scale += q->speed;
        if (q->age < lbl_806D9448) q->alpha = q->maxAlpha * (q->age / lbl_806D9448);
        else q->alpha = q->maxAlpha - q->maxAlpha * ((q->age - lbl_806D9448) / lbl_806D9464);
        q->age += lbl_806D9460;
        if (q->age > lbl_806D947C) q->age = lbl_806D944C;
        }
    }
}

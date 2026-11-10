#include "game/types/Vec3.h"
#include "game/types/HSD_JObj.h"
typedef struct Entry {
    void *model;
    HSD_JObj *scrollJoint;
    HSD_JObj *sourceJoint;
    int delay;
} Entry;
typedef struct Particle {
    float scale, growth, alpha;
    Vec3 velocity;
    Vec3 pos;
    Vec3 xAxis, yAxis, zAxis;
} Particle;
typedef struct Owner {
    void *vt;
    Entry *items;
    int count;
    void *model;
    Particle *particles;
    int delayIndex, scaleIndex, velocityIndex;
} Owner;
extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *, Vec3 *);
extern void Object_GetJObjPositionVec(void *, Vec3 *);
extern void Vec3_Subtract(const Vec3 *, const Vec3 *, Vec3 *);
extern float PSVECSquareMag(const Vec3 *);
extern void fn_80182B50(HSD_JObj *, float, float);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);
extern void __assert(char *, int, char *);
extern unsigned char fn_8016C360(int);
extern unsigned char SoundMgr_PlaySE(int);
extern void fn_8016C288(int, Vec3 *);
extern const Vec3 lbl_8037DBD8;
extern float lbl_80495A94[], lbl_80495994[];
extern const float lbl_806D9654, lbl_806D9658, lbl_806D965C, lbl_806D9660, lbl_806D9664;
extern const float lbl_806D9678, lbl_806D967C, lbl_806D9680, lbl_806D9684, lbl_806D9688, lbl_806D968C;
extern char lbl_806D9668[7], lbl_806D9670[5];
static inline float NextScale(Owner *o) {
    int i;
    if (o->scaleIndex >= 48) o->scaleIndex = 0;
    i = o->scaleIndex++;
    return lbl_80495A94[i];
}
static inline float NextVelocity(Owner *o) {
    int i;
    if (o->velocityIndex >= 64) o->velocityIndex = 0;
    i = o->velocityIndex++;
    return lbl_80495994[i];
}
static inline float NextDelay(Owner *o) {
    int i;
    if (o->delayIndex >= 64) o->delayIndex = 0;
    i = o->delayIndex++;
    return lbl_80495994[i];
}
static inline Particle *FindFree(Owner *o) {
    int i;
    for (i = 0; i < 60; i++) {
        if (lbl_806D9654 == o->particles[i].alpha) return &o->particles[i];
    }
    return 0;
}
static inline unsigned char MatrixDirty(HSD_JObj *j) {
    unsigned char dirty;
    if (j == 0) __assert(lbl_806D9668, 0x25D, lbl_806D9670);
    dirty = 0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void Spawn(Owner *o, Particle *p, HSD_JObj *j) {
    if (j == 0) __assert(lbl_806D9668, 0x47C, lbl_806D9670);
    if (j != 0 && MatrixDirty(j)) HSD_JObjSetupMatrixSub(j);
    p->pos.x = j->mtx[0][3];
    p->pos.y = j->mtx[1][3];
    p->pos.z = j->mtx[2][3];
    p->xAxis.x = j->mtx[0][0];
    p->xAxis.y = j->mtx[1][0];
    p->xAxis.z = j->mtx[2][0];
    p->yAxis.x = j->mtx[0][1];
    p->yAxis.y = j->mtx[1][1];
    p->yAxis.z = j->mtx[2][1];
    p->zAxis.x = -j->mtx[0][2];
    p->zAxis.y = j->mtx[1][2];
    p->zAxis.z = -j->mtx[2][2];
    p->scale = lbl_806D9678 + NextScale(o);
    {
        float r = NextScale(o);
        float k = lbl_806D967C;
        p->growth = k * r + k;
    }
    p->alpha = lbl_806D9678;
    p->velocity.x = lbl_806D9680 * NextVelocity(o) - lbl_806D9684;
    p->velocity.y = lbl_806D9684 * NextVelocity(o) - lbl_806D9678;
    p->velocity.z = lbl_806D9688;
}
static inline void UpdateParticle(Particle *p) {
            if (lbl_806D9654 != p->alpha) {
                p->pos.x += p->xAxis.x * p->velocity.x + p->yAxis.x * p->velocity.y + p->zAxis.x * p->velocity.z;
                p->pos.y += p->xAxis.y * p->velocity.x + p->yAxis.y * p->velocity.y + p->zAxis.y * p->velocity.z;
                p->pos.z += p->xAxis.z * p->velocity.x + p->yAxis.z * p->velocity.y + p->zAxis.z * p->velocity.z;
                p->scale += p->growth;
                p->velocity.z -= lbl_806D968C;
                if (p->velocity.z < lbl_806D9658) {
                    p->alpha = lbl_806D968C * p->velocity.z;
                    if (p->velocity.z < lbl_806D965C) p->alpha = lbl_806D9654;
                }
            }
}
#pragma push
#pragma opt_dead_assignments off
void fn_801980C8(Owner *o) {
    Particle *p;
    int i;
    Entry *entry;
    Vec3 eye, pos, diff;
    Vec3 nearest;
    float nearestDist, distance;
    if (o->count != 0) {
        CObj_LoadProjMatrix(GetCourseScene3D(), &eye);
        nearestDist = lbl_806D9654;
        nearest = lbl_8037DBD8;
        for (i = 0; i < o->count; i++) {
            entry = &o->items[i];
            Object_GetJObjPositionVec(entry->model, &pos);
            Vec3_Subtract(&eye, &pos, &diff);
            distance = PSVECSquareMag(&diff);
            if (nearestDist < lbl_806D965C || distance < nearestDist) {
                nearestDist = distance;
                nearest.x = pos.x; nearest.y = pos.y; nearest.z = pos.z;
            }
            if (entry->scrollJoint != 0) fn_80182B50(entry->scrollJoint, lbl_806D965C, lbl_806D9660);
            if (entry->delay != 0) {
                entry->delay--;
            } else {
                if (entry->sourceJoint != 0 && distance < lbl_806D9664) {
                    p = FindFree(o);
                    if (p != 0) Spawn(o, p, entry->sourceJoint);
                }
                entry->delay = (int)(lbl_806D9658 * NextDelay(o)) + 2;
            }
        }
        if (!fn_8016C360(0x2D)) SoundMgr_PlaySE(0x2D);
        fn_8016C288(0x2D, &nearest);
        for (i = 0; i < 60; i++) {
            UpdateParticle(&o->particles[i]);
        }
    }
}
#pragma pop

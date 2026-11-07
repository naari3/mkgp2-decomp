#include "game/objview/particle_update_private.h"

extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *, ParticleUpdateVec *);
extern void CObj_ApplyScissor(void *, ParticleUpdateVec *);
extern unsigned char fn_80123480(void *, ParticleUpdateVec *);
extern void Vec3_Subtract(const ParticleUpdateVec *, const ParticleUpdateVec *, ParticleUpdateVec *);
extern void Vec3_Normalize(const ParticleUpdateVec *, ParticleUpdateVec *);
extern float Vec3_Dot(const ParticleUpdateVec *, const ParticleUpdateVec *);
extern float LUT_Sin12Bit(float);
extern float lbl_80495994[];
extern float lbl_80495A94[];

static inline ViewParticle *FindFree(ViewParticleOwner *o) {
    int i;
    for (i = 0; i < 50; i++) {
        if (o->particles[i].active == 0) return &o->particles[i];
    }
    return 0;
}
static inline float RandomX(ViewParticleOwner *o, float lo, float hi) {
    if (o->randomX >= 64) o->randomX = 0;
    return (hi - lo) * lbl_80495994[o->randomX++] + lo;
}
static inline float RandomY(ViewParticleOwner *o, float lo, float hi) {
    if (o->randomY >= 48) o->randomY = 0;
    return (hi - lo) * lbl_80495A94[o->randomY++] + lo;
}
static inline float RandomDelay(ViewParticleOwner *o, float lo, float hi) {
    if (o->randomDelay >= 64) o->randomDelay = 0;
    return (hi - lo) * lbl_80495994[o->randomDelay++] + lo;
}
static inline float RandomParam(ViewParticleOwner *o, float lo, float hi) {
    if (o->randomParam >= 48) o->randomParam = 0;
    return (hi - lo) * lbl_80495A94[o->randomParam++] + lo;
}

static inline void UpdateParticles(ViewParticleOwner *o, float motion) {
    {
        int j;
        ViewParticle *q;
        int offset;
        for (j = 0, offset = 0; j < 50; offset += sizeof(ViewParticle), j++) {
            q = (ViewParticle *)((char *)o->particles + offset);
            if (q->active) {
                float speed;
                q->angle += q->angularSpeed;
                if (motion > 0.0f) q->depth += motion;
                speed = q->speed;
                q->x = q->amplitude * LUT_Sin12Bit(q->angle) + q->x;
                if (q->x < 0.0f) q->x += 1.0f;
                if (q->x > 1.0f) q->x -= 1.0f;
                q->y += speed;
                if (q->depth < -65.0f) {
                    if (o->enabled) { q->depth = -3.0f; q->alpha = 0.0f; }
                    else q->active = 0;
                } else if (q->depth > -3.0f) {
                    if (o->enabled) { q->depth = -65.0f; q->alpha = 0.0f; }
                    else q->active = 0;
                } else if (q->depth < -60.0f || q->depth > -5.0f) {
                    q->alpha = 0.0f;
                } else if (q->depth < -55.0f) {
                    q->alpha = 1.0f - -0.2f * (q->depth - -55.0f);
                } else if (q->depth > -10.0f) {
                    q->alpha = 1.0f - -0.2f * (-10.0f - q->depth);
                } else {
                    q->alpha = 1.0f;
                }
                if (q->y > 1.0f) q->active = 0;
            }
        }
    }
}

void fn_801972E0(ViewParticleOwner *o) {
    int i;
    ViewParticle *p;
    unsigned char wasEnabled;
    void *scene;
    float motion = 0.0f;
    wasEnabled = o->enabled;
    scene = GetCourseScene3D();
    if (scene == 0) return;
    if (o->reset) {
        CObj_LoadProjMatrix(scene, &o->position);
        o->reset = 0;
    } else {
        ParticleUpdateVec oldPosition;
        ParticleUpdateVec eye;
        ParticleUpdateVec delta;
        ParticleUpdateVec direction;
        o->enabled = fn_80123480(o->table, &o->position);
        oldPosition.x = o->position.x;
        oldPosition.y = o->position.y;
        oldPosition.z = o->position.z;
        CObj_LoadProjMatrix(scene, &o->position);
        CObj_ApplyScissor(scene, &eye);
        Vec3_Subtract(&o->position, &oldPosition, &delta);
        Vec3_Subtract(&eye, &o->position, &direction);
        if (delta.x != 0.0f || delta.y != 0.0f || delta.z != 0.0f) {
            Vec3_Normalize(&direction, &direction);
            motion = Vec3_Dot(&delta, &direction);
            if (motion > 0.0f) {
                if (o->enabled) motion *= 0.05f;
                else motion *= 0.3f;
            }
        }
    }
    if (o->enabled) {
        if (!wasEnabled) {
            o->randomX = 0;
            o->randomY = 0;
            o->randomParam = 0;
            o->randomDelay = 0;
            for (i = 0; i < 25; i++) {
                p = FindFree(o);
                if (p == 0) break;
                p->active = 1;
                p->x = RandomX(o, 0.0f, 1.0f);
                p->y = RandomY(o, 0.0f, 1.0f);
                p->depth = RandomParam(o, -65.0f, -60.0f);
                p->alpha = 0.0f;
                p->speed = RandomParam(o, 0.003f, 0.008f);
                p->amplitude = RandomParam(o, 0.001f, 0.003f);
                p->angle = RandomParam(o, 0.0f, 360.0f);
                p->angularSpeed = RandomParam(o, 4.0f, 8.0f);
            }
            o->delay = 0;
        } else if (o->delay != 0) {
            o->delay--;
        } else {
            p = FindFree(o);
            if (p != 0) {
                p->active = 1;
                p->x = RandomX(o, 0.0f, 1.0f);
                p->y = 0.0f;
                p->depth = RandomParam(o, -60.0f, -10.0f);
                p->alpha = 0.0f;
                p->speed = RandomParam(o, 0.003f, 0.008f);
                p->amplitude = RandomParam(o, 0.001f, 0.003f);
                p->angle = RandomParam(o, 0.0f, 360.0f);
                p->angularSpeed = RandomParam(o, 4.0f, 8.0f);
                o->delay = (int)RandomDelay(o, 3.0f, 7.0f);
            }
        }
    }
    UpdateParticles(o, motion);
}

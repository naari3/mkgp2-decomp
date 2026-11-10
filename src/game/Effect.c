/* Smoke-cloud effect: the parent follows the emitter, and each of its eight
 * sub-puffs drifts upward, is pulled back within a growing leash radius of
 * the emitter, grows, and fades out once its hold timer has run down. */

typedef struct SmokeVec {
    float x, y, z;
} SmokeVec;

typedef struct SmokePuff SmokePuff;

typedef struct SmokePuffSet {
    unsigned char pad00[0x10];
    SmokePuff *puffs[8];    /* 0x10 */
} SmokePuffSet;

struct SmokePuff {
    unsigned char pad000[0x14];
    unsigned char vfx[0x14];    /* 0x014: VfxSlot */
    signed char visible;        /* 0x028 */
    unsigned char pad029[0x3];
    float alpha;                /* 0x02C */
    unsigned char pad030[0x5C];
    SmokeVec pos;               /* 0x08C */
    unsigned char pad098[0xC];
    SmokeVec vel;               /* 0x0A4 */
    float scale;                /* 0x0B0 */
    unsigned char pad0B4[0x15];
    signed char finished;       /* 0x0C9 */
    unsigned char pad0CA[0x2];
    SmokePuffSet set;           /* 0x0CC */
    unsigned char pad0FC[0x24];
    SmokeVec offset;            /* 0x120 */
    unsigned char pad12C[0x24];
    float leash;                /* 0x150 */
    float life;                 /* 0x154 */
    unsigned char pad158[0x28];
    unsigned int timers[4];     /* 0x180 */
    signed char active;         /* 0x190 */
};

extern void Vec3_Add_DestFirst(SmokeVec *dst, const SmokeVec *a, const SmokeVec *b);
extern void Vec3_Copy();
extern float Vec3_Magnitude_Wrapper(const SmokeVec *v);
extern void Vec3_Scale(void *, void *, float);
extern void Vec3_Subtract_DestFirst(SmokeVec *dst, const SmokeVec *a, const SmokeVec *b);
#ifdef __MWERKS__
extern void VfxSlot_SetPositionFromVec(void *slot, SmokeVec pos);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlot_SetPositionFromVec(void *, SmokeVec *);
static inline void VfxSlot_SetPositionFromVec_ByValue(void *slot, SmokeVec pos) { VfxSlot_SetPositionFromVec(slot, &pos); }
#define VfxSlot_SetPositionFromVec VfxSlot_SetPositionFromVec_ByValue
#endif
extern void VfxSlot_SetScaleUniform(void *slot, float scale);

#pragma exceptions on
void Effect_SmokeCloud_DriveSubslots(SmokePuff *e, SmokeVec pos, SmokeVec dir, float alpha)
{
    SmokeVec anchor;
    SmokeVec d;
    SmokePuff *p;
    SmokePuffSet *set;
    int i;

    if (e == 0) {
        return;
    }
    Vec3_Copy(&e->pos, &pos);
    Vec3_Copy(&e->vel, &dir);
    set = &e->set;
    for (i = 0; i < 8; i++) {
        p = set->puffs[i];
        if (p == 0 || !p->active) {
            continue;
        }
        p->visible = 1;
        p->vel.x *= 0.9f;
        p->vel.z *= 0.9f;
        p->vel.y += 0.01f;
        Vec3_Add_DestFirst(&p->pos, &p->pos, &p->vel);
        p->leash += 0.5f;
        Vec3_Add_DestFirst(&anchor, &pos, &p->offset);
        Vec3_Subtract_DestFirst(&d, &p->pos, &anchor);
        {
            float mag = Vec3_Magnitude_Wrapper(&d);
            if (p->leash < mag) {
                Vec3_Scale(&d, &d, 1.0f / mag * p->leash);
                Vec3_Add_DestFirst(&p->pos, &anchor, &d);
            }
        }
        p->scale += 0.05f;
        if (p->timers[0] == 0) {
            p->life -= 0.1f;
            if (p->life < 0.0f) {
                p->visible = 0;
                p->active = 0;
                p->finished = 1;
            }
        }
        p->alpha = p->life * alpha;
        VfxSlot_SetPositionFromVec(p->vfx, p->pos);
        VfxSlot_SetScaleUniform(p->vfx, p->scale);
        if (p->timers[0]) {
            p->timers[0]--;
        }
        if (p->timers[1]) {
            p->timers[1]--;
        }
        if (p->timers[2]) {
            p->timers[2]--;
        }
        if (p->timers[3]) {
            p->timers[3]--;
        }
    }
}
#pragma exceptions reset

#include "src/game/Effect_SmokeCloud_Update.inc"

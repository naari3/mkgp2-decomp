/* ItemObject_Tick_Kind29_LightAttachment (0x800E03E4): light (lightning)
 * item effect attached over the kart. It hits all drivers, then on the
 * trigger flag switches to its second animation for 180 frames with a
 * child effect, and fades out. Its offset eases toward a rest point and
 * its scale pulses along a 4-segment keyframe curve. */
#include "game/types/Vec.h"

#include "game/types/ScaleCurve.h"

extern Vec ItemObject_Tick_Kind29_LightAttachment_rodata_8032E534;
extern ScaleCurve ItemObject_Tick_Kind29_LightAttachment_data_80420ED8;
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void Item_PropagateHitToAllDrivers(unsigned char *self, void *driver);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_TwoChild_Res35_36_Init(unsigned char *self);
extern void Vec3_Lerp(void *dst, Vec *a, Vec *b, float t);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec *in);
extern void SpriteSlot_SetPositionFromVec(void *slot, Vec *pos);
extern void SpriteSlot_SetRotationQuatFromVec(void *slot, Vec *rot);
extern void SpriteSlot_SetScaleXYZ(void *slot, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))

/* Keep both terms when this general interpolation is inlined at a zero target. */
static inline float LerpScalar(float a, float b, float t)
{
    return a * t + b * (1.0f - t);
}

static inline void Vec_SetUniform(Vec *out, float value)
{
    out->x = value;
    out->y = value;
    out->z = value;
}

void ItemObject_Tick_Kind29_LightAttachment(unsigned char *self, unsigned char *sub)
{
    float root[4][4];
    Vec scale;
    Vec a;
    Vec b;
    Vec local;
    Vec pos;
    Vec rot;
    float t;
    Vec *sp;
    ScaleCurve *c;
    float f;
    int i;
    int off;

    switch (S8(0xC9)) {
    case 0:
        SF(0x14) = 0.0f;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 2.0f);
        sub[0] = 0;
        Item_PropagateHitToAllDrivers(self, SP(0x98));
        S8(0xC9)++;
    case 1:
        if ((int)self[0x1E] == 1) {
            SU32(0x4) = 180;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            sub[0] = 1;
            SP(0x4C) = DrawEffect_SpawnDirect(Effect_TwoChild_Res35_36_Init);
            S8(0xC9)++;
        }
        break;
    case 2:
        if (SU32(0x4) == 0) {
            S8(0xC9)++;
        }
        break;
    case 3:
        F(0x2C) -= 0.1f;
        if (F(0x2C) < 0.0f) {
            if (SP(0x4C) != 0) {
                *(signed char *)(SP(0x4C) + 0xC9) = 1;
            }
            SP(0x4C) = 0;
            self[0x28] = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
        break;
    }

    SF(0x14) = 0.05f;
    if (1.0f < SF(0x14)) {
        SF(0x14) = 1.0f;
    }
    b = *(Vec *)(sub + 0x34);
    a = ItemObject_Tick_Kind29_LightAttachment_rodata_8032E534;
    Vec3_Lerp(sub + 0x34, &a, &b, SF(0x14));
    t = SF(0x14);
    F(0xAC) = LerpScalar(0.0f, F(0xAC), t);
    if (SP(0x98) != 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(SP(0x98)));
        local = *(Vec *)(sub + 0x34);
        Mtx44_TransformVec3((Vec *)(self + 0xA0), root, &local);
    }
    if (sub[0] == 0) {
        pos = *(Vec *)(self + 0xA0);
        SpriteSlot_SetPositionFromVec(self + 0x14, &pos);
        rot = *(Vec *)(self + 0xAC);
        SpriteSlot_SetRotationQuatFromVec(self + 0x14, &rot);
        t = 80.0f + F(0x20);
        sp = &scale;
        Vec_SetUniform(sp, F(0xC4));
        c = &ItemObject_Tick_Kind29_LightAttachment_data_80420ED8;
        off = 0;
        for (i = 0; i < 4; i++, off += 4) {
            if (c->t[i] <= t && t <= c->t[i + 1]) {
                /* View all three channels at the same key offset. */
                ScaleCurve *segment = (ScaleCurve *)((unsigned long)c + off);
                f = (1.0f / (c->t[i + 1] - c->t[i])) * (t - c->t[i]);
                sp->x = sp->x * (f * (segment->x[1] - segment->x[0]) + segment->x[0]);
                sp->y = sp->y * (f * (segment->y[1] - segment->y[0]) + segment->y[0]);
                sp->z = sp->z * (f * (segment->z[1] - segment->z[0]) + segment->z[0]);
            }
        }
        SpriteSlot_SetScaleXYZ(self + 0x14, sp->x, sp->y, sp->z);
    }
    if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}

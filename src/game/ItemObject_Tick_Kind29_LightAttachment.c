/* ItemObject_Tick_Kind29_LightAttachment (0x800E03E4): light (lightning)
 * item effect attached over the kart. It hits all drivers, then on the
 * trigger flag switches to its second animation for 180 frames with a
 * child effect, and fades out. Its offset eases toward a rest point and
 * its scale pulses along a 4-segment keyframe curve. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct ScaleCurve {
    float x[5];
    float y[5];
    float z[5];
    float t[5];
} ScaleCurve;

extern Vec lbl_8032E534;
extern ScaleCurve lbl_80420ED8;
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
    a = lbl_8032E534;
    Vec3_Lerp(sub + 0x34, &a, &b, SF(0x14));
    t = SF(0x14);
    F(0xAC) = 0.0f * t + F(0xAC) * (1.0f - t);
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
        sp->x = F(0xC4);
        sp->y = F(0xC4);
        sp->z = F(0xC4);
        c = &lbl_80420ED8;
        for (i = 0; i < 4; i++) {
            if (c->t[i] <= t && t <= c->t[i + 1]) {
                float *x = &lbl_80420ED8.x[i];
                float *y = &lbl_80420ED8.y[i];
                float *z = &lbl_80420ED8.z[i];
                f = (1.0f / (c->t[i + 1] - c->t[i])) * (t - c->t[i]);
                sp->x = sp->x * (f * (x[1] - x[0]) + x[0]);
                sp->y = sp->y * (f * (y[1] - y[0]) + y[0]);
                sp->z = sp->z * (f * (z[1] - z[0]) + z[0]);
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

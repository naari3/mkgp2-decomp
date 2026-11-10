/* fn_8010C110: held-item tick for the 0x71..0x73 item kinds. Spawns and
 * fades the attached effect, follows the kart toward the camera side, and
 * scales its joints along keyframe curves. */
#include "game/types/Vec.h"

typedef unsigned long long ItemEffectMask;
typedef struct ItemEffectBusView {
    unsigned char pad00[0x10];
    ItemEffectMask mask;
} ItemEffectBusView;

/* 4-key scalar curve and 5-key vector curve copied from the .rodata pool. */
typedef struct ScalarCurve4 {
    float t[4];
    float v[4];
} ScalarCurve4;

typedef struct VecCurve5 {
    float t[5];
    float x[5];
    float y[5];
    float z[5];
} VecCurve5;

extern float BuildOrientationFromYaw(float yaw);
extern void DrawEffect_Free(void *effect);
extern unsigned char *DrawEffect_SpawnDirect(void (*init)(unsigned char *));
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void ItemEffectBus_OrMask(void *bus, ItemEffectMask mask);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern float KartFxParam_GetConst1p5(void *driver);
extern void Mtx44_GetTranslation_RowMajor(Vec *dst, void *mtx);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
#ifdef __MWERKS__
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SoundMgr_PlaySE_WithChannel(int, Vec *, int);
static inline void SoundMgr_PlaySE_WithChannel_ByValue(int se, Vec pos, int ch) { SoundMgr_PlaySE_WithChannel(se, &pos, ch); }
#define SoundMgr_PlaySE_WithChannel SoundMgr_PlaySE_WithChannel_ByValue
#endif
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetJointScaleByName(void *slot, const char *name, float x, float y, float z);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Vec2_RotateY(Vec *out, Vec *in, float yaw);
extern void Vec3_Add_DestFirst(Vec *dst, Vec *a, Vec *b);
extern float Vec3_HorizontalYawTo(Vec *from, Vec *to);
#ifdef __MWERKS__
extern void Vec3_Lerp(void *dst, Vec a, Vec b, float t);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Vec3_Lerp(void *, Vec *, Vec *, float);
static inline void Vec3_Lerp_ByValue(void *dst, Vec a, Vec b, float t) { Vec3_Lerp(dst, &a, &b, t); }
#define Vec3_Lerp Vec3_Lerp_ByValue
#endif
extern void fn_8010BF20(unsigned char *self, unsigned char *sub);
extern void Effect_Res5F_Init(unsigned char *effect);
extern void Effect_Res7Eor62_Variant_Init(unsigned char *effect);

extern const char lbl_80331698[]; /* item .rodata pool */
extern unsigned char lbl_805DF3D0[];

#define F(p, o) (*(float *)((p) + (o)))
#define I(p, o) (*(int *)((p) + (o)))
#define U(p, o) (*(unsigned int *)((p) + (o)))
#define S8(p, o) (*(signed char *)((p) + (o)))
#define P(p, o) (*(unsigned char **)((p) + (o)))

static inline unsigned char ItemBus_Has(ItemEffectBusView *bus, ItemEffectMask bits)
{
    if ((bus->mask & bits) == 0) {
        return 0;
    }
    return 1;
}

static inline void ScalarCurve4_Eval(ScalarCurve4 *c, float x, float *out)
{
    int j;

    if (x <= c->t[0]) {
        *out = c->v[0];
        return;
    }
    if (c->t[3] <= x) {
        *out = c->v[3];
        return;
    }
    for (j = 0; j < 3; j++) {
        if (c->t[j] <= x && x <= c->t[j + 1]) {
            float k = (x - c->t[j]) * (1.0f / (c->t[j + 1] - c->t[j]));
            *out = k * (c->v[j + 1] - c->v[j]) + c->v[j];
        }
    }
}

#pragma exceptions on
void fn_8010C110(unsigned char *self, unsigned char *sub)
{
    const char *pool = lbl_80331698;
    Vec kartPos;
    Vec offset;
    Vec target;
    ScalarCurve4 curveA;
    VecCurve5 curveB;
    Vec scaleB;
    Vec *camera;
    float scaleA;
    float scaleC;
    float yaw;
    float x;
    int i;
    ItemEffectBusView *bus;

    switch (S8(self, 0xC9)) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
        self[0x3C] = 0;
        F(sub, 0x14) = 0.0f;
        I(sub, 0x4) = 1800;
        I(sub, 0x8) = 0;
        I(sub, 0xC) = 10;
        sub[0x0] = 0;
        I(sub, 0x30) = -1;
        S8(self, 0xC9)++;
    case 1:
        F(sub, 0x14) += 0.05f;
        if (1.0f < F(sub, 0x14)) {
            F(sub, 0x14) = 1.0f;
            switch (I(self, 0x8)) {
            case 0x71:
                P(sub, 0x4C) = DrawEffect_SpawnDirect(Effect_Res5F_Init);
                sub[0x0] = 1;
                break;
            case 0x72:
                P(sub, 0x4C) = DrawEffect_SpawnDirect(Effect_Res7Eor62_Variant_Init);
                if (P(sub, 0x4C) != 0) {
                    P(sub, 0x4C)[0x190] = 1;
                    I(P(sub, 0x4C), 0x10) = 1;
                }
                break;
            case 0x73:
                P(sub, 0x4C) = DrawEffect_SpawnDirect(Effect_Res7Eor62_Variant_Init);
                if (P(sub, 0x4C) != 0) {
                    P(sub, 0x4C)[0x190] = 1;
                }
                sub[0x0] = 1;
                break;
            }
            S8(self, 0xC9)++;
        }
        break;
    case 2:
        if (I(self, 0x8) == 0x71 && U(sub, 0x8) == 0) {
            if (P(P(sub, 0x9C), 0x304) != 0) {
                ItemEffectBus_OrMask(P(P(sub, 0x9C), 0x304), 0x4000000000000000ULL);
            }
            if (P(sub, 0x4C) != 0) {
                P(sub, 0x4C)[0x191] = 1;
            }
            SoundMgr_PlaySE_Positional(0x93, *(Vec *)(self + 0xA0), 0);
            I(sub, 0x8) = 60;
        }
        if (U(sub, 0x4) == 0) {
            if ((I(self, 0x8) == 0x73 || I(self, 0x8) == 0x72) && P(sub, 0x4C) != 0) {
                P(sub, 0x4C)[0x190] = 0;
            }
            if (I(self, 0x8) == 0x71) {
                if (I(sub, 0x30) >= 0) {
                    SoundMgr_StopSE_OrSpecial(0x92, I(sub, 0x30));
                    I(sub, 0x30) = -1;
                }
                sub[0x0] = 0;
            }
            if (I(self, 0x8) == 0x73) {
                if (I(sub, 0x30) >= 0) {
                    SoundMgr_StopSE_OrSpecial(0x9B, I(sub, 0x30));
                    I(sub, 0x30) = -1;
                }
                sub[0x0] = 0;
            }
            S8(self, 0xC9)++;
        }
        break;
    case 3:
        F(self, 0x2C) -= 0.05f;
        if (F(self, 0x2C) < 0.0f) {
            DrawEffect_Free(P(sub, 0x4C));
            P(sub, 0x4C) = 0;
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        break;
    }

    if (FinalLapCoinJump_CheckActiveForObject(P(sub, 0x9C))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }

    if (1.0f == F(sub, 0x14) && (bus = (ItemEffectBusView *)P(P(sub, 0x9C), 0x304)) != 0) {
        if (ItemBus_Has(bus, 0x10000ULL)) {
            fn_8010BF20(self, sub);
            DrawEffect_Free(P(sub, 0x4C));
            P(sub, 0x4C) = 0;
            if (I(self, 0x8) == 0x71) {
                if (sub[0x0] != 0) {
                    SoundMgr_StopSE_OrSpecial(0x92, 0);
                }
                sub[0x0] = 0;
            }
            if (I(self, 0x8) == 0x73) {
                if (sub[0x0] != 0) {
                    SoundMgr_StopSE_OrSpecial(0x9B, 0);
                }
                sub[0x0] = 0;
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            return;
        }
        switch (I(self, 0x8)) {
        case 0x71:
            if (!ItemBus_Has(bus, 0x200000ULL)) {
                U(sub, 0x4) = 0;
            }
            break;
        case 0x72:
            if (!ItemBus_Has(bus, 0x400000ULL)) {
                U(sub, 0x4) = 0;
            }
            break;
        case 0x73:
            if (!ItemBus_Has(bus, 0x100000ULL)) {
                U(sub, 0x4) = 0;
            }
            break;
        }
    }

    Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(P(sub, 0x9C)));
    offset = *(const Vec *)(pool + 0x3FC);
    camera = (Vec *)(lbl_805DF3D0 + 0x80);
    Vec2_RotateY(&offset, &offset, Vec3_HorizontalYawTo(&kartPos, camera));
    Vec3_Add_DestFirst(&target, &kartPos, &offset);
    Vec3_Lerp(self + 0xA0, target, *(Vec *)(self + 0xA0), F(sub, 0x14));
    yaw = Vec3_HorizontalYawTo(camera, &target);
    F(self, 0xAC) = BuildOrientationFromYaw(F(self, 0xAC) * (1.0f - F(sub, 0x14)) + -0.26179934f * F(sub, 0x14));
    F(self, 0xB0) = BuildOrientationFromYaw(yaw * F(sub, 0x14) + F(self, 0xB0) * (1.0f - F(sub, 0x14)));
    Item_DecayVelocityScalar(self, 1.2f * KartFxParam_GetConst1p5(P(sub, 0x9C)));
    if (S8(self, 0x1E) == 1) {
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
        SpriteSlot_SetScale(self + 0x14, 1.0f);
    }

    curveA = *(const ScalarCurve4 *)(pool + 0x408);
    curveB = *(const VecCurve5 *)(pool + 0x428);
    scaleB = *(const Vec *)(pool + 0x478);
    scaleA = 1.0f;
    if (S8(self, 0x1D) == 3) {
        x = F(self, 0x20);
        ScalarCurve4_Eval(&curveA, x, &scaleA);
        if (x <= curveB.t[0]) {
            scaleB.x = curveB.x[0];
            scaleB.y = curveB.y[0];
            scaleB.z = curveB.z[0];
        } else if (curveB.t[4] <= x) {
            scaleB.x = curveB.x[4];
            scaleB.y = curveB.y[4];
            scaleB.z = curveB.z[4];
        } else {
            for (i = 0; i < 4; i++) {
                if (curveB.t[i] <= x && x <= curveB.t[i + 1]) {
                    float k = (x - curveB.t[i]) * (1.0f / (curveB.t[i + 1] - curveB.t[i]));
                    scaleB.x = k * (curveB.x[i + 1] - curveB.x[i]) + curveB.x[i];
                    scaleB.y = k * (curveB.y[i + 1] - curveB.y[i]) + curveB.y[i];
                    scaleB.z = k * (curveB.z[i + 1] - curveB.z[i]) + curveB.z[i];
                }
            }
        }
        scaleC = 0.39999998f * (x / 30.0f) + 1.0f;
    } else {
        scaleB.x = curveB.x[4];
        scaleB.y = curveB.y[4];
        scaleB.z = curveB.z[4];
        scaleA = curveA.v[3];
        scaleC = 1.4f;
    }
    scaleB.x *= 0.85f;

    switch (I(self, 0x8)) {
    case 0x71:
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x4D8, scaleA, scaleA, scaleA);
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x4EC, scaleB.x, scaleB.y, scaleB.z);
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x500, scaleC, scaleC, 1.0f);
        break;
    case 0x72:
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x4D8, scaleA, scaleA, scaleA);
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x514, scaleB.x, scaleB.y, scaleB.z);
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x500, scaleC, scaleC, 1.0f);
        break;
    case 0x73:
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x4D8, scaleA, scaleA, scaleA);
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x528, scaleB.x, scaleB.y, scaleB.z);
        SpriteSlot_SetJointScaleByName(self + 0x14, pool + 0x500, scaleC, scaleC, 1.0f);
        break;
    }

    if (I(self, 0x8) == 0x71) {
        if (I(sub, 0x30) < 0) {
            if (sub[0x0] != 0) {
                I(sub, 0x30) = SoundMgr_CountActiveSEInstances(0x92);
                if (I(sub, 0x30) >= 0) {
                    SoundMgr_PlaySE_Positional(0x92, *(Vec *)(self + 0xA0), I(sub, 0x30));
                }
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0x92, *(Vec *)(self + 0xA0), I(sub, 0x30));
        }
    }
    if (I(self, 0x8) == 0x73) {
        if (I(sub, 0x30) < 0) {
            if (sub[0x0] != 0) {
                I(sub, 0x30) = SoundMgr_CountActiveSEInstances(0x9B);
                if (I(sub, 0x30) >= 0) {
                    SoundMgr_PlaySE_Positional(0x9B, *(Vec *)(self + 0xA0), I(sub, 0x30));
                }
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0x9B, *(Vec *)(self + 0xA0), I(sub, 0x30));
        }
    }
}
#pragma exceptions reset

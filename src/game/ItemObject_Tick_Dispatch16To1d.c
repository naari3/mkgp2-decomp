/* ItemObject_Tick_Dispatch16To1d (0x800E246C): handheld item kinds
 * 0x16..0x1D held by the character until the hold flag 0x18C is set. Kind
 * 0x19 pulses its scale along per-axis keyframe curves, kind 0x1B keeps a
 * second sprite nudged toward the camera, kind 0x1C flickers, and the
 * others drive a child effect from a named joint. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct PulseKey {
    float t[9];
    float v[9];
} PulseKey;

typedef struct {
    PulseKey axis[3];
} PulseTable;

extern const char lbl_8032E060[];
extern unsigned char lbl_805DF3D0[];
extern void fn_800D748C(unsigned char *self);
extern unsigned char *ItemObject_AllocFromPool(void (*fn)(unsigned char *));
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetTranslateDxDy(void *slot, float dx, float dy);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_SparkSprayCompound_Init(unsigned char *self);
extern void Effect_BindRes25_Init(unsigned char *self);
extern void CoinJumpFx_SpawnSlots(unsigned char *self);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Matrix4_Identity(float m[4][4]);
extern void Mtx44_Scale_PerAxis(float dst[4][4], float src[4][4], float x, float y, float z);
extern void Matrix4_Multiply(float a[4][4], float b[4][4], float out[4][4]);
extern void DbgScene_CopyMatrix3x4Transpose(void *dst, float src[4][4]);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern void Effect_TwoChildPlace_AndForward_E4(unsigned char *e, Vec pos, float scale, float alpha);
extern void Effect_BuildYawPitchScaleMtx_48(unsigned char *e, Vec pos, float scale, float alpha);
extern void CoinJumpFx_UpdateParticleGrid(unsigned char *e, Vec pos, float scale, float alpha);
extern void Mtx_Copy(void *dst, const void *src);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Vec3_Subtract_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern float Vec3_Magnitude_Wrapper(const Vec *v);
extern void Vec3_Scale(Vec *out, const Vec *in, float s);
extern void Mtx44_Translate(float dst[4][4], float src[4][4], Vec t);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double x);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define U32(o) (*(unsigned int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))

static inline float sinf(float x)
{
    return sin(x);
}

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ItemObject_Tick_Dispatch16To1d(unsigned char *self)
{
    PulseTable tbl;
    float m[4][4];
    float sm[4][4];
    float tm[4][4];
    Vec s;
    Vec v;
    Vec v2;
    Vec v3;
    Vec d;
    const char *names = lbl_8032E060;
    PulseKey *k;
    float *out;
    int i;
    int j;

    switch (S8(0xC8)) {
    case 0:
        switch (I(0x8)) {
        case 0x16:
            SpriteSlot_InitNonLoop(self + 0x14, 0x16);
            break;
        case 0x17:
            SpriteSlot_InitNonLoop(self + 0x14, 0x17);
            break;
        case 0x18:
            SpriteSlot_InitNonLoop(self + 0x14, 0x18);
            break;
        case 0x19:
            SpriteSlot_InitNonLoop(self + 0x14, 0x19);
            break;
        case 0x1A:
            SpriteSlot_InitNonLoop(self + 0x14, 0x1A);
            break;
        case 0x1B:
            SpriteSlot_InitNonLoop(self + 0x14, 0x1B);
            break;
        case 0x1C:
            SpriteSlot_InitNonLoop(self + 0x14, 0x1C);
            break;
        case 0x1D:
            SpriteSlot_InitNonLoop(self + 0x14, 0x1D);
            break;
        }
        self[0x14] = 4;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        F(0x2C) = 0.0f;
        F(0x100) = 0.0f;
        F(0x104) = 0.0f;
        Mtx44_GetTranslation_RowMajor((Vec *)(self + 0xA0), KartDriver_GetJointByIdx(P(0x184), 12));
        switch (I(0x8)) {
        case 0x16:
            P(0x138) = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Init);
            break;
        case 0x17:
            break;
        case 0x18:
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
            P(0x138) = DrawEffect_SpawnDirect(Effect_BindRes25_Init);
            break;
        case 0x19:
            break;
        case 0x1A:
            P(0x138) = DrawEffect_SpawnDirect(CoinJumpFx_SpawnSlots);
            break;
        case 0x1B:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x544, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x558, 0x10, 1);
            P(0x148) = ItemObject_AllocFromPool(fn_800D748C);
            if (P(0x148) != 0) {
                SpriteSlot_InitNonLoop(P(0x148) + 0x14, 0x1B);
                SpriteSlot_SetTranslateDxDy(P(0x148) + 0x14, 0.0f, -0.008333334f);
                SpriteSlot_SetJointVisibilityByName(P(0x148) + 0x14, names + 0x544, 0x10, 1);
                SpriteSlot_SetJointVisibilityByName(P(0x148) + 0x14, names + 0x558, 0x10, 0);
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(P(0x148) + 0x14, 1);
            }
            break;
        }
        U32(0xF0) = 0;
        S8(0xC8) = 1;
        S8(0xC9) = 0;
    case 1:
        break;
    }

    if (S8(0x18C)) {
        SpriteSlot_Container_Free(P(0x148));
        P(0x148) = 0;
        if (P(0x138) != 0) {
            *(signed char *)(P(0x138) + 0xC9) = 1;
        }
        P(0x138) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    if (I(0x8) == 0x16) {
        GabyouItem_BuildLocalTransformFromHandJoint(self, 0, 1.0f, 2.8797927f, 1.0f);
    } else {
        GabyouItem_BuildLocalTransformFromHandJoint(self, 0, 0.0f, 2.8797927f, 1.0f);
    }
    if (I(0x8) == 0x19) {
        tbl = *(const PulseTable *)(names + 0x3FC);
        k = tbl.axis;
        out = &s.x;
        for (i = 0; i < 3; i++) {
            if (F(0x104) <= k->t[0]) {
                *out = k->v[1];
            } else if (k->t[8] <= F(0x104)) {
                *out = k->v[8];
            } else {
                for (j = 0; j < 8; j++) {
                    if (k->t[j] <= F(0x104) && F(0x104) < k->t[j + 1]) {
                        *out = (F(0x104) - k->t[j]) * ((k->v[j + 1] - k->v[j]) / (k->t[j + 1] - k->t[j])) + k->v[j];
                    }
                }
            }
            *out = 0.5f * *out + 0.5f;
            k++;
            out++;
        }
        Mtx_TransposeToMtx44(m, self + 0x48);
        Matrix4_Identity(sm);
        Mtx44_Scale_PerAxis(sm, sm, s.x, s.y, s.z);
        Matrix4_Multiply(m, sm, m);
        DbgScene_CopyMatrix3x4Transpose(self + 0x48, m);
        F(0x104) += 1.0f;
        if (101.0f <= F(0x104)) {
            F(0x104) = 101.0f;
        }
    }
    SpriteSlot_TickAnim(self + 0x14);
    F(0x100) += 0.1f;
    if (1.0f < F(0x100)) {
        F(0x100) = 1.0f;
    }
    F(0x2C) = F(0x100);
    if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    switch (I(0x8)) {
    case 0x16:
        if (P(0x138) != 0) {
            JointByName_GetWorldPosition(&v, self + 0x14, names + 0x574);
            if (S8(0x28)) {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), v, 2.0f * F(0xC4), F(0x2C));
            } else {
                Effect_TwoChildPlace_AndForward_E4(P(0x138), v, 2.0f * F(0xC4), 0.0f);
            }
        }
        break;
    case 0x18:
        if (P(0x138) != 0) {
            JointByName_GetWorldPosition(&v2, self + 0x14, names + 0x58C);
            if (S8(0x28)) {
                Effect_BuildYawPitchScaleMtx_48(P(0x138), v2, 2.5f * F(0xC4), F(0x2C));
            } else {
                Effect_BuildYawPitchScaleMtx_48(P(0x138), v2, 2.5f * F(0xC4), 0.0f);
            }
        }
        break;
    case 0x1A:
        if (P(0x138) != 0) {
            JointByName_GetWorldPosition(&v3, self + 0x14, names + 0x5A0);
            if (S8(0x28)) {
                CoinJumpFx_UpdateParticleGrid(P(0x138), v3, 0.7f * F(0xC4), F(0x2C));
            } else {
                CoinJumpFx_UpdateParticleGrid(P(0x138), v3, 0.7f * F(0xC4), 0.0f);
            }
        }
        break;
    case 0x1B:
        if (P(0x148) != 0) {
            Mtx_Copy(P(0x148) + 0x48, self + 0x48);
            Vec3_Copy((Vec *)(P(0x148) + 0xA0), (Vec *)(self + 0xA0));
            Vec3_Copy((Vec *)(P(0x148) + 0xAC), (Vec *)(self + 0xAC));
            *(float *)(P(0x148) + 0xC4) = F(0xC4);
            if (S8(0x28)) {
                *(float *)(P(0x148) + 0x2C) = F(0x2C);
            } else {
                *(float *)(P(0x148) + 0x2C) = 0.0f;
            }
            Vec3_Subtract_DestFirst(&d, (Vec *)(lbl_805DF3D0 + 0x80), (Vec *)(P(0x148) + 0xA0));
            Vec3_Scale(&d, &d, 0.1f * (1.0f / Vec3_Magnitude_Wrapper(&d)));
            Mtx_TransposeToMtx44(tm, P(0x148) + 0x48);
            Mtx44_Translate(tm, tm, d);
            DbgScene_CopyMatrix3x4Transpose(P(0x148) + 0x48, tm);
        }
        if (U32(0xF0) == 0) {
            U32(0xF0) = 60;
        }
        break;
    case 0x1C:
        F(0x104) = BuildOrientationFromYaw(0.034906577f + F(0x104));
        F(0x2C) *= 0.2f * sinf(F(0x104)) + 0.6f;
        break;
    }
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}

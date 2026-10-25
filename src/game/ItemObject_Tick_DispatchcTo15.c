/* ItemObject_Tick_DispatchcTo15 (0x800E2CF0): handheld item kinds
 * 0x0C..0x15. Each kind is held either by the character's hand or by the
 * kart's joint 12 with a per-kind offset/rotation, scaled by the driver's
 * boost bonus, and drives a child effect until the hold flag 0x18C is set
 * (kinds 0x14/0x15 play an SE when dropped). */
typedef struct Vec { float x, y, z; } Vec;

typedef struct HandheldPose {
    signed char onKart;
    float scale;
    Vec ofs;
    Vec rot;
} HandheldPose;

typedef struct EffectAnchor {
    float y;
    float scale;
} EffectAnchor;

extern const char lbl_8032E5EC[];
extern HandheldPose lbl_80420BC8[];
extern EffectAnchor lbl_80420D08[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_InitLoop(void *slot, int id);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_SparkSprayCompound_Init(unsigned char *self);
extern void Effect_BindRes25_Init(unsigned char *self);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern float KartCharacterParam_GetKinopioBoostBonus(void *driver);
extern float KartFxParam_GetConst1p5(void *driver);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void KartDriver_BuildJoint12EulerTransform(void *slot, void *driver, Vec ofs, Vec rot, float scale);
extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec ofs, Vec rot, int c, float d);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
extern void Effect_TwoChildPlace_AndForward_E4(unsigned char *e, Vec pos, float scale, float alpha);
extern void Effect_BuildYawPitchScaleMtx_48(unsigned char *e, Vec pos, float scale, float alpha);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))

static inline void Timer_Tick(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void ItemObject_Tick_DispatchcTo15(unsigned char *self)
{
    float m[4][4];
    Vec ofs;
    Vec rot;
    Vec rot2;
    Vec v;
    Vec se1;
    Vec se2;
    float k;

    switch (S8(0xC8)) {
    case 0:
        switch (I(0x8)) {
        case 0xC:
            I(0x10) = 0;
            break;
        case 0xD:
            I(0x10) = 1;
            break;
        case 0xE:
            I(0x10) = 2;
            break;
        case 0xF:
            I(0x10) = 3;
            break;
        case 0x10:
            I(0x10) = 4;
            break;
        case 0x11:
            I(0x10) = 5;
            break;
        case 0x12:
            I(0x10) = 6;
            break;
        case 0x13:
            I(0x10) = 7;
            break;
        case 0x14:
            I(0x10) = 8;
            break;
        case 0x15:
            I(0x10) = 9;
            break;
        }
        switch (I(0x8)) {
        case 0xC:
            SpriteSlot_InitNonLoop(self + 0x14, 0xC);
            break;
        case 0xD:
            SpriteSlot_InitNonLoop(self + 0x14, 0xD);
            break;
        case 0xE:
            SpriteSlot_InitLoop(self + 0x14, 0xE);
            break;
        case 0xF:
            SpriteSlot_InitLoop(self + 0x14, 0xF);
            break;
        case 0x10:
            SpriteSlot_InitNonLoop(self + 0x14, 0x10);
            break;
        case 0x11:
            SpriteSlot_InitNonLoop(self + 0x14, 0x11);
            break;
        case 0x12:
            SpriteSlot_InitLoop(self + 0x14, 0x12);
            break;
        case 0x13:
            SpriteSlot_InitNonLoop(self + 0x14, 0x13);
            break;
        case 0x14:
            SpriteSlot_InitNonLoop(self + 0x14, 0x14);
            break;
        case 0x15:
            SpriteSlot_InitNonLoop(self + 0x14, 0x15);
            break;
        }
        self[0x14] = 4;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        F(0x2C) = 0.0f;
        switch (I(0x8)) {
        case 0xE:
        case 0x10:
        case 0x15:
            P(0x138) = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Init);
            break;
        case 0xC:
        case 0xD:
        case 0xF:
        case 0x11:
        case 0x13:
        case 0x14:
            P(0x138) = DrawEffect_SpawnDirect(Effect_BindRes25_Init);
            break;
        }
        S8(0xC8) = 1;
    case 1:
        break;
    }

    if (S8(0x18C)) {
        switch (I(0x8)) {
        case 0x13:
            break;
        case 0x14:
            se1 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xB4, &se1, 0);
            break;
        case 0x15:
            se2 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xB0, &se2, 0);
            break;
        }
        if (P(0x138) != 0) {
            *(signed char *)(P(0x138) + 0xC9) = 1;
        }
        P(0x138) = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    F(0x2C) += 0.1f;
    if (1.0f < F(0x2C)) {
        F(0x2C) = 1.0f;
    }
    F(0xC4) = lbl_80420BC8[I(0x10)].scale * KartFxParam_GetConst1p5(P(0x184)) * KartCharacterParam_GetKinopioBoostBonus(P(0x184));
    if (lbl_80420BC8[I(0x10)].onKart) {
        Mtx44_GetTranslation_RowMajor((Vec *)(self + 0xA0), KartDriver_GetJointByIdx(P(0x184), 12));
        Vec3_Copy(&ofs, &lbl_80420BC8[I(0x10)].ofs);
        rot.x = 0.017453289f * lbl_80420BC8[I(0x10)].rot.x;
        rot.y = 0.017453289f * lbl_80420BC8[I(0x10)].rot.y;
        rot.z = 0.017453289f * lbl_80420BC8[I(0x10)].rot.z;
        KartDriver_BuildJoint12EulerTransform(self + 0x14, P(0x184), ofs, rot, F(0xC4));
    } else {
        rot2.x = 0.017453289f * lbl_80420BC8[I(0x10)].rot.x;
        rot2.y = 0.017453289f * lbl_80420BC8[I(0x10)].rot.y;
        rot2.z = 0.017453289f * lbl_80420BC8[I(0x10)].rot.z;
        Item_RenderHandheldByCharacter(self, lbl_80420BC8[I(0x10)].ofs, rot2, 0, lbl_80420BC8[I(0x10)].scale);
    }
    if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    SpriteSlot_TickAnim(self + 0x14);
    switch (I(0x8)) {
    case 0x13:
        JointByName_GetWorldPosition(&v, self + 0x14, lbl_8032E5EC);
        break;
    case 0x10:
        JointByName_GetWorldPosition(&v, self + 0x14, lbl_8032E5EC);
        break;
    case 0xC:
        JointByName_GetWorldPosition(&v, self + 0x14, lbl_8032E5EC);
        break;
    default:
        GetSpawnPosition(&v, 0.0f, lbl_80420D08[I(0x10)].y, 0.0f);
        Mtx_TransposeToMtx44(m, self + 0x48);
        Mtx44_TransformVec3(&v, m, v);
        break;
    }
    k = F(0xC4) * lbl_80420D08[I(0x10)].scale;
    switch (I(0x8)) {
    case 0xE:
    case 0x10:
    case 0x15:
        if (S8(0x28)) {
            Effect_TwoChildPlace_AndForward_E4(P(0x138), v, k, F(0x2C));
        } else {
            Effect_TwoChildPlace_AndForward_E4(P(0x138), v, k, 0.0f);
        }
        break;
    case 0xC:
    case 0xD:
    case 0xF:
    case 0x11:
    case 0x13:
    case 0x14:
        if (S8(0x28)) {
            Effect_BuildYawPitchScaleMtx_48(P(0x138), v, k, F(0x2C));
        } else {
            Effect_BuildYawPitchScaleMtx_48(P(0x138), v, k, 0.0f);
        }
        break;
    }
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}

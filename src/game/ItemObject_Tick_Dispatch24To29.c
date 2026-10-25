/* ItemObject_Tick_Dispatch24To29 (0x800E1298): item kinds 0x24..0x29
 * (handheld fast drop, two spinning drops, timed drop, banana trio spawner
 * and light attachment). Holds the item in the character's hand with a
 * per-kind offset/rotation, launches or drops it on the hold flag, then runs
 * the kind's own tick. A child effect follows the item each frame. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct HandheldPose {
    int pad;
    float scale;
    Vec ofs;
    Vec rot;
} HandheldPose;

extern const char lbl_8032E060[];
extern HandheldPose lbl_80420E18[];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int b);
extern void SpriteSlot_SetTransform(void *slot, Vec pos, Vec rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_SparkSprayCompound_Init(unsigned char *self);
extern void Effect_BindRes25_Init(unsigned char *self);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double x);
extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec ofs, Vec rot, int c, float d);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void Mtx_TransposeToMtx44(float dst[4][4], const void *src);
extern void Mtx44_Inverse_GaussJordan(float dst[4][4], float src[4][4]);
extern void Mtx44_TransformVec3(Vec *out, float m[4][4], Vec in);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern void ItemObject_Tick_Kind2426_FastDrop(unsigned char *self, unsigned char *sub);
extern void ItemObject_Tick_Kind27_TimedDrop(unsigned char *self, unsigned char *sub);
extern void ItemObject_Tick_Kind28_BananaTrioSpawner(unsigned char *self, unsigned char *sub);
extern void ItemObject_Tick_Kind29_LightAttachment(unsigned char *self, unsigned char *sub);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern void Effect_TwoChildPlace_AndForward_E4(unsigned char *e, Vec pos, float scale, float alpha);
extern void Effect_BuildYawPitchScaleMtx_48(unsigned char *e, Vec pos, float scale, float alpha);
extern void JointByName_GetMatrix4x4Transposed(float dst[4][4], void *slot, const char *name);
extern void Effect_ApplyParentToChildPair_DcDe(unsigned char *e, float m[4][4], float alpha);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))

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

static inline void SpinDrop_Tick(unsigned char *self, unsigned char *sub)
{
    float root[4][4];
    Vec se;

    switch (S8(0xC9)) {
    case 0:
        SF(0x14) = 2.0f;
        se = *(Vec *)(self + 0xA0);
        SoundMgr_PlaySE_Positional(0xAB, &se, 0);
        S8(0xC9)++;
    case 1:
        break;
    }
    SF(0x14) -= 0.2f;
    if (SF(0x14) < 0.0f) {
        F(0x2C) -= 0.1f;
        if (F(0x2C) < 0.0f) {
            self[0x28] = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
    }
    SF(0x38) += SF(0x14);
    F(0xB0) = BuildOrientationFromYaw(0.34906578f + F(0xB0));
    if (SP(0x98) != 0) {
        Mtx_TransposeToMtx44(root, KartDriver_GetKartRootMtx(SP(0x98)));
        Mtx44_TransformVec3((Vec *)(self + 0xA0), root, *(Vec *)(sub + 0x34));
    }
    if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}

void ItemObject_Tick_Dispatch24To29(unsigned char *self)
{
    float inv[4][4];
    float m[4][4];
    float jm[4][4];
    Vec ofs;
    Vec rot;
    Vec v;
    const char *names = lbl_8032E060;
    unsigned char *sub = self + 0xEC;

    switch (S8(0xC8)) {
    case 0:
        switch (I(0x8)) {
        case 0x24:
            I(0x10) = 0;
            break;
        case 0x25:
            I(0x10) = 1;
            break;
        case 0x26:
            I(0x10) = 2;
            break;
        case 0x27:
            I(0x10) = 3;
            break;
        case 0x28:
            I(0x10) = 4;
            break;
        case 0x29:
            I(0x10) = 5;
            break;
        }
        switch (I(0x8)) {
        case 0x24:
            SpriteSlot_InitNonLoop(self + 0x14, 0x24);
            break;
        case 0x25:
            SpriteSlot_InitNonLoop(self + 0x14, 0x25);
            break;
        case 0x26:
            SpriteSlot_InitNonLoop(self + 0x14, 0x26);
            break;
        case 0x27:
            SpriteSlot_InitNonLoop(self + 0x14, 0x27);
            break;
        case 0x28:
            SpriteSlot_InitNonLoop(self + 0x14, 0x28);
            break;
        case 0x29:
            SpriteSlot_InitNonLoop(self + 0x14, 0x29);
            break;
        }
        self[0x14] = 4;
        F(0x2C) = 0.0f;
        sub[0] = 1;
        SF(0x14) = 0.0f;
        switch (I(0x8)) {
        case 0x24:
            SP(0x4C) = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Init);
            break;
        case 0x25:
        case 0x26:
            SP(0x4C) = DrawEffect_SpawnDirect(Effect_BindRes25_Init);
            break;
        case 0x27:
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            SP(0x4C) = DrawEffect_SpawnDirect(Effect_BindRes25_Init);
            break;
        case 0x28:
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x4F8, 0x10, 1);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x508, 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, names + 0x51C, 0x10, 1);
            SP(0x4C) = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Init);
            break;
        case 0x29:
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            break;
        }
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        S8(0xC8) = 1;
    case 1:
        F(0x2C) += 0.1f;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
        Vec3_Copy(&ofs, &lbl_80420E18[I(0x10)].ofs);
        rot.x = 0.017453289f * lbl_80420E18[I(0x10)].rot.x;
        rot.y = 0.017453289f * lbl_80420E18[I(0x10)].rot.y;
        rot.z = 0.017453289f * lbl_80420E18[I(0x10)].rot.z;
        if (I(0x8) == 0x24 || I(0x8) == 0x25 || I(0x8) == 0x26) {
            SF(0x14) = BuildOrientationFromYaw(0.08726645f + SF(0x14));
            rot.y = BuildOrientationFromYaw(rot.y + SF(0x14));
            ofs.y = (1.0f + sinf(SF(0x14))) / 2.0f + ofs.y;
        }
        Item_RenderHandheldByCharacter(self, ofs, rot, 0, lbl_80420E18[I(0x10)].scale);
        if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
            self[0x28] = 0;
        } else {
            self[0x28] = 1;
        }
        switch (*(signed char *)(sub + 0xA0)) {
        case 1:
            sub[0xA0] = 0;
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
            if (SP(0x4C) != 0) {
                *(signed char *)(SP(0x4C) + 0xC9) = 1;
            }
            SP(0x4C) = 0;
            F(0x2C) = 1.0f;
            if (SP(0x98) != 0) {
                Mtx_TransposeToMtx44(inv, KartDriver_GetKartRootMtx(SP(0x98)));
                Mtx44_Inverse_GaussJordan(inv, inv);
                Mtx44_TransformVec3((Vec *)(sub + 0x34), inv, *(Vec *)(self + 0xA0));
            }
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            break;
        case 2:
            sub[0xA0] = 0;
            if (SP(0x4C) != 0) {
                *(signed char *)(SP(0x4C) + 0xC9) = 1;
            }
            SP(0x4C) = 0;
            S8(0xC8) = 3;
            S8(0xC9) = 0;
            return;
        }
        break;
    case 2:
        switch (I(0x8)) {
        case 0x24:
            ItemObject_Tick_Kind2426_FastDrop(self, sub);
            break;
        case 0x25:
            SpinDrop_Tick(self, sub);
            break;
        case 0x26:
            SpinDrop_Tick(self, sub);
            break;
        case 0x27:
            ItemObject_Tick_Kind27_TimedDrop(self, sub);
            break;
        case 0x28:
            ItemObject_Tick_Kind28_BananaTrioSpawner(self, sub);
            break;
        case 0x29:
            ItemObject_Tick_Kind29_LightAttachment(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }

    if (sub[0] != 0) {
        SpriteSlot_SetTransform(self + 0x14, *(Vec *)(self + 0xA0), *(Vec *)(self + 0xAC), F(0xC4));
    }
    SpriteSlot_TickAnim(self + 0x14);
    Mtx_TransposeToMtx44(m, self + 0x48);
    if (SP(0x4C) != 0) {
        switch (I(0x8)) {
        case 0x24:
            GetSpawnPosition(&v, 0.0f, 2.5f, 0.0f);
            Mtx44_TransformVec3(&v, m, v);
            if (S8(0x28)) {
                Effect_TwoChildPlace_AndForward_E4(SP(0x4C), v, 2.0f * F(0xC4), F(0x2C));
            } else {
                Effect_TwoChildPlace_AndForward_E4(SP(0x4C), v, 2.0f * F(0xC4), 0.0f);
            }
            break;
        case 0x25:
        case 0x26:
            GetSpawnPosition(&v, 0.0f, 2.5f, 0.0f);
            Mtx44_TransformVec3(&v, m, v);
            if (S8(0x28)) {
                Effect_BuildYawPitchScaleMtx_48(SP(0x4C), v, 2.5f * F(0xC4), F(0x2C));
            } else {
                Effect_BuildYawPitchScaleMtx_48(SP(0x4C), v, 2.5f * F(0xC4), 0.0f);
            }
            break;
        case 0x27:
            GetSpawnPosition(&v, 0.0f, 1.5f, 0.0f);
            Mtx44_TransformVec3(&v, m, v);
            if (S8(0x28)) {
                Effect_BuildYawPitchScaleMtx_48(SP(0x4C), v, 1.3f * F(0xC4), F(0x2C));
            } else {
                Effect_BuildYawPitchScaleMtx_48(SP(0x4C), v, 1.3f * F(0xC4), 0.0f);
            }
            break;
        case 0x28:
            GetSpawnPosition(&v, 0.0f, 1.0f, 0.0f);
            Mtx44_TransformVec3(&v, m, v);
            if (S8(0x28)) {
                Effect_TwoChildPlace_AndForward_E4(SP(0x4C), v, F(0xC4), F(0x2C));
            } else {
                Effect_TwoChildPlace_AndForward_E4(SP(0x4C), v, F(0xC4), 0.0f);
            }
            break;
        case 0x29:
            JointByName_GetMatrix4x4Transposed(jm, self + 0x14, names + 0x530);
            if (S8(0x28)) {
                Effect_ApplyParentToChildPair_DcDe(SP(0x4C), jm, F(0x2C));
            } else {
                Effect_ApplyParentToChildPair_DcDe(SP(0x4C), jm, 0.0f);
            }
            break;
        }
    }
    Timer_Tick((unsigned int *)(sub + 0x4));
    Timer_Tick((unsigned int *)(sub + 0x8));
    Timer_Tick((unsigned int *)(sub + 0xC));
    Timer_Tick((unsigned int *)(sub + 0x10));
}

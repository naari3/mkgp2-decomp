/* ItemObject_Tick_DispatchShellGroup (0x800E33C4): shell-type items held
 * on the kart (kinds 1..0xB, 0x89, 0x8F). The item is attached to the
 * kart's joint 12, grows in with a sine pulse after being fired, hits the
 * kart that touches it and fades out on the hold flag 0x18C. Kind 8 also
 * drives a trail effect with a looping SE, kind 0xB animates its chain. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct ShellPose {
    int anim;
    int se;
    float scale;
    Vec near;
    Vec rot;
    unsigned char pad[0xC];
    Vec far;
    unsigned char pad2[0xC];
} ShellPose;

extern const char lbl_8032E618[];
extern ShellPose lbl_80420808[];
extern Vec lbl_80420BB0[2];
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetJointScaleByName(void *slot, const char *name, float x, float y, float z);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void SpriteSlot_Container_Free(void *self);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void DrawEffect_Cb_KartShadow_TwoSlot(unsigned char *self);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void ItemHit_Dispatch(unsigned char *self, int a, Vec *pos, int b);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec *pos, int ch);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern int SoundMgr_CountActiveSEInstances(int se);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern float KartCharacterParam_GetKinopioBoostBonus(void *driver);
extern float KartFxParam_GetConst1p5(void *driver);
extern double sin(double x);
extern void Vec3_Lerp(Vec *dst, Vec a, Vec b, float t);
extern void KartDriver_BuildJoint12EulerTransform(void *slot, void *driver, Vec ofs, Vec rot, float scale);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern void DrawEffect_KartItemTrail_ExplodeAndPropagate(unsigned char *e, void *mtx, float alpha);

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

static inline void Shell_TrailSE(unsigned char *self)
{
    Vec se5;
    Vec se4;

    if (*(unsigned char *)(P(0x184) + 0x2D0) != 0) {
        if (I(0x11C) < 0) {
            I(0x11C) = SoundMgr_CountActiveSEInstances(0x91);
            if (I(0x11C) >= 0) {
                se4 = *(Vec *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0x91, &se4, I(0x11C));
            }
        } else {
            se5 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_WithChannel(0x91, &se5, I(0x11C));
        }
    }
}

void ItemObject_Tick_DispatchShellGroup(unsigned char *self)
{
    Vec lp;
    Vec rot;
    Vec se;
    Vec se2;
    Vec se3;
    int done = 0;

    switch (S8(0xC8)) {
    case 0:
        switch (I(0x8)) {
        case 1:
            I(0x10) = 0;
            break;
        case 2:
            I(0x10) = 1;
            break;
        case 3:
            I(0x10) = 2;
            break;
        case 4:
            I(0x10) = 3;
            break;
        case 5:
            I(0x10) = 4;
            break;
        case 6:
            I(0x10) = 5;
            break;
        case 7:
            I(0x10) = 6;
            break;
        case 9:
            I(0x10) = 7;
            break;
        case 0xA:
            I(0x10) = 8;
            break;
        case 8:
            I(0x10) = 9;
            break;
        case 0xB:
            I(0x10) = 10;
            break;
        case 0x89:
            I(0x10) = 11;
            break;
        case 0x8F:
            I(0x10) = 12;
            break;
        }
        SpriteSlot_InitNonLoop(self + 0x14, lbl_80420808[I(0x10)].anim & 0xFF);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
        F(0x2C) = 0.0f;
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 0);
        F(0x100) = 1.0f;
        if (I(0x8) == 0xB) {
            SpriteSlot_SetJointScaleByName(self + 0x14, lbl_8032E618, 1.5f, 1.6f, 1.0f);
        }
        if (I(0x8) == 8) {
            P(0x138) = DrawEffect_SpawnDirect(DrawEffect_Cb_KartShadow_TwoSlot);
            I(0x11C) = -1;
        }
        U32(0xF0) = 0;
        S8(0xC8) = 1;
    case 1:
        break;
    }

    if (ItemCollision_Check(self) == 1) {
        fn_801B1D5C(P(0x184), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
        if (P(0x184) != ItemTracker_GetTargetKart(self)) {
            ItemHit_Dispatch(self, 0, 0, 0);
            se = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(lbl_80420808[I(0x10)].se, &se, 0);
        }
    }
    if (F(0x100) < 1.0f) {
        ItemTracker_SetTrackPhase(self, 1);
    } else {
        ItemTracker_SetTrackPhase(self, 0);
    }
    switch (S8(0x18C)) {
    case 0:
        F(0x2C) += 0.1f;
        if (1.0f < F(0x2C)) {
            F(0x2C) = 1.0f;
        }
        break;
    case 1:
        F(0x2C) -= 0.02f;
        if (F(0x2C) < 0.0f) {
            F(0x2C) = 0.0f;
            done = 1;
        }
        break;
    case 2:
        done = 1;
        break;
    }
    if (done) {
        if (I(0x8) == 8) {
            if (P(0x138) != 0) {
                *(signed char *)(P(0x138) + 0xC9) = 1;
            }
            P(0x138) = 0;
            if (I(0x11C) >= 0) {
                SoundMgr_StopSE_OrSpecial(0x91, I(0x11C));
                I(0x11C) = -1;
            }
        }
        ItemTracker_ReleaseLock(self);
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    if (self[0xEC] != 0) {
        F(0x100) = 0.0f;
        if (I(0x8) == 0xB) {
            se2 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xB6, &se2, 0);
            U32(0xF0) = 0;
        } else if (I(0x8) != 4 && I(0x8) != 5) {
            se3 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0x67, &se3, 0);
        }
        self[0xEC] = 0;
    }
    if (I(0x8) == 0xB) {
        if (U32(0xF0) == 0) {
            F(0x100) += 0.05f;
        }
    } else {
        F(0x100) += 0.045454547f;
    }
    if (1.0f < F(0x100)) {
        F(0x100) = 1.0f;
    }
    if (F(0x100) < 1.0f) {
        self[0x28] = 1;
    } else if (FinalLapCoinJump_CheckActiveForObject(P(0x184))) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
    F(0xC4) = lbl_80420808[I(0x10)].scale * KartFxParam_GetConst1p5(P(0x184)) * KartCharacterParam_GetKinopioBoostBonus(P(0x184));
    if (F(0x100) < 1.0f) {
        F(0xC4) = F(0xC4) * (1.0f + sinf(3.141592f * F(0x100)));
    }
    Vec3_Lerp(&lp, lbl_80420808[I(0x10)].far, lbl_80420808[I(0x10)].near, sinf(3.141592f * F(0x100)));
    if (*(int *)(P(0x184) + 0x1F8) == 0xC && I(0x8) == 8) {
        Vec3_Lerp(&lp, lbl_80420BB0[1], lbl_80420BB0[0], sinf(3.141592f * F(0x100)));
    }
    rot.x = 0.017453289f * lbl_80420808[I(0x10)].rot.x;
    rot.y = 0.017453289f * lbl_80420808[I(0x10)].rot.y;
    rot.z = 0.017453289f * lbl_80420808[I(0x10)].rot.z;
    KartDriver_BuildJoint12EulerTransform(self + 0x14, P(0x184), lp, rot, F(0xC4));
    Mtx44_GetTranslation_RowMajor((Vec *)(self + 0xA0), self + 0x48);
    if (I(0x8) == 0xB) {
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 20.0f * F(0x100));
        SpriteSlot_SetScale(self + 0x14, 0.0f);
    }
    if (I(0x8) == 8) {
        if (S8(0x28)) {
            DrawEffect_KartItemTrail_ExplodeAndPropagate(P(0x138), self + 0x48, F(0x2C));
        } else {
            DrawEffect_KartItemTrail_ExplodeAndPropagate(P(0x138), self + 0x48, 0.0f);
        }
        Shell_TrailSE(self);
    }
    Timer_Tick((unsigned int *)(self + 0xF0));
    Timer_Tick((unsigned int *)(self + 0xF4));
    Timer_Tick((unsigned int *)(self + 0xF8));
    Timer_Tick((unsigned int *)(self + 0xFC));
}

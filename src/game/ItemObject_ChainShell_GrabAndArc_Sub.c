/* ItemObject_ChainShell_GrabAndArc_Sub (0x800E55E4): chain shell (Wanwan)
 * held in the character's hand, then thrown. Thrown it homes in and lunges;
 * sub[0] is its phase (0 thrown, 1 lunging, 2 falling, 3 planted with a
 * smoke ring). Hits steal or knock the target per the ItemCollision result,
 * walls bounce it, and a planted shell ends when its hit entry expires. */
typedef struct Vec { float x, y, z; } Vec;

extern int g_ccClass;
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern float Vec3_ToYaw(const Vec *v);
extern float Vec3_Magnitude_Wrapper(const Vec *v);
extern void Vec3_Copy(Vec *dst, const Vec *src);
extern void Vec3_Add_DestFirst(Vec *out, const Vec *a, const Vec *b);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void SpriteSlot_SetScale(void *slot, float s);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern signed char ItemObject_GetGroundTypeAt(Vec *pos, float *outGroundY, int mode);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern void fn_801B129C(Vec *pos);
extern void Item_HomingScanAndSteer(unsigned char *self, float *yaw, int mode);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, int entryId, int mode);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_SmokeRing3_Update(unsigned char *self);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void Item_ComputeYawRelativeApproach(Vec *vel, void *kart, Vec *pos, Vec *prevVel);
extern void SoundMgr_PlaySE_Positional(int se, Vec *pos, int ch);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec *outNormal, int mode);
extern void Item_BounceOffWall(unsigned char *self, Vec *normal, int se, int flag, float k1, float k2);
extern int Item_AdvanceProjectileSimple(unsigned char *self, float *anchor, float k1, float k2);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *out, int a, float f);
extern void DrawEffect_ItemHitBurst_Spawn(Vec *pos, Vec *vel, int kind);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))

void ItemObject_ChainShell_GrabAndArc_Sub(unsigned char *self, unsigned char *sub)
{
    Vec normal;
    Vec ground;
    Vec pos3;
    Vec prevVel;
    Vec se1;
    Vec se2;
    Vec nc;
    Vec hitPos;
    Vec vel;
    int landed;
    int res;

    switch (S8(0xC9)) {
    case 0:
        S8(0xC9)++;
        S8(0xCA) = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            S8(0xCA)++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 0.0f, -0.52359867f, 0.7f);
            if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(sub + 0xA0)) {
            case 1:
                self[0x28] = 1;
                sub[0xA0] = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                Item_InitLaunchFromKart(self, sub + 0x34, 5.0f, 0.0f);
                S8(0xC9)++;
                S8(0xCA) = 0;
                break;
            case 2:
                sub[0xA0] = 0;
                self[0x28] = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor((Vec *)(sub + 0x34), KartDriver_GetJointByIdx(SP(0x98), 12));
            }
        }
        break;
    case 2:
        switch (S8(0xCA)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8D] = 1;
            self[0x3C] = 1;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 2.0f);
            ground = *(Vec *)(self + 0xA0);
            ItemObject_GetGroundTypeAt(&ground, (float *)(sub + 0x18), 0);
            SF(0x18) = F(0xA4) - SF(0x18);
            SU32(0x4) = 300;
            SU32(0x8) = 0;
            sub[0] = 0;
            S8(0xCA)++;
            S8(0xCB) = 0;
        case 1:
            switch (S8(0x1D)) {
            case 1:
                if ((int)self[0x1E] == 1) {
                    SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                    SpriteSlot_SetScale(self + 0x14, 1.0f);
                }
                break;
            case 2:
                if ((int)self[0x1E] == 1) {
                    SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 3, 0.0f);
                    SpriteSlot_SetScale(self + 0x14, 1.0f);
                    sub[0] = 1;
                }
                break;
            }
            Item_HomingScanAndSteer(self, (float *)(self + 0xB0), 0);
            if (sub[0] == 1) {
                Item_AccelClampVelocity(self, (g_ccClass == 0) ? 17.0f : 22.0f, (g_ccClass == 0) ? 1.0f : 2.0f);
                fn_801B129C((Vec *)(self + 0xA0));
            }
            if (SU32(0x4) == 0) {
                S8(0xCA) = 2;
                S8(0xCB) = 0;
            }
            break;
        case 2:
            switch (S8(0xCB)) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 2.0f);
                sub[0] = 2;
                S8(0xCB)++;
            case 1:
                F(0xBC) += -0.1f;
                break;
            }
            break;
        case 3:
            switch (S8(0xCB)) {
            case 0:
                SU32(0x4) = 900;
                sub[0] = 3;
                ItemHitRegistry_AddEntry(self);
                SP(0x4C) = DrawEffect_SpawnDirect(Effect_SmokeRing3_Update);
                if (SP(0x4C) != 0) {
                    Vec3_Copy((Vec *)(SP(0x4C) + 0x8C), (Vec *)(self + 0xA0));
                }
                S8(0xCB)++;
            case 1:
                if ((int)self[0x1E] == 1) {
                    SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 5, 0.0f);
                    SpriteSlot_SetScale(self + 0x14, 1.0f);
                }
                break;
            }
            break;
        }

        Item_DecayVelocityScalar(self, 1.0f);
        res = ItemCollision_Check(self);
        switch (res) {
        case 1:
            fn_801B1D5C(SP(0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
        case 2:
            if (res == 2) {
                fn_801B1660(SP(0x98), ItemTracker_GetTargetKart(self));
            }
        case 3:
            if (res == 3) {
                fn_801B158C(SP(0x98), ItemTracker_GetTargetKart(self));
            }
            if ((sub[0] == 0 || sub[0] == 1) && res == 3) {
                SU32(0x7C) = 0;
                prevVel = *(Vec *)(self + 0xB8);
                pos3 = *(Vec *)(self + 0xA0);
                Item_ComputeYawRelativeApproach((Vec *)(self + 0xB8), ItemTracker_GetTargetKart(self), &pos3, &prevVel);
                F(0xB0) = Vec3_ToYaw((Vec *)(self + 0xB8));
                ItemTracker_SetTrackPhase(self, 0);
                SU32(0x8) = 5;
                break;
            }
            SP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            se1 = *(Vec *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xCB, &se1, 0);
            if (SP(0x4C) != 0) {
                *(signed char *)(SP(0x4C) + 0xC9) = 1;
            }
            SP(0x4C) = 0;
            if (sub[0] == 0 || sub[0] == 1) {
                sub[1] = 1;
            } else {
                sub[1] = 0;
            }
            if (res == 1) {
                sub[0] = 1;
            } else {
                sub[0] = 0;
            }
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 0;
            return;
        case 4:
            fn_801B14B8(SP(0x98), ItemTracker_GetTargetKart(self));
            SP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (SP(0x4C) != 0) {
                *(signed char *)(SP(0x4C) + 0xC9) = 1;
            }
            SP(0x4C) = 0;
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (SU32(0x8) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if ((int)self[0x8D] == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (SP(0x4C) != 0) {
                *(signed char *)(SP(0x4C) + 0xC9) = 1;
            }
            SP(0x4C) = 0;
            if ((int)self[0x8E] == 1) {
                se2 = *(Vec *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0xCB, &se2, 0);
                Vec3_Add_DestFirst((Vec *)(self + 0xB8), (Vec *)(self + 0xB8), (Vec *)(self + 0x90));
                F(0xBC) = 2.0f;
                F(0xB8) *= 0.2f;
                F(0xC0) *= 0.2f;
                S8(0xC8) = 2;
                S8(0xC9) = 0;
                S8(0xCB) = 4;
            } else {
                S8(0xC8) = 2;
                S8(0xC9) = 0;
                S8(0xCB) = 6;
            }
            return;
        }
        if (sub[0] != 3 && Item_CheckWallCollision(self, &normal, 0) != 0) {
            nc = normal;
            Item_BounceOffWall(self, &nc, 0xCB, 2, 0.2f, 0.0f);
            if (sub[0] == 0 || sub[0] == 1) {
                S8(0xCA) = 2;
                S8(0xCB) = 0;
                return;
            }
        }
        if (sub[0] != 3) {
            if (sub[0] == 0 || sub[0] == 1) {
                res = Item_AdvanceProjectileSimple(self, (float *)(sub + 0x18), 7.0f, 7.0f);
            } else {
                res = Item_AdvanceFallingDrop(self, &landed, 0, 0.0f);
                if (landed != 0) {
                    vel = *(Vec *)(self + 0xB8);
                    hitPos = *(Vec *)(self + 0xA0);
                    DrawEffect_ItemHitBurst_Spawn(&hitPos, &vel, 2);
                    F(0xB8) *= 0.8f;
                    F(0xBC) *= -0.3f;
                    F(0xC0) *= 0.8f;
                    if (Vec3_Magnitude_Wrapper((Vec *)(self + 0xB8)) < 1.0f) {
                        GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
                        S8(0xCA) = 3;
                        S8(0xCB) = 0;
                        return;
                    }
                }
            }
            if (res == 0 && sub[0] != 0) {
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                S8(0xC8) = 2;
                S8(0xC9) = 0;
                S8(0xCB) = 9;
                return;
            }
        }
        if (sub[0] == 3) {
            if (ItemHitRegistry_RemoveEntry(self, SU32(0x4), 0)) {
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                if (SP(0x4C) != 0) {
                    *(signed char *)(SP(0x4C) + 0xC9) = 1;
                }
                SP(0x4C) = 0;
                S8(0xC8) = 3;
                S8(0xC9) = 0;
                S8(0xCB) = 5;
            }
        }
        break;
    }
}

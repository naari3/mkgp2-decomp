/* ItemObject_Teresa_GrabAndArc_Sub (0x800E40C8): Teresa (Boo) item held in
 * the character's hand, then thrown. Once thrown it homes in on the
 * tracked target and, on a hit, steals that kart's item (the ItemCollision
 * result picks the outcome) and switches to the track-to-kart state. Wall
 * hits, landing and timeouts end it with their own end codes in 0xCB. */
typedef struct Vec { float x, y, z; } Vec;

extern int g_ccClass;
extern void *KartDriver_GetKartRootMtx(void *driver);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(Vec *out, void *mtx);
extern float Vec3_HorizontalYawTo(const Vec *from, const Vec *to);
extern float Vec3_ToYaw(const Vec *v);
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
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void ItemHit_Dispatch(unsigned char *self, int a, Vec *pos, int b);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void Item_ComputeYawRelativeApproach(Vec *vel, void *kart, Vec *pos, Vec *prevVel);
extern void GetSpawnPosition(Vec *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec *outNormal, int mode);
extern int Item_AdvanceProjectileSimple(unsigned char *self, float *anchor, float k1, float k2);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define SF(o) (*(float *)(sub + (o)))
#define SU32(o) (*(unsigned int *)(sub + (o)))
#define SP(o) (*(unsigned char **)(sub + (o)))

void ItemObject_Teresa_GrabAndArc_Sub(unsigned char *self, unsigned char *sub)
{
    Vec kartPos;
    Vec ground;
    Vec pos;
    Vec prevVel;
    int alias;

    switch (S8(0xC9)) {
    case 0:
        if (I(0x10) != 0) {
            Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(SP(0x9C)));
            F(0xB0) = Vec3_HorizontalYawTo((Vec *)(self + 0xA0), &kartPos);
            F(0xC4) = 1.0f;
            F(0x2C) = 1.0f;
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 0;
            return;
        }
        S8(0xC9)++;
        S8(0xCA) = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 5, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            S8(0xCA)++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, -0.5f, -0.2617993f, 0.7f);
            if (FinalLapCoinJump_CheckActiveForObject(SP(0x98))) {
                self[0x14] |= 2;
            } else {
                self[0x14] &= ~2;
            }
            switch (*(signed char *)(sub + 0xA0)) {
            case 1:
                sub[0xA0] = 0;
                self[0x14] &= ~2;
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
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            SpriteSlot_SetScale(self + 0x14, 1.5f);
            ground = *(Vec *)(self + 0xA0);
            ItemObject_GetGroundTypeAt(&ground, (float *)(sub + 0x14), 0);
            SF(0x14) = F(0xA4) - SF(0x14);
            SU32(0x4) = 300;
            SU32(0x8) = 0;
            S8(0xCA)++;
        case 1:
            if ((int)self[0x1E] == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                S8(0xCA)++;
            }
            break;
        case 2:
            Item_AccelClampVelocity(self, (g_ccClass == 0) ? 17.0f : 22.0f, (g_ccClass == 0) ? 1.0f : 2.0f);
            fn_801B129C((Vec *)(self + 0xA0));
            break;
        }

        Item_HomingScanAndSteer(self, (float *)(self + 0xB0), 0);
        Item_DecayVelocityScalar(self, 1.0f);
        switch (ItemCollision_Check(self)) {
        case 1:
            alias = ItemAlias_HitRemapLookup(I(0x8));
            fn_801B1D5C(SP(0x98), ItemTracker_GetTargetKart(self), alias, 0);
            SP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemHit_Dispatch(self, 0, 0, 0);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 0;
            return;
        case 2:
            fn_801B1660(SP(0x98), ItemTracker_GetTargetKart(self));
            SP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 1;
            return;
        case 3:
            fn_801B158C(SP(0x98), ItemTracker_GetTargetKart(self));
            SU32(0x7C) = 0;
            prevVel = *(Vec *)(self + 0xB8);
            pos = *(Vec *)(self + 0xA0);
            Item_ComputeYawRelativeApproach((Vec *)(self + 0xB8), ItemTracker_GetTargetKart(self), &pos, &prevVel);
            F(0xB0) = Vec3_ToYaw((Vec *)(self + 0xB8));
            ItemTracker_SetTrackPhase(self, 0);
            SU32(0x8) = 5;
            break;
        case 4:
            fn_801B14B8(SP(0x98), ItemTracker_GetTargetKart(self));
            SP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
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
            GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
            if ((int)self[0x8E] == 1) {
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
        if (Item_CheckWallCollision(self, 0, 0) != 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            GetSpawnPosition((Vec *)(self + 0xB8), 0.0f, 0.0f, 0.0f);
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 7;
            return;
        }
        if (Item_AdvanceProjectileSimple(self, (float *)(sub + 0x14), 7.0f, 7.0f) == 0 && (int)self[0xCA] == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 9;
            return;
        }
        if (SU32(0x4) == 0 && (int)self[0xCA] == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            S8(0xC8) = 2;
            S8(0xC9) = 0;
            S8(0xCB) = 5;
        }
        break;
    }
}

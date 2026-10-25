typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enable);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float a, float b);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern void Item_AccelClampVelocity(unsigned char *self, float speedCap, float range);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec3 *pos, Vec3 *v);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern int Item_CheckWallCollision(unsigned char *self, Vec3 *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec3 *n, int a, int b, float k1, float k2);
extern int Item_AdvanceProjectileSimple(unsigned char *self, void *y, float a, float b);

extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec3 *a, Vec3 *b, int n, float k);
extern void fn_801B129C(void *pos);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, void *b);
extern float Vec3_ToYaw(void *v);
extern const Vec3 lbl_80331668;
extern const Vec3 lbl_80331674;
extern int g_ccClass;

void fn_8010ACF0(unsigned char *self, unsigned char *sub)
{
    Vec3 n;
    Vec3 a;
    Vec3 b;
    Vec3 g;
    Vec3 apPos;
    Vec3 apVel;
    Vec3 se;
    Vec3 wall;
    float range;
    float speedCap;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xCA]) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            self[0x28] = 1;
            *(float *)(self + 0x2C) = 1.0f;
            *(float *)(self + 0xC4) = 0.0f;
            self[0xCA]++;
        case 1:
            b = lbl_80331674;
            a = lbl_80331668;
            Item_RenderHandheldByCharacter(self, &a, &b, 2, 1.6f);
            if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch ((signed char)sub[0xA0]) {
            case 1:
                self[0x28] = 1;
                sub[0xA0] = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                Item_InitLaunchFromKart(self, sub + 0x34, 5.0f, 0.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                sub[0xA0] = 0;
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor(sub + 0x34, KartDriver_GetJointByIdx(*(void **)(sub + 0x98), 0xC));
                break;
            }
            break;
        }
        break;
    case 2:
        switch ((signed char)self[0xCA]) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8D] = 1;
            self[0x3C] = 1;
            g = *(Vec3 *)(self + 0xA0);
            ItemObject_GetGroundTypeAt(&g, (float *)(sub + 0x14), 0);
            *(float *)(sub + 0x14) = *(float *)(self + 0xA4) - *(float *)(sub + 0x14);
            *(int *)(sub + 0x4) = 300;
            *(int *)(sub + 0x8) = 0;
            self[0xCA]++;
        case 1:
            break;
        }
        range = (g_ccClass == 0) ? 1.0f : 2.0f;
        speedCap = (g_ccClass == 0) ? 17.0f : 22.0f;
        Item_AccelClampVelocity(self, speedCap, range);
        fn_801B129C(self + 0xA0);
        Item_DecayVelocityScalar(self, 3.0f);
        switch (ItemCollision_Check(self)) {
        case 1:
            fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
            ItemHit_Dispatch(self, 0, 0, 0);
            *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 0;
            return;
        case 2:
            fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            *(float *)(self + 0xBC) = 2.0f;
            *(float *)(self + 0xB8) *= 0.2f;
            *(float *)(self + 0xC0) *= 0.2f;
            *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 1;
            return;
        case 3:
            fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            apVel = *(Vec3 *)(self + 0xB8);
            apPos = *(Vec3 *)(self + 0xA0);
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), &apPos, &apVel);
            *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
            ItemTracker_SetTrackPhase(self, 0);
            *(int *)(sub + 0x8) = 5;
            break;
        case 4:
            fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (*(unsigned int *)(sub + 0x8) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (*(char *)(self + 0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (*(char *)(self + 0x8E) == 1) {
                Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
                *(float *)(self + 0xBC) = 2.0f;
                *(float *)(self + 0xB8) *= 0.2f;
                *(float *)(self + 0xC0) *= 0.2f;
                *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
                se = *(Vec3 *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0xCB, &se, 0);
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 4;
                return;
            }
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 6;
            return;
        }
        if (Item_CheckWallCollision(self, &n, 0)) {
            wall = n;
            Item_BounceOffWall(self, &wall, 0xCB, 2, 0.1f, 1.0f);
            *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 7;
            return;
        }
        if (!Item_AdvanceProjectileSimple(self, sub + 0x14, 7.0f, 1.0f)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 9;
            return;
        }
        if (*(unsigned int *)(sub + 0x4) == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 5;
        }
        break;
    }
}

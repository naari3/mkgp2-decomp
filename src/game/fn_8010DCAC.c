typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern char ItemObject_GetGroundTypeAt(Vec3 *pos, float *y, void *n);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern void fn_801B129C(void *pos);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec3 *pos, Vec3 *v);
extern float Vec3_ToYaw(void *v);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int flag);
extern int Item_CheckWallCollision(unsigned char *self, Vec3 *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec3 *n, int a, int b, float k1, float k2);
extern int Item_AdvanceProjectileSimple(unsigned char *self, void *y, float a, float b);

extern int g_ccClass;

void fn_8010DCAC(unsigned char *self, unsigned char *sub)
{
    Vec3 n;
    Vec3 g;
    Vec3 apPos;
    Vec3 apVel;
    Vec3 snd;
    Vec3 w;
    int hit;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xCA]) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            self[0x28] = 1;
            *(float *)(self + 0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 3.0f, 2.356194f, 0.5f);
            if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
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
            *(unsigned int *)(sub + 0x4) = 300;
            *(unsigned int *)(sub + 0x8) = 0;
            self[0xCA]++;
        case 1:
            break;
        }
        Item_AccelClampVelocity(self, g_ccClass == 0 ? 17.0f : 22.0f,
                                g_ccClass == 0 ? 1.0f : 2.0f);
        fn_801B129C(self + 0xA0);
        Item_DecayVelocityScalar(self, 0.6f);
        Item_HomingScanAndSteer(self, self + 0xB0, 0);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            }
        case 4:
            if (hit == 4) {
                fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            }
            *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (hit == 1) {
                sub[0] = 1;
            } else {
                sub[0] = 0;
            }
            if (hit != 4) {
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 0;
            } else {
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 3;
            }
            return;
        case 3:
            fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            *(int *)(sub + 0x7C) = 0;
            apVel = *(Vec3 *)(self + 0xB8);
            apPos = *(Vec3 *)(self + 0xA0);
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), &apPos, &apVel);
            *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
            ItemTracker_SetTrackPhase(self, 0);
            *(unsigned int *)(sub + 0x8) = 5;
            break;
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
                snd = *(Vec3 *)(self + 0xA0);
                SoundMgr_PlaySE_Positional(0xCB, &snd, 0);
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
            w = n;
            Item_BounceOffWall(self, &w, 0xCB, 2, 0.2f, 2.0f);
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

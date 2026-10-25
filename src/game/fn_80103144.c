typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern void Effect_Cluster16_Update(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void VfxEffect_InitVariantAndResetPos(void *e, int variant, float a, float b, float c);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern void fn_801B129C(void *pos);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec pos, Vec v);
extern float Vec3_ToYaw(void *v);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern int Item_AdvanceProjectileSimple(unsigned char *self, void *y, float a, float b);

extern int g_ccClass;

#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))

void fn_80103144(unsigned char *self, unsigned char *w)
{
    int hit;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xCA]) {
        case 0:
            w[0] = 0;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            self[0x28] = 1;
            *(float *)(self + 0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            if (*(int *)(self + 0x8) != 0x5B) {
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 3.0f, -0.785398f, 1.2f);
            } else {
                GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 3.0f, -0.2617993f, 1.2f);
            }
            if (FinalLapCoinJump_CheckActiveForObject(WP(0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(w + 0xA0)) {
            case 1:
                self[0x28] = 1;
                w[0xA0] = 0;
                w[0] = 1;
                Item_InitLaunchFromKart(self, w + 0x34, 5.0f, 0.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                w[0xA0] = 0;
                *(float *)(self + 0x2C) = 0.0f;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor(w + 0x34, KartDriver_GetJointByIdx(WP(0x98), 0xC));
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
            ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), (float *)(w + 0x18), 0);
            *(float *)(w + 0x18) = *(float *)(self + 0xA4) - *(float *)(w + 0x18);
            WU(0x4) = 300;
            WU(0x8) = 0;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
            WP(0x50) = DrawEffect_SpawnDirect(Effect_Cluster16_Update);
            VfxEffect_InitVariantAndResetPos(WP(0x50), 0, 0.5f, 0.0f, 0.8f);
            self[0xCA]++;
        case 1:
            if (*(char *)(self + 0x1E) == 1) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                self[0xCA]++;
            }
            break;
        case 2:
            Item_AccelClampVelocity(self, g_ccClass == 0 ? 17.0f : 22.0f,
                                    g_ccClass == 0 ? 1.0f : 2.0f);
            fn_801B129C(self + 0xA0);
            break;
        }
        Item_HomingScanAndSteer(self, self + 0xB0, 0);
        Item_DecayVelocityScalar(self, 2.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(WP(0x98), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(WP(0x98), ItemTracker_GetTargetKart(self));
            }
            WP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (hit == 1) {
                w[1] = 1;
            } else {
                w[1] = 0;
            }
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 0;
            return;
        case 3:
            fn_801B158C(WP(0x98), ItemTracker_GetTargetKart(self));
            *(int *)(w + 0x7C) = 0;
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self),
                                            *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
            *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
            ItemTracker_SetTrackPhase(self, 0);
            WU(0x8) = 5;
            break;
        case 4:
            fn_801B14B8(WP(0x98), ItemTracker_GetTargetKart(self));
            WP(0x9C) = ItemTracker_GetTargetKart(self);
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
        if (WU(0x8) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (*(char *)(self + 0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (*(char *)(self + 0x8E) == 1) {
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
        if (Item_CheckWallCollision(self, 0, 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 7;
            return;
        }
        if (!Item_AdvanceProjectileSimple(self, w + 0x18, 7.0f, 7.0f) && *(char *)(self + 0xCA) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 9;
            return;
        }
        if (WU(0x4) == 0 && *(char *)(self + 0xCA) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 5;
        }
        break;
    }
}

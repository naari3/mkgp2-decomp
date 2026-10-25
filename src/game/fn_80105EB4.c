typedef struct Vec { float x, y, z; } Vec;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *dst, void *mtx);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern char ItemObject_GetGroundTypeAt(Vec pos, float *y, void *n);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern void fn_801B129C(void *pos);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern float Vec3_ToYaw(void *v);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec pos, Vec v);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);

extern void Vec3_Copy(void *dst, void *src);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void fn_80105CC4(unsigned char *self, unsigned char *w, int type, float yaw);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Effect_Cluster16_Update(unsigned char *e);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, float *gy, float k);

extern int g_ccClass;

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define KIND (*(int *)(self + 0x8))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))
#define WB(o) (*(unsigned char **)(w + (o)))

void fn_80105EB4(unsigned char *self, unsigned char *w)
{
    Vec n;
    int landed;
    float gy;
    int hit;

    switch (S8(0xC9)) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            w[0] = 1;
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 4.0f, 0.0f, 0.7f);
            if (FinalLapCoinJump_CheckActiveForObject(WP(0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(w + 0xA0)) {
            case 1:
                self[0x28] = 1;
                w[0xA0] = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                w[0] = 0;
                Item_InitLaunchFromKart(self, w + 0x34, 10.0f, 0.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                w[0xA0] = 0;
                self[0x28] = 0;
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
        switch (S8(0xCA)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8D] = 1;
            self[0x3C] = 1;
            ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), (float *)(w + 0x18), 0);
            w[1] = 8;
            WU(0x4) = 300;
            WU(0x8) = 0;
            WU(0xC) = 30;
            WU(0x10) = 0;
            Vec3_Copy(w + 0x34, self + 0xB8);
            SpriteSlot_SetScale(self + 0x14, 1.0f);
            fn_80105CC4(self, w, 0, 0.0f);
            WP(0x4C) = DrawEffect_SpawnDirect(Effect_Cluster16_Update);
            if (WP(0x4C) != 0) {
                switch (KIND) {
                case 0x5F:
                    *(int *)(WB(0x4C) + 0x10) = 2;
                    break;
                case 0x60:
                    *(int *)(WB(0x4C) + 0x10) = 3;
                    break;
                }
                GetSpawnPosition(WB(0x4C) + 0x30, 1.0f, 1.0f, 1.0f);
            }
            SoundMgr_PlaySE_Positional(0xA9, *(Vec *)(self + 0xA0), 0);
            self[0xCA]++;
        case 1:
            F(0xBC) += -0.5f;
            Item_AccelClampVelocity(self, g_ccClass == 0 ? 17.0f : 22.0f,
                                    g_ccClass == 0 ? 1.0f : 2.0f);
            fn_801B129C(self + 0xA0);
            break;
        case 2:
            if (WU(0x8) == 0) {
                Vec3_Copy(self + 0xB8, w + 0x34);
                self[0xCA] = 1;
            }
            break;
        }
        Item_DecayVelocityScalar(self, 1.2f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(WP(0x98), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(KIND), 0);
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
        case 2:
            fn_801B1660(WP(0x98), ItemTracker_GetTargetKart(self));
            WP(0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 1;
            return;
        case 3:
            fn_801B158C(WP(0x98), ItemTracker_GetTargetKart(self));
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self),
                                            *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
            ItemTracker_SetTrackPhase(self, 0);
            WU(0x10) = 5;
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
        if (WU(0x10) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (*(char *)(self + 0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (*(char *)(self + 0x8E) == 1) {
                Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
                F(0xBC) = 2.0f;
                F(0xB8) *= 0.2f;
                F(0xC0) *= 0.2f;
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
        if (*(char *)(self + 0xCA) == 1) {
            if (Item_CheckWallCollision(self, &n, 0)) {
                Item_BounceOffWall(self, n, 0, 0, 1.0f, 0.0f);
                F(0xB0) = Vec3_ToYaw(&n);
                if (w[1] != 0) {
                    w[1]--;
                }
                if (w[1] != 0) {
                    if (WU(0xC) == 0) {
                        fn_80105CC4(self, w, 1, F(0xB0));
                    }
                    if (WU(0xC) == 0) {
                        WU(0x8) = 3;
                        Vec3_Copy(w + 0x34, self + 0xB8);
                        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                        self[0xCA] = 2;
                        return;
                    }
                } else {
                    GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                    ItemTracker_ReleaseLock(self);
                    self[0x8D] = 0;
                    self[0xC8] = 2;
                    self[0xC9] = 0;
                    self[0xCB] = 7;
                    return;
                }
            }
            F(0xA4) -= F(0xBC);
            if (Item_AdvanceFallingDrop(self, &landed, &gy, 0.6f)) {
                F(0xA4) += F(0xBC);
                F(0xA4) += gy - WF(0x18);
                WF(0x18) = gy;
                if (F(0xA4) < 0.6f * F(0xC4) + gy) {
                    F(0xA4) = 0.6f * F(0xC4) + gy;
                    F(0xBC) = 4.0f;
                    if (WU(0xC) == 0) {
                        fn_80105CC4(self, w, 2, 0.0f);
                    }
                    if (WU(0xC) == 0) {
                        WU(0x8) = 3;
                        Vec3_Copy(w + 0x34, self + 0xB8);
                        GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                        self[0xCA] = 2;
                        return;
                    }
                }
            } else {
                F(0xA4) += F(0xBC);
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 9;
                return;
            }
        }
        if (WU(0x4) == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 5;
        }
        break;
    }
}

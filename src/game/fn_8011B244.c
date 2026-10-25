typedef struct Vec3 { float x, y, z; } Vec3;

extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern signed char ItemObject_GetGroundTypeAt(float *pos, float *outGroundY, int flag);
extern void Item_HomingScanAndSteer(void *self, float *heading, int flag);
extern void Item_AccelClampVelocity(void *self, float accel, float maxv);
extern void fn_801B129C(float *pos);
extern void Item_DecayVelocityScalar(void *self, float k);
extern int ItemCollision_Check(void *self);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void ItemHit_Dispatch(void *self, int a, void *pos, void *b);
extern void *ItemObject_AllocFromPool(void (*fn)(void));
extern void KartPair3ArmUpdate(void);
extern void EffectActor_BindKartTargetPair(void *o, void *a, void *b);
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, float *pos, float *outVel);
extern float Vec3_ToYaw(float *v);
extern void SoundMgr_PlaySE_Positional(int se, float *pos, int flag);
extern void Vec3_Add_DestFirst(float *dst, float *a, float *b);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
extern void Item_BounceOffWall(void *self, float *normal, int se, int flag, float k1, float k2);
extern int Item_AdvanceProjectileSimple(void *self, float *anchor, float k1, float k2);
extern int ItemAlias_HitRemapLookup(int itemId);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double);
extern int g_ccClass;


void fn_8011B244(char *self, char *sub)
{
    Vec3 wallResult;
    Vec3 posCopy;
    Vec3 sePos2;
    Vec3 localPos;
    Vec3 localVel;
    Vec3 sePos4;
    Vec3 wallVec;
    Vec3 sePos7;
    float range;
    float speedCap;

    switch (*(signed char *)(self + 0xca)) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8d] = 1;
        self[0x3c] = 1;
        posCopy = *(Vec3 *)(self + 0xa0);
        ItemObject_GetGroundTypeAt((float *)&posCopy, (float *)(sub + 0x14), 0);
        *(float *)(sub + 0x14) = *(float *)(self + 0xa4) - *(float *)(sub + 0x14);
        *(int *)(sub + 4) = 300;
        *(int *)(sub + 8) = 0;
        *(float *)(sub + 0x18) = 0.0f;
        self[0xca]++;
    case 1:
        break;
    }
    Item_HomingScanAndSteer(self, (float *)(self + 0xb0), 0);
    range = (g_ccClass == 0) ? 1.0f : 2.0f;
    speedCap = (g_ccClass == 0) ? 17.0f : 22.0f;
    Item_AccelClampVelocity(self, speedCap, range);
    fn_801B129C((float *)(self + 0xa0));
    Item_DecayVelocityScalar(self, 2.0f);
    switch (ItemCollision_Check(self)) {
    case 1:
        fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                    (short)ItemAlias_HitRemapLookup(*(int *)(self + 8)), 0);
        *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 0;
        return;
    case 2:
        fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        *(float *)(self + 0xb8) *= 0.2f;
        *(float *)(self + 0xc0) *= 0.2f;
        *(float *)(self + 0xbc) = 2.0f;
        sePos2 = *(Vec3 *)(self + 0xa0);
        SoundMgr_PlaySE_Positional(0xcb, (float *)&sePos2, 0);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 1;
        return;
    case 3:
        fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        *(void **)(sub + 0x7c) = 0;
        localVel = *(Vec3 *)(self + 0xb8);
        localPos = *(Vec3 *)(self + 0xa0);
        Item_ComputeYawRelativeApproach((float *)(self + 0xb8), ItemTracker_GetTargetKart(self),
                                        (float *)&localPos, (float *)&localVel);
        *(float *)(self + 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
        ItemTracker_SetTrackPhase(self, 0);
        *(int *)(sub + 8) = 5;
        break;
    case 5:
        ItemTracker_SetTrackPhase(self, 1);
        break;
    }
    if (*(unsigned int *)(sub + 8) == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if ((int)*(unsigned char *)(self + 0x8d) == 2) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        if ((int)*(unsigned char *)(self + 0x8e) == 1) {
            Vec3_Add_DestFirst((float *)(self + 0xb8), (float *)(self + 0xb8), (float *)(self + 0x90));
            *(float *)(self + 0xb8) *= 0.2f;
            *(float *)(self + 0xc0) *= 0.2f;
            *(float *)(self + 0xbc) = 2.0f;
            sePos4 = *(Vec3 *)(self + 0xa0);
            SoundMgr_PlaySE_Positional(0xcb, (float *)&sePos4, 0);
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 4;
            return;
        }
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 6;
        return;
    }
    if (Item_CheckWallCollision(self, (float *)&wallResult, 0) != 0) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        wallVec = wallResult;
        Item_BounceOffWall(self, (float *)&wallVec, 0, 0, 0.2f, 2.0f);
        sePos7 = *(Vec3 *)(self + 0xa0);
        SoundMgr_PlaySE_Positional(0xcb, (float *)&sePos7, 0);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 7;
        return;
    }
    *(float *)(self + 0xa4) = *(float *)(self + 0xa4) - 1.5f * (float)sin(*(float *)(sub + 0x18));
    if (Item_AdvanceProjectileSimple(self, (float *)(sub + 0x14), 7.0f, 1.0f) == 0) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        self[0x28] = 0;
        self[0xc8] = 3;
        self[0xc9] = 0;
        return;
    }
    *(float *)(sub + 0x18) = BuildOrientationFromYaw(0.26179934f + *(float *)(sub + 0x18));
    *(float *)(self + 0xa4) = 1.5f * (float)sin(*(float *)(sub + 0x18)) + *(float *)(self + 0xa4);
    if (*(unsigned int *)(sub + 4) != 0) {
        return;
    }
    ItemTracker_ReleaseLock(self);
    self[0x8d] = 0;
    self[0xc8] = 2;
    self[0xc9] = 0;
    self[0xcb] = 5;
}

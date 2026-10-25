typedef struct Vec3 { float x, y, z; } Vec3;

extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern signed char ItemObject_GetGroundTypeAt(float *pos, float *outGroundY, int flag);
extern void Item_HomingScanAndSteer(void *self, float *heading, int flag);
extern void Item_AccelClampVelocity(void *self, float accel, float maxv);
extern void Item_DecayVelocityScalar(void *self, float k);
extern int ItemCollision_Check(void *self);
extern int ItemAlias_HitRemapLookup(int itemId);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, float *pos, float *outVel);
extern float Vec3_ToYaw(float *v);
extern void GetSpawnPosition(float *out, float x, float y, float z);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
extern int Item_AdvanceProjectileSimple(void *self, float *anchor, float k1, float k2);
extern void *DrawEffect_SpawnDirect(void *fn);
extern void Effect_Res76_MatrixSource_Init(void);
extern void fn_801B129C(float *pos);
extern int g_ccClass;


void fn_80113114(char *self, char *sub)
{
    Vec3 posCopy;
    Vec3 localPos;
    Vec3 localVel;
    float range;
    float speedCap;
    int collision;

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
        *(void **)(sub + 0x4c) = DrawEffect_SpawnDirect(Effect_Res76_MatrixSource_Init);
        self[0xca]++;
    case 1:
        break;
    }
    range = (g_ccClass == 0) ? 1.0f : 2.0f;
    speedCap = (g_ccClass == 0) ? 17.0f : 22.0f;
    Item_AccelClampVelocity(self, speedCap, range);
    fn_801B129C((float *)(self + 0xa0));
    Item_HomingScanAndSteer(self, (float *)(self + 0xb0), 0);
    Item_DecayVelocityScalar(self, 2.0f);
    collision = ItemCollision_Check(self);
    switch (collision) {
    case 1:
        fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                    (short)ItemAlias_HitRemapLookup(*(int *)(self + 8)), 0);
    case 2:
        if (collision == 2) {
            fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        }
        *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        if (collision == 1) {
            sub[0] = 1;
        } else {
            sub[0] = 0;
        }
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 0;
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
            GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
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
    if (Item_CheckWallCollision(self, 0, 0) != 0) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 7;
        return;
    }
    if (Item_AdvanceProjectileSimple(self, (float *)(sub + 0x14), 7.0f, 1.0f) == 0) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 5;
        return;
    }
    if (*(unsigned int *)(sub + 4) != 0) {
        return;
    }
    ItemTracker_ReleaseLock(self);
    self[0x8d] = 0;
    self[0xc8] = 2;
    self[0xc9] = 0;
    self[0xcb] = 5;
}

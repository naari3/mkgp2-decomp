typedef struct Vec3 { float x, y, z; } Vec3;

extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern void Item_SpawnGroundExplosionAndFX(void *self);
extern float Vec3_Magnitude_Wrapper(void *v);
extern void Vec3_Scale(void *dst, void *src, float s);
extern signed char ItemObject_GetGroundTypeAt(float *pos, float *outGroundY, int flag);
extern void *DrawEffect_SpawnDirect(void *fn);
extern void Effect_Res76_MatrixSource_Init(void);
extern float Vec3_ToPitch(void *v);
extern int ItemCollision_Check(void *self);
extern int ItemAlias_HitRemapLookup(int itemId);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, float *pos, float *outVel);
extern float Vec3_ToYaw(float *v);
extern void GetSpawnPosition(float *out, float x, float y, float z);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
extern int Item_AdvanceProjectileSimple(void *self, float *anchor, float k1, float k2);
extern int g_ccClass;

void fn_8010B664(char *self, char *sub)
{
    Vec3 posCopy;
    Vec3 localPos;
    Vec3 localVel;
    float speed;
    float mag;
    int collision;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x8d] = 0;
        self[0x3c] = 1;
        Item_SpawnGroundExplosionAndFX(self);
        speed = (g_ccClass == 0) ? 3e+01f : 4e+01f;
        mag = 1.0f / Vec3_Magnitude_Wrapper(self + 0xb8);
        Vec3_Scale(self + 0xb8, self + 0xb8, mag * speed);
        self[0x28] = 1;
        *(float *)(self + 0x2c) = 1.0f;
        *(float *)(self + 0xc4) = 1.5f;
        posCopy = *(Vec3 *)(self + 0xa0);
        ItemObject_GetGroundTypeAt((float *)&posCopy, (float *)(sub + 0x14), 0);
        *(float *)(sub + 0x14) = *(float *)(self + 0xa4) - *(float *)(sub + 0x14);
        *(int *)(sub + 4) = 0;
        *(int *)(sub + 8) = 3;
        *(void **)(sub + 0x4c) = DrawEffect_SpawnDirect(Effect_Res76_MatrixSource_Init);
        self[0xc9]++;
    case 1:
        break;
    }
    *(float *)(self + 0xac) = Vec3_ToPitch(self + 0xb8);
    collision = ItemCollision_Check(self);
    switch (collision) {
    case 1:
        fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                    (short)ItemAlias_HitRemapLookup(*(int *)(self + 8)), 0);
    case 2:
        if (collision == 2) {
            fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        }
    case 4:
        if (collision == 4) {
            fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        }
        *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        if (collision == 1) {
            sub[0] = 1;
        } else {
            sub[0] = 0;
        }
        if (collision != 4) {
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 0;
            return;
        }
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 3;
        return;
    case 3:
        fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        localVel = *(Vec3 *)(self + 0xb8);
        localPos = *(Vec3 *)(self + 0xa0);
        Item_ComputeYawRelativeApproach((float *)(self + 0xb8), ItemTracker_GetTargetKart(self),
                                        (float *)&localPos, (float *)&localVel);
        *(float *)(self + 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
        ItemTracker_SetTrackPhase(self, 0);
        *(int *)(sub + 4) = 5;
        break;
    case 5:
        ItemTracker_SetTrackPhase(self, 1);
        break;
    }
    if (*(unsigned int *)(sub + 4) == 0) {
        ItemTracker_SetTrackPhase(self, 1);
    }
    if (*(unsigned int *)(sub + 8) == 0 && *(signed char *)(self + 0x8d) == 0) {
        self[0x8d] = 1;
    }
    if ((int)*(unsigned char *)(self + 0x8d) == 2) {
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 4;
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
        self[0xcb] = 9;
    }
}

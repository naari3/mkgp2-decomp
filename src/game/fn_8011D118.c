typedef struct Vec3 { float x, y, z; } Vec3;

extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int a, float f);
extern void ItemHitRegistry_AddEntry(void *self);
extern unsigned char ItemHitRegistry_RemoveEntry(void *self, int t, int a);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double);
extern double cos(double);
extern float Vec3_HorizontalDistance(void *a, void *b);
extern void Item_DecayVelocityScalar(void *self, float k);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 *pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec3 *pos, int ch);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern int ItemCollision_Check(void *self);
extern int ItemAlias_HitRemapLookup(int itemId);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void ItemObject_DispatchVtable18_GetState(void *obj);
extern void ItemHit_Dispatch(void *self, int a, void *pos, void *b);
extern int Item_CheckWallCollision(void *self, void *out, void *out2);
extern int Item_AdvanceFallingDrop(void *self, int *out, int a, float f);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern void SpriteSlot_Container_Free(void *self);

void fn_8011D118(char *self, char *sub)
{
    Vec3 wallN;
    Vec3 wallPos;
    Vec3 sePos;
    Vec3 sePos2;
    int landed;
    float d;
    Vec3 dir;
    float sn;
    float dx;
    float dz;
    float nx;
    float nz;
    float ox;
    float oz;
    int collision;

    switch (*(signed char *)(self + 0xca)) {
    case 0:
        ItemTracker_AcquireLock(self);
        ItemTracker_SetTrackPhase(self, 1);
        self[0x3c] = 1;
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 10, 0.0f);
        *(int *)(sub + 4) = 900;
        *(int *)(sub + 8) = 0;
        *(int *)(sub + 0xc) = 10;
        *(int *)(sub + 0x24) = -1;
        self[0xca]++;
        ItemHitRegistry_AddEntry(self);
    case 1:
        if (*(unsigned int *)(sub + 0xc) == 0) {
            *(float *)(sub + 0x14) = 0.0f;
            *(float *)(sub + 0x18) = 0.0f;
            *(float *)(sub + 0x34) = *(float *)(self + 0xa0);
            *(float *)(sub + 0x3c) = *(float *)(self + 0xa8);
            self[0xca]++;
        }
        break;
    case 2:
        *(float *)(sub + 0x14) = BuildOrientationFromYaw(0.052359864f + *(float *)(sub + 0x14));
        *(float *)(sub + 0x18) = BuildOrientationFromYaw(0.052359864f + *(float *)(sub + 0x18));
        *(float *)(self + 0xb0) = *(float *)(sub + 0x14);
        sn = sin(*(float *)(self + 0xb0));
        *(float *)(self + 0xb8) = 0.5f * (3.0f * sn);
        sn = cos(*(float *)(self + 0xb0));
        *(float *)(self + 0xc0) = 0.5f * (3.0f * sn);
        d = Vec3_HorizontalDistance(self + 0xa0, sub + 0x34);
        if (1e+02f < d) {
            dir.x = *(float *)(self + 0xa0) - *(float *)(sub + 0x34);
            dir.z = *(float *)(self + 0xa8) - *(float *)(sub + 0x3c);
            dir.x = 1e+02f * (dir.x / d);
            dir.z = 1e+02f * (dir.z / d);
            *(float *)(self + 0xa0) = *(float *)(sub + 0x34) + dir.x;
            *(float *)(self + 0xa8) = *(float *)(sub + 0x3c) + dir.z;
            *(float *)(sub + 0x14) = BuildOrientationFromYaw(1.570796f + *(float *)(sub + 0x14));
        }
        break;
    }
    *(float *)(self + 0xbc) += -0.1f;
    Item_DecayVelocityScalar(self, 2.4f);
    if (*(int *)(sub + 0x24) < 0) {
        *(int *)(sub + 0x24) = SoundMgr_CountActiveSEInstances(0xD2);
        if (*(int *)(sub + 0x24) >= 0) {
            sePos = *(Vec3 *)(self + 0xA0);
            SoundMgr_PlaySE_Positional(0xD2, &sePos, *(int *)(sub + 0x24));
        }
    } else {
        sePos2 = *(Vec3 *)(self + 0xA0);
        SoundMgr_PlaySE_WithChannel(0xD2, &sePos2, *(int *)(sub + 0x24));
    }
    collision = ItemCollision_Check(self);
    switch (collision) {
    case 1:
        fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                    (short)ItemAlias_HitRemapLookup(*(int *)(self + 8)), 0);
    case 2:
        if (collision == 2) {
            fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        }
        if (collision == 1) {
            ItemObject_DispatchVtable18_GetState(ItemTracker_GetTargetKart(self));
            ItemHit_Dispatch(self, 0, 0, 0);
        }
        ItemTracker_SetTrackPhase(self, 0);
        *(int *)(sub + 8) = 5;
        *(int *)(sub + 8) = 30;
        break;
    case 3:
        fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
        *(float *)(sub + 0x14) = BuildOrientationFromYaw(3.141592f + *(float *)(sub + 0x14));
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
    if (Item_CheckWallCollision(self, &wallN, &wallPos) != 0) {
        *(float *)(sub + 0x14) = BuildOrientationFromYaw(0.17453289f + *(float *)(sub + 0x14));
        *(float *)(self + 0xa0) = wallPos.x;
        *(float *)(self + 0xa8) = wallPos.z;
    }
    if (Item_AdvanceFallingDrop(self, &landed, 0, 0.0f) && landed) {
        *(float *)(self + 0xbc) = 0.0f;
    }
    if (ItemHitRegistry_RemoveEntry(self, *(int *)(sub + 4), 0)) {
        if (*(int *)(sub + 0x24) >= 0) {
            SoundMgr_StopSE_OrSpecial(0xD2, *(int *)(sub + 0x24));
            *(int *)(sub + 0x24) = -1;
        }
        ItemTracker_ReleaseLock(self);
        self[0x8d] = 0;
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
    }
}

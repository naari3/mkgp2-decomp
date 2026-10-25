typedef struct Vec3 { float x, y, z; } Vec3;

extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *mtx);
extern void Item_InitLaunchFromKart(void *self, void *pos, float x, float y);
extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern int ItemCollision_Check(void *self);
extern int ItemAlias_HitRemapLookup(int itemId);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void ItemHit_Dispatch(void *self, int a, void *pos, void *b);
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, float *pos, float *outVel);
extern void GetSpawnPosition(float *out, float x, float y, float z);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
extern int Item_AdvanceFallingDrop(void *self, int *out, int a, float f);

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void GabyouItem_BuildLocalTransformFromHandJoint(void *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *obj);
extern void Item_HomingScanAndSteer(void *self, float *heading, int flag);
extern void Item_DecayVelocityScalar(void *self, float k);

void fn_80111D8C(char *self, char *sub)
{
    Vec3 localPos;
    Vec3 localVel;
    int landed;
    int collision;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        self[0xc9]++;
        self[0xca] = 0;
    case 1:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            self[0x28] = 1;
            *(float *)(self + 0x2c) = 0.0f;
            self[0xca]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 0.0f, 2.8797927f, 1.0f);
            if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(sub + 0xa0)) {
            case 1:
                self[0x28] = 1;
                sub[0xa0] = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                Item_InitLaunchFromKart(self, 0, 1.0f, -0.034906577f);
                self[0xc9]++;
                self[0xca] = 0;
                break;
            case 2:
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8d] = 1;
            self[0x3c] = 1;
            *(int *)(sub + 4) = 60;
            *(int *)(sub + 8) = 0;
            self[0xca]++;
        case 1:
            break;
        }
        *(float *)(self + 0xbc) += -0.1f;
        Item_HomingScanAndSteer(self, (float *)(self + 0xb0), 1);
        Item_DecayVelocityScalar(self, 1.0f);
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
            if (collision == 1) {
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            if (collision != 4) {
                GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
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
            *(void **)(sub + 0x7c) = 0;
            localVel = *(Vec3 *)(self + 0xb8);
            localPos = *(Vec3 *)(self + 0xa0);
            Item_ComputeYawRelativeApproach((float *)(self + 0xb8), ItemTracker_GetTargetKart(self),
                                            (float *)&localPos, (float *)&localVel);
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
            GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 7;
            return;
        }
        if (Item_AdvanceFallingDrop(self, &landed, 0, 0.0f) && landed) {
            GetSpawnPosition((float *)(self + 0xb8), 0.0f, 0.0f, 0.0f);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 8;
            return;
        }
        if (*(unsigned int *)(sub + 4) == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 5;
        }
        break;
    }
}

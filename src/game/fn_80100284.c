typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void *ItemObject_AllocGabyou(void);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Item_RenderFlyingFromKart(unsigned char *self, void *gabyou, int flag, float a, float b, float c);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void SpriteSlot_Container_Free(void *self);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(int id);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void fn_801B1D5C(void *kart, void *target, int alias, int flag);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B14B8(void *kart, void *target);
extern void ItemHit_Dispatch(void *self, int kind, void *pos, void *kart);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec3 *pos, Vec3 *v);
extern float Vec3_ToYaw(void *v);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec3 *n, int flag);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, int flag, float k);

void fn_80100284(unsigned char *self, unsigned char *sub)
{
    Vec3 apPos;
    Vec3 apVel;
    int landed;
    int hit;
    void *g;

    switch ((signed char)self[0xC9]) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch ((signed char)self[0xCA]) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            *(void **)(sub + 0x5C) = ItemObject_AllocGabyou();
            SpriteSlot_SetScale(self + 0x14, 0.0f);
            self[0x28] = 1;
            *(float *)(self + 0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            Item_RenderFlyingFromKart(self, *(void **)(sub + 0x5C), 1, -0.8f, 2.3561945f, 1.2f);
            g = *(void **)(sub + 0x5C);
            if (g != 0) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, self[0x1D], *(float *)((unsigned char *)g + 0x20));
            }
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
                SpriteSlot_Container_Free(*(void **)(sub + 0x5C));
                *(void **)(sub + 0x5C) = 0;
                Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
                SpriteSlot_SetScale(self + 0x14, 1.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                sub[0xA0] = 0;
                SpriteSlot_Container_Free(*(void **)(sub + 0x5C));
                *(void **)(sub + 0x5C) = 0;
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
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
            *(unsigned int *)(sub + 0x4) = 10;
            *(unsigned int *)(sub + 0x8) = 0;
            self[0xCA]++;
        case 1:
            break;
        }
        *(float *)(self + 0xBC) += -0.1f;
        Item_HomingScanAndSteer(self, self + 0xB0, 1);
        *(float *)(self + 0xAC) = BuildOrientationFromYaw(0.08726645f + *(float *)(self + 0xAC));
        Item_DecayVelocityScalar(self, 2.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                        ItemAlias_HitRemapLookup(*(int *)(self + 0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            }
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, self + 0xA0, 0);
            }
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 0;
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
        if (Item_AdvanceFallingDrop(self, &landed, 0, 0.0f)) {
            if (landed) {
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 8;
                return;
            }
        } else {
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

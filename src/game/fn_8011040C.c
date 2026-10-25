typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enable);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int flag, float a, float b, float c);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void Item_InitLaunchFromKart(unsigned char *self, int flag, float a, float b);
extern float Vec3_ToYaw(void *v);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
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
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec3 *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec3 *n, int a, int b, float k1, float k2);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, int flag, float k);
extern void DrawEffect_ItemHitBurst_Spawn(Vec3 *pos, Vec3 *vel, int kind);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, int id, int flag);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(void *self);


void fn_8011040C(unsigned char *self, unsigned char *sub)
{
    Vec3 n;
    Vec3 apPos;
    Vec3 apVel;
    Vec3 wall;
    Vec3 bpos;
    Vec3 bvel;
    int landed;
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
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 3.0f, 0.0f, 1.2f);
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
                Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                sub[0xA0] = 0;
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
            *(int *)(sub + 0x4) = 900;
            ItemHitRegistry_AddEntry(self);
            *(int *)(sub + 0x8) = 0;
            self[0xCA]++;
        case 1:
            *(float *)(self + 0xBC) += -0.1f;
            Item_HomingScanAndSteer(self, self + 0xB0, 1);
            break;
        case 2:
            break;
        }

        Item_DecayVelocityScalar(self, 3.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1: {
            int alias;
            int last;
            last = (signed char)self[0xCA] == 2;
            alias = ItemAlias_HitRemapLookup(*(int *)(self + 0x8));
            fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self), alias, !!last);
        }
        case 2:
            if (hit == 2) {
                fn_801B1660(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            }
        case 3:
            if (hit == 3) {
                fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            }
        case 4:
            if (hit == 4) {
                fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            }
            if (hit == 3 && *(char *)(self + 0xCA) == 1) {
                *(int *)(sub + 0x7C) = 0;
                apVel = *(Vec3 *)(self + 0xB8);
                apPos = *(Vec3 *)(self + 0xA0);
                Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), &apPos, &apVel);
                *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
                ItemTracker_SetTrackPhase(self, 0);
                *(int *)(sub + 0x8) = 5;
                break;
            }
            *(void **)(sub + 0x9C) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (hit == 1) {
                sub[0x1] = 1;
            } else {
                sub[0x1] = 0;
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
        if (*(char *)(self + 0xCA) == 1) {
            if (Item_CheckWallCollision(self, &n, 0)) {
                wall = n;
                Item_BounceOffWall(self, &wall, 0xCB, 2, 0.2f, 0.0f);
                *(float *)(self + 0xB0) = Vec3_ToYaw(self + 0xB8);
            }
            if (Item_AdvanceFallingDrop(self, &landed, 0, 4.0f)) {
                if (landed != 0) {
                    bvel = *(Vec3 *)(self + 0xB8);
                    bpos = *(Vec3 *)(self + 0xA0);
                    DrawEffect_ItemHitBurst_Spawn(&bpos, &bvel, 2);
                    GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                    self[0xCA] = 2;
                }
            } else {
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 9;
                return;
            }
        }
        if (ItemHitRegistry_RemoveEntry(self, *(int *)(sub + 0x4), 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}

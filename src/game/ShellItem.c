/*
 * ShellItem @ 0x800F4C28..0x800F5B7C (unit-claim #64, retrofit #68).
 *
 * Shell-family item unit (item ids 0x47/0x48/0x49):
 * ShellItem_TickReboundOrCarry / ShellItem_TickHitResolve /
 * ShellItem_TickActive / ShellItem_Update, promoted from the asm_fn
 * park to true C. ItemObject_Partial layout is accessed by raw offsets
 * (no committed struct header yet); see Ghidra bmp_output plate comments.
 *
 * Master state self[0xc8]: 0 init, 1 active, 2 hit, 3 free.
 * Hit type self[0xcb]: 0 rebound/carry, 3 tether, 4/5/7/9 settle,
 * 6 orbit-anchor recovery.
 * Sub-state buffer sub = self + 0xec.
 */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

/* --- extern decls: callees referenced from C bodies --- */
extern signed char ItemObject_GetGroundTypeAt(float *pos, float *outGroundY, int flag);
extern float *KartDriver_GetKartRootMtx(void *kart);
extern float *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(float *out, float *mtx);
extern void Vec3_Add_DestFirst(float *dst, float *a, float *b);
extern void Vec3_Subtract_DestFirst(float *dst, float *a, float *b);
extern void Vec3_AddNormalizedXZ(void *self, float *a, float *b);
extern float Vec3_HorizontalMagnitude(float *v);
extern void Vec3_ScaleXZ(float *dst, float *src, float k);
extern float Vec3_ToYaw(float *v);
extern void GetSpawnPosition(float x, float y, float z, float *out);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(void *item, float scalar);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void SpriteSlot_Container_Free(void *self);
extern void *ItemObject_AllocGabyou(void);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern void Item_PrepareHitRebound(void *self, float *pos, float *vel, int *timer);
extern void ItemHit_Dispatch(void *self, int a, float *pos, void *target);
extern void SoundMgr_PlaySE_Positional(int se, float *pos, int flag);
extern void Item_SpawnGroundExplosionAndFX(void *self);
extern void Item_RenderFlyingFromKart(void *self, void *gabyou, int flag, float k1, float k2, float k3);
extern void Item_InitLaunchFromKart(float k1, float k2, void *self, float *vel);
extern void ItemTracker_AcquireLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void ItemTracker_ReleaseLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern int ItemCollision_Check(void *self);
extern int ItemAlias_HitRemapLookup(int itemId);
extern void Item_AccelClampVelocity(void *self, float accel, float maxv);
extern void Item_HomingScanAndSteer(void *self, float *heading, int flag);
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, float *pos, float *outVel);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
extern void Item_BounceOffWall(float k1, float k2, void *self, float *normal, int se, int flag);
extern int Item_AdvanceProjectileSimple(float k1, float k2, void *self, float *anchor);
extern int Item_AdvanceTetherToJoint13(float anchor, float k2, float k3, void *self, float *state);
extern int Item_OrbitAnchorKart(float k1, float k2, void *self, float *offset, int timer);
extern void fn_801B129C(float *pos);
extern void fn_801B14B8(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);

/* --- extern decls: sdata2 float tuning bank --- */
extern const float lbl_806D6128;
extern const float lbl_806D612C;
extern const float lbl_806D6130;
extern const float lbl_806D6134;
extern const float lbl_806D6138;
extern const float lbl_806D613C;
extern const float lbl_806D6140;
extern const float lbl_806D6144;
extern const float lbl_806D6148;
extern const float lbl_806D614C;
extern const float lbl_806D6150;
extern const float lbl_806D6154;
extern const float lbl_806D6158;
extern const float lbl_806D615C;
extern const float lbl_806D6160;
extern const float lbl_806D6164;
extern const float lbl_806D6168;
extern const float lbl_806D616C;
extern const float lbl_806D6170;
extern const float lbl_806D6174;

/* --- extern decls: other data --- */
extern int g_ccClass;
extern unsigned int lbl_8032FA38[];

void ShellItem_TickReboundOrCarry(char *self, char *sub)
{
    Vec3 kartPos;
    Vec3 hitVel;
    Vec3 sePos;

    Mtx44_GetTranslation_RowMajor((float *)&kartPos, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9c)));
    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        Item_PrepareHitRebound(self, (float *)(sub + 0x40), (float *)(sub + 0x34), (int *)(sub + 4));
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        /* fallthrough */
    case 1:
        hitVel = *(Vec3 *)(sub + 0x34);
        Vec3_AddNormalizedXZ(self, (float *)(sub + 0x40), (float *)&hitVel);
        if (*(unsigned int *)(sub + 4) == 0) {
            self[0xc9] = 2;
            self[0xca] = 0;
        }
        break;
    case 2:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            if (*(unsigned char *)sub != 0) {
                ItemHit_Dispatch(self, 0, (float *)(self + 0xa0), *(void **)(sub + 0x9c));
            }
            sePos = *(Vec3 *)(self + 0xa0);
            SoundMgr_PlaySE_Positional(0xcb, (float *)&sePos, 0);
            *(float *)(sub + 0x38) = lbl_806D612C;
            *(float *)(sub + 0x34) = *(float *)(sub + 0x34) * lbl_806D6138;
            *(float *)(sub + 0x3c) = *(float *)(sub + 0x3c) * lbl_806D6138;
            *(int *)(sub + 4) = 10;
            *(unsigned char *)(self + 0xca) = *(unsigned char *)(self + 0xca) + 1;
            break;
        case 1:
            break;
        }
        *(float *)(sub + 0x38) = *(float *)(sub + 0x38) + lbl_806D613C;
        Vec3_Add_DestFirst((float *)(sub + 0x40), (float *)(sub + 0x40), (float *)(sub + 0x34));
        if (*(unsigned int *)(sub + 4) == 0) {
            *(float *)(self + 0x2c) = *(float *)(self + 0x2c) - lbl_806D6140;
            if (*(float *)(self + 0x2c) < lbl_806D6128) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
                return;
            }
        }
        break;
    }
    Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)&kartPos, (float *)(sub + 0x40));
    *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D6144 + *(float *)(self + 0xac));
    Item_DecayVelocityScalar(self, lbl_806D612C);
    if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x9c)) != 0) {
        self[0x28] = 0;
    } else {
        self[0x28] = 1;
    }
}

void ShellItem_TickHitResolve(char *self, char *sub)
{
    float groundY;
    Vec3 pos;
    Vec3 pos2;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        pos = *(Vec3 *)(self + 0xa0);
        ItemObject_GetGroundTypeAt((float *)&pos, (float *)(sub + 0x14), 0);
        if ((int)*(unsigned char *)(self + 0xcb) != 5) {
            *(int *)(sub + 4) = 10;
        } else {
            *(int *)(sub + 4) = 0;
        }
        if ((int)*(unsigned char *)(self + 0xcb) == 5) {
            *(float *)(self + 0xbc) = lbl_806D6128;
        }
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        break;
    case 1:
        break;
    }
    if (*(unsigned int *)(sub + 4) == 0) {
        *(float *)(self + 0x2c) = *(float *)(self + 0x2c) - lbl_806D6140;
        if (*(float *)(self + 0x2c) < lbl_806D6128) {
            self[0x28] = 0;
            self[0xc8] = 3;
            self[0xc9] = 0;
            return;
        }
    }
    if ((int)*(unsigned char *)(self + 0xcb) != 5) {
        *(float *)(self + 0xbc) = *(float *)(self + 0xbc) + lbl_806D613C;
    }
    pos2 = *(Vec3 *)(self + 0xa0);
    if (ItemObject_GetGroundTypeAt((float *)&pos2, &groundY, 0) != 0) {
        *(float *)(self + 0xa4) = *(float *)(self + 0xa4) + (groundY - *(float *)(sub + 0x14));
        *(float *)(sub + 0x14) = groundY;
    }
    switch (*(signed char *)(self + 0xcb)) {
    case 4:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D6148 + *(float *)(self + 0xac));
        break;
    case 7:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D6148 + *(float *)(self + 0xac));
        break;
    case 9:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D614C + *(float *)(self + 0xac));
        break;
    case 5:
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D614C + *(float *)(self + 0xac));
        break;
    }
    Item_DecayVelocityScalar(self, lbl_806D612C);
}

void ShellItem_TickActive(char *self, char *sub)
{
    Vec3 kartPos;
    Vec3 relPos;
    Vec3 wallResult;
    Vec3 posCopy;
    Vec3 localPos;
    Vec3 localVel;
    Vec3 sePos;
    Vec3 wallVec;
    int collision;
    float speedCap;
    float scaleF;
    float range;
    float dist;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        if (*(int *)(self + 8) == 0x49) {
            Item_SpawnGroundExplosionAndFX(self);
            *(float *)(self + 0xc4) = lbl_806D612C;
            *(float *)(self + 0x2c) = lbl_806D6150;
            self[0x28] = 0;
            self[0xc9] = 2;
            self[0xca] = 0;
            return;
        }
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        self[0xca] = 0;
        /* fallthrough */
    case 1:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            *(void **)(sub + 0x5c) = ItemObject_AllocGabyou();
            self[0x28] = 1;
            *(float *)(self + 0x2c) = lbl_806D6128;
            *(unsigned char *)(self + 0xca) = *(unsigned char *)(self + 0xca) + 1;
            /* fallthrough */
        case 1:
            Item_RenderFlyingFromKart(self, *(void **)(sub + 0x5c), 1, lbl_806D6154, lbl_806D6158,
                                      lbl_806D6150);
            if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98)) != 0) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(sub + 0xa0)) {
            case 1:
                self[0x28] = 1;
                sub[0xa0] = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                SpriteSlot_Container_Free(*(void **)(sub + 0x5c));
                *(void **)(sub + 0x5c) = 0;
                Item_InitLaunchFromKart(lbl_806D615C, lbl_806D6128, self, (float *)(sub + 0x34));
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                self[0xca] = 0;
                return;
            case 2:
                sub[0xa0] = 0;
                SpriteSlot_Container_Free(*(void **)(sub + 0x5c));
                *(void **)(sub + 0x5c) = 0;
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
                return;
            }
            Mtx44_GetTranslation_RowMajor((float *)(sub + 0x34),
                                          KartDriver_GetJointByIdx(*(void **)(sub + 0x98), 0xc));
            break;
        }
        break;
    case 2:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            self[0x28] = 1;
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8d] = 1;
            self[0x3c] = 1;
            posCopy = *(Vec3 *)(self + 0xa0);
            ItemObject_GetGroundTypeAt((float *)&posCopy, (float *)(sub + 0x14), 0);
            *(float *)(sub + 0x14) = *(float *)(self + 0xa4) - *(float *)(sub + 0x14);
            *(int *)(sub + 4) = 300;
            *(int *)(sub + 8) = 0;
            self[0xca] = 1;
            /* fallthrough */
        case 1:
            break;
        }
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D614C + *(float *)(self + 0xac));
        switch (*(int *)(self + 8)) {
        case 0x47:
            range = (g_ccClass == 0) ? lbl_806D6150 : lbl_806D612C;
            speedCap = (g_ccClass == 0) ? lbl_806D6160 : lbl_806D6164;
            Item_AccelClampVelocity(self, speedCap, range);
            fn_801B129C((float *)(self + 0xa0));
            break;
        case 0x48:
            Item_HomingScanAndSteer(self, (float *)(self + 0xb0), 1);
            range = (g_ccClass == 0) ? lbl_806D6150 : lbl_806D612C;
            speedCap = (g_ccClass == 0) ? lbl_806D6168 : lbl_806D6160;
            Item_AccelClampVelocity(self, speedCap, range);
            break;
        case 0x49:
            Item_HomingScanAndSteer(self, (float *)(self + 0xb0), 1);
            speedCap = lbl_806D6150 / Vec3_HorizontalMagnitude((float *)(self + 0xb8));
            scaleF = speedCap * ((g_ccClass == 0) ? lbl_806D616C : lbl_806D6170);
            if (*(void **)(sub + 0x7c) != 0) {
                Mtx44_GetTranslation_RowMajor((float *)&kartPos,
                                              KartDriver_GetKartRootMtx(*(void **)(sub + 0x7c)));
                relPos = *(Vec3 *)lbl_8032FA38;
                relPos.x = kartPos.x - *(float *)(self + 0xa0);
                relPos.z = kartPos.z - *(float *)(self + 0xa8);
                dist = Vec3_HorizontalMagnitude((float *)&relPos);
                if (dist < ((g_ccClass == 0) ? lbl_806D616C : lbl_806D6170)) {
                    scaleF = speedCap * dist;
                }
            }
            Vec3_ScaleXZ((float *)(self + 0xb8), (float *)(self + 0xb8), scaleF);
            break;
        }
        Item_DecayVelocityScalar(self, lbl_806D612C);
        collision = ItemCollision_Check(self);
        switch (collision) {
        case 1:
            fn_801B1D5C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self),
                        (short)ItemAlias_HitRemapLookup(*(int *)(self + 8)), 0);
            /* fallthrough */
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
        case 4:
            fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 3;
            return;
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
                *(float *)(self + 0xbc) = lbl_806D612C;
                *(float *)(self + 0xb8) = *(float *)(self + 0xb8) * lbl_806D6138;
                *(float *)(self + 0xc0) = *(float *)(self + 0xc0) * lbl_806D6138;
                sePos = *(Vec3 *)(self + 0xa0);
                SoundMgr_PlaySE_Positional(0xcb, (float *)&sePos, 0);
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
            Item_BounceOffWall(lbl_806D6138, lbl_806D612C, self, (float *)&wallVec, 0xcb, 2);
            *(float *)(self + 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 7;
            return;
        }
        if (Item_AdvanceProjectileSimple(lbl_806D6174, lbl_806D6150, self, (float *)(sub + 0x14)) == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            self[0x3c] = 0;
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 9;
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
        return;
    }
}

void ShellItem_Update(char *self)
{
    Vec3 pos;
    Vec3 rot;
    char *sub = self + 0xec;
    int code;

    switch (*(signed char *)(self + 0xc8)) {
    case 0:
        switch (*(int *)(self + 8)) {
        case 0x47:
            SpriteSlot_InitNonLoop(self + 0x14, 0x4a);
            break;
        case 0x48:
            SpriteSlot_InitNonLoop(self + 0x14, 0x4b);
            break;
        case 0x49:
            SpriteSlot_InitNonLoop(self + 0x14, 0x17);
            break;
        }
        self[0x8c] = 2;
        self[0x8d] = 0;
        self[0xc8] = 1;
        self[0xc9] = 0;
        /* fallthrough */
    case 1:
        ShellItem_TickActive(self, sub);
        break;
    case 2:
        switch (*(signed char *)(self + 0xcb)) {
        case 0:
            ShellItem_TickReboundOrCarry(self, sub);
            break;
        case 3:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D6128, lbl_806D6128, lbl_806D6128, (float *)(self + 0xb8));
                self[0x3c] = 0;
                *(float *)(sub + 0x14) = lbl_806D6128;
                *(float *)(sub + 0x18) = *(float *)(self + 0xc4);
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                break;
            case 1:
                break;
            }
            code = Item_AdvanceTetherToJoint13(*(float *)(sub + 0x18), lbl_806D6134, lbl_806D6134,
                                               self, (float *)(sub + 0x14));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 4:
            ShellItem_TickHitResolve(self, sub);
            break;
        case 6:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D6128, lbl_806D6128, lbl_806D6128, (float *)(self + 0xb8));
                self[0x3c] = 0;
                Vec3_Subtract_DestFirst((float *)(sub + 0x34), (float *)(self + 0xa0),
                                        (float *)(*(int *)(self + 0x9c) + 0xa0));
                *(int *)(sub + 4) = 0x1e;
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                break;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, lbl_806D612C);
            code = Item_OrbitAnchorKart(lbl_806D6130, lbl_806D6130, self, (float *)(sub + 0x34),
                                        *(int *)(sub + 4));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 7:
            ShellItem_TickHitResolve(self, sub);
            break;
        case 9:
            ShellItem_TickHitResolve(self, sub);
            break;
        case 5:
            ShellItem_TickHitResolve(self, sub);
            break;
        }
        break;
    case 3:
        if (*(int *)(self + 8) != 0x49) {
            ItemObject_DecrementCategoryBudget(self);
        }
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)(self + 0xa0), (float *)(self + 0xb8));
    rot = *(Vec3 *)(self + 0xac);
    pos = *(Vec3 *)(self + 0xa0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xc4));
    if (*(unsigned int *)(sub + 4) != 0) {
        *(unsigned int *)(sub + 4) = *(unsigned int *)(sub + 4) - 1;
    }
    if (*(unsigned int *)(sub + 8) != 0) {
        *(unsigned int *)(sub + 8) = *(unsigned int *)(sub + 8) - 1;
    }
    if (*(unsigned int *)(sub + 0xc) != 0) {
        *(unsigned int *)(sub + 0xc) = *(unsigned int *)(sub + 0xc) - 1;
    }
    if (*(unsigned int *)(sub + 0x10) != 0) {
        *(unsigned int *)(sub + 0x10) = *(unsigned int *)(sub + 0x10) - 1;
    }
}

/*
 * EggItem @ 0x800EADB4..0x800EBC00 (unit-claim #71, retrofit).
 *
 * Goro-Egg item (item kind 0x3B/0x3C): EggItem_OnGroundDriftTick_3B3C /
 * EggItem_Tick_HeldAndHoming_3B3C / EggItem_Dispatch_3B3C, promoted from the
 * asm_fn park to true C (automatic extab, -Cpp_exceptions on). Structural twin
 * of the Taru/Shell item units; ItemObject_Partial layout is accessed by raw
 * offsets like ShellItem.c.
 *
 * Master state self[0xc8]: 0 init, 1 active, 2 hit, 3 free.
 * Hit type self[0xcb]: 0 rebound, 3 tether, 4/7 shatter, 5/9 ground drift.
 * Sub-state buffer sub = self + 0xec (sub+0x30 = SE 200 channel).
 */

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

/* --- extern decls: callees --- */
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern float BuildOrientationFromYaw(float yaw);
extern float FAbs_FloatAsDouble(float x);
extern void Item_AccelClampVelocity(void *self, float accel, float maxv);
extern int Item_AdvanceFallingDrop(void *self, float gravity, int *landed, float *groundY);
extern void Item_BounceOffWall(float k1, float k2, void *self, float *normal, int se, int flag);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
extern void Item_DecayVelocityScalar(void *item, float scalar);
extern float Item_ProbeLateralGroundPitch(float *pos, float yaw, float a, float b);
extern void Vec2_RotateY(float *dst, float *src, float yaw);
extern float Vec3_ToYaw(float *v);
extern void DrawEffect_ItemHitOriented_Spawn(float *pos, float *vel, int mode);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void GabyouItem_BuildLocalTransformFromHandJoint(float k1, float k2, float k3, void *self, int flag);
extern void GetSpawnPosition(float x, float y, float z, float *out);
extern int ItemAlias_HitRemapLookup(int itemId);
extern int ItemCollision_Check(void *self);
extern void ItemTracker_AcquireLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern void ItemTracker_ReleaseLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, float *pos, float *outVel);
extern void Item_InitLaunchFromKart(float k1, float k2, void *self, float *vel);
extern float *KartDriver_GetJointByIdx(void *kart, int idx);
extern float *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(float *out, float *mtx);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, float *pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, float *pos, int ch);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int enabled);
extern void fn_801B129C(float *pos);
extern void fn_801B14B8(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);
extern void ItemHit_Dispatch(void *self, int a, float *pos, void *target);
extern void ItemObject_DecrementCategoryBudget(void *self);
extern int Item_AdvanceTetherToJoint13(float anchor, float k2, float k3, void *self, float *state);
extern void Item_PrepareHitRebound(void *self, float *pos, float *vel, int *timer);
extern void ShellPile_Spawn(void *self, void *sub);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int visible);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void Vec3_AddNormalizedXZ(void *self, float *a, float *b);
extern void Vec3_Add_DestFirst(float *dst, float *a, float *b);

/* --- extern decls: sdata2 float tuning bank --- */
extern const float lbl_806D5E28;
extern const float lbl_806D5E2C;
extern const float lbl_806D5E30;
extern const float lbl_806D5E34;
extern const float lbl_806D5E38;
extern const float lbl_806D5E3C;
extern const float lbl_806D5E40;
extern const float lbl_806D5E44;
extern const float lbl_806D5E48;
extern const float lbl_806D5E4C;
extern const float lbl_806D5E50;
extern const float lbl_806D5E54;
extern const float lbl_806D5E58;
extern const float lbl_806D5E5C;
extern const float lbl_806D5E60;
extern const float lbl_806D5E64;
extern const float lbl_806D5E68;
extern const float lbl_806D5E6C;
extern const float lbl_806D5E70;
extern const float lbl_806D5E74;

/* --- extern decls: other data --- */
extern int g_ccClass;
extern const char lbl_8032F480[]; /* "item_goro_egg" joint name */
extern const char lbl_8032F494[]; /* "item_goro_egg_hahen" joint name */

void EggItem_OnGroundDriftTick_3B3C(char *self, char *sub)
{
    Vec3 wallResult;
    Vec3 wallVec;
    Vec3 probePos;
    int landed;
    float groundY;
    float speedCap;
    float range;
    float pitch;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        if ((int)*(unsigned char *)(self + 0xcb) != 5) {
            *(int *)(sub + 4) = 10;
        } else {
            *(int *)(sub + 4) = 0;
        }
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        break;
    case 1:
        break;
    }
    if (*(unsigned int *)(sub + 4) == 0) {
        *(float *)(self + 0x2c) = *(float *)(self + 0x2c) - lbl_806D5E38;
        if (*(float *)(self + 0x2c) < lbl_806D5E28) {
            self[0x28] = 0;
            self[0xc8] = 3;
            self[0xc9] = 0;
            return;
        }
    }
    *(float *)(self + 0xbc) = *(float *)(self + 0xbc) + lbl_806D5E3C;
    range = (g_ccClass == 0) ? lbl_806D5E40 : lbl_806D5E44;
    speedCap = (g_ccClass == 0) ? lbl_806D5E48 : lbl_806D5E4C;
    Item_AccelClampVelocity(self, speedCap, range);
    *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D5E34 + *(float *)(self + 0xac));
    *(float *)(self + 0xb0) =
        AngleStepTowards_Shortest(*(float *)(self + 0xb0), Vec3_ToYaw((float *)(self + 0xb8)), lbl_806D5E50);
    Item_DecayVelocityScalar(self, lbl_806D5E30);
    if (Item_CheckWallCollision(self, (float *)&wallResult, 0) != 0) {
        wallVec = wallResult;
        Item_BounceOffWall(lbl_806D5E54, lbl_806D5E28, self, (float *)&wallVec, 0, 0);
    }
    FAbs_FloatAsDouble(BuildOrientationFromYaw(*(float *)(self + 0xac)));
    if (Item_AdvanceFallingDrop(self, lbl_806D5E30, &landed, &groundY) != 0 && landed != 0) {
        *(float *)(self + 0xbc) = *(float *)(self + 0xbc) * lbl_806D5E58;
        probePos = *(Vec3 *)(self + 0xa0);
        pitch = Item_ProbeLateralGroundPitch((float *)&probePos, *(float *)(self + 0xb0), lbl_806D5E5C,
                                             *(float *)(self + 0xa4) - groundY);
        if (lbl_806D5E34 < FAbs_FloatAsDouble(pitch)) {
            if (lbl_806D5E28 < pitch) {
                Vec2_RotateY((float *)(self + 0xb8), (float *)(self + 0xb8),
                             lbl_806D5E60 * -(pitch - lbl_806D5E34));
            } else {
                Vec2_RotateY((float *)(self + 0xb8), (float *)(self + 0xb8),
                             lbl_806D5E60 * -(lbl_806D5E34 + pitch));
            }
        }
    }
}

static inline void EggItem_StopRollSE(char *sub)
{
    if (*(int *)(sub + 0x30) >= 0) {
        SoundMgr_StopSE_OrSpecial(200, *(int *)(sub + 0x30));
        *(int *)(sub + 0x30) = -1;
    }
}

void EggItem_Tick_HeldAndHoming_3B3C(char *self, char *sub)
{
    Vec3 wallResult;
    Vec3 localPos;
    Vec3 localVel;
    Vec3 wallVec;
    Vec3 burstPos;
    Vec3 burstVel;
    Vec3 probePos;
    Vec3 sePos1;
    Vec3 sePos2;
    int landed;
    float groundY;
    int collision;
    float speedCap;
    float range;
    float pitch;
    float ratio;
    float thr;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        self[0xca] = 0;
        /* fallthrough */
    case 1:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            self[0x28] = 1;
            *(float *)(self + 0x2c) = lbl_806D5E28;
            *(unsigned char *)(self + 0xca) = *(unsigned char *)(self + 0xca) + 1;
            /* fallthrough */
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(lbl_806D5E30, lbl_806D5E28, lbl_806D5E64, self, 1);
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
                Item_InitLaunchFromKart(lbl_806D5E5C, lbl_806D5E68, self, (float *)(sub + 0x34));
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                self[0xca] = 0;
                return;
            case 2:
                sub[0xa0] = 0;
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
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8d] = 1;
            self[0x3c] = 1;
            *(int *)(sub + 4) = 600;
            *(int *)(sub + 0xc) = 0;
            *(int *)(sub + 8) = 0;
            sub[0] = 8;
            *(int *)(sub + 0x30) = -1;
            *(unsigned char *)(self + 0xca) = *(unsigned char *)(self + 0xca) + 1;
            /* fallthrough */
        case 1:
            break;
        }
        *(float *)(self + 0xbc) = *(float *)(self + 0xbc) + lbl_806D5E3C;
        range = (g_ccClass == 0) ? lbl_806D5E40 : lbl_806D5E44;
        speedCap = (g_ccClass == 0) ? lbl_806D5E48 : lbl_806D5E4C;
        Item_AccelClampVelocity(self, speedCap, range);
        fn_801B129C((float *)(self + 0xa0));
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D5E34 + *(float *)(self + 0xac));
        *(float *)(self + 0xb0) =
            AngleStepTowards_Shortest(*(float *)(self + 0xb0), Vec3_ToYaw((float *)(self + 0xb8)), lbl_806D5E50);
        Item_DecayVelocityScalar(self, lbl_806D5E30);
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
            EggItem_StopRollSE(sub);
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
            localVel = *(Vec3 *)(self + 0xb8);
            localPos = *(Vec3 *)(self + 0xa0);
            Item_ComputeYawRelativeApproach((float *)(self + 0xb8), ItemTracker_GetTargetKart(self),
                                            (float *)&localPos, (float *)&localVel);
            *(float *)(self + 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
            ItemTracker_SetTrackPhase(self, 0);
            *(int *)(sub + 0xc) = 5;
            break;
        case 4:
            fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            EggItem_StopRollSE(sub);
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (*(unsigned int *)(sub + 0xc) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if ((int)*(unsigned char *)(self + 0x8d) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            GetSpawnPosition(lbl_806D5E28, lbl_806D5E28, lbl_806D5E28, (float *)(self + 0xb8));
            EggItem_StopRollSE(sub);
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 4;
            return;
        }
        if (Item_CheckWallCollision(self, (float *)&wallResult, 0) != 0) {
            if (*(unsigned char *)sub != 0) {
                *(unsigned char *)sub = *(unsigned char *)sub - 1;
            }
            if (*(unsigned char *)sub != 0) {
                wallVec = wallResult;
                Item_BounceOffWall(lbl_806D5E54, lbl_806D5E28, self, (float *)&wallVec, 0xcb, 3);
            } else {
                ItemTracker_ReleaseLock(self);
                self[0x8d] = 0;
                GetSpawnPosition(lbl_806D5E28, lbl_806D5E28, lbl_806D5E28, (float *)(self + 0xb8));
                EggItem_StopRollSE(sub);
                self[0xc8] = 2;
                self[0xc9] = 0;
                self[0xcb] = 7;
                return;
            }
        }
        ratio = FAbs_FloatAsDouble(BuildOrientationFromYaw(*(float *)(self + 0xac))) / lbl_806D5E6C;
        thr = lbl_806D5E74;
        if (Item_AdvanceFallingDrop(self,
                                    (ratio < thr) ? lbl_806D5E30 : lbl_806D5E70 * ((ratio - thr) / thr) + lbl_806D5E30,
                                    &landed, &groundY) != 0) {
            if (landed != 0) {
                if (*(unsigned int *)(sub + 8) == 0) {
                    burstVel = *(Vec3 *)(self + 0xb8);
                    burstPos = *(Vec3 *)(self + 0xa0);
                    DrawEffect_ItemHitOriented_Spawn((float *)&burstPos, (float *)&burstVel, 3);
                    *(int *)(sub + 8) = 3;
                }
                *(float *)(self + 0xbc) = *(float *)(self + 0xbc) * lbl_806D5E58;
                probePos = *(Vec3 *)(self + 0xa0);
                pitch = Item_ProbeLateralGroundPitch((float *)&probePos, *(float *)(self + 0xb0), lbl_806D5E5C,
                                                     *(float *)(self + 0xa4) - groundY);
                if (lbl_806D5E34 < FAbs_FloatAsDouble(pitch)) {
                    if (lbl_806D5E28 < pitch) {
                        Vec2_RotateY((float *)(self + 0xb8), (float *)(self + 0xb8),
                                     lbl_806D5E60 * -(pitch - lbl_806D5E34));
                    } else {
                        Vec2_RotateY((float *)(self + 0xb8), (float *)(self + 0xb8),
                                     lbl_806D5E60 * -(lbl_806D5E34 + pitch));
                    }
                }
                if (*(int *)(sub + 0x30) < 0) {
                    *(int *)(sub + 0x30) = SoundMgr_CountActiveSEInstances(200);
                    if (*(int *)(sub + 0x30) >= 0) {
                        sePos1 = *(Vec3 *)(self + 0xa0);
                        SoundMgr_PlaySE_Positional(200, (float *)&sePos1, *(int *)(sub + 0x30));
                    }
                } else {
                    sePos2 = *(Vec3 *)(self + 0xa0);
                    SoundMgr_PlaySE_WithChannel(200, (float *)&sePos2, *(int *)(sub + 0x30));
                }
            } else {
                EggItem_StopRollSE(sub);
            }
        } else {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            EggItem_StopRollSE(sub);
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
        EggItem_StopRollSE(sub);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 5;
        return;
    }
}

void EggItem_Dispatch_3B3C(char *self)
{
    Vec3 pos;
    Vec3 rot;
    Vec3 hitVel;
    Vec3 kartPos;
    char *sub = self + 0xec;
    int code;

    switch (*(signed char *)(self + 0xc8)) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x3c);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_8032F480, 0x10, 0);
        SpriteSlot_SetJointVisibilityByName(self + 0x14, lbl_8032F494, 0x10, 1);
        self[0x8c] = 4;
        self[0x8d] = 0;
        self[0xc8] = 1;
        self[0xc9] = 0;
        /* fallthrough */
    case 1:
        EggItem_Tick_HeldAndHoming_3B3C(self, sub);
        break;
    case 2:
        switch (*(signed char *)(self + 0xcb)) {
        case 0:
            Mtx44_GetTranslation_RowMajor((float *)&kartPos, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9c)));
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                Item_PrepareHitRebound(self, (float *)(sub + 0x40), (float *)(sub + 0x34), (int *)(sub + 4));
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                /* fallthrough */
            case 1:
                break;
            }
            if (*(unsigned int *)(sub + 4) == 0) {
                if (*(unsigned char *)sub != 0) {
                    ItemHit_Dispatch(self, 0, (float *)(self + 0xa0), *(void **)(sub + 0x9c));
                }
                ShellPile_Spawn(self, sub);
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            } else {
                hitVel = *(Vec3 *)(sub + 0x34);
                Vec3_AddNormalizedXZ(self, (float *)(sub + 0x40), (float *)&hitVel);
                Vec3_Add_DestFirst((float *)(self + 0xa0), (float *)&kartPos, (float *)(sub + 0x40));
                Item_DecayVelocityScalar(self, lbl_806D5E30);
                *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D5E34 + *(float *)(self + 0xac));
            }
            break;
        case 3:
            switch (*(signed char *)(self + 0xc9)) {
            case 0:
                GetSpawnPosition(lbl_806D5E28, lbl_806D5E28, lbl_806D5E28, (float *)(self + 0xb8));
                self[0x3c] = 0;
                *(float *)(sub + 0x14) = lbl_806D5E28;
                *(float *)(sub + 0x18) = *(float *)(self + 0xc4);
                *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
                /* fallthrough */
            case 1:
                break;
            }
            code = Item_AdvanceTetherToJoint13(*(float *)(sub + 0x18), lbl_806D5E2C, lbl_806D5E2C, self,
                                               (float *)(sub + 0x14));
            if (code != 0) {
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
            }
            break;
        case 4:
            ShellPile_Spawn(self, sub);
            self[0x28] = 0;
            self[0xc8] = 3;
            self[0xc9] = 0;
            break;
        case 7:
            ShellPile_Spawn(self, sub);
            self[0x28] = 0;
            self[0xc8] = 3;
            self[0xc9] = 0;
            break;
        case 9:
            EggItem_OnGroundDriftTick_3B3C(self, sub);
            break;
        case 5:
            EggItem_OnGroundDriftTick_3B3C(self, sub);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
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

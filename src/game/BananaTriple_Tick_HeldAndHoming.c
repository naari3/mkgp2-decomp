/* BananaTriple_Tick_HeldAndHoming_32to36 (0x800E8CAC): banana variants
 * 0x32..0x36 while held on the kart (state 1) and while thrown/homing or
 * lying on the ground (state 2). Raw offsets as in fn_801025C0.c.
 * w = self + 0xec: [0] render, [1] landed-on-ground flag, [2] direct hit,
 * [3] variant, +4 life/registry id, +8 settle timer, +0xc track timer,
 * +0x18 ground height, +0x4c chained item, +0x98 driver, +0x9c target.
 * Compiled as C++: the hit call's last parameter is a bool, and the int
 * ternary argument is normalised (neg/or/srwi) at the call. */
#pragma cplusplus on

extern "C" {

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern float BuildOrientationFromYaw(float yaw);
extern void DrawEffect_ItemHitBurst_Spawn(Vec3 pos, Vec3 vel, int kind);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern short ItemAlias_HitRemapLookup(int id);
extern int ItemCollision_Check(char *self);
extern void ItemHitRegistry_AddEntry(char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(char *self, int id, int flag);
extern signed char ItemObject_GetGroundTypeAt(Vec3 pos, float *groundY, int mode);
extern void ItemObject_DecrementCategoryBudget(char *self);
extern void ItemTracker_AcquireLock(char *self);
extern void *ItemTracker_GetTargetKart(char *self);
extern void ItemTracker_ReleaseLock(char *self);
extern void ItemTracker_SetTrackPhase(char *self, int phase);
extern void Item_AccelClampVelocity(char *self, float accel, float maxv);
extern int Item_AdvanceFallingDrop(char *self, float gravity, int *landed, float *groundY);
extern int Item_AdvanceProjectileSimple(char *self, void *groundY, float a, float b);
extern void Item_BendVelocityByGroundProbe(void *vel, Vec3 pos, float yaw, float speed, float pitch);
extern void Item_BounceOffWall(char *self, Vec3 n, int se, int flag, float k1, float k2);
extern int Item_CheckWallCollision(char *self, Vec3 *n, int flag);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec3 pos, Vec3 v);
extern void Item_DecayVelocityScalar(char *self, float k);
extern void Item_HomingScanAndSteer(char *self, void *yaw, int flag);
extern void Item_InitLaunchFromKart(char *self, void *pos, float x, float y);
extern float Item_ProbeForwardGroundPitch(Vec3 pos, float yaw, float a, float b);
extern float Item_ProbeLateralGroundPitch(Vec3 pos, float yaw, float a, float b);
extern void Item_RenderCharacterScaledFromJoint12(char *self, Vec3 a, Vec3 b, int flag, float s);
extern void Item_SpawnGroundExplosionAndFX(char *self);
extern void KartDriver_TransformWorldToLocalY0(void *dst, Vec3 src, void *kart);
extern void SpriteSlot_Container_Free(char *self);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float scale);
extern void SpriteSlot_SetJointVisibilityByName(void *slot, const char *name, int a, int visible);
extern void SpriteSlot_SetScale(void *slot, float scale);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern float Vec3_ToPitch(void *v);
extern float Vec3_ToYaw(void *v);
extern void fn_801B14B8(void *kart, void *target);
extern void fn_801B158C(void *kart, void *target);
extern void fn_801B1660(void *kart, void *target);
extern void fn_801B1D5C(void *kart, void *target, int alias, bool flag);

extern int g_ccClass;
extern unsigned char BananaTriple_Tick_HeldAndHoming_32to36_rodata_8032EFF0[];
extern char BananaTriple_data_804211B0[][0xC0];
extern const float lbl_806D5D90;
extern const float lbl_806D5D94;
extern const float lbl_806D5D98;
extern const float lbl_806D5DA0;
extern const float lbl_806D5DA4;
extern const float lbl_806D5DAC;
extern const float lbl_806D5DB4;
extern const float lbl_806D5DB8;
extern const float lbl_806D5DBC;
extern const float lbl_806D5DC0;
extern const float lbl_806D5DC4;
extern const float lbl_806D5DC8;
extern const float lbl_806D5DCC;
extern const float lbl_806D5DD0;
extern const float lbl_806D5DD4;
extern const float lbl_806D5DD8;

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define U8(o) ((int)*(unsigned char *)(self + (o)))
#define WF(o) (*(float *)(w + (o)))
#define WU(o) (*(unsigned int *)(w + (o)))
#define WP(o) (*(void **)(w + (o)))

static inline void BananaTriple_SetIdleAnim(char *self)
{
    if (U8(0x1d) != 4) {
        SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, lbl_806D5D90);
        SpriteSlot_SetScale(self + 0x14, lbl_806D5DAC);
    }
}

#pragma exceptions on
#pragma use_lmw_stmw on
void BananaTriple_Tick_HeldAndHoming_32to36(char *self, char *w)
{
    unsigned char *base = BananaTriple_Tick_HeldAndHoming_32to36_rodata_8032EFF0;
    Vec3 n;
    int landed;
    float groundY;
    float pitch;
    float roll;
    int result;
    char *chained;

    switch (S8(0xc9)) {
    case 0:
        if (I(8) == 0x35 || I(8) == 0x36 || I(0x10) != 0) {
            if (I(8) == 0x35 || I(8) == 0x36) {
                Item_SpawnGroundExplosionAndFX(self);
            } else {
                Item_BendVelocityByGroundProbe(self + 0xb8, *(Vec3 *)(self + 0xa0), F(0xb0), lbl_806D5DAC,
                                               lbl_806D5D90);
                KartDriver_TransformWorldToLocalY0(self + 0xa0, *(Vec3 *)(self + 0xa0), WP(0x98));
            }
            F(0xc4) = lbl_806D5D94;
            F(0x2c) = lbl_806D5DAC;
            self[0x28] = 0;
            self[0xc9] = 2;
            self[0xca] = 0;
            break;
        }
        self[0xc9]++;
        self[0xca] = 0;
        /* fallthrough */
    case 1:
        switch (S8(0xca)) {
        case 0:
            w[0] = 0;
            if (I(8) != 0x34) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 5, lbl_806D5D90);
                SpriteSlot_SetScale(self + 0x14, lbl_806D5D90);
            } else {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, lbl_806D5D90);
                SpriteSlot_SetScale(self + 0x14, lbl_806D5D90);
            }
            self[0x28] = 1;
            F(0x2c) = lbl_806D5D90;
            self[0xca]++;
            /* fallthrough */
        case 1:
            if (I(8) != 0x34) {
                Item_RenderCharacterScaledFromJoint12(self, *(Vec3 *)(base + 0x3fc), *(Vec3 *)(base + 0x408), 1,
                                                      lbl_806D5DB8);
            } else {
                Item_RenderCharacterScaledFromJoint12(self, *(Vec3 *)(base + 0x414), *(Vec3 *)(base + 0x420), 1,
                                                      lbl_806D5DBC);
            }
            if (FinalLapCoinJump_CheckActiveForObject(WP(0x98))) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(w + 0xa0)) {
            case 1:
                self[0x28] = 1;
                w[0xa0] = 0;
                w[0] = 1;
                Item_InitLaunchFromKart(self, 0, lbl_806D5DAC, lbl_806D5D90);
                self[0xc9]++;
                self[0xca] = 0;
                break;
            case 2:
                w[0xa0] = 0;
                self[0x28] = 0;
                self[0xc8] = 3;
                self[0xc9] = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        switch (S8(0xca)) {
        case 0:
            self[0x28] = 1;
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8d] = 1;
            self[0x3c] = 1;
            SpriteSlot_SetJointVisibilityByName(self + 0x14, BananaTriple_data_804211B0[*(unsigned char *)(w + 3)], 0x10, 0);
            SpriteSlot_SetJointVisibilityByName(self + 0x14, BananaTriple_data_804211B0[*(unsigned char *)(w + 3)] + 0x40, 0x10,
                                                1);
            ItemObject_GetGroundTypeAt(*(Vec3 *)(self + 0xa0), (float *)(w + 0x18), 0);
            WF(0x18) = F(0xa4) - WF(0x18);
            WU(0xc) = 0;
            if (I(8) == 0x35 || I(8) == 0x36) {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, lbl_806D5D90);
                SpriteSlot_SetScale(self + 0x14, lbl_806D5DAC);
                WU(4) = 300;
                WU(8) = 60;
                self[0xca] = 1;
            } else {
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 4, lbl_806D5D90);
                SpriteSlot_SetScale(self + 0x14, lbl_806D5DAC);
                WU(4) = 0;
                WU(8) = 0;
                self[0xca] = 2;
            }
            break;
        case 1:
            Item_HomingScanAndSteer(self, self + 0xb0, 0);
            Item_AccelClampVelocity(self, g_ccClass == 0 ? lbl_806D5DC0 : lbl_806D5DC4,
                                    g_ccClass == 0 ? lbl_806D5DAC : lbl_806D5DA4);
            if (WU(4) == 0) {
                self[0xca]++;
            }
            break;
        case 2:
            F(0xbc) = F(0xbc) + lbl_806D5DB4;
            if (I(8) == 0x32 || I(8) == 0x33 || I(8) == 0x34) {
                Item_HomingScanAndSteer(self, self + 0xb0, 1);
            }
            break;
        case 3:
            F(0xbc) = F(0xbc) + lbl_806D5DB4;
            break;
        }
        if (WU(8) == 0) {
            BananaTriple_SetIdleAnim(self);
        }
        if (I(8) != 0x34) {
            Item_DecayVelocityScalar(self, lbl_806D5D94);
        } else {
            Item_DecayVelocityScalar(self, lbl_806D5D98);
        }
        result = ItemCollision_Check(self);
        switch (result) {
        case 1:
            fn_801B1D5C(WP(0x98), ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(8)),
                        S8(0xca) == 3 ? 1 : 0);
            /* fallthrough */
        case 2:
            if (result == 2) {
                fn_801B1660(WP(0x98), ItemTracker_GetTargetKart(self));
            }
            /* fallthrough */
        case 3:
            if (result == 3) {
                fn_801B158C(WP(0x98), ItemTracker_GetTargetKart(self));
            }
            fn_801B14B8(WP(0x98), ItemTracker_GetTargetKart(self));
            if (U8(0xca) != 3 && result == 3) {
                *(int *)(w + 0x7c) = 0;
                Item_ComputeYawRelativeApproach(self + 0xb8, ItemTracker_GetTargetKart(self),
                                                *(Vec3 *)(self + 0xa0), *(Vec3 *)(self + 0xb8));
                F(0xb0) = Vec3_ToYaw(self + 0xb8);
                ItemTracker_SetTrackPhase(self, 0);
                WU(0xc) = 5;
                break;
            }
            WP(0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            BananaTriple_SetIdleAnim(self);
            if (U8(0xca) == 1) {
                w[1] = 1;
            } else {
                w[1] = 0;
            }
            if (result == 1) {
                w[2] = 1;
            } else {
                w[2] = 0;
            }
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 0;
            return;
        case 4:
            fn_801B14B8(WP(0x98), ItemTracker_GetTargetKart(self));
            WP(0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            BananaTriple_SetIdleAnim(self);
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (WU(0xc) == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (U8(0x8d) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            BananaTriple_SetIdleAnim(self);
            if (U8(0x8e) == 1) {
                Vec3_Add_DestFirst(self + 0xb8, self + 0xb8, self + 0x90);
                F(0xbc) = lbl_806D5DA4;
                F(0xb8) = F(0xb8) * lbl_806D5DC8;
                F(0xc0) = F(0xc0) * lbl_806D5DC8;
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
        if (U8(0xca) != 3 && Item_CheckWallCollision(self, &n, 0)) {
            if (I(8) != 0x34) {
                Item_BounceOffWall(self, n, 0, 2, lbl_806D5DC8, lbl_806D5D90);
            } else {
                Item_BounceOffWall(self, n, 0, 3, lbl_806D5DC8, lbl_806D5D90);
            }
            BananaTriple_SetIdleAnim(self);
            if (U8(0xca) == 1) {
                WU(4) = 0;
            }
        }
        if (S8(0xca) == 0 || S8(0xca) == 1) {
            result = Item_AdvanceProjectileSimple(self, w + 0x18, lbl_806D5DCC, lbl_806D5DCC);
            if (I(8) == 0x35 || I(8) == 0x36) {
                F(0xac) = BuildOrientationFromYaw(lbl_806D5DD0 + Vec3_ToPitch(self + 0xb8));
            } else {
                F(0xac) = Vec3_ToPitch(self + 0xb8);
            }
        } else {
            if (I(8) != 0x34) {
                result = Item_AdvanceFallingDrop(self, lbl_806D5DD4, &landed, &groundY);
            } else {
                result = Item_AdvanceFallingDrop(self, lbl_806D5DD4, &landed, &groundY);
            }
            if (landed != 0) {
                if (U8(0xca) == 2) {
                    if (I(8) != 0x34) {
                        DrawEffect_ItemHitBurst_Spawn(*(Vec3 *)(self + 0xa0), *(Vec3 *)(self + 0xb8), 2);
                    } else {
                        DrawEffect_ItemHitBurst_Spawn(*(Vec3 *)(self + 0xa0), *(Vec3 *)(self + 0xb8), 3);
                    }
                    WU(4) = 900;
                    self[0xca] = 3;
                    ItemHitRegistry_AddEntry(self);
                }
                BananaTriple_SetIdleAnim(self);
                GetSpawnPosition(self + 0xb8, lbl_806D5D90, lbl_806D5D90, lbl_806D5D90);
            }
            pitch = Item_ProbeForwardGroundPitch(*(Vec3 *)(self + 0xa0), F(0xb0), lbl_806D5DD8, F(0xa4) - groundY);
            F(0xac) = AngleStepTowards_Shortest(F(0xac), pitch, lbl_806D5DA0);
            roll = Item_ProbeLateralGroundPitch(*(Vec3 *)(self + 0xa0), F(0xb0), lbl_806D5DD8, F(0xa4) - groundY);
            F(0xb4) = AngleStepTowards_Shortest(F(0xb4), roll, lbl_806D5DA0);
        }
        if (result == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            BananaTriple_SetIdleAnim(self);
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 9;
            return;
        }
        if (U8(0xca) == 3 && ItemHitRegistry_RemoveEntry(self, WU(4), 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            chained = *(char **)(w + 0x4c);
            if (chained != 0) {
                chained[0xc9] = 1;
            }
            *(char **)(w + 0x4c) = 0;
            if (I(8) != 0x35 && I(8) != 0x36) {
                ItemObject_DecrementCategoryBudget(self);
            }
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}
#pragma use_lmw_stmw reset
#pragma exceptions reset

}

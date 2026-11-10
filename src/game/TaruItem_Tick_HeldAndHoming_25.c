/* TaruItem_Tick_HeldAndHoming_25 (0x800EA0E8): the barrel item while held
 * on the kart (state 1) and while rolling/homing after launch (state 2).
 * Structural twin of EggItem_Tick_HeldAndHoming_3B3C; raw offsets as there.
 * sub = self + 0xec: [0] render, [1] hit flag, [2] wall bounces left,
 * +4 life timer, +8 landing burst, +0xc track timer, +0x30 SE 0xbd channel. */
#include "game/types/Vec3.h"

extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern float BuildOrientationFromYaw(float yaw);
#ifdef __MWERKS__
extern void DrawEffect_ItemHitOriented_Spawn(Vec3 pos, Vec3 vel, int mode);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void DrawEffect_ItemHitOriented_Spawn(Vec3 *, Vec3 *, int);
static inline void DrawEffect_ItemHitOriented_Spawn_ByValue(Vec3 pos, Vec3 vel, int mode) { DrawEffect_ItemHitOriented_Spawn(&pos, &vel, mode); }
#define DrawEffect_ItemHitOriented_Spawn DrawEffect_ItemHitOriented_Spawn_ByValue
#endif
extern float FAbs_FloatAsDouble(float x);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *kart);
#ifdef __MWERKS__
extern void GetSpawnPosition(float x, float y, float z, float *out);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void GetSpawnPosition(float *, float, float, float);
static inline void GetSpawnPosition_Reordered(float x, float y, float z, float *out) { GetSpawnPosition(out, x, y, z); }
#define GetSpawnPosition GetSpawnPosition_Reordered
#endif
extern int ItemAlias_HitRemapLookup(int itemId);
extern int ItemCollision_Check(void *self);
extern void ItemTracker_AcquireLock(void *self);
extern void *ItemTracker_GetTargetKart(void *self);
extern void ItemTracker_ReleaseLock(void *self);
extern void ItemTracker_SetTrackPhase(void *self, int enable);
extern void Item_AccelClampVelocity(void *self, float accel, float maxv);
#ifdef __MWERKS__
extern int Item_AdvanceFallingDrop(void *self, float gravity, int *landed, float *groundY);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern int Item_AdvanceFallingDrop(void *, int *, float *, float);
static inline int Item_AdvanceFallingDrop_Reordered(void *self, float gravity, int *landed, float *groundY) { return Item_AdvanceFallingDrop(self, landed, groundY, gravity); }
#define Item_AdvanceFallingDrop Item_AdvanceFallingDrop_Reordered
#endif
extern void Item_BounceOffWall(float k1, float k2, void *self, Vec3 normal, int se, int flag);
extern int Item_CheckWallCollision(void *self, float *out, int flag);
#ifdef __MWERKS__
extern void Item_ComputeYawRelativeApproach(float *vel, void *target, Vec3 pos, Vec3 curVel);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_ComputeYawRelativeApproach(float *, void *, Vec3 *, Vec3 *);
static inline void Item_ComputeYawRelativeApproach_ByValue(float *vel, void *target, Vec3 pos, Vec3 curVel) { Item_ComputeYawRelativeApproach(vel, target, &pos, &curVel); }
#define Item_ComputeYawRelativeApproach Item_ComputeYawRelativeApproach_ByValue
#endif
extern void Item_DecayVelocityScalar(void *item, float scalar);
#ifdef __MWERKS__
extern void Item_InitLaunchFromKart(float k1, float k2, void *self, float *vel);
#else
/* The definition orders its int and float parameters differently; see docs/notes/port_abi.md. */
extern void Item_InitLaunchFromKart(void *, float *, float, float);
static inline void Item_InitLaunchFromKart_Reordered(float k1, float k2, void *self, float *vel) { Item_InitLaunchFromKart(self, vel, k1, k2); }
#define Item_InitLaunchFromKart Item_InitLaunchFromKart_Reordered
#endif
#ifdef __MWERKS__
extern float Item_ProbeLateralGroundPitch(Vec3 pos, float yaw, float a, float b);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeLateralGroundPitch(Vec3 *, float, float, float);
static inline float Item_ProbeLateralGroundPitch_ByValue(Vec3 pos, float yaw, float a, float b) { return Item_ProbeLateralGroundPitch(&pos, yaw, a, b); }
#define Item_ProbeLateralGroundPitch Item_ProbeLateralGroundPitch_ByValue
#endif
extern void Item_RenderCharacterScaledFromJoint12(void *self, Vec3 ofs, Vec3 rot, int flag, float scale);
extern float *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(float *out, float *mtx);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec3 pos, int ch);
#ifdef __MWERKS__
extern void SoundMgr_PlaySE_WithChannel(int se, Vec3 pos, int ch);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SoundMgr_PlaySE_WithChannel(int, Vec3 *, int);
static inline void SoundMgr_PlaySE_WithChannel_ByValue(int se, Vec3 pos, int ch) { SoundMgr_PlaySE_WithChannel(se, &pos, ch); }
#define SoundMgr_PlaySE_WithChannel SoundMgr_PlaySE_WithChannel_ByValue
#endif
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern void Vec2_RotateY(float *dst, float *src, float yaw);
extern float Vec3_ToYaw(float *v);
extern void fn_801B129C(float *pos);
extern void fn_801B14B8(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B1D5C(void *driver, void *target, int remap, int flag);

extern int g_ccClass;
extern const float lbl_806D5DE0;
extern const float lbl_806D5DE8;
extern const float lbl_806D5DEC;
extern const float lbl_806D5DF4;
extern const float lbl_806D5DF8;
extern const float lbl_806D5DFC;
extern const float lbl_806D5E00;
extern const float lbl_806D5E04;
extern const float lbl_806D5E08;
extern const float lbl_806D5E0C;
extern const float lbl_806D5E10;
extern const float lbl_806D5E14;
extern const float lbl_806D5E18;
extern const float lbl_806D5E1C;
extern const float lbl_806D5E20;
extern Vec3 TaruItem_Tick_HeldAndHoming_25_rodata_8032F440;
extern Vec3 TaruItem_Tick_HeldAndHoming_25_rodata_8032F44C;

static inline void TaruItem_StopRollSE(char *sub)
{
    if (*(int *)(sub + 0x30) >= 0) {
        SoundMgr_StopSE_OrSpecial(0xbd, *(int *)(sub + 0x30));
        *(int *)(sub + 0x30) = -1;
    }
}

#pragma exceptions on
void TaruItem_Tick_HeldAndHoming_25(char *self, char *sub)
{
    Vec3 wallResult;
    int landed;
    float groundY;
    int collision;
    float speedCap;
    float range;

    switch (*(signed char *)(self + 0xc9)) {
    case 0:
        *(unsigned char *)(self + 0xc9) = *(unsigned char *)(self + 0xc9) + 1;
        self[0xca] = 0;
        /* fallthrough */
    case 1:
        switch (*(signed char *)(self + 0xca)) {
        case 0:
            sub[0] = 0;
            self[0x28] = 1;
            *(float *)(self + 0x2c) = lbl_806D5DE0;
            *(unsigned char *)(self + 0xca) = *(unsigned char *)(self + 0xca) + 1;
            /* fallthrough */
        case 1:
            Item_RenderCharacterScaledFromJoint12(self, TaruItem_Tick_HeldAndHoming_25_rodata_8032F440, TaruItem_Tick_HeldAndHoming_25_rodata_8032F44C, 1, lbl_806D5E18);
            if (FinalLapCoinJump_CheckActiveForObject(*(void **)(sub + 0x98)) != 0) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (*(signed char *)(sub + 0xa0)) {
            case 1:
                self[0x28] = 1;
                sub[0xa0] = 0;
                sub[0] = 1;
                Item_InitLaunchFromKart(lbl_806D5DE8, lbl_806D5E1C, self, (float *)(sub + 0x34));
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
            sub[1] = 0;
            sub[2] = 8;
            *(int *)(sub + 0x30) = -1;
            *(unsigned char *)(self + 0xca) = *(unsigned char *)(self + 0xca) + 1;
            /* fallthrough */
        case 1:
            break;
        }
        *(float *)(self + 0xbc) = *(float *)(self + 0xbc) + lbl_806D5DF4;
        range = (g_ccClass == 0) ? lbl_806D5DF8 : lbl_806D5DFC;
        speedCap = (g_ccClass == 0) ? lbl_806D5E00 : lbl_806D5E04;
        Item_AccelClampVelocity(self, speedCap, range);
        fn_801B129C((float *)(self + 0xa0));
        *(float *)(self + 0xac) = BuildOrientationFromYaw(lbl_806D5DEC + *(float *)(self + 0xac));
        *(float *)(self + 0xb0) =
            AngleStepTowards_Shortest(*(float *)(self + 0xb0), Vec3_ToYaw((float *)(self + 0xb8)), lbl_806D5E08);
        Item_DecayVelocityScalar(self, lbl_806D5DE8);
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
            TaruItem_StopRollSE(sub);
            if (collision == 1) {
                sub[1] = 1;
            } else {
                sub[1] = 0;
            }
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 0;
            return;
        case 3:
            fn_801B158C(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            Item_ComputeYawRelativeApproach((float *)(self + 0xb8), ItemTracker_GetTargetKart(self),
                                            *(Vec3 *)(self + 0xa0), *(Vec3 *)(self + 0xb8));
            *(float *)(self + 0xb0) = Vec3_ToYaw((float *)(self + 0xb8));
            ItemTracker_SetTrackPhase(self, 0);
            *(int *)(sub + 0xc) = 5;
            break;
        case 4:
            fn_801B14B8(*(void **)(sub + 0x98), ItemTracker_GetTargetKart(self));
            *(void **)(sub + 0x9c) = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            TaruItem_StopRollSE(sub);
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
            GetSpawnPosition(lbl_806D5DE0, lbl_806D5DE0, lbl_806D5DE0, (float *)(self + 0xb8));
            TaruItem_StopRollSE(sub);
            self[0xc8] = 2;
            self[0xc9] = 0;
            self[0xcb] = 4;
            return;
        }
        if (Item_CheckWallCollision(self, (float *)&wallResult, 0) != 0) {
            if (*(unsigned char *)(sub + 2) != 0) {
                *(unsigned char *)(sub + 2) = *(unsigned char *)(sub + 2) - 1;
            }
            if (*(unsigned char *)(sub + 2) != 0) {
                Item_BounceOffWall(lbl_806D5E0C, lbl_806D5DE0, self, wallResult, 0, 3);
            } else {
                ItemTracker_ReleaseLock(self);
                self[0x8d] = 0;
                GetSpawnPosition(lbl_806D5DE0, lbl_806D5DE0, lbl_806D5DE0, (float *)(self + 0xb8));
                TaruItem_StopRollSE(sub);
                self[0xc8] = 2;
                self[0xc9] = 0;
                self[0xcb] = 7;
                return;
            }
        }
        if (Item_AdvanceFallingDrop(self, lbl_806D5E10, &landed, &groundY) != 0) {
            if (landed != 0) {
                if (*(unsigned int *)(sub + 8) == 0) {
                    DrawEffect_ItemHitOriented_Spawn(*(Vec3 *)(self + 0xa0), *(Vec3 *)(self + 0xb8), 3);
                    *(int *)(sub + 8) = 3;
                }
                if (*(unsigned char *)(sub + 1) != 0) {
                    *(float *)(self + 0xbc) = *(float *)(self + 0xbc) * lbl_806D5DF4;
                } else {
                    *(float *)(self + 0xbc) = *(float *)(self + 0xbc) * lbl_806D5E20;
                }
                sub[1] = 1;
                *(float *)(self + 0xb4) = Item_ProbeLateralGroundPitch(
                    *(Vec3 *)(self + 0xa0), *(float *)(self + 0xb0), lbl_806D5DE8, *(float *)(self + 0xa4) - groundY);
                if (lbl_806D5DEC < FAbs_FloatAsDouble(*(float *)(self + 0xb4))) {
                    if (lbl_806D5DE0 < *(float *)(self + 0xb4)) {
                        Vec2_RotateY((float *)(self + 0xb8), (float *)(self + 0xb8),
                                     lbl_806D5E14 * -(*(float *)(self + 0xb4) - lbl_806D5DEC));
                    } else {
                        Vec2_RotateY((float *)(self + 0xb8), (float *)(self + 0xb8),
                                     lbl_806D5E14 * -(lbl_806D5DEC + *(float *)(self + 0xb4)));
                    }
                }
                if (*(int *)(sub + 0x30) < 0) {
                    *(int *)(sub + 0x30) = SoundMgr_CountActiveSEInstances(0xbd);
                    if (*(int *)(sub + 0x30) >= 0) {
                        SoundMgr_PlaySE_Positional(0xbd, *(Vec3 *)(self + 0xa0), *(int *)(sub + 0x30));
                    }
                } else {
                    SoundMgr_PlaySE_WithChannel(0xbd, *(Vec3 *)(self + 0xa0), *(int *)(sub + 0x30));
                }
            } else {
                TaruItem_StopRollSE(sub);
            }
        } else {
            ItemTracker_ReleaseLock(self);
            self[0x8d] = 0;
            TaruItem_StopRollSE(sub);
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
        TaruItem_StopRollSE(sub);
        self[0xc8] = 2;
        self[0xc9] = 0;
        self[0xcb] = 5;
        return;
    }
}
#pragma exceptions reset

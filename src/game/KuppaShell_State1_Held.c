/* KuppaShell_State1_Held (0x800F17F4): held and flying states of the Kuppa
 * (Bowser) shell. Sub-state 1 holds it in the kart's hand until it is
 * thrown, sub-state 2 rolls it forward, bouncing off walls a few times and
 * hopping along the ground, until a kart hit, a wall stop, a fall or a
 * timeout ends the flight. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct KuppaShellWork {
    unsigned char bounces;
    unsigned char pad1[3];
    unsigned int timers[4];
    unsigned char pad14[0x30 - 0x14];
    int seCh;
    Vec launchPos;
    unsigned char pad40[0x98 - 0x40];
    void *driver;
    void *target;
    signed char launch;
} KuppaShellWork;

extern int g_ccClass;
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *mtx);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern void fn_801B129C(void *pos);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, int b);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec pos, Vec v);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *out, void *groundY, float f);
extern void DrawEffect_ItemHitOriented_Spawn(Vec pos, Vec vel, int mode);
extern float Vec3_ToYaw(const void *v);
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);
extern float FAbs_FloatAsDouble(float x);
extern void Vec2_RotateY(void *dst, void *src, float a);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define C8(o) (*(char *)(self + (o)))

static inline void KuppaShell_StopRollSE(KuppaShellWork *w)
{
    if (w->seCh >= 0) {
        SoundMgr_StopSE_OrSpecial(0xB2, w->seCh);
        w->seCh = -1;
    }
}

void KuppaShell_State1_Held(unsigned char *self, KuppaShellWork *w)
{
    Vec n;
    int hit;
    int landed;
    float gy;

    switch (S8(0xC9)) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 1.5f, 0.17453289f, 1.4f);
            if (FinalLapCoinJump_CheckActiveForObject(w->driver)) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (w->launch) {
            case 1:
                self[0x28] = 1;
                w->launch = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 0);
                Item_InitLaunchFromKart(self, &w->launchPos, 5.0f, -0.17453289f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                w->launch = 0;
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor(&w->launchPos, KartDriver_GetJointByIdx(w->driver, 12));
                break;
            }
            break;
        }
        break;
    case 2:
        switch (S8(0xCA)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8D] = 1;
            self[0x3C] = 1;
            w->timers[0] = 600;
            w->timers[2] = 0;
            w->timers[1] = 0;
            w->bounces = 8;
            w->seCh = -1;
            self[0xCA]++;
        case 1:
            break;
        }
        F(0xBC) += -0.2f;
        Item_AccelClampVelocity(self, g_ccClass == 0 ? 12.0f : 17.0f, g_ccClass == 0 ? 1.0f : 2.0f);
        fn_801B129C(self + 0xA0);
        F(0xB0) = BuildOrientationFromYaw(0.2617993f + F(0xB0));
        Item_DecayVelocityScalar(self, 8.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(w->driver, ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(w->driver, ItemTracker_GetTargetKart(self));
            }
            if (hit == 1) {
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            ItemTracker_SetTrackPhase(self, 1);
            break;
        case 3:
            fn_801B158C(w->driver, ItemTracker_GetTargetKart(self));
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
            ItemTracker_SetTrackPhase(self, 0);
            w->timers[2] = 5;
            break;
        case 4:
            fn_801B14B8(w->driver, ItemTracker_GetTargetKart(self));
            w->target = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            KuppaShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (w->timers[2] == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (C8(0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
            KuppaShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 4;
            return;
        }
        if (Item_CheckWallCollision(self, &n, 0)) {
            if (w->bounces != 0) {
                w->bounces--;
            }
            if (w->bounces != 0) {
                Item_BounceOffWall(self, n, 0xCB, 3, 0.5f, 0.0f);
            } else {
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                KuppaShell_StopRollSE(w);
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 7;
                return;
            }
        }
        if (Item_AdvanceFallingDrop(self, &landed, &gy, 2.5f)) {
            if (landed != 0) {
                if (w->timers[1] == 0) {
                    DrawEffect_ItemHitOriented_Spawn(*(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8), 3);
                    w->timers[1] = 3;
                }
                F(0xBC) *= -0.1f;
                Item_ProbeLateralGroundPitch(*(Vec *)(self + 0xA0), Vec3_ToYaw(self + 0xB8), 5.0f, F(0xA4) - gy);
                if (0.2617993f < FAbs_FloatAsDouble(F(0xB4))) {
                    if (0.0f < F(0xB4)) {
                        Vec2_RotateY(self + 0xB8, self + 0xB8, 0.1f * -(F(0xB4) - 0.2617993f));
                    } else {
                        Vec2_RotateY(self + 0xB8, self + 0xB8, 0.1f * -(0.2617993f + F(0xB4)));
                    }
                }
            }
        } else {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            KuppaShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 9;
            return;
        }
        if (w->timers[0] == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            KuppaShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 5;
            return;
        }
        if (w->seCh < 0) {
            w->seCh = SoundMgr_CountActiveSEInstances(0xB2);
            if (w->seCh >= 0) {
                SoundMgr_PlaySE_Positional(0xB2, *(Vec *)(self + 0xA0), w->seCh);
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0xB2, *(Vec *)(self + 0xA0), w->seCh);
        }
        break;
    }
}

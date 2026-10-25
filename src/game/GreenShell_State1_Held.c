/* GreenShell_State1_Held (0x800EF2DC): held and flying states of the
 * green shell items (kinds 0x3D..0x3F). Sub-state 1 holds the shell in the
 * kart's hand until it is thrown, sub-state 2 rolls it along the ground
 * with a spin, bouncing off walls a few times and leaving the flying
 * state on a kart hit, a wall stop, a fall or a timeout. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct GreenShellWork {
    unsigned char bounces;
    unsigned char pad1[3];
    unsigned int timers[4];
    float groundY;
    float spin;
    float phase;
    unsigned char pad20[0x30 - 0x20];
    int seCh;
    Vec launchPos;
    unsigned char pad40[0x4C - 0x40];
    unsigned char *eff;
    unsigned char pad50[0x5C - 0x50];
    void *gabyou;
    unsigned char pad60[0x98 - 0x60];
    void *driver;
    void *target;
    signed char launch;
} GreenShellWork;

extern int g_ccClass;
extern void Item_BendVelocityByGroundProbe(void *vel, Vec pos, float yaw, float speed, float pitch);
extern void KartDriver_TransformWorldToLocalY0(void *dst, Vec src, void *kart);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void *ItemObject_AllocGabyou(void);
extern void Item_RenderFlyingFromKart(unsigned char *self, void *obj, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void SpriteSlot_Container_Free(void *self);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *mtx);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void Effect_Cluster16_Update(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void Item_AccelClampVelocity(unsigned char *self, float accel, float maxv);
extern void fn_801B129C(void *pos);
extern float BuildOrientationFromYaw(float yaw);
extern double sin(double x);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void Item_ComputeYawRelativeApproach(void *vel, void *target, Vec pos, Vec v);
extern void SoundMgr_StopSE_OrSpecial(int se, int ch);
extern int SoundMgr_CountActiveSEInstances(int se);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void SoundMgr_PlaySE_WithChannel(int se, Vec pos, int ch);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);
extern int Item_AdvanceProjectileGravity(unsigned char *self, float *groundY, float a, float b, float c);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define C8(o) (*(char *)(self + (o)))

static inline float sinf(float x)
{
    return sin(x);
}

static inline void GreenShell_StopRollSE(GreenShellWork *w)
{
    if (w->seCh >= 0) {
        SoundMgr_StopSE_OrSpecial(0x80, w->seCh);
        w->seCh = -1;
    }
}

void GreenShell_State1_Held(unsigned char *self, GreenShellWork *w)
{
    Vec n;
    int hit;

    switch (S8(0xC9)) {
    case 0:
        if (I(0x10) != 0) {
            Item_BendVelocityByGroundProbe(self + 0xB8, *(Vec *)(self + 0xA0), F(0xB0), g_ccClass == 0 ? 17.0f : 22.0f, 0.0f);
            KartDriver_TransformWorldToLocalY0(self + 0xA0, *(Vec *)(self + 0xA0), w->driver);
            F(0xC4) = 1.75f;
            F(0x2C) = 1.0f;
            self[0x28] = 1;
            self[0xC9] = 2;
            self[0xCA] = 0;
            break;
        }
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            w->gabyou = ItemObject_AllocGabyou();
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            Item_RenderFlyingFromKart(self, w->gabyou, 1, 0.8f, 0.5235987f, 1.0f);
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
                SpriteSlot_Container_Free(w->gabyou);
                w->gabyou = 0;
                Mtx44_GetTranslation_RowMajor(self + 0xA0, KartDriver_GetJointByIdx(w->driver, 12));
                Item_InitLaunchFromKart(self, &w->launchPos, 5.0f, 0.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                w->launch = 0;
                SpriteSlot_Container_Free(w->gabyou);
                w->gabyou = 0;
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
            ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &w->groundY, 0);
            w->groundY = F(0xA4) - w->groundY;
            if (I(0x8) != 0x3E) {
                w->bounces = 8;
            } else {
                w->bounces = 1;
            }
            w->spin = 0.087266445f;
            w->phase = 0.0f;
            w->timers[0] = 300;
            w->timers[1] = 0;
            w->eff = DrawEffect_SpawnDirect(Effect_Cluster16_Update);
            if (w->eff != 0) {
                switch (I(0x8)) {
                case 0x3D:
                    *(int *)(w->eff + 0x10) = 0;
                    break;
                case 0x3E:
                    *(int *)(w->eff + 0x10) = 1;
                    break;
                case 0x3F:
                    *(int *)(w->eff + 0x10) = 0;
                    break;
                }
                switch (I(0x8)) {
                case 0x3D:
                    GetSpawnPosition(w->eff + 0x30, 0.0f, 1.0f, 0.0f);
                    break;
                case 0x3E:
                    GetSpawnPosition(w->eff + 0x30, 0.2f, 0.0f, 1.0f);
                    break;
                case 0x3F:
                    GetSpawnPosition(w->eff + 0x30, 1.0f, 1.0f, 0.0f);
                    break;
                }
            }
            w->seCh = -1;
            self[0xCA]++;
        case 1:
            break;
        }
        Item_AccelClampVelocity(self, g_ccClass == 0 ? 17.0f : 22.0f, g_ccClass == 0 ? 1.0f : 2.0f);
        fn_801B129C(self + 0xA0);
        w->spin += 0.034906577f;
        if (1.0471973f < w->spin) {
            w->spin = 1.0471973f;
        }
        F(0xB0) = BuildOrientationFromYaw(F(0xB0) + w->spin);
        w->phase = BuildOrientationFromYaw(0.5235987f + w->phase);
        F(0xAC) = 0.785398f * sinf(w->phase);
        Item_DecayVelocityScalar(self, 1.75f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(w->driver, ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(w->driver, ItemTracker_GetTargetKart(self));
            }
            w->target = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (hit == 1) {
                w->bounces = 1;
            } else {
                w->bounces = 0;
            }
            GreenShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 0;
            return;
        case 3:
            fn_801B158C(w->driver, ItemTracker_GetTargetKart(self));
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
            ItemTracker_SetTrackPhase(self, 0);
            w->timers[1] = 5;
            break;
        case 4:
            fn_801B14B8(w->driver, ItemTracker_GetTargetKart(self));
            w->target = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            GreenShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(self, 1);
            break;
        }
        if (w->timers[1] == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (C8(0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (C8(0x8E) == 1) {
                Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
                F(0xBC) = 2.0f;
                F(0xB8) *= 0.1f;
                F(0xC0) *= 0.1f;
                GreenShell_StopRollSE(w);
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 4;
                return;
            }
            GreenShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 6;
            return;
        }
        if (Item_CheckWallCollision(self, &n, 0)) {
            if (w->bounces != 0) {
                w->bounces--;
            }
            if (w->bounces != 0) {
                Item_BounceOffWall(self, n, 0xCB, 2, 0.8f, 0.0f);
            } else {
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                Item_BounceOffWall(self, n, 0, 0, 0.8f, 0.0f);
                GreenShell_StopRollSE(w);
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 7;
                return;
            }
        }
        if (!Item_AdvanceProjectileGravity(self, &w->groundY, 7.0f, 1.0f, -0.2f)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            GreenShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 9;
            return;
        }
        if (w->timers[0] == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            GreenShell_StopRollSE(w);
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 5;
            return;
        }
        if (w->seCh < 0) {
            w->seCh = SoundMgr_CountActiveSEInstances(0x80);
            if (w->seCh >= 0) {
                SoundMgr_PlaySE_Positional(0x80, *(Vec *)(self + 0xA0), w->seCh);
            }
        } else {
            SoundMgr_PlaySE_WithChannel(0x80, *(Vec *)(self + 0xA0), w->seCh);
        }
        break;
    }
}

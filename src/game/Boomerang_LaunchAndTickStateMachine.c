/* Boomerang_LaunchAndTickStateMachine (0x800FF18C): held, flying and
 * landed states of the boomerang item and its partner object. Sub-state 1
 * holds it in the kart's hand until it is thrown, sub-state 2 flies it
 * until it lands, and sub-state 3 lets the partner spin on the ground,
 * pacing its animation along a keyframe curve, until its timer runs out
 * and the return flight starts. A kart hit or a kick on either object ends
 * the flight. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct PaceKey {
    float t[4];
    float v[4];
} PaceKey;

typedef struct BoomerangWork {
    unsigned char thrown;
    unsigned char hits;
    unsigned char pad2[2];
    unsigned int timers[4];
    float pace;
    unsigned char pad18[0x5C - 0x18];
    unsigned char *sub;
    unsigned char pad60[0x98 - 0x60];
    void *driver;
    void *target;
    signed char launch;
} BoomerangWork;

extern const PaceKey lbl_80330794;
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern float Mtx44_GetYawOfPosZ_Padded(void *mtx);
extern float BuildOrientationFromYaw(float yaw);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, int id, int flag);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void Vec3_Copy(void *dst, void *src);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *out, void *groundY, float f);
extern void DrawEffect_ItemHitBurst_Spawn(Vec pos, Vec vel, int kind);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void Boomerang_ReturnAndAcquireTargetTick(unsigned char *self, BoomerangWork *w);
extern float Item_ProbeForwardGroundPitch(Vec pos, float yaw, float a, float b);
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern int ItemCollision_Check(unsigned char *self);
extern void ItemObject_DispatchVtable18_GetState(void *kart);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, int b);
extern void SpriteSlot_Container_Free(void *self);

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define C8(o) (*(char *)(self + (o)))

static inline void PaceKey_Eval(PaceKey *k, float x, float *out)
{
    int j;

    if (x <= k->t[0]) {
        *out = k->v[0];
    } else if (k->t[3] <= x) {
        *out = k->v[3];
    } else {
        for (j = 0; j < 3; j++) {
            if (k->t[j] < x && x <= k->t[j + 1]) {
                *out = (x - k->t[j]) * ((k->v[j + 1] - k->v[j]) / (k->t[j + 1] - k->t[j])) + k->v[j];
            }
        }
    }
}

void Boomerang_LaunchAndTickStateMachine(unsigned char *self, BoomerangWork *w)
{
    PaceKey k;
    Vec n;
    int kicked;
    int hit;
    int landed;
    float x;
    float p;
    float p2;

    switch (S8(0xC9)) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            w->thrown = 0;
            if (w->sub != 0) {
                SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 0, 0.0f);
            }
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, 0.0f, 2.8797927f, 1.5f);
            F(0xB0) = BuildOrientationFromYaw(2.8797927f + Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(w->driver)));
            if (w->sub != 0) {
                *(float *)(w->sub + 0xB0) = F(0xB0);
            }
            if (FinalLapCoinJump_CheckActiveForObject(w->driver)) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (w->launch) {
            case 1:
                self[0x28] = 1;
                w->launch = 0;
                w->thrown = 1;
                Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
                if (w->sub != 0) {
                    *(float *)(w->sub + 0xB0) = 3.141592f + F(0xB0);
                }
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                w->launch = 0;
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
                break;
            }
            break;
        }
        break;
    case 2:
        switch (S8(0xCA)) {
        case 0:
            self[0x8D] = 1;
            if (w->sub != 0) {
                w->sub[0x8D] = 1;
            }
            self[0x3C] = 1;
            self[0xCA]++;
            ItemHitRegistry_AddEntry(self);
        case 1:
            F(0xBC) += -0.1f;
            Item_HomingScanAndSteer(self, self + 0xB0, 1);
            Item_DecayVelocityScalar(self, 4.5f);
            kicked = 0;
            if (C8(0x8D) == 2) {
                kicked = 1;
            }
            if (w->sub != 0 && *(char *)(w->sub + 0x8D) == 2) {
                Vec3_Copy(self + 0x90, w->sub + 0x90);
                kicked = 1;
            }
            if (kicked) {
                self[0x8D] = 0;
                if (w->sub != 0) {
                    w->sub[0x8D] = 0;
                }
                SoundMgr_PlaySE_Positional(0xCB, *(Vec *)(self + 0xA0), 0);
                Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
                F(0xBC) = 1.0f;
                F(0xB8) *= 0.1f;
                F(0xC0) *= 0.1f;
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 4;
                break;
            }
            if (Item_CheckWallCollision(self, &n, 0)) {
                Item_BounceOffWall(self, n, 0xAA, 1, 0.2f, 0.0f);
            }
            if (Item_AdvanceFallingDrop(self, &landed, 0, 0.0f)) {
                if (landed != 0) {
                    SoundMgr_PlaySE_Positional(0xAA, *(Vec *)(self + 0xA0), 0);
                    DrawEffect_ItemHitBurst_Spawn(*(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8), 1);
                    GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                    self[0xC9]++;
                    self[0xCA] = 0;
                }
            } else {
                self[0x8D] = 0;
                if (w->sub != 0) {
                    w->sub[0x8D] = 0;
                }
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 9;
            }
            break;
        }
        break;
    case 3:
        switch (S8(0xCA)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            if (w->sub != 0) {
                ItemTracker_AcquireLock(w->sub);
                ItemTracker_SetTrackPhase(w->sub, 0);
            }
            w->timers[0] = 120;
            if (w->sub != 0) {
                SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 3, 0.0f);
            }
            self[0xCA]++;
            self[0xCB] = 0;
        case 1:
            if (w->sub != 0) {
                x = *(float *)(w->sub + 0x20);
                k = lbl_80330794;
                PaceKey_Eval(&k, x, &w->pace);
                if (*(char *)(w->sub + 0x1E) == 1) {
                    w->timers[0] = 0;
                }
            }
            if (w->timers[0] == 0) {
                w->timers[0] = 900;
                w->pace = 1.0f;
                if (w->sub != 0) {
                    SpriteSlot_SetAnimFrameAndApplyScale(w->sub + 0x14, 1, 0.0f);
                }
                w->hits = 0;
                self[0xCA]++;
            }
            break;
        case 2:
            Boomerang_ReturnAndAcquireTargetTick(self, w);
            break;
        }
        p = Item_ProbeForwardGroundPitch(*(Vec *)(self + 0xA0), F(0xB0), 5.0f, 0.0f);
        F(0xAC) = AngleStepTowards_Shortest(F(0xAC), p, 0.052359864f);
        p2 = Item_ProbeLateralGroundPitch(*(Vec *)(self + 0xA0), F(0xB0), 5.0f, 0.0f);
        F(0xB4) = AngleStepTowards_Shortest(F(0xB4), p2, 0.052359864f);
        Item_DecayVelocityScalar(self, 4.5f);
        switch (hit = ItemCollision_Check(self)) {
        case 0:
            break;
        case 1:
        case 2:
        case 3:
        case 5:
            if (hit == 1) {
                ItemObject_DispatchVtable18_GetState(ItemTracker_GetTargetKart(self));
                ItemHit_Dispatch(self, 0, 0, 0);
            }
            ItemTracker_SetTrackPhase(self, 1);
            break;
        case 4:
            w->target = ItemTracker_GetTargetKart(self);
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (w->sub != 0) {
                ItemTracker_ReleaseLock(w->sub);
            }
            if (w->sub != 0) {
                w->sub[0x8D] = 0;
            }
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 3;
            return;
        }
        if (w->sub != 0) {
            switch (hit = ItemCollision_Check(w->sub)) {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 5:
                if (hit == 1) {
                    ItemObject_DispatchVtable18_GetState(ItemTracker_GetTargetKart(w->sub));
                    ItemHit_Dispatch(w->sub, 0, 0, 0);
                    w->hits++;
                    if (w->hits >= 3) {
                        w->timers[0] = 0;
                    }
                }
                ItemTracker_SetTrackPhase(w->sub, 0);
                break;
            case 4:
                w->target = ItemTracker_GetTargetKart(w->sub);
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                ItemTracker_ReleaseLock(w->sub);
                w->sub[0x8D] = 0;
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 3;
                return;
            }
        }
        kicked = 0;
        if (C8(0x8D) == 2) {
            kicked = 1;
        }
        if (w->sub != 0 && *(char *)(w->sub + 0x8D) == 2) {
            Vec3_Copy(self + 0x90, w->sub + 0x90);
            kicked = 1;
        }
        if (kicked) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (w->sub != 0) {
                ItemTracker_ReleaseLock(w->sub);
            }
            if (w->sub != 0) {
                w->sub[0x8D] = 0;
            }
            SoundMgr_PlaySE_Positional(0xCB, *(Vec *)(self + 0xA0), 0);
            Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
            F(0xBC) = 1.0f;
            F(0xB8) *= 0.1f;
            F(0xC0) *= 0.1f;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 4;
            return;
        }
        if (C8(0xCA) == 2 && ItemHitRegistry_RemoveEntry(self, w->timers[0], 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (w->sub != 0) {
                ItemTracker_ReleaseLock(w->sub);
            }
            if (w->sub != 0) {
                w->sub[0x8D] = 0;
            }
            SpriteSlot_Container_Free(w->sub);
            w->sub = 0;
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}

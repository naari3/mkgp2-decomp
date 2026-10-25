/* Dossun_State1And2_HeldOrFly (0x800ED3C0): held / flying states of the
 * Dossun (Thwomp) item. Sub-state 1 holds it in the kart's hand until it
 * is thrown, sub-state 2 flies it forward along the ground, and sub-state
 * 3 is the stomp: it slams down, bounces back up and repeats until its
 * hit registry entry is gone. A kart hit while airborne kicks the item
 * back into the drop state. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct DossunWork {
    unsigned char landed;
    unsigned char hitKart;
    unsigned char stopped;
    unsigned char buildMtx;
    unsigned int timers[4];
    float groundY;
    float yaw;
    unsigned char pad1C[0x98 - 0x1C];
    void *driver;
    void *target;
    signed char launch;
    unsigned char padA1[3];
    Vec dir;
} DossunWork;

extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int frame, float f);
extern void GabyouItem_BuildLocalTransformFromHandJoint(unsigned char *self, int a, float x, float y, float z);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern signed char ItemObject_GetGroundTypeAt(Vec pos, float *outGroundY, int mode);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
extern float BuildOrientationFromYaw(float yaw);
extern void Item_DecayVelocityScalar(unsigned char *self, float k);
extern void SoundMgr_PlaySE_Positional(int se, Vec pos, int ch);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void Item_BounceOffWall(unsigned char *self, Vec n, int se, int flag, float k1, float k2);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern float Vec3_ToYaw(const Vec *v);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, int id, int flag);
extern void DrawEffect_ItemHitBurst_Spawn(Vec pos, Vec vel, int kind);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void DrawEffect_Cb_ItemBoxBurstSpawner(unsigned char *self);
extern void Vec3_Copy(void *dst, void *src);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(unsigned char *self);
extern float AngleStepForward_OrSnap(float current, float target, float step);
extern float AngleStepTowards_Shortest(float cur, float target, float step);
extern float Item_ProbeForwardGroundPitch(Vec pos, float yaw, float a, float b);
extern float Item_ProbeLateralGroundPitch(Vec pos, float yaw, float a, float b);
extern float FAbs_FloatAsDouble(float x);
extern int ItemCollision_Check(unsigned char *self);
extern short ItemAlias_HitRemapLookup(unsigned int itemId);
extern void fn_801B1D5C(void *a, void *kart, int remapId, int flag);
extern void fn_801B1660(void *driver, void *target);
extern void fn_801B158C(void *driver, void *target);
extern void fn_801B14B8(void *driver, void *target);
extern void ItemHit_Dispatch(unsigned char *self, int a, void *pos, int b);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define C8(o) (*(char *)(self + (o)))

static inline void Dossun_Kick(unsigned char *self, DossunWork *w)
{
    self[0x8D] = 0;
    SoundMgr_PlaySE_Positional(0xCB, *(Vec *)(self + 0xA0), 0);
    Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
    F(0xBC) = 3.0f;
    F(0xB8) *= 0.1f;
    F(0xC0) *= 0.1f;
    self[0xC8] = 2;
    self[0xC9] = 0;
    self[0xCB] = 4;
}

static inline float Dossun_ClampPitch(float p)
{
    if (0.17453289f < FAbs_FloatAsDouble(p)) {
        p = 0.17453289f * (p / FAbs_FloatAsDouble(p));
    }
    return p;
}

void Dossun_State1And2_HeldOrFly(unsigned char *self, DossunWork *w)
{
    Vec n;
    Vec p;
    float gy;

    switch (S8(0xC9)) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            w->buildMtx = 0;
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            self[0xCA]++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(self, 1, -1.0f, 2.8797927f, 1.0f);
            if (FinalLapCoinJump_CheckActiveForObject(w->driver)) {
                self[0x28] = 0;
            } else {
                self[0x28] = 1;
            }
            switch (w->launch) {
            case 1:
                self[0x28] = 1;
                w->launch = 0;
                w->buildMtx = 1;
                Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
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
            self[0x3C] = 1;
            w->timers[0] = 10;
            ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &w->groundY, 0);
            w->yaw = 0.0f;
            self[0xCA]++;
        case 1:
            F(0xBC) += -0.1f;
            if (w->timers[0] == 0) {
                self[0xCA]++;
            }
            break;
        case 2:
            F(0xBC) += 0.1f;
            F(0xB8) *= 0.98f;
            F(0xC0) *= 0.98f;
            break;
        }
        Item_HomingScanAndSteer(self, 0, 1);
        F(0xB0) = BuildOrientationFromYaw(0.17453289f + F(0xB0));
        Item_DecayVelocityScalar(self, 5.0f);
        if (C8(0x8D) == 2) {
            self[0x8D] = 0;
            SoundMgr_PlaySE_Positional(0xCB, *(Vec *)(self + 0xA0), 0);
            Vec3_Add_DestFirst(self + 0xB8, self + 0xB8, self + 0x90);
            F(0xBC) = 3.0f;
            F(0xB8) *= 0.1f;
            F(0xC0) *= 0.1f;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 4;
            break;
        }
        if (Item_CheckWallCollision(self, &n, 0)) {
            Item_BounceOffWall(self, n, 0xAA, 3, 0.2f, 0.0f);
        }
        Vec3_Add_DestFirst(&p, self + 0xA0, self + 0xB8);
        if (ItemObject_GetGroundTypeAt(p, &gy, 0)) {
            F(0xA4) += gy - w->groundY;
            w->groundY = gy;
            if (p.y < gy && F(0xBC) < 0.0f) {
                F(0xBC) = 0.0f;
            }
        }
        w->yaw += F(0xBC);
        if (60.0f < w->yaw) {
            F(0xB8) = 0.0f;
            F(0xC0) = 0.0f;
            if (ItemObject_GetGroundTypeAt(*(Vec *)(self + 0xA0), &w->groundY, 0)) {
                self[0xC9] = 3;
                self[0xCA] = 0;
            } else {
                self[0x8D] = 0;
                self[0xC8] = 2;
                self[0xC9] = 0;
                self[0xCB] = 9;
            }
        }
        break;
    case 3:
        switch (S8(0xCA)) {
        case 0:
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            w->yaw = Vec3_ToYaw(&w->dir);
            w->timers[0] = 900;
            ItemHitRegistry_AddEntry(self);
            self[0xCA] = 1;
            self[0xCB] = 0;
        case 1:
            switch (S8(0xCB)) {
            case 0:
                w->landed = 0;
                w->hitKart = 0;
                w->stopped = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
                self[0xCB] = 1;
            case 1:
                break;
            }
            if (w->stopped == 0) {
                F(0xBC) += -0.5f;
            }
            if (F(0xA4) + F(0xBC) < w->groundY - 3.0f || w->stopped != 0) {
                if (w->stopped == 0) {
                    unsigned char *e;

                    SoundMgr_PlaySE_Positional(0xB5, *(Vec *)(self + 0xA0), 0);
                    DrawEffect_ItemHitBurst_Spawn(*(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8), 3);
                    F(0xA4) = w->groundY - 3.0f;
                    if (w->hitKart != 0) {
                        e = DrawEffect_SpawnDirect(DrawEffect_Cb_ItemBoxBurstSpawner);
                        if (e != 0) {
                            Vec3_Copy(e + 0x8C, self + 0xA0);
                        }
                    }
                }
                F(0xBC) = 0.0f;
                w->landed = 1;
                if (w->hitKart == 0) {
                    self[0xCA] = 2;
                    self[0xCB] = 0;
                } else {
                    ItemTracker_ReleaseLock(self);
                    self[0x8D] = 0;
                    self[0xC8] = 2;
                    self[0xC9] = 0;
                    self[0xCB] = 0;
                    return;
                }
                return;
            }
            break;
        case 2:
            switch (S8(0xCB)) {
            case 0:
                w->timers[1] = 30;
                self[0xCB] = 1;
            case 1:
                break;
            }
            if (w->timers[1] == 0) {
                if (!ItemHitRegistry_RemoveEntry(self, w->timers[0], 0)) {
                    self[0xCA] = 3;
                    self[0xCB] = 0;
                } else {
                    ItemTracker_ReleaseLock(self);
                    self[0x8D] = 0;
                    ItemObject_DecrementCategoryBudget(self);
                    SpriteSlot_Container_Free(self);
                    return;
                }
            }
            break;
        case 3:
            switch (S8(0xCB)) {
            case 0:
                SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                self[0xCB] = 1;
            case 1:
                break;
            }
            F(0xBC) += 0.1f;
            if (60.0f + w->groundY < F(0xA4)) {
                self[0xCA] = 1;
                self[0xCB] = 0;
            }
            break;
        }
        Item_DecayVelocityScalar(self, 5.0f);
        F(0xB0) = AngleStepForward_OrSnap(F(0xB0), w->yaw, 0.17453289f);
        if (S8(0xCA) == 1 || S8(0xCA) == 2) {
            F(0xAC) = AngleStepTowards_Shortest(F(0xAC), Dossun_ClampPitch(Item_ProbeForwardGroundPitch(*(Vec *)(self + 0xA0), F(0xB0), 10.0f, F(0xA4) - w->groundY)), 0.017453289f);
            F(0xB4) = AngleStepTowards_Shortest(F(0xB4), Dossun_ClampPitch(Item_ProbeLateralGroundPitch(*(Vec *)(self + 0xA0), F(0xB0), 10.0f, F(0xA4) - w->groundY)), 0.017453289f);
        } else {
            F(0xAC) = AngleStepTowards_Shortest(F(0xAC), 0.0f, 0.017453289f);
            F(0xB4) = AngleStepTowards_Shortest(F(0xB4), 0.0f, 0.017453289f);
        }
        switch (ItemCollision_Check(self)) {
        case 1:
            fn_801B1D5C(w->driver, ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
            if (w->landed == 0) {
                ItemHit_Dispatch(self, 0, self + 0xA0, 0);
                ItemTracker_ReleaseLock(self);
                self[0x8D] = 0;
                w->hitKart = 1;
            } else {
                ItemHit_Dispatch(self, 1, self + 0xA0, 0);
                ItemTracker_SetTrackPhase(self, 1);
            }
            break;
        case 2:
            fn_801B1660(w->driver, ItemTracker_GetTargetKart(self));
        case 3:
            if (ItemCollision_Check(self) == 3) {
                fn_801B158C(w->driver, ItemTracker_GetTargetKart(self));
            }
            ItemTracker_SetTrackPhase(self, 1);
            if (w->landed == 0) {
                F(0xBC) = 0.0f;
                w->stopped = 1;
            }
            break;
        case 4:
            fn_801B14B8(w->driver, ItemTracker_GetTargetKart(self));
            w->target = ItemTracker_GetTargetKart(self);
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
        if (C8(0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            Dossun_Kick(self, w);
        }
        break;
    }
}

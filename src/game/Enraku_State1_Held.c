/* Enraku_State1_Held (0x800F091C): held and flying states of the Enraku
 * item. Sub-state 1 holds it on the kart's joint 12 with a smoke cloud
 * until it is thrown, sub-state 2 flies it forward with homing and a spin,
 * and leaves the flying state on a kart hit, a wall, a landing or a
 * timeout. */
typedef struct Vec { float x, y, z; } Vec;

typedef struct EnrakuWork {
    unsigned char pad0[4];
    unsigned int timers[4];
    unsigned char pad14[0x4C - 0x14];
    unsigned char *eff;
    unsigned char pad50[0x7C - 0x50];
    int approach;
    unsigned char pad80[0x98 - 0x80];
    void *driver;
    void *target;
    signed char launch;
} EnrakuWork;

extern const Vec lbl_8032F518;
extern const Vec lbl_8032F524;
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void Effect_SmokeCloud_Update(unsigned char *self);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Vec3_Copy(void *dst, void *src);
extern void Item_RenderCharacterScaledFromJoint12(unsigned char *self, Vec ofs, Vec rot, int c, float scale);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
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
extern float Vec3_ToYaw(const void *v);
extern int Item_CheckWallCollision(unsigned char *self, Vec *n, int flag);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *out, int a, float f);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define C8(o) (*(char *)(self + (o)))

void Enraku_State1_Held(unsigned char *self, EnrakuWork *w)
{
    int hit;
    int landed;

    switch (S8(0xC9)) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            w->eff = DrawEffect_SpawnDirect(Effect_SmokeCloud_Update);
            if (w->eff != 0) {
                Vec3_Copy(w->eff + 0x8C, self + 0xA0);
            }
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            Item_RenderCharacterScaledFromJoint12(self, lbl_8032F518, lbl_8032F524, 1, 1.2f);
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
                Item_InitLaunchFromKart(self, 0, 1.0f, 0.0f);
                self[0xC9]++;
                self[0xCA] = 0;
                break;
            case 2:
                w->launch = 0;
                self[0x28] = 0;
                if (w->eff != 0) {
                    w->eff[0xC9] = 1;
                }
                w->eff = 0;
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
            ItemTracker_AcquireLock(self);
            ItemTracker_SetTrackPhase(self, 1);
            self[0x8D] = 1;
            self[0x3C] = 1;
            w->timers[0] = 10;
            w->timers[1] = 0;
            self[0xCA]++;
        case 1:
            break;
        }
        F(0xBC) += -0.1f;
        Item_HomingScanAndSteer(self, self + 0xB0, 1);
        F(0xAC) = BuildOrientationFromYaw(0.34906578f + F(0xAC));
        Item_DecayVelocityScalar(self, 2.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(w->driver, ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(w->driver, ItemTracker_GetTargetKart(self));
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
            fn_801B158C(w->driver, ItemTracker_GetTargetKart(self));
            w->approach = 0;
            Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
            F(0xB0) = Vec3_ToYaw(self + 0xB8);
            ItemTracker_SetTrackPhase(self, 0);
            w->timers[1] = 5;
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
        if (w->timers[1] == 0) {
            ItemTracker_SetTrackPhase(self, 1);
        }
        if (C8(0x8D) == 2) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (C8(0x8E) == 1) {
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
            if (landed != 0) {
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
        if (w->timers[0] == 0) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            self[0xC8] = 2;
            self[0xC9] = 0;
            self[0xCB] = 5;
        }
        break;
    }
}

/* BombItem_TickActive (0x800F6F54): held and flying states of the bomb
 * item. Sub-state 1 holds it in the character's hand until it is thrown,
 * sub-state 2 flies it forward with homing, bounces it off walls and
 * leaves the flying state on a kart hit, a landing or a timeout. */
#include "game/types/Vec.h"

#include "game/types/BombWork.h"

extern const Vec BombItem_TickActive_rodata_8032FA48;
extern const Vec BombItem_TickActive_rodata_8032FA54;
extern void Effect_TwoChild_Res8F_Update(unsigned char *self);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *slot, int en);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *slot, int anim, float frame);
extern unsigned char *DrawEffect_SpawnDirect(void (*callback)(unsigned char *));
extern void Item_RenderHandheldByCharacter(unsigned char *self, Vec ofs, Vec rot, int c, float scale);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *driver);
extern void Item_InitLaunchFromKart(unsigned char *self, void *pos, float x, float y);
extern void ItemTracker_AcquireLock(unsigned char *self);
extern void ItemTracker_SetTrackPhase(unsigned char *self, int phase);
extern void ItemTracker_ReleaseLock(unsigned char *self);
extern void *ItemTracker_GetTargetKart(unsigned char *self);
extern void ItemHitRegistry_AddEntry(unsigned char *self);
extern unsigned char ItemHitRegistry_RemoveEntry(unsigned char *self, unsigned int id, int flag);
extern void Item_HomingScanAndSteer(unsigned char *self, void *yaw, int flag);
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
extern void Item_BounceOffWall(unsigned char *self, Vec n, int a, int b, float x, float y);
extern int Item_AdvanceFallingDrop(unsigned char *self, int *landed, int *hit, float f);
extern void DrawEffect_ItemHitBurst_Spawn(Vec pos, Vec vel, int kind);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern void ItemObject_DecrementCategoryBudget(unsigned char *self);
extern void SpriteSlot_Container_Free(unsigned char *self);

#define F(o) (*(float *)(self + (o)))
#define I(o) (*(int *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define C8(o) (*(char *)(self + (o)))

void BombItem_TickActive(unsigned char *self, BombWork *w)
{
    int hit;
    int landed;
    int bounced;
    Vec n;

    switch (S8(0xC9)) {
    case 0:
        self[0xC9]++;
        self[0xCA] = 0;
    case 1:
        switch (S8(0xCA)) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(self + 0x14, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 0, 0.0f);
            self[0x28] = 1;
            F(0x2C) = 0.0f;
            self[0xCA]++;
        case 1:
            Item_RenderHandheldByCharacter(self, BombItem_TickActive_rodata_8032FA48, BombItem_TickActive_rodata_8032FA54, 1, 1.0f);
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
            SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 1, 0.0f);
            w->fx[0] = DrawEffect_SpawnDirect(Effect_TwoChild_Res8F_Update);
            w->timers[0] = 900;
            w->timers[1] = 0;
            self[0xCA]++;
            ItemHitRegistry_AddEntry(self);
        case 1:
            F(0xBC) += -0.1f;
            Item_HomingScanAndSteer(self, self + 0xB0, 1);
            break;
        case 2:
            break;
        }
        Item_DecayVelocityScalar(self, 2.0f);
        hit = ItemCollision_Check(self);
        switch (hit) {
        case 1:
            fn_801B1D5C(w->driver, ItemTracker_GetTargetKart(self), ItemAlias_HitRemapLookup(I(0x8)), 0);
        case 2:
            if (hit == 2) {
                fn_801B1660(w->driver, ItemTracker_GetTargetKart(self));
            }
        case 3:
            if (hit == 3) {
                fn_801B158C(w->driver, ItemTracker_GetTargetKart(self));
            }
            if (hit == 3 && C8(0xCA) == 1) {
                w->approach = 0;
                Item_ComputeYawRelativeApproach(self + 0xB8, ItemTracker_GetTargetKart(self), *(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8));
                F(0xB0) = Vec3_ToYaw(self + 0xB8);
                ItemTracker_SetTrackPhase(self, 0);
                w->timers[1] = 5;
                break;
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
        if (C8(0xCA) == 1) {
            if (Item_CheckWallCollision(self, &n, 0)) {
                Item_BounceOffWall(self, n, 0xCB, 2, 0.2f, 0.0f);
                F(0xB0) = Vec3_ToYaw(self + 0xB8);
            }
            if (Item_AdvanceFallingDrop(self, &landed, &bounced, 0.0f)) {
                if (landed != 0) {
                    DrawEffect_ItemHitBurst_Spawn(*(Vec *)(self + 0xA0), *(Vec *)(self + 0xB8), 2);
                    GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                    SpriteSlot_SetAnimFrameAndApplyScale(self + 0x14, 2, 0.0f);
                    if (C8(0xCA) == 1) {
                        self[0xCA] = 2;
                    }
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
        if (ItemHitRegistry_RemoveEntry(self, w->timers[0], 0)) {
            ItemTracker_ReleaseLock(self);
            self[0x8D] = 0;
            if (w->fx[0] != 0) {
                w->fx[0][0xC9] = 1;
            }
            w->fx[0] = 0;
            ItemObject_DecrementCategoryBudget(self);
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}

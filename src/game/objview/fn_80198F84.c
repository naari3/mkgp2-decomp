#include "game/objview/item_state_private.h"
extern int g_ccClass;
extern const float lbl_806D9690, lbl_806D9694, lbl_806D9698;
extern const float lbl_806D96A8, lbl_806D96B4, lbl_806D96C0, lbl_806D96C4, lbl_806D96C8;
#ifdef __MWERKS__
extern char ItemObject_GetGroundTypeAt(Vec3 pos, float *height, void *normal);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern char ItemObject_GetGroundTypeAt(Vec3 *, float *, void *);
static inline char ItemObject_GetGroundTypeAt_ByValue(Vec3 pos, float *height, void *normal) { return ItemObject_GetGroundTypeAt(&pos, height, normal); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
extern void Item_AccelClampVelocity(Item *, float, float);
extern void Item_DecayVelocityScalar(Item *, float);
extern float Vec3_ToYaw(Vec3 *);
#ifdef __MWERKS__
extern void *FindNearestDriverWithinConeAndRadius(Vec3, void *, int, float, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void * FindNearestDriverWithinConeAndRadius(Vec3 *, void *, int, float, float, float);
static inline void * FindNearestDriverWithinConeAndRadius_ByValue(Vec3 a0, void *a1, int a2, float a3, float a4, float a5) { return FindNearestDriverWithinConeAndRadius(&a0, a1, a2, a3, a4, a5); }
#define FindNearestDriverWithinConeAndRadius FindNearestDriverWithinConeAndRadius_ByValue
#endif
extern void ItemTracker_ReleaseLock(Item *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void SoundMgr_PlaySE_Positional(int, Vec3, int);
extern int Item_CheckWallCollision(Item *, Vec3 *, int);
#ifdef __MWERKS__
extern void Item_BounceOffWall(Item *, Vec3, int, int, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_BounceOffWall(Item *, Vec3 *, int, int, float, float);
static inline void Item_BounceOffWall_ByValue(Item *a0, Vec3 a1, int a2, int a3, float a4, float a5) { Item_BounceOffWall(a0, &a1, a2, a3, a4, a5); }
#define Item_BounceOffWall Item_BounceOffWall_ByValue
#endif
extern int Item_AdvanceProjectileSimple(Item *, float *, float, float);

void fn_80198F84(Item *self, State *state) {
    Vec3 wall;
    float maxv;
    float accel;
    switch (self->step) {
    case 0:
        self->tracking = 1;
        self->x3c = 1;
        ItemObject_GetGroundTypeAt(self->pos, &state->height, 0);
        state->height = self->pos.y - state->height;
        state->timer = 300;
        state->x8 = 0;
        self->step++;
        break;
    case 1:
        break;
    }
    maxv = g_ccClass == 0 ? lbl_806D9698 : lbl_806D9690;
    accel = g_ccClass == 0 ? lbl_806D96C0 : lbl_806D96C4;
    Item_AccelClampVelocity(self, accel, maxv);
    Item_DecayVelocityScalar(self, lbl_806D9690);
    state->target = FindNearestDriverWithinConeAndRadius(self->pos, state->owner, 0, Vec3_ToYaw(&self->velocity), lbl_806D96A8, lbl_806D96C8);
    if (state->target != 0) {
        self->tracking = 0;
        ItemTracker_ReleaseLock(self);
        self->phase = 2;
        self->subphase = 0;
        self->reason = 0;
        return;
    }
    if (self->tracking == 2) {
        ItemTracker_ReleaseLock(self);
        self->tracking = 0;
        if (self->hit == 1) {
            Vec3_Add_DestFirst(&self->velocity, &self->velocity, &self->impulse);
            self->velocity.x *= lbl_806D96B4;
            self->velocity.z *= lbl_806D96B4;
            self->velocity.y = lbl_806D9690;
            SoundMgr_PlaySE_Positional(0xCB, self->pos, 0);
            self->phase = 2;
            self->subphase = 0;
            self->reason = 4;
            return;
        }
        self->phase = 2;
        self->subphase = 0;
        self->reason = 6;
        return;
    }
    if (Item_CheckWallCollision(self, &wall, 0)) {
        ItemTracker_ReleaseLock(self);
        self->tracking = 0;
        Item_BounceOffWall(self, wall, 0, 0, lbl_806D96B4, lbl_806D9690);
        SoundMgr_PlaySE_Positional(0xCB, self->pos, 0);
        self->phase = 2;
        self->subphase = 0;
        self->reason = 7;
        return;
    }
    if (!Item_AdvanceProjectileSimple(self, &state->height, lbl_806D9694, lbl_806D9698)) {
        ItemTracker_ReleaseLock(self);
        self->tracking = 0;
        self->visible = 0;
        self->phase = 3;
        self->subphase = 0;
        return;
    }
    if (state->timer == 0) {
        ItemTracker_ReleaseLock(self);
        self->tracking = 0;
        self->phase = 2;
        self->subphase = 0;
        self->reason = 5;
    }
}

/* Held/launch/homing state for the Onchi Speaker item. */
#include "game/objview/item_state_private.h"

extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *, int);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *, int, float);
extern void SpriteSlot_SetScale(void *, float);
extern void GabyouItem_BuildLocalTransformFromHandJoint(Item *, int, float, float, float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
extern void Item_InitLaunchFromKart(Item *, Vec3 *, float, float);
extern void *KartDriver_GetJointByIdx(void *, int);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void ItemTracker_AcquireLock(Item *);
extern void ItemTracker_SetTrackPhase(Item *, int);
#ifdef __MWERKS__
extern signed char ItemObject_GetGroundTypeAt(Vec3, float *, int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(Vec3 *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(Vec3 a0, float *a1, int a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
extern void Item_HomingScanAndSteer(Item *, float *, int);
extern void Item_AccelClampVelocity(Item *, float, float);
extern void Item_DecayVelocityScalar(Item *, float);
extern int ItemCollision_Check(Item *);
extern int ItemAlias_HitRemapLookup(int);
extern void *ItemTracker_GetTargetKart(Item *);
extern void fn_801B1D5C(void *, void *, short, int);
extern void fn_801B1660(void *, void *);
extern void fn_801B158C(void *, void *);
extern void fn_801B14B8(void *, void *);
extern void ItemHit_Dispatch(Item *, int, int, int);
extern void ItemTracker_ReleaseLock(Item *);
extern void Item_ComputeYawRelativeApproach(Vec3 *, void *, Vec3 *, Vec3 *);
extern float Vec3_ToYaw(Vec3 *);
extern void SoundMgr_PlaySE_Positional(int, Vec3, int);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
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
extern int g_ccClass;

static inline void SetLaunchGround(Item *item, State *state)
{
    ItemObject_GetGroundTypeAt(item->pos, &state->height, 0);
}

static inline void DeflectSpeaker(Item *item, State *state)
{
    Vec3 vel, pos;
    fn_801B158C(state->owner, ItemTracker_GetTargetKart(item));
    /* Per-state counter outside the common State view. */
    *(int *)((char *)state + 0x7c) = 0;
    vel = item->velocity;
    pos = item->pos;
    Item_ComputeYawRelativeApproach(&item->velocity, ItemTracker_GetTargetKart(item), &pos, &vel);
    item->rotation.y = Vec3_ToYaw(&item->velocity);
    ItemTracker_SetTrackPhase(item, 0);
    state->x8 = 5;
}

static inline void PlayImpactSound(Item *item)
{
    SoundMgr_PlaySE_Positional(203, item->pos, 0);
}

static inline void BounceSpeaker(Item *item, Vec3 *wall)
{
    Item_BounceOffWall(item, *wall, 203, 2, 0.2f, 2.0f);
}

#pragma exceptions on
void OnchiSpeaker_State1_Held(Item *item, State *state)
{
    Vec3 wall;
    switch (item->subphase) {
    case 0:
        item->subphase++;
        item->step = 0;
    case 1:
        switch (item->step) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, 0.0f);
            SpriteSlot_SetScale(item->sprite, 1.0f);
            item->visible = 1;
            item->scale = 0.0f;
            item->step++;
        case 1:
            GabyouItem_BuildLocalTransformFromHandJoint(item, 1, 3.0f, 2.8797926902770996f, 1.2f);
            if (FinalLapCoinJump_CheckActiveForObject(state->owner)) item->visible = 0;
            else item->visible = 1;
            switch (state->action) {
            case 1:
                item->visible = 1;
                state->action = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 0);
                Item_InitLaunchFromKart(item, &state->delta, 5.0f, 0.0f);
                item->subphase++;
                item->step = 0;
                break;
            case 2:
                state->action = 0;
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor(&state->delta, KartDriver_GetJointByIdx(state->owner, 12));
                break;
            }
            break;
        }
        break;
    case 2:
        switch (item->step) {
        case 0:
            ItemTracker_AcquireLock(item);
            ItemTracker_SetTrackPhase(item, 1);
            item->tracking = 1;
            item->x3c = 1;
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 1, 0.0f);
            SpriteSlot_SetScale(item->sprite, 1.0f);
            SetLaunchGround(item, state);
            state->height = item->pos.y - state->height;
            state->timer = 300;
            state->x8 = 0;
            item->step++;
            break;
        case 1:
            break;
        }
        Item_HomingScanAndSteer(item, &item->rotation.y, 0);
        Item_AccelClampVelocity(item, g_ccClass == 0 ? 17.0f : 22.0f, g_ccClass == 0 ? 1.0f : 2.0f);
        Item_DecayVelocityScalar(item, 3.0f);
        switch (ItemCollision_Check(item)) {
        case 1: {
            short hit = ItemAlias_HitRemapLookup(item->id);
            fn_801B1D5C(state->owner, ItemTracker_GetTargetKart(item), hit, 0);
            state->target = ItemTracker_GetTargetKart(item);
            ItemHit_Dispatch(item, 0, 0, 0);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 0;
            return;
        }
        case 2:
            fn_801B1660(state->owner, ItemTracker_GetTargetKart(item));
            state->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->velocity.y = 2.0f;
            item->velocity.x *= 0.1f;
            item->velocity.z *= 0.1f;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 1;
            return;
        case 3:
            DeflectSpeaker(item, state);
            break;
        case 4:
            fn_801B14B8(state->owner, ItemTracker_GetTargetKart(item));
            state->target = ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 3;
            return;
        case 5:
            ItemTracker_SetTrackPhase(item, 1);
            break;
        }
        if (state->x8 == 0) ItemTracker_SetTrackPhase(item, 1);
        if (item->tracking == 2) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            if (item->hit == 1) {
                PlayImpactSound(item);
                Vec3_Add_DestFirst(&item->velocity, &item->velocity, &item->impulse);
                item->velocity.y = 2.0f;
                item->velocity.x *= 0.2f;
                item->velocity.z *= 0.2f;
                item->phase = 2;
                item->subphase = 0;
                item->reason = 4;
            } else {
                item->phase = 2;
                item->subphase = 0;
                item->reason = 6;
            }
            return;
        }
        if (Item_CheckWallCollision(item, &wall, 0)) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            BounceSpeaker(item, &wall);
            item->phase = 2;
            item->subphase = 0;
            item->reason = 7;
            return;
        }
        if (!Item_AdvanceProjectileSimple(item, &state->height, 7.0f, 7.0f)) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 9;
            return;
        }
        if (state->timer == 0) {
            ItemTracker_ReleaseLock(item);
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 5;
        }
        break;
    }
}
#pragma exceptions reset

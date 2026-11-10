#include "game/objview/item_state_private.h"

extern float AngleStepTowards_Shortest(float, float, float);
extern float BuildOrientationFromYaw(float);
extern void *DrawEffect_SpawnDirect();
extern unsigned char FinalLapCoinJump_CheckActiveForObject();
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern short ItemAlias_HitRemapLookup();
extern void ItemHit_Dispatch();
extern int Item_AdvanceTetherToJoint13(Item *, float *, float, float, float);
extern void Item_DecayVelocityScalar(void *, float);
extern int KartCharacterParam_GetIdentityIndex();
extern void *KartDriver_GetJointByIdx();
extern void *KartDriver_GetKartRootMtx();
extern float KartFxParam_GetConst1p5();
extern void KartItem_ApplyEffectToTarget();
extern int KartItem_QueryEffectStateFromIse();
extern void Mtx44_GetTranslation_RowMajor();
#ifndef __MWERKS__ /* this unit passes the position as the address of its own copy (SoundMgr_PlaySE_Positional.c) */
#define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress
#endif
extern void SoundMgr_PlaySE_Positional();
extern void Vec3_Add_DestFirst();
extern void Vec3_Copy();
extern void Vec3_Lerp(void *, void *, void *, float);
extern void Vec3_Subtract_DestFirst();
extern void fn_801B14B8();
extern void fn_801B158C();
extern void fn_801B1660();
extern void fn_801B1D5C();
extern double sin(double);
extern const float lbl_806D5E78;
extern const float lbl_806D5E7C;
extern const float lbl_806D5E80;
extern const float lbl_806D5E84;
extern const float lbl_806D5E88;
extern const float lbl_806D5E8C;
extern const float lbl_806D5E90;
extern const float lbl_806D5E94;
extern const float lbl_806D5E98;
extern const float lbl_806D5E9C;
extern const float lbl_806D5EA0;
extern const float lbl_806D5EA4;
extern const float lbl_806D5EA8;
extern const float lbl_806D5EAC;
extern unsigned int Effect_KartJoint15_Res7B_Update[];
extern unsigned int MukadeItem_Tick_HeldAndHoming_3839_rodata_8032F4C8[];
extern void *FindNearestDriverWithinConeAndRadius(void *, void *, int, float, float, float);
extern signed char ItemObject_GetGroundTypeAt();
extern void Item_AccelClampVelocity(void *, float, float);
extern int Item_AdvanceProjectileSimple(void *, void *, float, float);
extern void Item_BendVelocityByGroundProbe(void *, void *, float, float, float);
extern void Item_BounceOffWall(void *, void *, int, int, float, float);
extern int Item_CheckWallCollision();
extern void Item_HomingScanAndSteer();
extern void Item_InitLaunchFromKart(void *, void *, float, float);
#ifdef __MWERKS__
extern void Item_RenderCharacterScaledFromJoint12();
#else /* this unit passes the two vectors as addresses of its own copies (ItemCharacterRender.c) */
#define Item_RenderCharacterScaledFromJoint12 Item_RenderCharacterScaledFromJoint12_ByAddress
extern void Item_RenderCharacterScaledFromJoint12(void *item, const void *offset, const void *euler, int mode, float scale);
#endif
extern float KartCharacterParam_GetVfxBindHeightOffset();
extern void KartDriver_TransformWorldToLocalY0();
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed();
extern float Vec3_ToYaw();
extern void fn_801B129C();
extern int g_ccClass;
extern const float lbl_806D5EB0;
extern const float lbl_806D5EB4;
extern const float lbl_806D5EB8;
extern const float lbl_806D5EBC;
extern const float lbl_806D5EC0;
extern const float lbl_806D5EC4;
extern const float lbl_806D5EC8;
extern const float lbl_806D5ECC;
extern const Vec3 MukadeItem_TickHeldOrSnake_3839_rodata_8032F4B0;
extern const Vec3 MukadeItem_TickHeldOrSnake_3839_rodata_8032F4BC;
extern void ItemObject_DecrementCategoryBudget();
extern int Item_OrbitAnchorKart(void *, void *, void *, float, float);
extern void SpriteSlot_Container_Free();
extern void SpriteSlot_InitNonLoop();
extern void SpriteSlot_SetTransform(void *, void *, void *, float);

/* Enter the retreat phase with the requested number of remaining tethers. */
static inline void MukadeItem_BeginRetreat(Item *item, State *state, unsigned char count)
{
    item->subphase = 2;
    item->step = 0;
    state->count = count;
}

#pragma use_lmw_stmw on
void MukadeItem_Tick_HeldAndHoming_3839(Item *item, State *state)
{
    struct Heights { float values[11]; } heights;
    Vec3 root, joint;
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(state->target));
    if (FinalLapCoinJump_CheckActiveForObject(state->target)) item->visible = 0;
    else item->visible = 1;
    switch (item->subphase) {
    case 0:
        GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
        if (item->id == 0x39) state->count = 1;
        else state->count = 3;
        item->subphase++;
        item->step = 0;
    case 1:
        switch (item->step) {
        case 0:
            state->timer = 20;
            state->height = 0.0f;
            state->lift = 11.0f;
            state->gravity = 0.0f;
            *(float *)((char *)state + 0x20) = 0.0f;
            item->step++;
        case 1:
            item->rotation.y = BuildOrientationFromYaw(0.34906578063964844f + item->rotation.y);
            *(float *)((char *)state + 0x20) = BuildOrientationFromYaw(0.5235986709594727f + *(float *)((char *)state + 0x20));
            item->rotation.x = 0.26179933547973633f * (float)sin(*(float *)((char *)state + 0x20));
            if (state->timer == 0) item->step++;
            break;
        case 2:
            item->rotation.x = AngleStepTowards_Shortest(item->rotation.x, 0.0f, 0.08726644515991211f);
            state->gravity += -0.10000000149011612f;
            break;
        }
        {
            float zero = 0.0f;
            state->lift += state->gravity;
            if (state->lift <= zero) state->lift = zero;
        }
        heights = *(const struct Heights *)MukadeItem_Tick_HeldAndHoming_3839_rodata_8032F4C8;
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(state->target, 15));
        joint.y += state->lift + heights.values[KartCharacterParam_GetIdentityIndex(state->target)];
        state->height += 0.20000000298023224f;
        if (1.0f < state->height) state->height = 1.0f;
        {
            Vec3 a, b = item->pos;
            a = joint;
            Vec3_Lerp(&item->pos, &a, &b, state->height);
        }
        if (state->lift <= 0.0f) {
            int effect = KartItem_QueryEffectStateFromIse(state->target);
            KartItem_ApplyEffectToTarget(item, state->target, effect);
            switch (effect) {
            case 1:
                fn_801B1D5C(state->owner, state->target, (short)ItemAlias_HitRemapLookup(item->id), 0);
                ItemHit_Dispatch(item, 0, &item->pos, state->target);
                {
                    Vec3 pos = item->pos;
                    SoundMgr_PlaySE_Positional(0x85, &pos, 0);
                }
                {
                    char *fx = DrawEffect_SpawnDirect(Effect_KartJoint15_Res7B_Update);
                    if (fx != 0) {
                        Vec3_Copy(fx + 0x8c, &item->pos);
                        *(float *)(fx + 0xb0) = item->param;
                        *(void **)(fx + 0x11c) = state->target;
                    }
                }
                break;
            case 2:
                fn_801B1660(state->owner, state->target);
            case 3:
                if (effect == 3) fn_801B158C(state->owner, state->target);
                {
                    Vec3 pos = item->pos;
                    SoundMgr_PlaySE_Positional(0x85, &pos, 0);
                }
                break;
            case 4:
                fn_801B14B8(state->owner, state->target);
                item->subphase = 3;
                item->step = 0;
                return;
            case 5:
                MukadeItem_BeginRetreat(item, state, 1);
                state->height = state->gravity;
                Vec3_Subtract_DestFirst(&state->delta, &item->pos, &root);
                return;
            }
            if (state->count != 0) state->count--;
            if (state->count != 0) item->step = 0;
            else {
                MukadeItem_BeginRetreat(item, state, 0);
                Vec3_Subtract_DestFirst(&state->delta, &item->pos, &root);
                return;
            }
        }
        Item_DecayVelocityScalar(item, 3.0f * KartFxParam_GetConst1p5(state->target));
        break;
    case 2:
        switch (item->step) {
        case 0:
            if (state->count == 0) state->height = 2.0f;
            item->rotation.x = BuildOrientationFromYaw(0.17453289031982422f + item->rotation.x);
            state->timer = 10;
            item->step++;
        case 1:
        default:
            break;
        }
        if (state->timer == 0) {
            item->scale -= 0.05000000074505806f;
            if (item->scale < 0.0f) {
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
                return;
            }
        }
        state->height += -0.10000000149011612f;
        state->delta.y += state->height;
        Vec3_Add_DestFirst(&item->pos, &root, &state->delta);
        item->rotation.x = BuildOrientationFromYaw(0.05235986411571503f + item->rotation.x);
        Item_DecayVelocityScalar(item, 3.0f * KartFxParam_GetConst1p5(state->target));
        break;
    case 3:
        switch (item->step) {
        case 0:
            GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
            item->x3c = 0;
            state->height = 0.0f;
            state->lift = item->param;
            item->step++;
        case 1:
        default:
            break;
        }
        if (Item_AdvanceTetherToJoint13(item, &state->height, state->lift, 0.08726644515991211f, 0.08726644515991211f)) {
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
        }
        break;
    }
}
#pragma use_lmw_stmw reset

void MukadeItem_TickHeldOrSnake_3839(Item *item, State *state)
{
    Vec3 bind;
    Vec3 wall;
    switch (item->subphase) {
    case 0:
        if (*(int *)((char *)item + 0x10) != 0) {
            float speed = g_ccClass == 0 ? lbl_806D5EB0 : lbl_806D5EB4;
            Vec3 probe = item->pos;
            Item_BendVelocityByGroundProbe(&item->velocity, &probe, item->rotation.y,
                speed, lbl_806D5E78);
            {
                Vec3 pos = item->pos;
                KartDriver_TransformWorldToLocalY0(&item->pos, &pos, state->owner);
            }
            item->param = lbl_806D5E7C;
            item->scale = lbl_806D5E9C;
            item->visible = 1;
            item->subphase = 2;
            item->step = 0;
            break;
        }
        item->subphase++;
        item->step = 0;
    case 1:
        switch (item->step) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
            item->visible = 1;
            item->scale = lbl_806D5E78;
            item->step++;
        case 1:
            if (FinalLapCoinJump_CheckActiveForObject(state->owner)) item->visible = 0;
            else item->visible = 1;
            bind = MukadeItem_TickHeldOrSnake_3839_rodata_8032F4B0;
            bind.x = lbl_806D5EB8 + KartCharacterParam_GetVfxBindHeightOffset(state->owner);
            {
                Vec3 offset;
                Vec3 rotation = MukadeItem_TickHeldOrSnake_3839_rodata_8032F4BC;
                offset = bind;
                Item_RenderCharacterScaledFromJoint12(item, &offset, &rotation, 1, lbl_806D5E7C);
            }
            switch (state->action) {
            case 1:
                item->visible = 1;
                state->action = 0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 0);
                Item_InitLaunchFromKart(item, &state->delta, lbl_806D5EBC, lbl_806D5E78);
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
            item->tracking = 1;
            item->x3c = 1;
            {
                Vec3 pos = item->pos;
                ItemObject_GetGroundTypeAt(&pos, &state->height, 0);
            }
            state->height = item->pos.y - state->height;
            state->timer = 300;
            state->lift = lbl_806D5E78;
            item->step++;
            item->reason = 0;
        case 1:
        default:
            break;
        }
        Item_HomingScanAndSteer(item, 0, 0);
        Item_AccelClampVelocity(item, g_ccClass == 0 ? lbl_806D5EB0 : lbl_806D5EB4,
            g_ccClass == 0 ? lbl_806D5E9C : lbl_806D5EA0);
        fn_801B129C(&item->pos);
        item->rotation.y = BuildOrientationFromYaw(lbl_806D5E88 + item->rotation.y);
        state->lift = BuildOrientationFromYaw(lbl_806D5E8C + state->lift);
        item->rotation.x = lbl_806D5E80 * (float)sin(state->lift);
        Item_DecayVelocityScalar(item, lbl_806D5E7C);
        {
            Vec3 pos = item->pos;
            state->target = FindNearestDriverWithinConeAndRadius(&pos, state->owner, 0,
                Vec3_ToYaw(&item->velocity), lbl_806D5EC0, lbl_806D5EC4);
        }
        if (state->target != 0) {
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 0;
            break;
        }
        if (item->tracking == 2) {
            item->tracking = 0;
            if (item->hit == 1) {
                Vec3 pos = item->pos;
                SoundMgr_PlaySE_Positional(0x86, &pos, 0);
                Vec3_Add_DestFirst(&item->velocity, &item->velocity, &item->impulse);
                item->velocity.y = lbl_806D5EA0;
                item->velocity.x *= lbl_806D5EC8;
                item->velocity.z *= lbl_806D5EC8;
                item->phase = 2;
                item->subphase = 0;
                item->reason = 4;
            } else {
                item->phase = 2;
                item->subphase = 0;
                item->reason = 6;
            }
            break;
        }
        if (Item_CheckWallCollision(item, &wall, 0)) {
            Vec3 normal;
            item->tracking = 0;
            normal = wall;
            Item_BounceOffWall(item, &normal, 0x86, 2, lbl_806D5E98, lbl_806D5EA0);
            item->rotation.x = BuildOrientationFromYaw(lbl_806D5EA4 + item->rotation.x);
            item->phase = 2;
            item->subphase = 0;
            item->reason = 7;
            break;
        }
        if (!Item_AdvanceProjectileSimple(item, &state->height, lbl_806D5ECC, lbl_806D5ECC)) {
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 9;
            break;
        }
        if (state->timer == 0) {
            item->tracking = 0;
            item->phase = 2;
            item->subphase = 0;
            item->reason = 5;
        }
        break;
    }
}

static inline void MukadeItem_FallAndFade(Item *item, State *state)
{
    switch (item->subphase) {
    case 0:
        {
            Vec3 pos = item->pos;
            ItemObject_GetGroundTypeAt(&pos, &state->height, 0);
        }
        if (item->reason != 5) state->timer = 10;
        else state->timer = 0;
        if (item->reason == 5) item->velocity.y = lbl_806D5E78;
        item->subphase++;
    case 1:
    default:
        break;
    }
    if (state->timer == 0) {
        item->scale -= lbl_806D5EA8;
        if (item->scale < lbl_806D5E78) {
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            return;
        }
    }
    if (item->reason != 5) item->velocity.y += lbl_806D5E94;
    {
        float height;
        Vec3 pos = item->pos;
        if (ItemObject_GetGroundTypeAt(&pos, &height, 0)) {
            item->pos.y += height - state->height;
            state->height = height;
        }
    }
    if (item->reason != 5) item->rotation.x = BuildOrientationFromYaw(lbl_806D5EAC + item->rotation.x);
    Item_DecayVelocityScalar(item, lbl_806D5E7C);
}

void MukadeItem_Dispatch_3839(Item *item)
{
    State *state = (State *)((char *)item + 0xec);
    switch (item->phase) {
    case 0:
        if (item->id == 0x39) SpriteSlot_InitNonLoop(item->sprite, 0x3d);
        else SpriteSlot_InitNonLoop(item->sprite, 0x3e);
        item->flags8c = 3;
        item->tracking = 0;
        item->phase = 1;
        item->subphase = 0;
    case 1:
        MukadeItem_TickHeldOrSnake_3839(item, state);
        break;
    case 2:
        switch (item->reason) {
        case 0:
            MukadeItem_Tick_HeldAndHoming_3839(item, state);
            break;
        case 4:
            MukadeItem_FallAndFade(item, state);
            break;
        case 6:
            switch (item->subphase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D5E78, lbl_806D5E78, lbl_806D5E78);
                item->x3c = 0;
                Vec3_Subtract_DestFirst(&state->delta, &item->pos, &item->anchor->pos);
                state->timer = 30;
                item->subphase++;
            case 1:
            default:
                break;
            }
            Item_DecayVelocityScalar(item, lbl_806D5E7C);
            if (Item_OrbitAnchorKart(item, &state->delta, (void *)state->timer, lbl_806D5E80, lbl_806D5E80)) {
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
            }
            break;
        case 7:
            MukadeItem_FallAndFade(item, state);
            break;
        case 9:
            MukadeItem_FallAndFade(item, state);
            break;
        case 5:
            MukadeItem_FallAndFade(item, state);
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->pos, &item->pos, &item->velocity);
    {
        Vec3 pos;
        Vec3 rotation = item->rotation;
        pos = item->pos;
        SpriteSlot_SetTransform(item->sprite, &pos, &rotation, item->param);
    }
    if (state->timer) state->timer--;
    if (state->x8) state->x8--;
    if (state->xc) state->xc--;
    if (state->x10) state->x10--;
}

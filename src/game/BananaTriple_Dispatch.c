/* Banana variants 0x32..0x36: initialize, dispatch their state, and update rendering. */
#include "game/BananaTripleDispatchPrivate.h"

#pragma exceptions on
void BananaTriple_Dispatch_32to36(Item *item)
{
    float matrix[4][4];
    Vec3 position;
    BananaState *state = (BananaState *)((char *)item + 0xec);
    switch (item->phase) {
    case 0:
        state->active = 1;
        switch (item->id) {
        case 0x32: state->variant = 0; break;
        case 0x33: state->variant = 1; break;
        case 0x34: state->variant = 2; break;
        case 0x35: state->variant = 3; break;
        case 0x36: state->variant = 4; break;
        }
        SpriteSlot_InitNonLoop(item->sprite, lbl_806CF3C0[state->variant]);
        item->sprite[0] = 4;
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
        state->matrixEnabled = 1;
        SpriteSlot_SetJointVisibilityByName(item->sprite, BananaTriple_data_804211B0[state->variant], 16, 1);
        SpriteSlot_SetJointVisibilityByName(item->sprite, BananaTriple_data_804211B0[state->variant] + 0x40, 16, 0);
        switch (item->id) {
        case 0x32: case 0x33: case 0x35:
            item->flags8c = 2; item->tracking = 0; break;
        case 0x34: case 0x36:
            item->flags8c = 3; item->tracking = 0; break;
        }
        if (item->id == 0x33) state->effect = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Update);
        item->phase = 1; item->subphase = 0;
    case 1:
        BananaTriple_Tick_HeldAndHoming_32to36(item, state);
        break;
    case 2:
        switch (item->reason) {
        case 0: BananaTriple_StuckOnDriverTick_32to36(item, state); break;
        case 3:
            switch (item->subphase) {
            case 0:
                GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
                item->x3c = 0;
                state->height = 0.0f;
                state->lift = item->param;
                item->subphase++;
                break;
            case 1: break;
            }
            if (Item_AdvanceTetherToJoint13(item, &state->height, state->lift, 0.08726644515991211f, 0.08726644515991211f)) {
                item->visible = 0; item->phase = 3; item->subphase = 0;
            }
            break;
        case 4: BananaTriple_OnImpactTick_32to36(item, state); break;
        case 6:
            switch (item->subphase) {
            case 0:
                GetSpawnPosition(&item->velocity, 0.0f, 0.0f, 0.0f);
                item->x3c = 0;
                Vec3_Subtract_DestFirst(&state->delta, &item->pos, &item->anchor->pos);
                state->timer = 30;
                item->subphase++;
                break;
            case 1: break;
            }
            if (item->id != 0x34) Item_DecayVelocityScalar(item, 2.5f);
            else Item_DecayVelocityScalar(item, 8.0f);
            if (Item_OrbitAnchorKart(item, &state->delta, state->timer, 0.26179933547973633f, 0.26179933547973633f)) {
                item->visible = 0; item->phase = 3; item->subphase = 0;
            }
            break;
        case 9: BananaTriple_OnImpactTick_32to36(item, state); break;
        case 5: BananaTriple_OnImpactTick_32to36(item, state); break;
        }
        break;
    case 3:
        if (item->id == 0x33) {
            if (state->effect) state->effect->subphase = 1;
            state->effect = 0;
        }
        if (item->id != 0x35 && item->id != 0x36) ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->pos, &item->pos, &item->velocity);
    if (state->matrixEnabled) {
        Matrix4_Identity(matrix);
        Mtx44_Scale_Uniform(matrix, matrix, item->param);
        Matrix4_PreMultiplyRotZ(matrix, matrix, item->rotation.z);
        Matrix4_PreMultiplyRotX(matrix, matrix, item->rotation.x);
        Matrix4_PreMultiplyRotY(matrix, matrix, item->rotation.y);
        Mtx44_Translate(matrix, matrix, item->pos);
        DbgScene_CopyMatrix3x4Transpose((char *)item + 0x48, matrix);
    }
    SpriteSlot_TickAnim(item->sprite);
    if (item->id == 0x33) {
        JointByName_GetWorldPosition(&position, item->sprite, lbl_8032F41C);
        /* This dispatcher consumes the visibility flag as a signed byte. */
        if (*(signed char *)&item->visible) Effect_SparkSpray_PlaceChildren(state->effect, position, 1.5f * item->param, item->scale);
        else Effect_SparkSpray_PlaceChildren(state->effect, position, 1.5f * item->param, 0.0f);
    }
    if (state->timer) state->timer--;
    if (state->timer8) state->timer8--;
    if (state->timerC) state->timerC--;
    if (state->timer10) state->timer10--;
}
#pragma exceptions reset

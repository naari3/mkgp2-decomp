#include "game/TaruItemDispatch25Private.h"

extern void SpriteSlot_InitNonLoop(void *, int);
extern void SpriteSlot_SetJointVisibilityByName(void *, const void *, int, int);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *, int);
extern void TaruItem_Tick_HeldAndHoming_25(Item *, TaruState *);
extern void TaruItem_OnGroundDriftTick_25(Item *, TaruState *);
extern void *KartDriver_GetKartRootMtx(void *);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void Item_PrepareHitRebound(Item *, Vec3 *, Vec3 *, unsigned int *);
extern void ItemHit_Dispatch(Item *, int, int, void *);
extern void ShellPile_Spawn(Item *, TaruState *);
#ifndef __MWERKS__ /* this unit passes the position as the address of its own copy (SoundMgr_PlaySE_Positional.c) */
#define SoundMgr_PlaySE_Positional SoundMgr_PlaySE_Positional_ByAddress
#endif
extern void SoundMgr_PlaySE_Positional(int, Vec3 *, int);
extern void Vec3_AddNormalizedXZ(Item *, Vec3 *, Vec3 *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Item_DecayVelocityScalar(Item *, float);
extern float BuildOrientationFromYaw(float);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern int Item_AdvanceTetherToJoint13(Item *, float *, float, float, float);
extern void ItemObject_DecrementCategoryBudget(Item *);
extern void SpriteSlot_Container_Free(Item *);
extern void Matrix4_Identity(float *);
extern void Mtx44_Scale_Uniform(float *, float *, float);
extern void Matrix4_PreMultiplyRotX(float *, float *, float);
extern void Matrix4_PreMultiplyRotY(float *, float *, float);
extern void Matrix4_PreMultiplyRotZ(float *, float *, float);
extern void Mtx44_Translate(float *, float *, Vec3 *);
extern void DbgScene_CopyMatrix3x4Transpose(void *, float *);
extern char lbl_8032F458[], lbl_8032F468[];
#pragma exceptions on
void TaruItem_Dispatch_25(Item *item)
{
    TaruState *state = (TaruState *)((char *)item + 0xec);
    float matrix[16];
    Vec3 translation;
    switch (item->phase) {
    case 0:
        SpriteSlot_InitNonLoop(item->sprite, 0x3b);
        SpriteSlot_SetJointVisibilityByName(item->sprite, lbl_8032F458, 0x10, 0);
        SpriteSlot_SetJointVisibilityByName(item->sprite, lbl_8032F468, 0x10, 1);
        SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite, 1);
        state->render = 1;
        item->flags8c = 4;
        item->tracking = 0;
        item->phase = 1;
        item->subphase = 0;
    case 1:
        TaruItem_Tick_HeldAndHoming_25(item, state);
        break;
    case 2:
        switch (item->reason) {
        case 0: {
            Vec3 velocity, base;
            Mtx44_GetTranslation_RowMajor(&base, KartDriver_GetKartRootMtx(state->driver));
            switch (item->subphase) {
            case 0:
                Item_PrepareHitRebound(item, &state->offset, &state->velocity, &state->timer);
                item->subphase++;
                break;
            case 1: break;
            }
            if (state->timer == 0) {
                Vec3 sound;
                if (state->hit) ItemHit_Dispatch(item, 0, 0, state->driver);
                ShellPile_Spawn(item, state);
                sound = item->pos;
                SoundMgr_PlaySE_Positional(0xbe, &sound, 0);
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
            } else {
                velocity = state->velocity;
                Vec3_AddNormalizedXZ(item, &state->offset, &velocity);
                Vec3_Add_DestFirst(&item->pos, &base, &state->offset);
                Item_DecayVelocityScalar(item, 5.0f);
                item->rotation.x = BuildOrientationFromYaw(0.26179934f + item->rotation.x);
            }
            break;
        }
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
            if (Item_AdvanceTetherToJoint13(item, &state->height, state->lift, 0.087266445f, 0.087266445f)) {
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
            }
            break;
        case 4: {
            Vec3 sound;
            ShellPile_Spawn(item, state);
            sound = item->pos;
            SoundMgr_PlaySE_Positional(0xbe, &sound, 0);
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            break;
        }
        case 7: {
            Vec3 sound;
            ShellPile_Spawn(item, state);
            sound = item->pos;
            SoundMgr_PlaySE_Positional(0xbe, &sound, 0);
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            break;
        }
        case 9: TaruItem_OnGroundDriftTick_25(item, state); break;
        case 5: TaruItem_OnGroundDriftTick_25(item, state); break;
        case 1: case 2: case 6: case 8: break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->pos, &item->pos, &item->velocity);
    if (state->render) {
        Matrix4_Identity(matrix);
        Mtx44_Scale_Uniform(matrix, matrix, item->param);
        Matrix4_PreMultiplyRotX(matrix, matrix, item->rotation.x);
        Matrix4_PreMultiplyRotZ(matrix, matrix, item->rotation.z);
        Matrix4_PreMultiplyRotY(matrix, matrix, item->rotation.y);
        translation = item->pos;
        Mtx44_Translate(matrix, matrix, &translation);
        DbgScene_CopyMatrix3x4Transpose((char *)item + 0x48, matrix);
    }
    if (state->timer) state->timer--;
    if (state->timer2) state->timer2--;
    if (state->timer3) state->timer3--;
    if (state->timer4) state->timer4--;
}
#pragma exceptions reset

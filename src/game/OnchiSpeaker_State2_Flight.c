#include "game/OnchiSpeakerFlightPrivate.h"
extern float BuildOrientationFromYaw(float);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern signed char ItemObject_GetGroundTypeAt(Vec3, float *, int);
extern void Item_DecayVelocityScalar(Item *, float);
extern void *KartDriver_GetKartRootMtx(void *);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *, int, float);
extern void SpriteSlot_SetScale(void *, float);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Vec3_Copy(Vec3 *, Vec3 *);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern const float lbl_806D5F18, lbl_806D5F1C, lbl_806D5F20, lbl_806D5F2C;
extern const float lbl_806D5F40, lbl_806D5F44, lbl_806D5F48;
#pragma exceptions on
void OnchiSpeaker_State2_Flight(Item *item, OnchiFlightState *state)
{
    Vec3 initialRoot;
    Vec3 root;
    float height;
    switch (item->subphase) {
    case 0:
        SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D5F18);
        SpriteSlot_SetScale(item->sprite, lbl_806D5F1C);
        ItemObject_GetGroundTypeAt(item->pos, &state->height, 0);
        if ((int)(unsigned char)item->reason != 5) state->timer = 10;
        else state->timer = 0;
        if ((int)(unsigned char)item->reason == 5) item->velocity.y = lbl_806D5F18;
        if (state->driver) {
            Mtx44_GetTranslation_RowMajor(&initialRoot, KartDriver_GetKartRootMtx(state->driver));
            Vec3_Subtract_DestFirst(&state->offset, &item->pos, &initialRoot);
            Vec3_Copy(&state->delta, &item->velocity);
            GetSpawnPosition(&item->velocity, lbl_806D5F18, lbl_806D5F18, lbl_806D5F18);
        }
        item->subphase++;
        break;
    case 1:
        break;
    }
    if (state->timer == 0) {
        item->scale -= lbl_806D5F2C;
        if (item->scale < lbl_806D5F18) {
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            return;
        }
    }
    Item_DecayVelocityScalar(item, lbl_806D5F20);
    switch (item->reason) {
    case 1:
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D5F40);
        break;
    case 4:
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D5F40);
        break;
    case 7:
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D5F40);
        break;
    case 9:
        item->rotation.x = BuildOrientationFromYaw(lbl_806D5F48 + item->rotation.x);
        break;
    }
    if (state->driver == 0) {
        if ((int)(unsigned char)item->reason != 5) item->velocity.y += lbl_806D5F44;
        if (ItemObject_GetGroundTypeAt(item->pos, &height, 0)) {
            item->pos.y += height - state->height;
            state->height = height;
        }
    } else {
        state->delta.y += lbl_806D5F44;
        Vec3_Add_DestFirst(&state->offset, &state->offset, &state->delta);
        Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(state->driver));
        Vec3_Add_DestFirst(&item->pos, &root, &state->offset);
    }
}
#pragma exceptions reset

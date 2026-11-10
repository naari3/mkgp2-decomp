#include "game/objview/item_state_private.h"

extern float BuildOrientationFromYaw(float);
#ifdef __MWERKS__
extern signed char ItemObject_GetGroundTypeAt(Vec3, float *, int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(Vec3 *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(Vec3 a0, float *a1, int a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
extern void Item_DecayVelocityScalar(Item *, float);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *, int, float);
extern void SpriteSlot_SetScale(void *, float);
extern const float lbl_806D5D90, lbl_806D5D94, lbl_806D5D98;
extern const float lbl_806D5DA0, lbl_806D5DAC, lbl_806D5DB0, lbl_806D5DB4;

#pragma exceptions on
void BananaTriple_OnImpactTick_32to36(Item *item, State *state)
{
    float height;
    switch (item->subphase) {
    case 0:
        ItemObject_GetGroundTypeAt(item->pos, &state->height, 0);
        if ((int)(unsigned char)item->reason != 5) state->timer = 10;
        else state->timer = 0;
        if ((int)(unsigned char)item->reason == 4) {
            SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 6, lbl_806D5D90);
            SpriteSlot_SetScale(item->sprite, lbl_806D5DAC);
        }
        item->subphase++;
        break;
    case 1:
        break;
    }
    if (state->timer == 0) {
        item->scale -= lbl_806D5DB0;
        if (item->scale < lbl_806D5D90) {
            item->visible = 0;
            item->phase = 3;
            item->subphase = 0;
            return;
        }
    }
    if (item->id != 0x34) Item_DecayVelocityScalar(item, lbl_806D5D94);
    else Item_DecayVelocityScalar(item, lbl_806D5D98);
    if ((int)(unsigned char)item->reason != 5) {
        if (ItemObject_GetGroundTypeAt(item->pos, &height, 0)) {
            item->pos.y += height - state->height;
            state->height = height;
        }
        item->velocity.y += lbl_806D5DB4;
        if ((int)(unsigned char)item->reason == 4)
            item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D5DA0);
        else
            item->rotation.x = BuildOrientationFromYaw(lbl_806D5DA0 + item->rotation.x);
    }
}
#pragma exceptions reset

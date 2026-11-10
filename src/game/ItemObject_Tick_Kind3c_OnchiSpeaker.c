#include "game/OnchiSpeakerTickPrivate.h"
#ifdef __MWERKS__
extern void DrawEffect_KartImpactRing_AdvanceByVfxDelta(void *, Vec3, float, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void DrawEffect_KartImpactRing_AdvanceByVfxDelta(void *, Vec3 *, float, float);
static inline void DrawEffect_KartImpactRing_AdvanceByVfxDelta_ByValue(void *a0, Vec3 a1, float a2, float a3) { DrawEffect_KartImpactRing_AdvanceByVfxDelta(a0, &a1, a2, a3); }
#define DrawEffect_KartImpactRing_AdvanceByVfxDelta DrawEffect_KartImpactRing_AdvanceByVfxDelta_ByValue
#endif
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void ItemObject_DecrementCategoryBudget(Item *);
extern int Item_AdvanceTetherToJoint13(Item *, float *, float, float, float);
extern void Item_DecayVelocityScalar(Item *, float);
extern int Item_OrbitAnchorKart(Item *, Vec3 *, unsigned int, float, float);
extern void OnchiSpeaker_State1_Held(Item *, OnchiSpeakerTickState *);
extern void OnchiSpeaker_State2_Active(Item *, OnchiSpeakerTickState *);
extern void OnchiSpeaker_State2_Flight(Item *, OnchiSpeakerTickState *);
extern void SpriteSlot_Container_Free(Item *);
extern void SpriteSlot_InitNonLoop(void *, int);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *, int, float);
extern void SpriteSlot_SetScale(void *, float);
#ifdef __MWERKS__
extern void SpriteSlot_SetTransform(void *, Vec3, Vec3, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void SpriteSlot_SetTransform(void *, Vec3 *, Vec3 *, float);
static inline void SpriteSlot_SetTransform_ByValue(void *a0, Vec3 a1, Vec3 a2, float a3) { SpriteSlot_SetTransform(a0, &a1, &a2, a3); }
#define SpriteSlot_SetTransform SpriteSlot_SetTransform_ByValue
#endif
extern void SpriteSlot_TickAnim(void *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern const float lbl_806D5F18, lbl_806D5F1C, lbl_806D5F20, lbl_806D5F24, lbl_806D5F28;
#pragma exceptions on
void ItemObject_Tick_Kind3c_OnchiSpeaker(Item *item)
{
    OnchiSpeakerTickState *state = (OnchiSpeakerTickState *)((char *)item + 0xec);
    switch (item->phase) {
    case 0:
        SpriteSlot_InitNonLoop(item->sprite, 0x40);
        item->sprite[0] = 4;
        item->flags8c = 3;
        item->tracking = 0;
        item->phase = 1;
        item->subphase = 0;
    case 1:
        OnchiSpeaker_State1_Held(item, state);
        break;
    case 2:
        switch (item->reason) {
        case 0: OnchiSpeaker_State2_Active(item, state); break;
        case 1: OnchiSpeaker_State2_Flight(item, state); break;
        case 3:
            switch (item->subphase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D5F18, lbl_806D5F18, lbl_806D5F18);
                item->x3c = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D5F18);
                SpriteSlot_SetScale(item->sprite, lbl_806D5F1C);
                state->height = lbl_806D5F18;
                state->lift = item->param;
                item->subphase++;
                break;
            case 1: break;
            }
            if (Item_AdvanceTetherToJoint13(item, &state->height, state->lift, lbl_806D5F28, lbl_806D5F28)) {
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
            }
            break;
        case 4: OnchiSpeaker_State2_Flight(item, state); break;
        case 6:
            switch (item->subphase) {
            case 0:
                GetSpawnPosition(&item->velocity, lbl_806D5F18, lbl_806D5F18, lbl_806D5F18);
                item->x3c = 0;
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 0, lbl_806D5F18);
                SpriteSlot_SetScale(item->sprite, lbl_806D5F1C);
                Vec3_Subtract_DestFirst(&state->delta, &item->pos, &item->anchor->pos);
                state->timer = 30;
                item->subphase++;
                break;
            case 1: break;
            }
            Item_DecayVelocityScalar(item, lbl_806D5F20);
            if (Item_OrbitAnchorKart(item, &state->delta, state->timer, lbl_806D5F24, lbl_806D5F24)) {
                item->visible = 0;
                item->phase = 3;
                item->subphase = 0;
            }
            break;
        case 7: OnchiSpeaker_State2_Flight(item, state); break;
        case 9: OnchiSpeaker_State2_Flight(item, state); break;
        case 5: OnchiSpeaker_State2_Flight(item, state); break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(item);
        SpriteSlot_Container_Free(item);
        return;
    }
    Vec3_Add_DestFirst(&item->pos, &item->pos, &item->velocity);
    SpriteSlot_SetTransform(item->sprite, item->pos, item->rotation, item->param);
    SpriteSlot_TickAnim(item->sprite);
    if (*(signed char *)&item->visible) {
        DrawEffect_KartImpactRing_AdvanceByVfxDelta(state->effect, item->pos, item->param, item->scale);
    } else {
        DrawEffect_KartImpactRing_AdvanceByVfxDelta(state->effect, item->pos, item->param, lbl_806D5F18);
    }
    if (state->timer) state->timer--;
    if (state->timer8) state->timer8--;
    if (state->timerc) state->timerc--;
    if (state->timer10) state->timer10--;
}
#pragma exceptions reset

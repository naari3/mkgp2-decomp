#include "game/BananaTripleStuckPrivate.h"
extern void *KartDriver_GetKartRootMtx(void *);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void Item_PrepareHitRebound(Item *, Vec3 *, Vec3 *, unsigned int *);
extern void Vec3_Copy(Vec3 *, Vec3 *);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
#ifdef __MWERKS__
extern void Vec3_AddNormalizedXZ(Item *, Vec3 *, Vec3);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Vec3_AddNormalizedXZ(Item *, Vec3 *, Vec3 *);
static inline void Vec3_AddNormalizedXZ_ByValue(Item *a0, Vec3 *a1, Vec3 a2) { Vec3_AddNormalizedXZ(a0, a1, &a2); }
#define Vec3_AddNormalizedXZ Vec3_AddNormalizedXZ_ByValue
#endif
extern void ItemHit_Dispatch(Item *, int, Vec3 *, void *);
extern void SpriteSlot_SetAnimFrameAndApplyScale(void *, int, float);
extern void SpriteSlot_SetScale(void *, float);
extern float BuildOrientationFromYaw(float);
extern void Item_DecayVelocityScalar(Item *, float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
extern const float lbl_806D5D90, lbl_806D5D94, lbl_806D5D98, lbl_806D5DA0;
extern const float lbl_806D5DA4, lbl_806D5DA8, lbl_806D5DAC, lbl_806D5DB0, lbl_806D5DB4;
#pragma exceptions on
void BananaTriple_StuckOnDriverTick_32to36(Item *item, BananaDriverState *state)
{
    Vec3 root;
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(state->driver));
    switch (item->subphase) {
    case 0:
        if (state->rebound) {
            Item_PrepareHitRebound(item, &state->offset, &state->delta, &state->timer);
            item->subphase = 1;
            item->step = 0;
        } else {
            Vec3_Copy(&state->delta, &item->velocity);
            GetSpawnPosition(&item->velocity, lbl_806D5D90, lbl_806D5D90, lbl_806D5D90);
            Vec3_Subtract_DestFirst(&state->offset, &item->pos, &root);
            item->subphase = 2;
            item->step = 0;
        }
        break;
    case 1:
        Vec3_AddNormalizedXZ(item, &state->offset, state->delta);
        if (state->timer == 0) {
            item->subphase = 2;
            item->step = 0;
        }
        break;
    case 2:
        switch (item->step) {
        case 0:
            if (state->dispatchHit) ItemHit_Dispatch(item, 0, &item->pos, state->driver);
            state->delta.y = lbl_806D5DA4;
            state->delta.x *= lbl_806D5DA8;
            state->delta.z *= lbl_806D5DA8;
            state->timer = 10;
            if (item->reason == 0 || item->reason == 4) {
                SpriteSlot_SetAnimFrameAndApplyScale(item->sprite, 6, lbl_806D5D90);
                SpriteSlot_SetScale(item->sprite, lbl_806D5DAC);
            }
            item->step++;
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
        state->delta.y += lbl_806D5DB4;
        Vec3_Add_DestFirst(&state->offset, &state->offset, &state->delta);
        item->rotation.x = BuildOrientationFromYaw(item->rotation.x - lbl_806D5DA0);
        break;
    }
    Vec3_Add_DestFirst(&item->pos, &root, &state->offset);
    if (item->id != 0x34) Item_DecayVelocityScalar(item, lbl_806D5D94);
    else Item_DecayVelocityScalar(item, lbl_806D5D98);
    if (FinalLapCoinJump_CheckActiveForObject(state->driver)) item->visible = 0;
    else item->visible = 1;
}
#pragma exceptions reset

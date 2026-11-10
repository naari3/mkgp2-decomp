#include "game/objview/item_state_private.h"
extern float lbl_806CFCF8;
extern Vec3 lbl_804963C0, lbl_804963CC;
extern const float lbl_806D9690, lbl_806D9694, lbl_806D9698, lbl_806D969C;
extern const float lbl_806D96A0, lbl_806D96A4, lbl_806D96A8, lbl_806D96AC, lbl_806D96BC;
extern void SpriteSlot_InitNonLoop(void *, int);
extern void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *, int);
extern void Item_RenderHandheldByCharacter(Item *, const Vec3 *, const Vec3 *, int, float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
extern void Item_InitLaunchFromKart(Item *, Vec3 *, float, float);
extern void *KartDriver_GetJointByIdx(void *, int);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void fn_80198F84(Item *, State *);
extern void fn_80198ABC(Item *, State *);
extern void Item_DecayVelocityScalar(Item *, float);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern int Item_OrbitAnchorKart(Item *, Vec3 *, unsigned int, float, float);
#ifdef __MWERKS__
extern char ItemObject_GetGroundTypeAt(Vec3, float *, void *);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern char ItemObject_GetGroundTypeAt(Vec3 *, float *, void *);
static inline char ItemObject_GetGroundTypeAt_ByValue(Vec3 a0, float *a1, void *a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
extern int Item_AdvanceProjectileSimple(Item *, float *, float, float);
extern void ItemObject_DecrementCategoryBudget(Item *);
extern void SpriteSlot_Container_Free(Item *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void SpriteSlot_SetTransform(void *, const Vec3 *, const Vec3 *, float);
static inline void Fade(Item *self, State *state) {
    switch (self->subphase) {
    case 0:
        self->rotation.z = lbl_806D96A8;
        state->timer = 10;
        self->subphase++;
    case 1:
        self->velocity.y += lbl_806D96AC;
        Item_DecayVelocityScalar(self, lbl_806D9690);
        if (state->timer == 0) {
            self->scale -= lbl_806D969C;
            if (self->scale < lbl_806D96A0) {
                self->visible = 0;
                self->phase = 3;
                self->subphase = 0;
            }
        }
        break;
    }
}
void fn_801992B0(Item *self) {
    /* Preserve the by-value vector copies used by these pointer ABIs. */
    Vec3 transformPos;
    Vec3 transformRot;
    Vec3 heldRot;
    Vec3 heldPos;
    State *state = (State *)((unsigned char *)self + 0xEC);
    switch (self->phase) {
    case 0:
        SpriteSlot_InitNonLoop(self->sprite, 0x85);
        self->flags8c = 3;
        self->tracking = 0;
        self->phase = 1;
        self->subphase = 0;
        self->step = 0;
    case 1:
        switch (self->subphase) {
        case 0:
            switch (self->step) {
            case 0:
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self->sprite, 1);
                self->visible = 1;
                self->scale = lbl_806D96A0;
                self->step++;
                break;
            case 1:
                break;
            }
            heldRot = lbl_804963CC;
            heldPos = lbl_804963C0;
            Item_RenderHandheldByCharacter(self, &heldPos, &heldRot, 1, lbl_806CFCF8);
            if (FinalLapCoinJump_CheckActiveForObject(state->owner)) self->visible = 0;
            else self->visible = 1;
            switch (state->action) {
            case 1:
                self->visible = 1;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(self->sprite, 0);
                self->scale = lbl_806D9698;
                state->action = 0;
                Item_InitLaunchFromKart(self, &state->delta, lbl_806D96BC, lbl_806D96A0);
                self->subphase++;
                self->step = 0;
                break;
            case 2:
                state->action = 0;
                self->visible = 0;
                self->phase = 3;
                self->subphase = 0;
                break;
            default:
                Mtx44_GetTranslation_RowMajor(&state->delta, KartDriver_GetJointByIdx(state->owner, 12));
                break;
            }
            break;
        case 1:
            fn_80198F84(self, state);
            break;
        }
        break;
    case 2:
        switch (self->reason) {
        case 0:
            fn_80198ABC(self, state);
            break;
        case 1:
            Fade(self, state);
            break;
        case 4:
            Fade(self, state);
            break;
        case 6:
            switch (self->subphase) {
            case 0:
                GetSpawnPosition(&self->velocity, lbl_806D96A0, lbl_806D96A0, lbl_806D96A0);
                self->x3c = 0;
                Vec3_Subtract_DestFirst(&state->delta, &self->pos, &self->anchor->pos);
                state->timer = 30;
                self->subphase++;
                break;
            case 1:
                break;
            }
            Item_DecayVelocityScalar(self, lbl_806D9690);
            if (Item_OrbitAnchorKart(self, &state->delta, state->timer, lbl_806D96A4, lbl_806D96A4)) {
                self->visible = 0;
                self->phase = 3;
                self->subphase = 0;
            }
            break;
        case 7:
            Fade(self, state);
            break;
        case 5:
            switch (self->subphase) {
            case 0:
                ItemObject_GetGroundTypeAt(self->pos, &state->height, 0);
                state->height = self->pos.y - state->height;
                self->subphase++;
            case 1:
                Item_DecayVelocityScalar(self, lbl_806D9690);
                Item_AdvanceProjectileSimple(self, &state->height, lbl_806D9694, lbl_806D9698);
                {
                    self->scale -= lbl_806D969C;
                    if (self->scale < lbl_806D96A0) {
                        self->visible = 0;
                        self->phase = 3;
                        self->subphase = 0;
                    }
                }
                break;
            }
            break;
        }
        break;
    case 3:
        ItemObject_DecrementCategoryBudget(self);
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(&self->pos, &self->pos, &self->velocity);
    transformRot = self->rotation;
    transformPos = self->pos;
    SpriteSlot_SetTransform(self->sprite, &transformPos, &transformRot, self->param);
    if (state->timer != 0) state->timer--;
    if (state->x8 != 0) state->x8--;
    if (state->xc != 0) state->xc--;
    if (state->x10 != 0) state->x10--;
}

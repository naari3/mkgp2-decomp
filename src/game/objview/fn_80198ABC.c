#include "game/objview/item_state_private.h"
#include "game/types/HitEffect.h"
extern const float lbl_8037DD48[];
extern void *KartDriver_GetKartRootMtx(void *);
extern void Mtx44_GetTranslation_RowMajor(Vec3 *, void *);
extern void GetSpawnPosition(Vec3 *, float, float, float);
extern void *KartDriver_GetJointByIdx(void *, int);
extern int KartCharacterParam_GetIdentityIndex(void *);
#ifdef __MWERKS__
extern void Vec3_Lerp(Vec3 *, Vec3, Vec3, float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Vec3_Lerp(Vec3 *, Vec3 *, Vec3 *, float);
static inline void Vec3_Lerp_ByValue(Vec3 *a0, Vec3 a1, Vec3 a2, float a3) { Vec3_Lerp(a0, &a1, &a2, a3); }
#define Vec3_Lerp Vec3_Lerp_ByValue
#endif
extern int KartItem_QueryEffectStateFromIse(void *);
extern void KartItem_ApplyEffectToTarget(Item *, void *, int);
extern short ItemAlias_HitRemapLookup(int);
extern void *ItemTracker_GetTargetKart(Item *);
extern void fn_801B1D5C(void *, void *, int, int);
extern void ItemHit_Dispatch(Item *, int, Vec3 *, void *);
extern void SoundMgr_PlaySE_Positional(int, Vec3, int);
extern void Effect_KartJoint15_Res7B_Update(HitEffect *);
extern HitEffect *DrawEffect_SpawnDirect(void (*)(HitEffect *));
extern void Vec3_Copy(Vec3 *, Vec3 *);
extern void fn_801B1660(void *, void *);
extern void fn_801B158C(void *, void *);
extern void Vec3_Subtract_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Vec3_Add_DestFirst(Vec3 *, Vec3 *, Vec3 *);
extern void Item_DecayVelocityScalar(Item *, float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);

void fn_80198ABC(Item *self, State *state) {
    Vec3 root;
    Vec3 joint;
    int result;
    HitEffect *effect;
    Mtx44_GetTranslation_RowMajor(&root, KartDriver_GetKartRootMtx(state->target));
    switch (self->subphase) {
    case 0:
        GetSpawnPosition(&self->velocity, 0.0f, 0.0f, 0.0f);
        state->count = 3;
        self->subphase++;
        self->step = 0;
    case 1:
        switch (self->step) {
        case 2:
            break;
        case 0:
            state->height = 0.0f;
            state->lift = 11.0f;
            state->timer = 20;
            state->gravity = 0.0f;
            self->step++;
        case 1:
            if (state->timer == 0) self->step++;
            break;
        }
        {
            float step, limit, value;
            value = state->height;
            step = 0.2f;
            limit = 1.0f;
            state->height = value + step;
            if (limit < state->height) state->height = limit;
        }
        if (state->timer == 0) state->gravity += -0.1f;
        {
            float zero, gravity, lift;
            lift = state->lift;
            gravity = state->gravity;
            zero = 0.0f;
            state->lift = lift + gravity;
            if (state->lift <= zero) state->lift = zero;
        }
        Mtx44_GetTranslation_RowMajor(&joint, KartDriver_GetJointByIdx(state->target, 15));
        joint.y += self->param + (state->lift + lbl_8037DD48[KartCharacterParam_GetIdentityIndex(state->target)]);
        Vec3_Lerp(&self->pos, joint, self->pos, state->height);
        if (state->lift <= 0.0f) {
            result = KartItem_QueryEffectStateFromIse(state->target);
            KartItem_ApplyEffectToTarget(self, state->target, result);
            switch (result) {
            case 1:
                result = ItemAlias_HitRemapLookup(self->id);
                fn_801B1D5C(state->owner, ItemTracker_GetTargetKart(self), result, 0);
                ItemHit_Dispatch(self, 0, &self->pos, state->target);
                SoundMgr_PlaySE_Positional(0xCB, self->pos, 0);
                effect = DrawEffect_SpawnDirect(Effect_KartJoint15_Res7B_Update);
                if (effect != 0) {
                    Vec3_Copy(&effect->position, &self->pos);
                    effect->scale = self->param;
                    effect->target = state->target;
                }
                break;
            case 2:
                fn_801B1660(state->owner, ItemTracker_GetTargetKart(self));
            case 3:
                if (result == 3) fn_801B158C(state->owner, ItemTracker_GetTargetKart(self));
                SoundMgr_PlaySE_Positional(0xCB, self->pos, 0);
                break;
            case 5:
                self->subphase = 2;
                self->step = 0;
                state->count = 1;
                state->height = state->gravity;
                Vec3_Subtract_DestFirst(&state->delta, &self->pos, &root);
                return;
            }
            if (state->count != 0) state->count--;
            if (state->count != 0) {
                self->step = 0;
            } else {
                self->subphase = 2;
                self->step = 0;
                state->count = 0;
                Vec3_Subtract_DestFirst(&state->delta, &self->pos, &root);
                return;
            }
        }
        break;
    case 2:
        switch (self->step) {
        case 0:
            if (state->count == 0) state->height = 2.0f;
            state->timer = 10;
            self->step++;
            break;
        case 1:
            break;
        }
        if (state->timer == 0) {
            self->scale -= 0.05f;
            if (self->scale < 0.0f) {
                self->visible = 0;
                self->phase = 3;
                self->subphase = 0;
                return;
            }
        }
        state->height += -0.1f;
        state->delta.y += state->height;
        Vec3_Add_DestFirst(&self->pos, &root, &state->delta);
        break;
    }
    Item_DecayVelocityScalar(self, 5.0f);
    if (FinalLapCoinJump_CheckActiveForObject(state->target)) {
        self->visible = 0;
    } else {
        self->visible = 1;
    }
}

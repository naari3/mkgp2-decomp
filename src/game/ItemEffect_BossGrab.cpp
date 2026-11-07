/* Boss grab item effect: copies the pose into the grab state. */
#include "game/ItemEffectArmPrivate.h"

extern "C" {
extern const float lbl_806D27F8;
void *CarObject_GetRenderObj(void *);
void ItemEffectBus_OrMask(void *, unsigned long long);
}

extern "C" int ItemEffect_BossGrab(BossGrabSlot *__restrict slot, const ArmMtx *__restrict pose,
                                   int flags, int duration)
{
    if (slot->armed != 0) return 0;
    slot->armed = slot->state;
    BossGrabState *state = slot->state;
    state->Reset();
    state->timer = 0;
    state->elapsed = lbl_806D27F8;
    for (int i=0;i<16;i++) ((float *)&state->start)[i]=((float *)pose)[i];
    for (int i=0;i<16;i++) ((float *)&state->current)[i]=((float *)pose)[i];
    state->duration = duration;
    float x, y, z;
    z=state->start.m[14];
    y=state->start.m[13];
    x=state->start.m[12];
    state->position.x=x; state->position.y=y; state->position.z=z;
    state->owner->car->held = 0;
    state->flags = flags;
    ItemEffectBus_OrMask(*(void **)((char *)CarObject_GetRenderObj(state->owner->car) + 0x304), 0x20000000000ULL);
    return 1;
}

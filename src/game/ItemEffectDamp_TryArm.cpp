/* Built with GC/2.6 (constant load scheduling). */
#include "game/ItemEffectArmPrivate.h"

extern "C" const float lbl_806D2824;

extern "C" int ItemEffectDamp_TryArm(DampArmSlot *slot, const ArmVec *__restrict velocity,
                                    int flags, float strength, float duration)
{
    if (slot->armed != 0) return 0;
    slot->armed = slot->state;
    DampArmState *state = slot->state;
    state->Reset();
    state->velocity = *velocity;
    state->velocity.x *= lbl_806D2824;
    state->velocity.y *= lbl_806D2824;
    state->velocity.z *= lbl_806D2824;
    state->strength = strength;
    state->duration = duration;
    state->flags = flags;
    return 1;
}

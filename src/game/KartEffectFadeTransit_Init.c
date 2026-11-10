#include "game/types/KartEffectFadeTransit.h"

extern float lbl_806D2890;

KartEffectFadeTransit *KartEffectFadeTransit_Init(
    KartEffectFadeTransit *self, void *owner, void *effect, void *camera,
    unsigned char active)
{
    float zero;

    self->active = active;
    zero = lbl_806D2890;
    self->owner = owner;
    self->effect = effect;
    self->camera = camera;
    self->value = zero;
    self->target = zero;
    self->timer = 0;
    return self;
}

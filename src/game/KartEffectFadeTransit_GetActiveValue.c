#include "game/types/KartEffectFadeTransit.h"

unsigned int KartEffectFadeTransit_GetActiveValue(KartEffectFadeTransit *self)
{
    return self->timer;
}

unsigned char KartEffectFadeTransit_IsActive(KartEffectFadeTransit *self)
{
    return self->timer != 0;
}

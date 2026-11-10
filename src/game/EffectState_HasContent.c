#include "game/types/EffectState.h"

unsigned char EffectState_HasContent(EffectState *self)
{
    return self->content != 0;
}

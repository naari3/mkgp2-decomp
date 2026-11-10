#include "game/types/SpriteSlot.h"

void SpriteSlot_SetTranslateDxDy(SpriteSlot *slot, float dx, float dy)
{
    if (slot == 0) {
        return;
    }
    slot->translate_dx = dx;
    slot->translate_dy = dy;
}

#include "game/types/SpriteSlot.h"

void SpriteSlot_SetScale(SpriteSlot *slot, float scale)
{
    if (slot->object == 0) {
        return;
    }
    slot->speed = scale;
}

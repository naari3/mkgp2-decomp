#include "game/types/SpriteSlot.h"

extern void JObj_SetRotationQuat(void *object, float x, float y, float z);

void SpriteSlot_SetRotationQuat(SpriteSlot *slot, float x, float y, float z)
{
    if (slot->object != 0) {
        JObj_SetRotationQuat(slot->object, x, y, z);
    }
}

/* VfxSlot animation speed/frame setters; no-ops while the slot is unbound. */

#include "game/types/VfxSlot.h"

void VfxSlot_SetAnimSpeed(VfxSlot *self, float speed)
{
    if (self->slot != 0) {
        self->scale = speed;
    }
}

void VfxSlot_SetAnimFrame(VfxSlot *self, float frame)
{
    if (self->slot != 0) {
        self->animDone = 0;
        self->animFrame = frame;
    }
}

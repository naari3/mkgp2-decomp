/* Uniform scale on a bound VfxSlot's model. */
#include "game/types/VfxSlot.h"

extern void cLNormal3DWrap_Slot_SetScaleVec3(void *model, float x, float y, float z);

void VfxSlot_SetScaleUniform(VfxSlot *self, float scale)
{
    void *model = self->slot;

    if (model != 0) {
        cLNormal3DWrap_Slot_SetScaleVec3(model, scale, scale, scale);
    }
}

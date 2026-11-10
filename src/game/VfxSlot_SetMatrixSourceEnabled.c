/* Attach or detach the VfxSlot's own matrix as its model's matrix source. */
#include "game/types/VfxSlot.h"

extern void cLNormal3DWrap_Slot_SetMatrixSource(void *model, float (*mtx)[4]);
extern void cLNormal3DWrap_Slot_ClearMatrixSource(void *model);

void VfxSlot_SetMatrixSourceEnabled(VfxSlot *self, signed char enable)
{
    void *model = self->slot;

    if (model != 0) {
        if (enable) {
            cLNormal3DWrap_Slot_SetMatrixSource(model, self->mtx);
        } else {
            cLNormal3DWrap_Slot_ClearMatrixSource(model);
        }
    }
}

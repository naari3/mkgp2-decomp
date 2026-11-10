/* Position a bound VfxSlot's model from a vector. */
#include "game/types/VfxSlot.h"

#include "game/types/Vec3.h"

extern void cLNormal3DWrap_Slot_SetPositionXYZ(void *model, float x, float y, float z);

void VfxSlot_SetPositionFromVec(VfxSlot *self, const Vec3 *pos)
{
    void *model = self->slot;

    if (model != 0) {
        cLNormal3DWrap_Slot_SetPositionXYZ(model, pos->x, pos->y, pos->z);
    }
}

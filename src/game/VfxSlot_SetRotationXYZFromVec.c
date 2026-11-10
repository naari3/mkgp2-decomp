/* Rotate a bound VfxSlot's model from a vector. */
#include "game/types/VfxSlot.h"

#include "game/types/Vec3.h"

extern void cLNormal3DWrap_Slot_SetRotationXYZ(void *model, float x, float y, float z);

void VfxSlot_SetRotationXYZFromVec(VfxSlot *self, const Vec3 *rot)
{
    void *model = self->slot;

    if (model != 0) {
        cLNormal3DWrap_Slot_SetRotationXYZ(model, rot->x, rot->y, rot->z);
    }
}

#include "game/types/VfxSlot.h"

extern void cLNormal3DWrap_Slot_SetRotationXYZ(void* slot, float x, float y, float z);

void VfxSlot_SetRotationXYZ(VfxSlot* vfx, float x, float y, float z)
{
    if (vfx->slot != 0) {
        cLNormal3DWrap_Slot_SetRotationXYZ(vfx->slot, x, y, z);
    }
}

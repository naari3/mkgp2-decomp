#include "game/types/VfxSlot.h"

extern void cLNormal3DWrap_Slot_SetRotationZ(void* slot, float rotation);

void VfxSlot_SetRotationZ(VfxSlot* vfx, float rotation)
{
    if (vfx->slot != 0) {
        cLNormal3DWrap_Slot_SetRotationZ(vfx->slot, rotation);
    }
}

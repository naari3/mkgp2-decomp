#include "game/types/VfxSlot.h"

extern void cLNormal3DWrap_Slot_ResolveJoint(void* slot, void* joint);

void VfxSlot_ResolveJoint(VfxSlot* vfx, void* joint)
{
    if (vfx->slot != 0) {
        cLNormal3DWrap_Slot_ResolveJoint(vfx->slot, joint);
    }
}

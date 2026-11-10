#include "game/types/VfxSlot.h"

/* Callers pass (slot, x, y, z) and the callee takes the same; the three
 * floats stay in f1..f3 across this function. Written with the float
 * parameters MWCC emits other code, so that form is for other compilers. */
#ifdef __MWERKS__
extern void cLNormal3DWrap_Slot_SetScaleVec3(void* slot, const void* scale);
#else
extern void cLNormal3DWrap_Slot_SetScaleVec3(void* slot, float x, float y, float z);
#endif

#ifdef __MWERKS__
void VfxSlot_SetScaleVec3(VfxSlot* vfx, const void* scale)
#else
void VfxSlot_SetScaleVec3(VfxSlot* vfx, float x, float y, float z)
#endif
{
    if (vfx->slot != 0) {
#ifdef __MWERKS__
        cLNormal3DWrap_Slot_SetScaleVec3(vfx->slot, scale);
#else
        cLNormal3DWrap_Slot_SetScaleVec3(vfx->slot, x, y, z);
#endif
    }
}

/* Return a VfxSlot's model to the manager. */
#include "game/types/VfxSlot.h"

extern void *g_normal3DWrapMgr;
extern void cLNormal3DWrap_Mgr_ReleaseSlot(void *mgr, void *model);

void VfxSlot_Release(VfxSlot *self)
{
    if (self->slot != 0) {
        cLNormal3DWrap_Mgr_ReleaseSlot(g_normal3DWrapMgr, self->slot);
        self->slot = 0;
    }
}

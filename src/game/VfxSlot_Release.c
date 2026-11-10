/* Return a VfxSlot's model to the manager. */
#include "game/types/VfxSlot.h"

extern void *lbl_806D14A8;
extern void cLNormal3DWrap_Mgr_ReleaseSlot(void *mgr, void *model);

void VfxSlot_Release(VfxSlot *self)
{
    if (self->model != 0) {
        cLNormal3DWrap_Mgr_ReleaseSlot(lbl_806D14A8, self->model);
        self->model = 0;
    }
}

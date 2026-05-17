#include "sysdolphin/baselib/aobj.h"

void HSD_AObjReqAnim(HSD_AObj* aobj, float frame)
{
    unsigned int flags;
    if (aobj == 0) {
        return;
    }
    aobj->curr_frame = frame;
    flags = aobj->flags & ~AOBJ_NO_ANIM;
    aobj->flags = flags | AOBJ_FIRST_PLAY;
    HSD_FObjReqAnimAll(aobj->fobj, frame);
}

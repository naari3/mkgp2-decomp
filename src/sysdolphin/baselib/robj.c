#include "sysdolphin/baselib/robj.h"

static inline void HSD_RObjReqAnimByFlags(HSD_RObj* robj, float frame, u32 flags)
{
    if (robj == 0) {
        return;
    }
    if (robj->aobj != 0 && (flags & 0x80) != 0) {
        HSD_AObjReqAnim(robj->aobj, frame);
    }
}

void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, float frame, u32 flags)
{
    if (robj == 0) {
        return;
    }
    for (; robj != 0; robj = robj->next) {
        HSD_RObjReqAnimByFlags(robj, frame, flags);
    }
}

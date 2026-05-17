#include "sysdolphin/baselib/dobj.h"

static inline void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, float frame, u32 flags)
{
    if (dobj == 0) {
        return;
    }
    HSD_MObjReqAnimAllByFlags(dobj->mobj, frame, flags);
    HSD_PObjReqAnimByFlags(dobj->pobj, frame, flags);
}

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float frame, u32 flags)
{
    HSD_DObj* dp;
    if (dobj == 0) {
        return;
    }
    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, frame, flags);
    }
}

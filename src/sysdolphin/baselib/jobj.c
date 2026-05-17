#include "sysdolphin/baselib/jobj.h"

void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, unsigned int flags, float frame)
{
    int has_dobj;
    if (jobj != 0) {
        if (flags & 1) {
            HSD_AObjReqAnim(jobj->aobj, frame);
        }
        if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
            has_dobj = 0;
        } else {
            has_dobj = 1;
        }
        if (has_dobj) {
            HSD_DObjReqAnimAllByFlags(jobj->dobj, frame, flags);
        }
        HSD_RObjReqAnimAllByFlags(jobj->robj, frame, flags);
    }
}

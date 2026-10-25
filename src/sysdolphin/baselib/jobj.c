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

/* The child walk is inlined five levels deep in the target, which needs a
 * larger auto-inline size budget than the default. */
#pragma push
#pragma inline_max_size(600)
void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, unsigned int flags, float frame)
{
    HSD_JObj* child;

    if (jobj == 0) {
        return;
    }
    HSD_JObjReqAnimByFlags(jobj, flags, frame);
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        for (child = jobj->child; child != 0; child = child->next) {
            HSD_JObjReqAnimAllByFlags(child, flags, frame);
        }
    }
}
#pragma pop

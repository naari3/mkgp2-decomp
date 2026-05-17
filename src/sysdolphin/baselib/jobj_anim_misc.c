#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/fobj.h"
#include "sysdolphin/baselib/jobj.h"

extern void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, unsigned int flags, float frame);

void HSD_JObjReqAnimAll(HSD_JObj* jobj, float frame)
{
    HSD_JObjReqAnimAllByFlags(jobj, 0x7FF, frame);
}

/* HSD_JObjReqAnim is HSD_JObjReqAnimByFlags(jobj, 0x7FF, frame) inlined.
 * The wrapper form cannot reach 100% because HSD_JObjReqAnimByFlags lives in
 * a separate TU (jobj.c), so CW emits the call instead of expanding it. */
void HSD_JObjReqAnim(HSD_JObj* jobj, float frame)
{
    int has_dobj;
    if (jobj != 0) {
        HSD_AObjReqAnim(jobj->aobj, frame);
        if (jobj->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
            has_dobj = 0;
        } else {
            has_dobj = 1;
        }
        if (has_dobj) {
            HSD_DObjReqAnimAllByFlags(jobj->dobj, frame, 0x7FF);
        }
        HSD_RObjReqAnimAllByFlags(jobj->robj, frame, 0x7FF);
    }
}

void JObjSortAnim(HSD_AObj* aobj)
{
    HSD_FObj* fobj;
    HSD_FObj** fobj_ptr;

    if (aobj == 0 || aobj->fobj == 0) {
        return;
    }
    for (fobj_ptr = &aobj->fobj; *fobj_ptr != 0; fobj_ptr = &fobj->next) {
        fobj = *fobj_ptr;
        if (fobj->obj_type == TYPE_JOBJ) {
            *fobj_ptr = fobj->next;
            fobj->next = aobj->fobj;
            aobj->fobj = fobj;
            break;
        }
    }
}

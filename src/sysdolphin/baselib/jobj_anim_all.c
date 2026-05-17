#include "sysdolphin/baselib/aobj.h"
#include "sysdolphin/baselib/fobj.h"
#include "sysdolphin/baselib/jobj.h"

/* HSD_JObjReqAnimAllByFlags ships in mkgp2 as a manual 6-level tree walk
 * (levels 0-4 inline HSD_JObjReqAnimByFlags, level 5 calls it, level 6
 * recurses). My CW 1.3.2 build emits 716 bytes / 81% match; target is 712.
 * Held in a separate NonMatching TU so jobj.c stays 100% match for the other
 * four anim funcs. Promote back to Matching once the source converges. */

static void JObjReqAnimByFlagsInline(HSD_JObj* j, unsigned int flags, float frame)
{
    int has_dobj;
    if (flags & 1) {
        HSD_AObjReqAnim(j->aobj, frame);
    }
    if (j->flags & (JOBJ_PTCL | JOBJ_SPLINE)) {
        has_dobj = 0;
    } else {
        has_dobj = 1;
    }
    if (has_dobj) {
        HSD_DObjReqAnimAllByFlags(j->dobj, frame, flags);
    }
    HSD_RObjReqAnimAllByFlags(j->robj, frame, flags);
}

void HSD_JObjReqAnimAllByFlags(HSD_JObj* jobj, unsigned int flags, float frame)
{
    HSD_JObj* c1;
    HSD_JObj* c2;
    HSD_JObj* c3;
    HSD_JObj* c4;
    HSD_JObj* c5;
    HSD_JObj* c6;

    if (jobj == 0) {
        return;
    }
    JObjReqAnimByFlagsInline(jobj, flags, frame);
    if (jobj->flags & JOBJ_INSTANCE) {
        return;
    }
    c1 = jobj->child;
    while (c1 != 0) {
        JObjReqAnimByFlagsInline(c1, flags, frame);
        if (!(c1->flags & JOBJ_INSTANCE)) {
            c2 = c1->child;
            while (c2 != 0) {
                JObjReqAnimByFlagsInline(c2, flags, frame);
                if (!(c2->flags & JOBJ_INSTANCE)) {
                    c3 = c2->child;
                    while (c3 != 0) {
                        JObjReqAnimByFlagsInline(c3, flags, frame);
                        if (!(c3->flags & JOBJ_INSTANCE)) {
                            c4 = c3->child;
                            while (c4 != 0) {
                                JObjReqAnimByFlagsInline(c4, flags, frame);
                                if (!(c4->flags & JOBJ_INSTANCE)) {
                                    c5 = c4->child;
                                    while (c5 != 0) {
                                        HSD_JObjReqAnimByFlags(c5, flags, frame);
                                        if (!(c5->flags & JOBJ_INSTANCE)) {
                                            c6 = c5->child;
                                            while (c6 != 0) {
                                                HSD_JObjReqAnimAllByFlags(c6, flags, frame);
                                                c6 = c6->next;
                                            }
                                        }
                                        c5 = c5->next;
                                    }
                                }
                                c4 = c4->next;
                            }
                        }
                        c3 = c3->next;
                    }
                }
                c2 = c2->next;
            }
        }
        c1 = c1->next;
    }
}

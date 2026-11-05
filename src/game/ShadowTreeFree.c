#include "game/ShadowTree_private.h"
static inline void FreeJoint(HSD_JObj *j) {
    if (j) {
        int has_dobj;
        if (j->flags & 0x4020) has_dobj = 0; else has_dobj = 1;
        if (has_dobj) {
            HSD_DObj *d = HSD_JObjGetDObj(j);
            while (d) {
                HSD_DObj *next = fn_801752A8(d);
                d->flags = 0; d->mobj = 0; d->pobj = 0;
                HSD_DObjRemove(d); lbl_806D15EC--;
                d = next;
            }
            j->dobj = 0;
        } else if (j->flags & 0x4000) j->dobj = 0;
        else if (j->flags & 0x20) j->dobj = 0;
        if (!(j->flags & 0x1000)) fn_80174D94(j->child, 0);
        j->child = 0;
        fn_80174D94(j->next, 0);
        j->next = 0;
        HSD_JObjUnref(j); lbl_806D15E8--;
    }
}
void fn_80174D94(HSD_JObj *j, unsigned char keep) {
    if (j) {
        int has_dobj;
        if (j->flags & 0x4020) has_dobj = 0; else has_dobj = 1;
        if (has_dobj) {
            HSD_DObj *d = HSD_JObjGetDObj(j);
            while (d) {
                HSD_DObj *next = ShadowDObjNext(d);
                d->flags = 0; d->mobj = 0; d->pobj = 0;
                HSD_DObjRemove(d); lbl_806D15EC--;
                d = next;
            }
            j->dobj = 0;
        } else if (j->flags & 0x4000) j->dobj = 0;
        else if (j->flags & 0x20) j->dobj = 0;
        if (!(j->flags & 0x1000)) FreeJoint(j->child);
        j->child = 0;
        FreeJoint(j->next);
        j->next = 0;
        if (!keep) { HSD_JObjUnref(j); lbl_806D15E8--; }
    }
}


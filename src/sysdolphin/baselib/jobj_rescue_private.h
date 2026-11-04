/* Shared inline view for the rescued runs. Keep the canonical layout and
 * redirect the outlined dirty helper to the original global definition. */
#ifndef MKGP2_JOBJ_RESCUE_PRIVATE_H
#define MKGP2_JOBJ_RESCUE_PRIVATE_H
#define HSD_JObjMtxIsDirty jobj_header_mtx_is_dirty
#define HSD_JObjSetupMatrix jobj_header_setup_matrix
#include "jobj.h"
#undef HSD_JObjSetupMatrix
#undef HSD_JObjMtxIsDirty

extern char lbl_806D0DA0[7];
extern char lbl_806D0DA8[5];

#ifndef MKGP2_JOBJ_DEFINE_DIRTY
inline
#endif
bool HSD_JObjMtxIsDirty(HSD_JObj* jobj)
{
    bool result;
    if (!jobj) {
        __assert(lbl_806D0DA0, 605, lbl_806D0DA8);
    }
    result = false;
    if (!(jobj->flags & JOBJ_USER_DEF_MTX) && (jobj->flags & JOBJ_MTX_DIRTY)) {
        result = true;
    }
    return result;
}

#ifndef MKGP2_JOBJ_DEFINE_SETUP
inline
#endif
void HSD_JObjSetupMatrix(HSD_JObj* jobj)
{
    if (!jobj || !HSD_JObjMtxIsDirty(jobj)) {
        return;
    }
    HSD_JObjSetupMatrixSub(jobj);
}

inline void HSD_JObjCheckDepend(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }
    if (!HSD_JObjMtxIsDirty(jobj)) {
        if ((jobj->flags & JOBJ_USER_DEF_MTX)) {
            if (!(jobj->flags & JOBJ_MTX_INDEP_PARENT) &&
                jobj->parent != NULL && HSD_JObjMtxIsDirty(jobj->parent))
            {
                jobj->flags |= JOBJ_MTX_DIRTY;
            }
        } else if ((jobj->parent != NULL &&
                    (jobj->parent->flags & JOBJ_MTX_DIRTY)) ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT1 ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_JOINT2 ||
                   (jobj->flags & JOBJ_EFFECTOR) == JOBJ_EFFECTOR ||
                   jobj->robj != NULL)
        {
            jobj->flags |= JOBJ_MTX_DIRTY;
        }
    }
}


#endif

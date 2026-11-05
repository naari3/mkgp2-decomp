#include "mkgp2_names.h"
#include "jobj_unlock_private.h"

#include <math.h>
#include <string.h>

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "displayfunc.h"
#include "dobj.h"
#include "fobj.h"
#include "id.h"
#include "mobj.h"
#include "mtx.h"
#include "pobj.h"
#include "robj.h"
#include "spline.h"
#include <dolphin/mtx.h>

double acos(double);

void HSD_JObjCheckDepend(HSD_JObj* jobj)
{
    if (jobj == NULL) {
        return;
    }
    switch (HSD_JObjMtxIsDirty(jobj)) {
    case 0:
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
        break;
    }
}

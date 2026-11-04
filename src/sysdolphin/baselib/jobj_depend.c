#include "mkgp2_names.h"
#include "jobj_rescue_private.h"

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

#pragma push
#pragma inline_max_size(600)
void HSD_JObjCheckDependAll(HSD_JObj* jobj)
{
    HSD_JObj* child;

    if (jobj == NULL) {
        return;
    }
    HSD_JObjCheckDepend(jobj);
    if (!(jobj->flags & JOBJ_INSTANCE)) {
        for (child = jobj->child; child != NULL; child = child->next) {
            HSD_JObjCheckDependAll(child);
        }
    }
}
#pragma pop

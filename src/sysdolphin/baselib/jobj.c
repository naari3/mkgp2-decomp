#include "mkgp2_names.h"
#include "jobj.h"

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

void JObjInfoInit(void);
HSD_JObjInfo hsdJObj = { JObjInfoInit };

static HSD_ClassInfo* default_class;
static HSD_SList* ufc_callbacks;
static void (*dptcl_callback)(int, int lo, int hi, HSD_JObj* jobj);
static void (*jsound_callback)(s32);
static void (*ptcltgt_callback)(HSD_JObj*, s32);
static HSD_JObj* current_jobj;

void HSD_JObjCheckDepend(HSD_JObj* jobj)
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

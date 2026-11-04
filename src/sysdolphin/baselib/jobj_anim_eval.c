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

void HSD_JObjAnim(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_JObjCheckDepend(jobj);
        HSD_AObjInterpretAnim(jobj->aobj, jobj, HSD_JOBJ_METHOD(jobj)->update);
        HSD_RObjAnimAll(jobj->robj);
        if (union_type_dobj(jobj)) {
            HSD_DObjAnimAll(jobj->u.dobj);
        }
    }
}

void JObjAnimAll(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if (jobj != NULL) {
        HSD_JObjAnim(jobj);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            child = jobj->child;
            while (child != NULL) {
                JObjAnimAll(child);
                child = child->next;
            }
        }
    }
}

void HSD_JObjAnimAll(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_AObjInitEndCallBack();
        JObjAnimAll(jobj);
        HSD_AObjInvokeCallBacks();
    }
}

/* mkgp2: an instance is drawn with the caller's view matrix when given,
 * otherwise with the current camera's. */
void JObjMakeInstanceMtx(MtxPtr vmtx, HSD_JObj* jobj, Mtx mtx)
{
    HSD_CObj* cobj;

    HSD_JObjSetupMatrix(jobj);
    HSD_JObjSetupMatrix(jobj->child);
    PSMTXInverse(jobj->child->mtx, mtx);
    PSMTXConcat(jobj->mtx, mtx, mtx);
    if (vmtx != NULL) {
        PSMTXConcat(vmtx, mtx, mtx);
    } else {
        cobj = HSD_CObjGetCurrent();
        if (cobj != NULL) {
            PSMTXConcat(HSD_CObjGetViewingMtxPtrDirect(cobj), mtx, mtx);
        }
    }
}

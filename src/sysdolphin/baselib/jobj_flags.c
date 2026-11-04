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

char lbl_806D0DA0[7] = "jobj.h";
char lbl_806D0DA8[5] = "jobj";

inline void(HSD_JObjSetMtxDirty)(HSD_JObj* jobj)
{
    if (jobj != NULL && !HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}


HSD_DObj* HSD_JObjGetDObj(HSD_JObj* jobj)
{
    if (jobj == NULL || !union_type_dobj(jobj)) {
        return NULL;
    }
    return jobj->u.dobj;
}

void HSD_JObjAddDObj(HSD_JObj* jobj, HSD_DObj* dobj)
{
    if (jobj == NULL || dobj == NULL || !union_type_dobj(jobj)) {
        return;
    }
    dobj->next = jobj->u.dobj;
    jobj->u.dobj = dobj;
}

static inline HSD_RObj* robj_set_next(HSD_RObj* robj, HSD_RObj* next)
{
    if (robj == NULL) {
        return next;
    }
    robj->next = next;
    return robj;
}

void HSD_JObjPrependRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    jobj->robj = robj_set_next(robj, jobj->robj);
}

void HSD_JObjDeleteRObj(HSD_JObj* jobj, HSD_RObj* robj)
{
    if (jobj == NULL || robj == NULL) {
        return;
    }
    if (robj != NULL) {
        HSD_RObj** cur_ptr = &jobj->robj;
        HSD_RObj* cur;
        while (*cur_ptr != NULL) {
            cur = *cur_ptr;
            if (cur == robj) {
                *cur_ptr = cur->next;
                robj->next = NULL;
                return;
            }
            cur_ptr = &cur->next;
        }
    }
}

u32 HSD_JObjGetFlags(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        return jobj->flags;
    }
    return 0;
}

void HSD_JObjSetFlags(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ flags) & JOBJ_CLASSICAL_SCALE) {
            (HSD_JObjSetMtxDirty)(jobj);
        }
        jobj->flags |= flags;
    }
}

#pragma push
#pragma inline_max_size(550)
void HSD_JObjSetFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjSetFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjSetFlagsAll(i, flags);
            }
        }
    }
}
#pragma pop

void HSD_JObjClearFlags(HSD_JObj* jobj, u32 arg1)
{
    if (jobj != NULL) {
        if ((jobj->flags ^ arg1) & JOBJ_CLASSICAL_SCALE) {
            (HSD_JObjSetMtxDirty)(jobj);
        }
        jobj->flags &= ~arg1;
    }
}

#pragma push
#pragma inline_max_size(600)
void HSD_JObjClearFlagsAll(HSD_JObj* jobj, u32 flags)
{
    if (jobj != NULL) {
        HSD_JObjClearFlags(jobj, flags);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* i;
            for (i = jobj->child; i != NULL; i = i->next) {
                HSD_JObjClearFlagsAll(i, flags);
            }
        }
    }
}
#pragma pop

/* mkgp2: destroys the object through its class without releasing it first. */
void fn_802D0EC0(HSD_JObj* jobj)
{
    if (jobj != NULL) {
        HSD_CLASS_METHOD(jobj)->destroy((HSD_Class*) jobj);
    }
}

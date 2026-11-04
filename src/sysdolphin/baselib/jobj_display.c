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

/* mkgp2: an instance is drawn with the caller's view matrix when given,
 * otherwise with the current camera's. */
static inline void JObjMakeInstanceMtx(MtxPtr vmtx, HSD_JObj* jobj, Mtx mtx)
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

#pragma push
#pragma inline_max_size(700)
void HSD_JObjDispAll(HSD_JObj* jobj, Mtx vmtx, u32 flags, u32 rendermode)
{
    HSD_JObj* child;

    if (jobj == NULL) {
        return;
    }
    if (jobj->flags & JOBJ_INSTANCE) {
        if (!(jobj->flags & JOBJ_HIDDEN)) {
            Mtx mtx;
            JObjMakeInstanceMtx(vmtx, jobj, mtx);
            HSD_JObjDispAll(jobj->child, mtx, flags, rendermode);
        }
    } else {
        if (jobj->flags & (flags << 0x12)) {
            HSD_JObjDisp(jobj, vmtx, flags, rendermode);
        }
        if (jobj->flags & (flags << 0x1C)) {
            for (child = jobj->child; child != NULL; child = child->next) {
                HSD_JObjDispAll(child, vmtx, flags, rendermode);
            }
        }
    }
}
#pragma pop

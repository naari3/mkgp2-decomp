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

void HSD_JObjSetDPtclCallback(DPCtlCallback cb)
{
    dptcl_callback = cb;
}

void JObjReleaseChild(HSD_JObj* jobj)
{
    HSD_JObj* child;
    if ((child = jobj->child) != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            HSD_JObjUnref(child);
        } else {
            child->parent = NULL;
            HSD_JObjRemoveAll(jobj->child);
        }
        jobj->child = NULL;
    }
    if (jobj->parent != NULL) {
        HSD_JObjReparent(jobj, NULL);
    }
    if (union_type_dobj(jobj)) {
        if (jobj->u.dobj != NULL) {
            HSD_DObjRemoveAll(jobj->u.dobj);
            jobj->u.dobj = NULL;
        }
    }
    if (jobj->robj != NULL) {
        HSD_RObjRemoveAll(jobj->robj);
        jobj->robj = NULL;
    }
    if (jobj->aobj != NULL) {
        HSD_AObjRemove(jobj->aobj);
        jobj->aobj = NULL;
    }
}

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static char unused3[] = "jobj[%d,%d]";
static char unused4[] = "SKELETON_ROOT ";
static char unused5[] = "SKELETON ";
static char unused6[] = "ENVELOPE_MODEL ";
static char unused7[] = "EFFECTOR ";
static char unused8[] = "  rot(L): ";
static char unused9[] = "  sca(L): ";
static char unused10[] = "  tra(L): ";
static char unused11[] = "  rot(G): ";
static char unused12[] = "  sca(G): ";
static char unused13[] = "  tra(G): ";
#pragma pop
#endif

#ifdef MUST_MATCH
#pragma push
#pragma force_active on
static u32 unused14[6] = { 0 };
#pragma pop
#endif

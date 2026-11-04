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

extern HSD_JObjInfo lbl_804FC9A8;
extern HSD_ClassInfo* lbl_806D21B0;
extern HSD_SList* lbl_806D21B4;
extern HSD_JObj* lbl_806D21C4;
#define hsdJObj lbl_804FC9A8
#define default_class lbl_806D21B0
#define ufc_callbacks lbl_806D21B4
#define current_jobj lbl_806D21C4

extern char lbl_806D0DB0[7];
extern char lbl_806D0DA8[5];
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) \
    ((cond) ? ((void) 0) : __assert(lbl_806D0DB0, line, lbl_806D0DA8))

HSD_JObj* HSD_JObjAlloc(void)
{
    HSD_JObj* jobj =
        hsdNew(default_class != NULL ? default_class : &hsdJObj.parent.parent);
    HSD_ASSERT(2006, jobj);
    return jobj;
}

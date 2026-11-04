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

int JObjInit(HSD_Class* o)
{
    int status = HSD_OBJECT_PARENT_INFO(&hsdJObj)->init(o);
    if (status >= 0) {
        HSD_JObj* jobj = (HSD_JObj*) o;
        status = 0;
        jobj->flags = JOBJ_MTX_DIRTY;
        jobj->scale.x = 1.0F;
        jobj->scale.y = 1.0F;
        jobj->scale.z = 1.0F;
    }
    return status;
}

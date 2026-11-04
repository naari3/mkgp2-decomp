#include "tobj.h"

#include <placeholder.h>
#include <string.h>

#include "aobj.h"
#include "cobj.h"
#include "debug.h"
#include "lobj.h"
#include "memory.h"
#include "mtx.h"
#include "tev.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>

#define FLT_EPSILON 1.00000001335e-10F

#include "tobj_private.h"
static char tobj_unused_descendant[36] = "hsdIsDescendantOf(info, &hsdTObj)";
static char tobj_library[24] = "sysdolphin_base_library";
static char tobj_classname[16] = "hsd_tobj";
#define hsdInitClassInfo(info, parent, lib, name, isize, osize) hsdInitClassInfo(info, parent, tobj_library, tobj_classname, isize, osize)
void TObjInfoInit(void)
{
    hsdInitClassInfo(HSD_CLASS_INFO(&hsdTObj), HSD_CLASS_INFO(&hsdObj),
                     "sysdolphin_base_library", "hsd_tobj",
                     sizeof(HSD_TObjInfo), sizeof(HSD_TObj));

    HSD_CLASS_INFO(&hsdTObj)->init = TObjInit;
    HSD_CLASS_INFO(&hsdTObj)->release = TObjRelease;
    HSD_CLASS_INFO(&hsdTObj)->amnesia = TObjAmnesia;
    HSD_TOBJ_INFO(&hsdTObj)->load = TObjLoad;
    HSD_TOBJ_INFO(&hsdTObj)->make_texp = TObjMakeTExp;

    hsdTObj.make_mtx = MakeTextureMtx;
    HSD_TOBJ_INFO(&hsdTObj)->update = TObjUpdateFunc;
}

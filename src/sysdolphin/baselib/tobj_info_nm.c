#define hsdTObj hsdTObj_type_declaration
#include "tobj.h"
#undef hsdTObj

/* This TU uses the original contiguous data pool as its address base.
 * hsdTObj itself remains defined with the canonical HSD_TObjInfo type in
 * its owning TU; the local byte-array view also reaches the nearby strings. */
extern char hsdTObj[];

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
void TObjInfoInit(void)
{
    char* pool = hsdTObj;
    HSD_TObjInfo* info = (HSD_TObjInfo*) pool;

    /* The original tobj data pool addresses these strings from hsdTObj. */
    hsdInitClassInfo(HSD_CLASS_INFO(info), HSD_CLASS_INFO(&hsdObj),
                     pool + 0x4A8, pool + 0x4C0,
                     sizeof(HSD_TObjInfo), sizeof(HSD_TObj));

    HSD_CLASS_INFO(info)->init = TObjInit;
    HSD_CLASS_INFO(info)->release = TObjRelease;
    HSD_CLASS_INFO(info)->amnesia = TObjAmnesia;
    HSD_TOBJ_INFO(info)->load = TObjLoad;
    HSD_TOBJ_INFO(info)->make_texp = TObjMakeTExp;

    info->make_mtx = MakeTextureMtx;
    HSD_TOBJ_INFO(info)->update = TObjUpdateFunc;
}

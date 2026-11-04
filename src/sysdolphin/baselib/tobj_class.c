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
HSD_TObj* tobj_head;
HSD_TObjInfo* tobj_default_class;
static inline void HSD_TlutRemove(HSD_Tlut* tlut)
{
    if (tlut) {
        hsdFreeMemPiece(tlut, sizeof(HSD_Tlut));
    }
}

static inline void HSD_TObjTevFree(HSD_TObjTev* tev)
{
    hsdFreeMemPiece(tev, sizeof(HSD_TObjTev));
}
static inline void HSD_TObjTevRemove(HSD_TObjTev* tev)
{
    if (tev) {
        HSD_TObjTevFree(tev);
    }
}
int TObjInit(HSD_Class* o)
{
    int ret = HSD_PARENT_INFO(&hsdTObj)->init(o);
    if (ret >= 0) {
        HSD_TOBJ(o)->desc_id = 0xFFFF;
        ret = 0;
    }
    return ret;
}

void TObjRelease(HSD_Class* o)
{
    HSD_TObj* tobj = HSD_TOBJ(o);

    HSD_AObjRemove(tobj->aobj);
    HSD_TlutRemove(tobj->tlut);
    HSD_TObjTevRemove(tobj->tev);
    if (tobj->tluttbl) {
        int i;
        for (i = 0; tobj->tluttbl[i]; i++) {
            HSD_TlutRemove(tobj->tluttbl[i]);
        }
        HSD_Free(tobj->tluttbl);
    }

    HSD_PARENT_INFO(&hsdTObj)->release(o);
}

void TObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(default_class)) {
        default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdTObj)) {
        tobj_head = NULL;
    }
    HSD_PARENT_INFO(&hsdTObj)->amnesia(info);
}

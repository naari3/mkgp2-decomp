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
extern char lbl_806D0C94[7];
extern char lbl_806D0C9C[5];
#undef __FILE__
#define __FILE__ lbl_806D0C94
#undef HSD_ASSERT
#define HSD_ASSERT(line, cond) ((cond) ? (void) 0 : __assert(__FILE__, line, lbl_806D0C9C))
static inline void HSD_TObjAnim(HSD_TObj* tobj)
{
    if (tobj == NULL) {
        return;
    }

    HSD_AObjInterpretAnim(tobj->aobj, tobj, HSD_TOBJ_METHOD(tobj)->update);
}

void HSD_TObjAnimAll(HSD_TObj* tobj)
{
    HSD_TObj* i;

    if (tobj == NULL) {
        return;
    }

    for (i = tobj; i != NULL; i = i->next) {
        HSD_TObjAnim(i);
    }
}

int TObjLoad(HSD_TObj* tobj, HSD_TObjDesc* td)
{
    tobj->next = HSD_TObjLoadDesc(td->next);
    tobj->desc_id = td->id;
    tobj->src = td->src;
    tobj->mtxid = GX_IDENTITY;
    tobj->rotate.x = td->rotate.x;
    tobj->rotate.y = td->rotate.y;
    tobj->rotate.z = td->rotate.z;
    tobj->scale = td->scale;
    tobj->translate = td->translate;
    tobj->wrap_s = td->wrap_s;
    tobj->wrap_t = td->wrap_t;
    tobj->repeat_s = td->repeat_s;
    tobj->repeat_t = td->repeat_t;
    tobj->flags = td->blend_flags;
    tobj->blending = td->blending;
    tobj->magFilt = td->magFilt;
    tobj->imagedesc = td->imagedesc;
    tobj->tlut = HSD_TlutLoadDesc(td->tlutdesc);
    tobj->lod = td->lod;
    tobj->aobj = NULL;
    tobj->flags |= TEX_MTX_DIRTY;
    tobj->tlut_no = (u8) -1;
    tobj->tev = HSD_TObjTevLoadDesc(td->tev);
    fn_802D47F4(2);

    return 0;
}

HSD_TObj* HSD_TObjLoadDesc(HSD_TObjDesc* td)
{
    if (td != NULL) {
        HSD_TObj* tobj;
        HSD_ClassInfo* info;

        if (!td->class_name || !(info = hsdSearchClassInfo(td->class_name))) {
            tobj = HSD_TObjAlloc();
        } else {
            tobj = hsdNew(info);
            HSD_ASSERT(600, tobj);
        }
        HSD_TOBJ_METHOD(tobj)->load(tobj, td);
        return tobj;
    } else {
        return NULL;
    }
}

HSD_Tlut* HSD_TlutLoadDesc(HSD_TlutDesc* tlutdesc)
{
    if (tlutdesc != NULL) {
        HSD_Tlut* tlut = HSD_TlutAlloc();
        memcpy(tlut, tlutdesc, sizeof(HSD_Tlut));
        return tlut;
    }
    return NULL;
}

HSD_TObjTev* HSD_TObjTevLoadDesc(HSD_TObjTevDesc* tevdesc)
{
    if (tevdesc != NULL) {
        HSD_TObjTev* new = HSD_TObjTevAlloc();
        memcpy(new, tevdesc, sizeof(HSD_TObjTev));
        return new;
    }
    return NULL;
}

HSD_TObj* _HSD_TObjGetCurrentByType(HSD_TObj* from, u32 mapping)
{
    HSD_TObj* tp;

    if (from == NULL) {
        tp = tobj_head;
    } else {
        tp = from->next;
    }

    for (; tp != NULL; tp = tp->next) {
        if (tobj_coord(tp) == mapping) {
            return tp;
        }
    }
    return NULL;
}

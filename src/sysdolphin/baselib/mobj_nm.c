#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

extern char lbl_804FC24C[0x22];
extern char lbl_806D0CE8[7];
extern char lbl_806D0CF0[5];
extern char lbl_806D0CF8[5];
extern unsigned char lbl_806D0CF5[3];

void MObjUpdateFunc(void*, enum_t, HSD_ObjData*);
extern HSD_ClassInfo* default_class;
extern HSD_MObj* current_mobj;
int MObjLoad(HSD_MObj* mobj, HSD_MObjDesc* desc)
{
    mobj->rendermode = desc->rendermode;
    mobj->tobj = HSD_TObjLoadDesc(desc->texdesc);
    mobj->mat = HSD_MaterialAlloc();
    memcpy(mobj->mat, desc->mat, sizeof(HSD_Material));
    mobj->rendermode |= RENDER_TOON;
    if (desc->pedesc != NULL) {
        mobj->pe = hsdAllocMemPiece(sizeof(HSD_PEDesc));
        memcpy(mobj->pe, desc->pedesc, sizeof(HSD_PEDesc));
    }
    mobj->aobj = NULL;
    return 0;
}

void HSD_MObjSetDefaultClass(HSD_MObjInfo* info)
{
    if (info) {
        if (!hsdIsDescendantOf(HSD_CLASS_INFO(info), HSD_CLASS_INFO(&hsdMObj))) {
            __assert(lbl_806D0CE8, 367, lbl_804FC24C);
        }
    }
    default_class = HSD_CLASS_INFO(info);
}

HSD_ClassInfo* HSD_MObjGetDefaultClass(void)
{
    return default_class != NULL ? default_class : HSD_CLASS_INFO(&hsdMObj);
}

HSD_MObj* HSD_MObjLoadDesc(HSD_MObjDesc* mobjdesc)
{
    if (mobjdesc) {
        HSD_MObj* mobj;
        HSD_ClassInfo* info;

        if (!mobjdesc->class_name ||
            !(info = hsdSearchClassInfo(mobjdesc->class_name)))
        {
            mobj = HSD_MObjAlloc();
        } else {
            mobj = hsdNew(info);
            if (!mobj) {
                __assert(lbl_806D0CE8, 406, lbl_806D0CF0);
            }
        }

        HSD_MOBJ_METHOD(mobj)->load(mobj, mobjdesc);
        HSD_MObjCompileTev(mobj);

        return mobj;
    } else {
        return NULL;
    }
}


#include "mobj.h"

#include <string.h>

#include "aobj.h"
#include "class.h"
#include "debug.h"
#include "state.h"
#include "tev.h"
#include "texp.h"
#include <dolphin/gx/GXEnum.h>

HSD_MObj* current_mobj;
HSD_ClassInfo* default_class;
void MObjInfoInit(void);
HSD_MObjInfo hsdMObj = { MObjInfoInit };
void HSD_MObjSetCurrent(HSD_MObj* mobj)
{
    current_mobj = mobj;
}

#ifndef MUST_MATCH
void HSD_MObjSetFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) {
        mobj->rendermode |= flags;
    }
}
#endif

#ifndef MUST_MATCH
void HSD_MObjClearFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj != NULL) {
        mobj->rendermode &= ~flags;
    }
}
#endif

#ifndef MUST_MATCH
void HSD_MObjRemoveAnimByFlags(HSD_MObj* mobj, u32 flags)
{
    if (mobj == NULL) {
        return;
    }

    if (flags & MOBJ_ANIM) {
        HSD_AObjRemove(mobj->aobj);
        mobj->aobj = NULL;
    }
    if (flags & TOBJ_ANIM) {
        HSD_TObjRemoveAnimAll(mobj->tobj);
    }
}
#endif

void HSD_MObjAddAnim(HSD_MObj* mobj, HSD_MatAnim* matanim)
{
    if (mobj == NULL) {
        return;
    }

    if (matanim != NULL) {
        if (mobj->aobj != NULL) {
            HSD_AObjRemove(mobj->aobj);
        }
        mobj->aobj = HSD_AObjLoadDesc(matanim->aobjdesc);
        HSD_TObjAddAnimAll(mobj->tobj, matanim->texanim);
    }
}

void HSD_MObjReqAnimByFlags(HSD_MObj* mobj, f32 startframe, u32 flags)
{
    if (mobj == NULL) {
        return;
    }
    if (flags & MOBJ_ANIM) {
        HSD_AObjReqAnim(mobj->aobj, startframe);
    }
    HSD_TObjReqAnimAllByFlags(mobj->tobj, startframe, flags);
}

#ifndef MUST_MATCH
void HSD_MObjReqAnim(HSD_MObj* mobj, f32 startframe)
{
    HSD_MObjReqAnimByFlags(mobj, startframe, ALL_ANIM);
}
#endif

#include "sysdolphin/baselib/dobj.h"

/* mkgp2 placeholder names: pobj.c/mobj.c/aobj.c functions */
extern void fn_802CA77C(HSD_PObj* pobj, HSD_ShapeAnim* shapeanim); /* HSD_PObjAddAnimAll */
extern void fn_802C22E0(HSD_MObj* mobj, HSD_MatAnim* matanim);     /* HSD_MObjAddAnim */
extern void HSD_MObjReqAnimAllByFlags(HSD_PObj* pobj, float frame, u32 flags);
extern void HSD_PObjReqAnimByFlags(HSD_MObj* mobj, float frame, u32 flags);
extern void fn_802C3C00(HSD_AObj* aobj, void* obj, void* update_func); /* HSD_AObjInterpretAnim */
extern void fn_802CA8CC(HSD_PObj* pobj); /* HSD_PObjAnimAll */
extern void fn_802C2848(HSD_MObj* mobj); /* HSD_MObjAnim */

extern HSD_DObj* lbl_806D20B4; /* current_dobj */

#define next_p(o) ((o) != 0 ? (o)->next : 0)

void fn_802BCF94(HSD_DObj* dobj)
{
    lbl_806D20B4 = dobj;
}

void fn_802BCF9C(HSD_DObj* dobj, u32 flags)
{
    if (dobj != 0) {
        dobj->flags |= flags;
    }
}

void fn_802BCFB4(HSD_DObj* dobj, u32 flags)
{
    if (dobj != 0) {
        dobj->flags &= ~flags;
    }
}

static inline void HSD_DObjAddAnim(HSD_DObj* dobj, HSD_MatAnim* mat_anim,
                                   HSD_ShapeAnimDObj* sh_anim)
{
    if (dobj == 0) {
        return;
    }
    fn_802CA77C(dobj->pobj, sh_anim != 0 ? sh_anim->shapeanim : 0);
    fn_802C22E0(dobj->mobj, mat_anim);
}

void fn_802BCFCC(HSD_DObj* dobj, HSD_MatAnim* matanim,
                 HSD_ShapeAnimDObj* shapeanimdobj)
{
    HSD_DObj* dp;
    HSD_MatAnim* ma;
    HSD_ShapeAnimDObj* sd;

    if (dobj == 0) {
        return;
    }
    for (dp = dobj, ma = matanim, sd = shapeanimdobj; dp != 0;
         dp = dp->next, ma = next_p(ma), sd = next_p(sd))
    {
        HSD_DObjAddAnim(dp, ma, sd);
    }
}

static inline void HSD_DObjReqAnimByFlags(HSD_DObj* dobj, float frame, u32 flags)
{
    if (dobj == 0) {
        return;
    }
    HSD_MObjReqAnimAllByFlags(dobj->pobj, frame, flags); /* really HSD_PObjReqAnimAllByFlags */
    HSD_PObjReqAnimByFlags(dobj->mobj, frame, flags);    /* really HSD_MObjReqAnimByFlags */
}

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float frame, u32 flags)
{
    HSD_DObj* dp;
    if (dobj == 0) {
        return;
    }
    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjReqAnimByFlags(dp, frame, flags);
    }
}

static inline void HSD_DObjAnim(HSD_DObj* dobj)
{
    if (dobj == 0) {
        return;
    }
    fn_802C3C00(dobj->aobj, dobj, dobj->class_info[0x44 / 4]);
    fn_802CA8CC(dobj->pobj);
    fn_802C2848(dobj->mobj);
}

void fn_802BD0FC(HSD_DObj* dobj)
{
    HSD_DObj* dp;
    if (dobj == 0) {
        return;
    }
    for (dp = dobj; dp != 0; dp = dp->next) {
        HSD_DObjAnim(dp);
    }
}

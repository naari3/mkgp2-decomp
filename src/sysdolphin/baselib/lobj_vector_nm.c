#include "lobj_private.h"

#undef __FILE__
#define __FILE__ "lobj.c"
u32 HSD_LObjGetFlags(HSD_LObj* lobj)
{
    return lobj ? lobj->flags : 0;
}

void HSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

void HSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags &= ~flags;
}

s32 HSD_LObjGetLightMaskAttnFunc(void)
{
    return lightmask_attnfunc;
}

u32 HSD_LObjGetType(HSD_LObj* lobj)
{
    return lobj->flags & LOBJ_TYPE_MASK;
}

void HSD_LObjSetActive(HSD_LObj* lobj)
{
    int idx;

    if (HSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
        idx = MAX_GXLIGHT - 1;
        if (active_lights[idx]) {
            return;
        }
    } else {
        idx = nb_active_lights++;
    }
    active_lights[idx] = lobj;
    lobj->id = HSD_Index2LightID(idx);
}

void HSD_LObjClearActive(void)
{
    int i;

    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
}

void HSD_LObjAnim(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_AObjInterpretAnim(lobj->aobj, lobj, &LObjUpdateFunc);
        HSD_WObjInterpretAnim(HSD_LObjGetPositionWObj(lobj));
        HSD_WObjInterpretAnim(HSD_LObjGetInterestWObj(lobj));
    }
}

void HSD_LObjAnimAll(HSD_LObj* lobj)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjAnim(lp);
    }
}

void HSD_LObjReqAnim(HSD_LObj* lobj, f32 startframe)
{
    if (lobj == NULL) {
        return;
    }

    HSD_AObjReqAnim(lobj->aobj, startframe);
    HSD_WObjReqAnim(HSD_LObjGetPositionWObj(lobj), startframe);
    HSD_WObjReqAnim(HSD_LObjGetInterestWObj(lobj), startframe);
}

void HSD_LObjReqAnimAll(HSD_LObj* lobj, f32 startframe)
{
    HSD_LObj* lp;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj; lp; lp = lp->next) {
        HSD_LObjReqAnim(lp, startframe);
    }
}

Vec3 const HSD_LObj_803B94A0 = { 0.0F, 0.0F, 0.0F };
Vec3 const HSD_LObj_803B94AC = { 0.0F, 0.0F, 0.0F };

static inline int LObjNormalize(Vec3* src, Vec3* dst)
{
    if (src == NULL || dst == NULL) {
        return -1;
    }
    if (fabsf(src->x) <= LOBJ_FLT_MIN && fabsf(src->y) <= LOBJ_FLT_MIN &&
        fabsf(src->z) <= LOBJ_FLT_MIN)
    {
        return -1;
    }
    PSVECNormalize(src, dst);
    return 0;
}

void HSD_LObjGetLightVector(HSD_LObj* lobj, Vec3* dir)
{
    Vec3 position = HSD_LObj_803B94A0;
    Vec3 interest = HSD_LObj_803B94AC;

    if (lobj == NULL) {
        return;
    }

    HSD_LObjGetPosition(lobj, &position);
    HSD_LObjGetInterest(lobj, &interest);
    PSVECSubtract(&interest, &position, dir);
    if (LObjNormalize(dir, dir) != 0) {
        dir->x = 0.0F;
        dir->y = 0.0F;
        dir->z = 1.0F;
    }
}

void HSD_LObjSetCurrentAll(HSD_LObj* lobj)
{
    u32 _;

    LObjRemoveAll();
    HSD_LObjAddCurrent(lobj);
}

static inline void LObjReplaceAll(HSD_LObj* lobj)
{
    int i;
    HSD_LObj* cur;
    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
    for (cur = lobj; cur != NULL; cur = cur->next) {
        HSD_LObjAddCurrent(cur);
    }
}

void HSD_LObj_803668EC(HSD_LObj* lobj)
{
    PAD_STACK(4);

    LObjReplaceAll(lobj);
}

void HSD_LObjSetPosition(HSD_LObj* lobj, Vec3* position)
{
    HSD_ASSERT(1369, lobj);
    if (lobj->position == NULL) {
        lobj->position = HSD_WObjAlloc();
        HSD_ASSERT(1372, lobj->position);
    }
    HSD_WObjSetPosition(lobj->position, position);
}

void HSD_LObjSetInterest(HSD_LObj* lobj, Vec3* interest)
{
    HSD_ASSERT(1405, lobj);
    if (lobj->interest == NULL) {
        lobj->interest = HSD_WObjAlloc();
        HSD_ASSERT(1408, lobj->interest);
    }
    HSD_WObjSetPosition(lobj->interest, interest);
}

void HSD_LObjSetDefaultClass(HSD_LObjInfo* info)
{
    if (info != NULL) {
        HSD_ASSERT(1420, hsdIsDescendantOf(info, &hsdLObj));
    }
    lobj_default_class = info;
}

void HSD_LObjAddAnim(HSD_LObj* lobj, HSD_LightAnim* lanim)
{
    if (lobj == NULL) {
        return;
    }

    if (lanim != NULL) {
        if (lobj->aobj) {
            HSD_AObjRemove(lobj->aobj);
        }
        lobj->aobj = HSD_AObjLoadDesc(lanim->aobjdesc);
        HSD_WObjAddAnim(HSD_LObjGetPositionWObj(lobj), lanim->position_anim);
        HSD_WObjAddAnim(HSD_LObjGetInterestWObj(lobj), lanim->interest_anim);
    }
}

void HSD_LObjAddAnimAll(HSD_LObj* lobj, HSD_LightAnim* lanim)
{
    HSD_LObj* lp;
    HSD_LightAnim* la;

    if (lobj == NULL) {
        return;
    }

    for (lp = lobj, la = lanim; lp; lp = next_p(lp), la = next_p(la)) {
        HSD_LObjAddAnim(lp, la);
    }
}

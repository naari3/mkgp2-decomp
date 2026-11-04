#include "lobj_private.h"

extern char lbl_806D0D20[7];
extern char lbl_806D0D3C[4];
extern char lbl_806D0D40[1];
extern char lbl_806D0D44[3];
extern char lbl_804FC480[];

static inline void PrivateHSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

static inline void PrivateHSD_LObjSetColor(HSD_LObj* lobj, GXColor color)
{
    lobj->color = color;
}

static inline void PrivateHSD_LObjGetColor(HSD_LObj* lobj, GXColor* color)
{
    *color = lobj->color;
}

static inline void PrivateHSD_LObjSetSpot(HSD_LObj* lobj, f32 cutoff, s32 point_func)
{
    if (lobj != NULL) {
        lobj->u.point.cutoff = cutoff;
        lobj->u.point.point_func = point_func;
    }
}

static inline void PrivateHSD_LObjSetDistAttn(HSD_LObj* lobj, f32 ref_dist, f32 ref_br,
                         s32 dist_func)
{
    if (lobj != NULL) {
        lobj->u.point.ref_dist = ref_dist;
        lobj->u.point.ref_br = ref_br;
        lobj->u.point.dist_func = dist_func;
    }
}

static inline void PrivateHSD_LObjSetAttnA(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2)
{
    if (lobj == NULL) {
        return;
    }

    lobj->u.attn.a0 = a0;
    lobj->u.attn.a1 = a1;
    lobj->u.attn.a2 = a2;
}

static inline void PrivateHSD_LObjSetAttnK(HSD_LObj* lobj, f32 k0, f32 k1, f32 k2)
{
    if (lobj == NULL) {
        return;
    }

    lobj->u.attn.k0 = k0;
    lobj->u.attn.k1 = k1;
    lobj->u.attn.k2 = k2;
}

static inline void PrivateHSD_LObjSetAttn(HSD_LObj* lobj, f32 a0, f32 a1, f32 a2, f32 k0, f32 k1,
                     f32 k2)
{
    PrivateHSD_LObjSetAttnA(lobj, a0, a1, a2);
    PrivateHSD_LObjSetAttnK(lobj, k0, k1, k2);
}

static inline HSD_LObjInfo* PrivateHSD_LObjGetDefaultClass(void)
{
    return lobj_default_class ? lobj_default_class : &hsdLObj;
}

static inline HSD_LObj* PrivateHSD_LObjAlloc(void)
{
    HSD_LObj* new = hsdNew(&PrivateHSD_LObjGetDefaultClass()->parent.parent);
    ((new) ? ((void) 0) : __assert(lbl_806D0D20, 1500, lbl_806D0D3C));
    return new;
}

static inline HSD_WObj* PrivateHSD_LObjGetPositionWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->position;
    }
    return NULL;
}

static inline HSD_WObj* PrivateHSD_LObjGetInterestWObj(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        return lobj->interest;
    }
    return NULL;
}

static inline void PrivateHSD_LObjSetPositionWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->position);
    lobj->position = wobj;
}

static inline void PrivateHSD_LObjSetInterestWObj(HSD_LObj* lobj, HSD_WObj* wobj)
{
    if (lobj == NULL) {
        return;
    }

    HSD_WObjUnref(lobj->interest);
    lobj->interest = wobj;
}

int LObjLoad(HSD_LObj* lobj, HSD_LightDesc* ldesc)
{
    PrivateHSD_LObjSetColor(lobj, ldesc->color);
    PrivateHSD_LObjSetFlags(lobj, ldesc->flags);
    switch (ldesc->flags & LOBJ_TYPE_MASK) {
    case LOBJ_AMBIENT:
        break;
    case LOBJ_INFINITE:
        PrivateHSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        break;
    case LOBJ_POINT:
        PrivateHSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            PrivateHSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            PrivateHSD_LObjSetAttnK(lobj, ldesc->u.attn->k0, ldesc->u.attn->k1,
                             ldesc->u.attn->k2);
        } else {
            PrivateHSD_LObjSetDistAttn(lobj, ldesc->u.point->ref_dist,
                                ldesc->u.point->ref_br,
                                ldesc->u.point->dist_func);
        }
        break;
    case LOBJ_SPOT:
        PrivateHSD_LObjSetPositionWObj(lobj, HSD_WObjLoadDesc(ldesc->position));
        PrivateHSD_LObjSetInterestWObj(lobj, HSD_WObjLoadDesc(ldesc->interest));
        if (ldesc->attnflags & LOBJ_LIGHT_ATTN) {
            PrivateHSD_LObjSetFlags(lobj, LOBJ_RAW_PARAM);
            PrivateHSD_LObjSetAttn(lobj, ldesc->u.attn->a0, ldesc->u.attn->a1,
                            ldesc->u.attn->a2, ldesc->u.attn->k0,
                            ldesc->u.attn->k1, ldesc->u.attn->k2);
        } else {
            PrivateHSD_LObjSetDistAttn(lobj, ldesc->u.spot->ref_dist,
                                ldesc->u.spot->ref_br,
                                ldesc->u.spot->dist_func);
            PrivateHSD_LObjSetSpot(lobj, ldesc->u.spot->cutoff,
                            ldesc->u.spot->spot_func);
        }
        break;
    default:
        OSReport(lbl_804FC480, ldesc->flags);
        HSD_Panic(lbl_806D0D20, 1632, lbl_806D0D40);
        break;
    }
    return 0;
}

HSD_LObj* HSD_LObjLoadDesc(HSD_LightDesc* ldesc)
{
    HSD_LObj *top, **p = &top;

    for (; ldesc; ldesc = ldesc->next) {
        HSD_ClassInfo* info;

        if (!ldesc->class_name ||
            !(info = hsdSearchClassInfo(ldesc->class_name)))
        {
            *p = PrivateHSD_LObjAlloc();
        } else {
            *p = hsdNew(info);
            ((*p) ? ((void) 0) : __assert(lbl_806D0D20, 1666, lbl_806D0D44));
        }
        HSD_LOBJ_METHOD(*p)->load(*p, ldesc);
        p = &(*p)->next;
    }
    *p = NULL;

    return top;
}

void LObjRelease(HSD_Class* o)
{
    HSD_LObj* lobj = HSD_LOBJ(o);
    ///@todo Unused stack
    u8 _[8];

    HSD_AObjRemove(lobj->aobj);
    HSD_WObjUnref(PrivateHSD_LObjGetPositionWObj(lobj));
    HSD_WObjUnref(PrivateHSD_LObjGetInterestWObj(lobj));

    HSD_OBJECT_PARENT_INFO(&hsdLObj)->release(o);
}

void LObjAmnesia(HSD_ClassInfo* info)
{
    if (info == HSD_CLASS_INFO(lobj_default_class)) {
        lobj_default_class = NULL;
    }
    if (info == HSD_CLASS_INFO(&hsdLObj)) {
        current_lights = NULL;
    }
    HSD_OBJECT_PARENT_INFO(&hsdLObj)->amnesia(info);
}

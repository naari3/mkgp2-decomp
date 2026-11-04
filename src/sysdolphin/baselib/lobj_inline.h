#ifndef MKGP2_LOBJ_INLINE_H
#define MKGP2_LOBJ_INLINE_H
#include "lobj_private.h"
static inline u32 PrivateInlineHSD_LObjGetFlags(HSD_LObj* lobj)
{
    return lobj ? lobj->flags : 0;
}

static inline void PrivateInlineHSD_LObjSetFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags |= flags;
}

static inline void PrivateInlineHSD_LObjClearFlags(HSD_LObj* lobj, u32 flags)
{
    if (lobj == NULL) {
        return;
    }
    lobj->flags &= ~flags;
}

static inline u32 PrivateInlineHSD_LObjGetType(HSD_LObj* lobj)
{
    return lobj->flags & LOBJ_TYPE_MASK;
}

static inline void PrivateInlineHSD_LObjSetActive(HSD_LObj* lobj)
{
    int idx;

    if (PrivateInlineHSD_LObjGetType(lobj) == LOBJ_AMBIENT) {
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

static inline void PrivateInlineHSD_LObjClearActive(void)
{
    int i;

    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
}

static inline bool PrivateInlineHSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj != NULL && lobj->position != NULL) {
        HSD_WObjGetPosition(lobj->position, position);
        return true;
    }
    return false;
}

static inline bool PrivateInlineHSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj != NULL && lobj->interest != NULL) {
        HSD_WObjGetPosition(lobj->interest, interest);
        return true;
    }
    return false;
}


#define HSD_LObjGetFlags PrivateInlineHSD_LObjGetFlags
#define HSD_LObjSetFlags PrivateInlineHSD_LObjSetFlags
#define HSD_LObjClearFlags PrivateInlineHSD_LObjClearFlags
#define HSD_LObjGetType PrivateInlineHSD_LObjGetType
#define HSD_LObjSetActive PrivateInlineHSD_LObjSetActive
#define HSD_LObjClearActive PrivateInlineHSD_LObjClearActive
#define HSD_LObjGetPosition PrivateInlineHSD_LObjGetPosition
#define HSD_LObjGetInterest PrivateInlineHSD_LObjGetInterest
#endif

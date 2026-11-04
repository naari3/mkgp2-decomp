#include "lobj_private.h"

static inline void PrivateHSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        hsdDelete(lobj);
    }
}

static inline void PrivateHSD_LObjDeleteCurrent(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        HSD_SList** p;
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if ((*p)->data == lobj) {
                int i;
                for (i = 0; i < MAX_GXLIGHT; i++) {
                    if (lobj == active_lights[i]) {
                        active_lights[i] = NULL;
                    }
                }
                *p = HSD_SListRemove(*p);
                PrivateHSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

void HSD_LObjRemoveAll(HSD_LObj* lobj)
{
    HSD_LObj* next;
    HSD_LObj* cur;

    cur = lobj;
    while (cur != NULL) {
        next = cur->next;
        PrivateHSD_LObjDeleteCurrent(cur);
        PrivateHSD_LObjUnrefThis(cur);
        cur = next;
    }
}

bool HSD_LObjGetPosition(HSD_LObj* lobj, Vec3* position)
{
    if (lobj != NULL && lobj->position != NULL) {
        HSD_WObjGetPosition(lobj->position, position);
        return true;
    }
    return false;
}

bool HSD_LObjGetInterest(HSD_LObj* lobj, Vec3* interest)
{
    if (lobj != NULL && lobj->interest != NULL) {
        HSD_WObjGetPosition(lobj->interest, interest);
        return true;
    }
    return false;
}

#include "lobj_private.h"

extern char lbl_804FC3E4[9];
extern char lbl_804FC3F0[39];
extern char lbl_806D0D2C[7];
extern char lbl_806D0D34[5];

static inline void PrivateRefINC(void* o)
{
    if (o != NULL) {
        HSD_OBJ(o)->ref_count++;
        ((HSD_OBJ(o)->ref_count != HSD_OBJ_NOREF) ? ((void) 0) :
         __assert(lbl_804FC3E4, 93, lbl_804FC3F0));
    }
}

static inline u8 PrivatePriority(HSD_LObj* lobj)
{
    ((lobj) ? ((void) 0) : __assert(lbl_806D0D2C, 355, lbl_806D0D34));
    return lobj->priority;
}

static inline void LObjAddCurrentOne(HSD_LObj* lobj)
{
    HSD_SList* node;
    HSD_SList** p;

    if (lobj != NULL) {
        node = current_lights;
        while (node != NULL) {
            if (node->data == lobj) {
                HSD_LObjDeleteCurrent(lobj);
                break;
            }
            node = node->next;
        }
        PrivateRefINC(lobj);
        for (p = &current_lights; *p != NULL; p = &(*p)->next) {
            if (PrivatePriority((*p)->data) > PrivatePriority(lobj)) {
                break;
            }
        }
        *p = HSD_SListAllocAndPrepend(*p, lobj);
    }
}

void HSD_LObjAddCurrent(HSD_LObj* lobj)
{
    for (; lobj != NULL; lobj = lobj->next) {
        LObjAddCurrentOne(lobj);
    }
}

void HSD_LObjUnrefThis(HSD_LObj* lobj)
{
    if (lobj != NULL && ref_DEC(lobj)) {
        hsdDelete(lobj);
    }
}

void HSD_LObjDeleteCurrent(HSD_LObj* lobj)
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
                HSD_LObjUnrefThis(lobj);
                return;
            }
        }
    }
}

static inline void LObjRemoveAll(void)
{
    int i;
    for (i = 0; i < MAX_GXLIGHT; i++) {
        active_lights[i] = NULL;
    }
    nb_active_lights = 0;
    while (current_lights != NULL) {
        HSD_LObjUnrefThis(current_lights->data);
        current_lights = HSD_SListRemove(current_lights);
    }
}

void HSD_LObjDeleteCurrentAll(HSD_LObj* lobj)
{
    if (lobj != NULL) {
        while (lobj != NULL) {
            HSD_LObjDeleteCurrent(lobj);
            lobj = lobj->next;
        }
        return;
    }
    LObjRemoveAll();
}

HSD_LObj* HSD_LObjGetCurrentByType(u16 flags)
{
    u32 type = flags & LOBJ_TYPE_MASK;
    HSD_SList* cur = current_lights;
    while (cur != NULL) {
        HSD_LObj* lobj = cur->data;
        if (type == (lobj->flags & LOBJ_TYPE_MASK)) {
            return lobj;
        }
        cur = cur->next;
    }
    return NULL;
}

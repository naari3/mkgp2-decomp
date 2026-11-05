#include "mkgp2_names.h"
#define HSD_JObjRef header_JObjRef
#define jobj_ref_INC header_jobj_ref_INC
#define HSD_IDGetData header_IDGetData
#include "jobj_unlock_private.h"
#include "id.h"
#undef HSD_JObjRef
#undef jobj_ref_INC
#undef HSD_IDGetData
#include "robj.h"
#include "dobj.h"
void HSD_JObjRef(HSD_JObj*);
void jobj_ref_INC(void*);
void* HSD_IDGetData(HSD_IDKey, s32*);

static inline void RefIncrement(void* o)
{
    HSD_OBJ(o)->ref_count++;
    if (HSD_OBJ(o)->ref_count == HSD_OBJ_NOREF) __assert(lbl_804FCB88, 93, lbl_804FCB94);
}
void HSD_JObjRef(HSD_JObj* jobj)
{
    if (jobj != NULL) RefIncrement(jobj);
}
void* HSD_IDGetData(HSD_IDKey id, s32* success)
{
    return HSD_IDGetDataFromTable(NULL, id, success);
}
void jobj_ref_INC(void* o)
{
    HSD_OBJ(o)->ref_count++;
    if (HSD_OBJ(o)->ref_count == HSD_OBJ_NOREF)
        __assert(lbl_804FCB88, 93, lbl_804FCB94);
}
void HSD_JObjUnref(HSD_JObj* jobj)
{
    if (jobj != NULL && ref_DEC(jobj)) {
        if (iref_CNT(jobj) - 1 < 0) {
            hsdDelete(jobj);
        } else {
            iref_INC(jobj);
            HSD_JOBJ_METHOD(jobj)->release_child(jobj);
            if (iref_DEC(jobj)) {
                hsdDelete(jobj);
            }
        }
    }
}

void HSD_JObjUnrefThis(HSD_JObj* jobj)
{
    if (jobj != NULL && iref_DEC(jobj) && ref_CNT(jobj) < 0) {
        hsdDelete(jobj);
    }
}

static inline void UpdateParentTrspBits(HSD_JObj* jobj, HSD_JObj* child)
{
    u32 flags = (child->flags | (child->flags << 10)) & JOBJ_ROOT_MASK;
    while (jobj != NULL) {
        if (!(flags & ~jobj->flags)) {
            break;
        }
        jobj->flags |= flags;
        jobj = jobj->parent;
    }
}

void HSD_JObjAddChild(HSD_JObj* jobj, HSD_JObj* child)
{
    char* pool = lbl_804FC9A8;
    HSD_JObj* last;

    if (jobj == NULL || child == NULL) {
        return;
    }
    if (child->parent != NULL) { OSReport(pool + 0x250); __assert(lbl_806D0DB0, 1353, pool + 0x26c); }
    if (child->next != NULL) { OSReport(pool + 0x284); __assert(lbl_806D0DB0, 1354, pool + 0x23c); }
    if (jobj->child == NULL) {
        jobj->child = child;
    } else {
        if (jobj->flags & JOBJ_INSTANCE) __assert(lbl_806D0DB0, 1360, pool + 0x2a4);
        last = jobj->child;
        while (last->next != NULL) {
            if (last == child) __assert(lbl_806D0DB0, 1363, pool + 0x2c4);
            last = last->next;
        }
        last->next = child;
    }
    child->parent = jobj;
    UpdateParentTrspBits(jobj, child);
}



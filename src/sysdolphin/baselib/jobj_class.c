#include "mkgp2_names.h"
#include "jobj.h"
#include "dobj.h"
#include "robj.h"

/* The original joint class shares its assertion strings with these helpers. */
extern char lbl_804FC9A8[0x3D8];
extern char lbl_806D0DB0[7];
extern char lbl_806D0DBC[5];

static inline void ReleaseJoint(HSD_JObj* jobj, char* pool)
{
    if (jobj != NULL && ref_DEC(jobj)) {
        if (iref_CNT(jobj) - 1 < 0) {
            hsdDelete(jobj);
        } else {
            jobj->object.ref_count_individual++;
            if (jobj->object.ref_count_individual == 0) {
                __assert(pool + 0x1E0, 158, pool + 0x214);
            }
            HSD_JOBJ_METHOD(jobj)->release_child(jobj);
            if (iref_DEC(jobj)) {
                hsdDelete(jobj);
            }
        }
    }
}

static inline HSD_JObj* PreviousJoint(HSD_JObj* jobj, char* pool)
{
    HSD_JObj* prev;
    if (jobj == NULL || jobj->parent == NULL) {
        return NULL;
    }
    prev = jobj->parent->child;
    if (jobj == prev) {
        return NULL;
    }
    while (prev != NULL) {
        if (prev->next == jobj) {
            return prev;
        }
        prev = prev->next;
    }
    HSD_Panic(lbl_806D0DB0, 1519, pool + 0x2D4);
    return NULL;
}

static inline void RemoveJoints(HSD_JObj* jobj, char* pool)
{
    HSD_JObj* next;
    HSD_JObj* prev;
    if (jobj == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        prev = PreviousJoint(jobj, pool);
        if (prev != NULL) {
            prev->next = NULL;
        } else {
            jobj->parent->child = NULL;
        }
    }
    while (jobj != NULL) {
        next = jobj->next;
        jobj->parent = NULL;
        jobj->next = NULL;
        ReleaseJoint(jobj, pool);
        jobj = next;
    }
}

static inline void RecalcTransparency(HSD_JObj* jobj)
{
    HSD_JObj* child;
    u32 flags;
    while (jobj != NULL) {
        flags = ~JOBJ_ROOT_MASK;
        for (child = jobj->child; child != NULL; child = child->next) {
            flags |= (child->flags | (child->flags << 10)) & JOBJ_ROOT_MASK;
        }
        if (!(jobj->flags & ~flags)) {
            break;
        }
        jobj->flags &= flags;
        jobj = jobj->next;
    }
}

static inline HSD_JObj* DetachJoint(HSD_JObj* jobj, char* pool)
{
    HSD_JObj* next;
    HSD_JObj* prev;
    if (jobj == NULL) {
        return NULL;
    }
    next = jobj->next;
    if (jobj->parent != NULL) {
        if (jobj->parent->child == jobj) {
            jobj->parent->child = next;
        } else {
            prev = PreviousJoint(jobj, pool);
            if (prev == NULL) {
                __assert(lbl_806D0DB0, 1394, lbl_806D0DBC);
            }
            prev->next = next;
        }
        RecalcTransparency(jobj->parent);
        jobj->parent = NULL;
    }
    jobj->next = NULL;
    return next;
}

void JObjReleaseChild(HSD_JObj* jobj)
{
    HSD_JObj* child;
    char* pool = lbl_804FC9A8;
    if ((child = jobj->child) != NULL) {
        if (jobj->flags & JOBJ_INSTANCE) {
            ReleaseJoint(child, pool);
        } else {
            child->parent = NULL;
            RemoveJoints(jobj->child, pool);
        }
        jobj->child = NULL;
    }
    if (jobj->parent != NULL) {
        DetachJoint(jobj, pool);
    }
    if (union_type_dobj(jobj)) {
        if (jobj->u.dobj != NULL) {
            HSD_DObjRemoveAll(jobj->u.dobj);
            jobj->u.dobj = NULL;
        }
    }
    if (jobj->robj != NULL) {
        HSD_RObjRemoveAll(jobj->robj);
        jobj->robj = NULL;
    }
    if (jobj->aobj != NULL) {
        HSD_AObjRemove(jobj->aobj);
        jobj->aobj = NULL;
    }
}

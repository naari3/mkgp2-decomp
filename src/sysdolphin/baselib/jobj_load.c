#include "mkgp2_names.h"
#include "jobj.h"

#include <math.h>
#include <string.h>

#include "aobj.h"
#include "class.h"
#include "cobj.h"
#include "displayfunc.h"
#include "dobj.h"
#include "fobj.h"
#include "id.h"
#include "mobj.h"
#include "mtx.h"
#include "pobj.h"
#include "robj.h"
#include "spline.h"
#include <dolphin/mtx.h>

double acos(double);

void JObjInfoInit(void);
HSD_JObjInfo hsdJObj = { JObjInfoInit };

static HSD_ClassInfo* default_class;
static HSD_SList* ufc_callbacks;
static void (*dptcl_callback)(int, int lo, int hi, HSD_JObj* jobj);
static void (*jsound_callback)(s32);
static void (*ptcltgt_callback)(HSD_JObj*, s32);
static HSD_JObj* current_jobj;

void HSD_JObjSetDefaultClass(HSD_ClassInfo* info)
{
    if (info != NULL) {
        HSD_ASSERT(0x3A5, hsdIsDescendantOf(info, &hsdJObj));
    }
    default_class = info;
}

static inline HSD_JObj* JObjLoadJointSub(HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_JObj* jobj;
    HSD_ClassInfo* info;
    if (joint == NULL) {
        return NULL;
    }
    if (joint->class_name == NULL ||
        !(info = hsdSearchClassInfo(joint->class_name)))
    {
        jobj = HSD_JObjAlloc();
    } else {
        jobj = hsdNew(info);
        HSD_ASSERT(981, jobj);
    }
    HSD_JOBJ_METHOD(jobj)->load(jobj, joint, parent);
    return jobj;
}

s32 JObjLoad(HSD_JObj* jobj, HSD_Joint* joint, HSD_JObj* parent)
{
    HSD_Joint* cjoint;

    jobj->child = NULL;
    jobj->next = NULL;
    jobj->parent = NULL;
    jobj->flags |= joint->flags;
    if (union_type_spline(jobj)) {
        jobj->u.spline = joint->u.spline;
    } else if (union_type_ptcl(jobj)) {
        HSD_SList* slist;
        jobj->u.ptcl = joint->u.ptcl;
        slist = joint->u.ptcl;
        while (slist != NULL) {
            *(u32*) &slist->data |= 0x80000000;
            slist = slist->next;
        }
    } else {
        jobj->u.dobj = HSD_DObjLoadDesc(joint->u.dobjdesc);
    }
    jobj->robj = HSD_RObjLoadDesc(joint->robjdesc);
    jobj->rotate.x = joint->rotation.x;
    jobj->rotate.y = joint->rotation.y;
    jobj->rotate.z = joint->rotation.z;
    jobj->scale = joint->scale;
    jobj->translate = joint->position;
    PSMTXIdentity(jobj->mtx);
    jobj->scl = NULL;
    if (joint->mtx != NULL) {
        jobj->envelopemtx = HSD_MtxAlloc();
        memcpy(jobj->envelopemtx, joint->mtx, sizeof(Mtx));
    }
    HSD_IDInsertToTable(NULL, (HSD_IDKey) joint, jobj);
    jobj->id = (HSD_IDKey) joint;
    if (!(joint->flags & JOBJ_INSTANCE)) {
        for (cjoint = joint->child; cjoint != NULL; cjoint = cjoint->next) {
            HSD_JObj* child = JObjLoadJointSub(cjoint, jobj);
            if (child == NULL) {
                return -1;
            }
            HSD_JObjAddChild(jobj, child);
        }
    }
    return 0;
}

/* mkgp2: find the jobj built from `joint` in a tree loaded from joint_root. */
#pragma push
#pragma inline_max_size(600)
HSD_JObj* fn_802CFB68(HSD_Joint* joint, HSD_Joint* joint_root,
                      HSD_JObj* jobj_root)
{
    HSD_Joint* jp;
    HSD_JObj* jobj;
    HSD_JObj* found;

    if (joint_root != NULL) {
        HSD_ASSERT(1059, jobj_root);
        jp = joint_root;
        jobj = jobj_root;
        while (jp != NULL) {
            HSD_ASSERT(1061, jobj);
            if (jp == joint) {
                return jobj;
            }
            if (!(jobj->flags & JOBJ_INSTANCE)) {
                found = fn_802CFB68(joint, jp->child, jobj->child);
                if (found != NULL) {
                    return found;
                }
            }
            jp = jp->next;
            jobj = jobj->next;
        }
    } else {
        HSD_ASSERT(1070, jobj_root == NULL);
    }
    return NULL;
}
#pragma pop

HSD_JObj* HSD_JObjLoadJoint(HSD_Joint* arg0)
{
    HSD_JObj* jobj = JObjLoadJointSub(arg0, 0);
    HSD_JObjResolveRefsAll(jobj, arg0);
    return jobj;
}

void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint)
{
    u8 _[4];

    if (jobj == NULL || joint == NULL) {
        return;
    }

    HSD_RObjResolveRefsAll(jobj->robj, joint->robjdesc);
    if (!!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObjUnref(jobj->child);
        jobj->child =
            HSD_IDGetData((HSD_IDKey) joint->child, NULL);
        HSD_ASSERT(1119, jobj->child);
        HSD_JObjRef(jobj->child);
    }
    if (union_type_dobj(jobj)) {
        HSD_DObjResolveRefsAll(jobj->u.dobj, joint->u.dobjdesc);
    }
}

void HSD_JObjResolveRefsAll(HSD_JObj* jobj, HSD_Joint* joint)
{
    u8 _[4];

    while (jobj != NULL && joint != NULL) {
        HSD_JObjResolveRefs(jobj, joint);
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObjResolveRefsAll(jobj->child, joint->child);
        }
        jobj = jobj->next;
        joint = joint->next;
    }
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

HSD_JObj* HSD_JObjGetPrev(HSD_JObj*);

HSD_JObj* HSD_JObjRemove(HSD_JObj* jobj)
{
    HSD_JObj* child;
    HSD_JObj* next;
    HSD_JObj* prev;

    if (jobj == NULL) {
        return 0;
    }
    child = jobj->child;
    if (child != NULL) {
        HSD_ASSERT(1216, child->next == NULL);
    }

    next = child != NULL ? child : jobj->next;

    prev = HSD_JObjGetPrev(jobj);
    if (prev != NULL) {
        prev->next = next;
    } else if (jobj->parent != NULL) {
        jobj->parent->child = next;
    }
    if (next != NULL && next == child) {
        next->next = jobj->next;
        next->parent = jobj->parent;
    }
    jobj->parent = NULL;
    jobj->child = NULL;
    jobj->next = NULL;
    HSD_JObjUnref(jobj);
    return child;
}

void HSD_JObjRemoveAll(HSD_JObj* jobj)
{
    HSD_JObj* prev;
    HSD_JObj* next;

    if (jobj == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        prev = HSD_JObjGetPrev(jobj);
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
        HSD_JObjUnref(jobj);
        jobj = next;
    }
}

void RecalcParentTrspBits(HSD_JObj* jobj)
{
    while (jobj != NULL) {
        HSD_JObj* child = jobj->child;
        u32 flags = ~JOBJ_ROOT_MASK;
        while (child != NULL) {
            flags |= (child->flags | child->flags << 10) & JOBJ_ROOT_MASK;
            child = child->next;
        }
        if (!(jobj->flags & ~flags)) {
            break;
        }
        jobj->flags &= flags;
        jobj = jobj->next;
    }
}

static void UpdateParentTrspBits(HSD_JObj* jobj, HSD_JObj* child)
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
    HSD_JObj* last;

    if (jobj == NULL || child == NULL) {
        return;
    }
    HSD_ASSERTREPORT(1353, child->parent == NULL,
                     "child should be a orphan.\n");
    HSD_ASSERTREPORT(1354, child->next == NULL,
                     "child should not have siblings");
    if (jobj->child == NULL) {
        jobj->child = child;
    } else {
        HSD_ASSERT(1360, !(jobj->flags & JOBJ_INSTANCE));
        last = jobj->child;
        while (last->next != NULL) {
            HSD_ASSERT(1363, last != child);
            last = last->next;
        }
        last->next = child;
    }
    child->parent = jobj;
    UpdateParentTrspBits(jobj, child);
}

HSD_JObj* HSD_JObjReparent(HSD_JObj* jobj, HSD_JObj* parent)
{
    HSD_JObj* next;

    if (jobj == NULL) {
        return NULL;
    }
    next = jobj->next;
    if (jobj->parent != NULL) {
        if (jobj->parent->child == jobj) {
            jobj->parent->child = next;
        } else {
            HSD_JObj* prev = HSD_JObjGetPrev(jobj);
            HSD_ASSERT(1394, prev);
            prev->next = next;
        }
        RecalcParentTrspBits(jobj->parent);
        jobj->parent = NULL;
    }
    jobj->next = NULL;
    HSD_JObjAddChild(parent, jobj);
    return next;
}

void HSD_JObjAddNext(HSD_JObj* jobj, HSD_JObj* next)
{
    HSD_JObj* cur;

    if (jobj == NULL || next == NULL) {
        return;
    }
    if (jobj->parent != NULL) {
        cur = jobj->parent->child;
        jobj->parent->child = NULL;
        jobj->flags &= ~JOBJ_ROOT_MASK;
    } else {
        cur = jobj;
    }
    HSD_JObjReparent(next, jobj->parent);
    if (next->child != NULL) {
        HSD_JObj* child = next->child;
        while (child->next != NULL) {
            child = child->next;
        }
        child->next = cur;
    } else {
        next->child = cur;
    }
    while (cur != NULL) {
        cur->parent = next;
        UpdateParentTrspBits(next, cur);
        cur = cur->next;
    }
}

HSD_JObj* HSD_JObjGetPrev(HSD_JObj* jobj)
{
    HSD_JObj* cur;

    if (jobj == NULL || jobj->parent == NULL) {
        return NULL;
    }
    if (jobj == jobj->parent->child) {
        return NULL;
    }
    cur = jobj->parent->child;
    while (cur != NULL) {
        if (cur->next == jobj) {
            return cur;
        }
        cur = cur->next;
    }
    HSD_Panic(__FILE__, 1519,
              "can not find specified jobj. maybe jobj tree is broken.\n");
    return NULL;
}

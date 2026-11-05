#include "mkgp2_names.h"
#include "jobj_unlock_private.h"

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

extern HSD_SList* lbl_806D21B4;
extern void (*lbl_806D21B8)(int, int, int, HSD_JObj*);
extern void (*lbl_806D21BC)(s32);
extern void (*lbl_806D21C0)(HSD_JObj*, s32);
#define ufc_callbacks lbl_806D21B4
#define dptcl_callback lbl_806D21B8
#define jsound_callback lbl_806D21BC
#define ptcltgt_callback lbl_806D21C0


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
        if (!jobj) __assert(lbl_806D0DB0, 981, lbl_806D0DA8);
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

extern char lbl_804FCB5C[10];
extern char lbl_804FCB68[17];

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
        if (!jobj_root) __assert(lbl_806D0DB0, 1059, lbl_804FCB5C);
        jp = joint_root;
        jobj = jobj_root;
        while (jp != NULL) {
            if (!jobj) __assert(lbl_806D0DB0, 1061, lbl_806D0DB8);
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
        if (jobj_root != NULL) __assert(lbl_806D0DB0, 1070, lbl_804FCB68);
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

static inline void JObjRefFromPool(HSD_JObj* jobj, char* pool)
{
    if (jobj != NULL) {
        jobj->object.ref_count++;
        if (jobj->object.ref_count == HSD_OBJ_NOREF)
            __assert(pool + 0x1e0, 93, pool + 0x1ec);
    }
}

void HSD_JObjResolveRefs(HSD_JObj* jobj, HSD_Joint* joint)
{
    char* pool = lbl_804FC9A8;
    u8 _[4];

    if (jobj == NULL || joint == NULL) {
        return;
    }

    HSD_RObjResolveRefsAll(jobj->robj, joint->robjdesc);
    if (!!(jobj->flags & JOBJ_INSTANCE)) {
        HSD_JObjUnref(jobj->child);
        jobj->child =
            HSD_IDGetData((HSD_IDKey) joint->child, NULL);
        if (!jobj->child) __assert(lbl_806D0DB0, 1119, pool + 0x1d4);
        JObjRefFromPool(jobj->child, pool);
    }
    if (union_type_dobj(jobj)) {
        HSD_DObjResolveRefsAll(jobj->u.dobj, joint->u.dobjdesc);
    }
}

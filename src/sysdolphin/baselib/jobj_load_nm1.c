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

/* Retain four traversal levels and the progressively outlined helpers. */
void HSD_JObjResolveRefsAll(HSD_JObj* jobj, HSD_Joint* joint)
{
    char* pool = lbl_804FC9A8;
    while (jobj != NULL && joint != NULL) {
        if (jobj != NULL && joint != NULL) {
            HSD_RObjResolveRefsAll(jobj->robj, joint->robjdesc);
            if (jobj->flags & JOBJ_INSTANCE) {
                HSD_JObjUnref(jobj->child);
                jobj->child = HSD_IDGetDataFromTable(NULL, (HSD_IDKey) joint->child, NULL);
                if (!jobj->child) __assert(lbl_806D0DB0, 1119, pool + 0x1d4);
                {
                    HSD_JObj* child = jobj->child;
                    if (child != NULL) {
                        child->object.ref_count++;
                        if (child->object.ref_count == HSD_OBJ_NOREF) __assert(pool + 0x1e0, 93, pool + 0x1ec);
                    }
                }
            }
            if (union_type_dobj(jobj)) HSD_DObjResolveRefsAll(jobj->u.dobj, joint->u.dobjdesc);
        }
        if (!(jobj->flags & JOBJ_INSTANCE)) {
            HSD_JObj* j1;
            HSD_Joint* t1;
            t1 = joint->child;
            j1 = jobj->child;
            while (j1 != NULL && t1 != NULL) {
                if (j1 != NULL && t1 != NULL) {
                    HSD_RObjResolveRefsAll(j1->robj, t1->robjdesc);
                    if (j1->flags & JOBJ_INSTANCE) {
                        HSD_JObjUnref(j1->child);
                        j1->child = HSD_IDGetDataFromTable(NULL, (HSD_IDKey) t1->child, NULL);
                        if (!j1->child) __assert(lbl_806D0DB0, 1119, pool + 0x1d4);
                        if (j1->child != NULL) jobj_ref_INC(j1->child);
                    }
                    if (union_type_dobj(j1)) HSD_DObjResolveRefsAll(j1->u.dobj, t1->u.dobjdesc);
                }
                if (!(j1->flags & JOBJ_INSTANCE)) {
                    HSD_JObj* j2;
                    HSD_Joint* t2;
                    t2 = t1->child;
                    j2 = j1->child;
                    while (j2 != NULL && t2 != NULL) {
                        if (j2 != NULL && t2 != NULL) {
                            HSD_RObjResolveRefsAll(j2->robj, t2->robjdesc);
                            if (j2->flags & JOBJ_INSTANCE) {
                                HSD_JObjUnref(j2->child);
                                j2->child = HSD_IDGetData((HSD_IDKey) t2->child, NULL);
                                if (!j2->child) __assert(lbl_806D0DB0, 1119, pool + 0x1d4);
                                HSD_JObjRef(j2->child);
                            }
                            if (union_type_dobj(j2)) HSD_DObjResolveRefsAll(j2->u.dobj, t2->u.dobjdesc);
                        }
                        if (!(j2->flags & JOBJ_INSTANCE)) {
                            HSD_JObj* j3;
                            HSD_Joint* t3;
                            t3 = t2->child;
                            j3 = j2->child;
                            while (j3 != NULL && t3 != NULL) {
                                HSD_JObjResolveRefs(j3, t3);
                                if (!(j3->flags & JOBJ_INSTANCE)) HSD_JObjResolveRefsAll(j3->child, t3->child);

                                j3 = j3->next;
                                t3 = t3->next;
                            }

                        }

                        j2 = j2->next;
                        t2 = t2->next;
                    }

                }

                j1 = j1->next;
                t1 = t1->next;
            }

        }

        jobj = jobj->next;
        joint = joint->next;
    }
}

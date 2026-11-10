#include "game/types/Vec3.h"
#include "game/types/HSD_JObj.h"
typedef struct Obj {
    void *vt;
    void *gobj;
    HSD_JObj *jobj;
} Obj;

extern char lbl_806D93A8[7];
extern char lbl_806D93B0[5];
extern const float lbl_806D93BC;
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);
extern void __assert(const char *, int, const char *);

static inline HSD_JObj *JObjGetChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline HSD_JObj *JObjGetNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline unsigned char JObjMtxIsDirty(HSD_JObj *jobj) {
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D93A8, 0x25d, lbl_806D93B0);
    }
    result = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void JObjAddRotationZ(HSD_JObj *jobj, float z) {
    if (!jobj) {
        __assert(lbl_806D93A8, 0x41d, lbl_806D93B0);
    }
    jobj->rotate.y += z;
    if (!(jobj->flags & 0x2000000)) {
        if (jobj != 0 && !JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

void fn_8018CE38(Obj *o) {
    HSD_JObj *jobj;

    if (o->gobj == 0 || o->jobj == 0) {
        return;
    }
    for (jobj = JObjGetChild(o->jobj); jobj != 0; jobj = JObjGetNext(jobj)) {
        JObjAddRotationZ(jobj, lbl_806D93BC);
    }
}

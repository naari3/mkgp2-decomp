#include "game/types/HSD_JObj.h"

#include "game/types/ObjectJObjView.h"

extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern char lbl_802E97B8[0xA];
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);

static inline void update_matrix(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char skip;

    flags = jobj->flags;
    skip = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        skip = 1;
    }
    if (!skip) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

#pragma exceptions on
void Object_SetJObjPositionVec(ObjectJObjView *object, float *position) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x3A9, lbl_806D2350);
        }
        if (position == 0) {
            __assert(lbl_806D2348, 0x3AA, lbl_802E97B8);
        }
        jobj->translate.x = position[0];
        jobj->translate.y = position[1];
        jobj->translate.z = position[2];
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

float Object_GetJObjRotationZ(ObjectJObjView *object) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0.0f;
    }
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x308, lbl_806D2350);
    }
    return jobj->rotate.z;
}

float Object_GetJObjRotationY(ObjectJObjView *object) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0.0f;
    }
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x2FA, lbl_806D2350);
    }
    return jobj->rotate.y;
}

float Object_GetJObjRotationX(ObjectJObjView *object) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0.0f;
    }
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x2EC, lbl_806D2350);
    }
    return jobj->rotate.x;
}
#pragma exceptions reset

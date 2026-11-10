#include "game/types/HSD_JObj.h"

typedef struct ObjectRotationView {
    unsigned char pad[0x2C];
    HSD_JObj *jobj;
} ObjectRotationView;

extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern char lbl_806D2358[4];
extern char lbl_802E9790[0x25];
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);

static void update_matrix(HSD_JObj *jobj) {
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
void Object_SetJObjRotationZ(ObjectRotationView *object, float rotation) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x2CC, lbl_806D2350);
        }
        if (jobj->flags & 0x00020000) {
            __assert(lbl_806D2348, 0x2CD, lbl_802E9790);
        }
        jobj->rotate.z = rotation;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjRotationY(ObjectRotationView *object, float rotation) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x2B8, lbl_806D2350);
        }
        if (jobj->flags & 0x00020000) {
            __assert(lbl_806D2348, 0x2B9, lbl_802E9790);
        }
        jobj->rotate.y = rotation;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjRotationX(ObjectRotationView *object, float rotation) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x2A4, lbl_806D2350);
        }
        if (jobj->flags & 0x00020000) {
            __assert(lbl_806D2348, 0x2A5, lbl_802E9790);
        }
        jobj->rotate.x = rotation;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjScaleXYZ(ObjectRotationView *object, float scale_x, float scale_y,
                            float scale_z) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x316, lbl_806D2350);
        }
        jobj->scale.x = scale_x;
        jobj->scale.y = scale_y;
        jobj->scale.z = scale_z;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjScaleVec(ObjectRotationView *object, float *scale) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x316, lbl_806D2350);
        }
        if (scale == 0) {
            __assert(lbl_806D2348, 0x317, lbl_806D2358);
        }
        jobj->scale.x = scale[0];
        jobj->scale.y = scale[1];
        jobj->scale.z = scale[2];
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjField40(ObjectRotationView *object, float value) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x3D4, lbl_806D2350);
        }
        jobj->translate.z = value;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjPositionY(ObjectRotationView *object, float position) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x3C6, lbl_806D2350);
        }
        jobj->translate.y = position;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjPositionX(ObjectRotationView *object, float position) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x3B8, lbl_806D2350);
        }
        jobj->translate.x = position;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

void Object_SetJObjPositionXYZ(ObjectRotationView *object, float position_x,
                               float position_y, float position_z) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x3A9, lbl_806D2350);
        }
        jobj->translate.x = position_x;
        jobj->translate.y = position_y;
        jobj->translate.z = position_z;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}
#pragma exceptions reset

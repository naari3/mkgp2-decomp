typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned int pad_18;
    float rotation_x;
    float rotation_y;
    float rotation_z;
    unsigned char pad_28[4];
    float scale_x;
    float scale_y;
    float scale_z;
    unsigned char pad_38[8];
    float field_40;
} HSD_JObj;

typedef struct ObjectRotationView {
    unsigned char pad[0x2C];
    HSD_JObj *jobj;
} ObjectRotationView;

extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern char lbl_806D2358[4];
extern char lbl_802E9790[0x25];
extern void __assert(char *, int, char *);
extern void fn_802D20AC(HSD_JObj *);

static void update_matrix(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char skip;

    flags = jobj->flags;
    skip = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        skip = 1;
    }
    if (!skip) {
        fn_802D20AC(jobj);
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
        jobj->rotation_z = rotation;
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
        jobj->rotation_y = rotation;
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
        jobj->rotation_x = rotation;
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
        jobj->scale_x = scale_x;
        jobj->scale_y = scale_y;
        jobj->scale_z = scale_z;
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
        jobj->scale_x = scale[0];
        jobj->scale_y = scale[1];
        jobj->scale_z = scale[2];
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
        jobj->field_40 = value;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}
#pragma exceptions reset

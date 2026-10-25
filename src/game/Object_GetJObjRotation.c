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
    float position_x;
    float position_y;
    float position_z;
} HSD_JObj;

typedef struct ObjectJObjView {
    unsigned char pad[0x2C];
    HSD_JObj *jobj;
} ObjectJObjView;

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
        jobj->position_x = position[0];
        jobj->position_y = position[1];
        jobj->position_z = position[2];
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
    return jobj->rotation_z;
}

float Object_GetJObjRotationY(ObjectJObjView *object) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0.0f;
    }
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x2FA, lbl_806D2350);
    }
    return jobj->rotation_y;
}

float Object_GetJObjRotationX(ObjectJObjView *object) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0.0f;
    }
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x2EC, lbl_806D2350);
    }
    return jobj->rotation_x;
}
#pragma exceptions reset

typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad_18[0x20];
    float position_x;
    float position_y;
    float position_z;
    float mtx[3][4];
} HSD_JObj;

typedef struct ObjectJObjView {
    unsigned char pad_00[2];
    unsigned char dirty;
    unsigned char pad_03[5];
    float frame;
    unsigned char pad_0C[8];
    float end_frame;
    void *override;
    unsigned char pad_1C[0x10];
    HSD_JObj *jobj;
} ObjectJObjView;

extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern char lbl_802E97B8[0xA];
extern void __assert(char *, int, char *);
extern void HSD_MtxGetTranslate(void *, float *);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);

static inline unsigned char mtx_is_dirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char dirty;

    if (jobj == 0) {
        __assert(lbl_806D2348, 0x25D, lbl_806D2350);
    }
    flags = jobj->flags;
    dirty = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        dirty = 1;
    }
    return dirty;
}

#pragma exceptions on
int Object_GetJObjPositionVec(ObjectJObjView *object, float *position) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0;
    }
    if (object->override != 0) {
        HSD_MtxGetTranslate(object->override, position);
    } else {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x3E4, lbl_806D2350);
        }
        if (position == 0) {
            __assert(lbl_806D2348, 0x3E5, lbl_802E97B8);
        }
        position[0] = jobj->position_x;
        position[1] = jobj->position_y;
        position[2] = jobj->position_z;
    }
    return 1;
}

void *Object_GetJObjLocalMatrix(ObjectJObjView *object) {
    HSD_JObj *jobj = object->jobj;

    if (jobj == 0) {
        return 0;
    }
    if (object->override != 0) {
        return object->override;
    }
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x47C, lbl_806D2350);
    }
    if (jobj != 0 && mtx_is_dirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
    return jobj->mtx;
}
#pragma exceptions reset

int Object_SetField14_IfValid(ObjectJObjView *object, float end_frame) {
    if (object->jobj == 0) {
        return 0;
    }
    if (object->frame < 0.0f) {
        return 0;
    }
    if (end_frame < 0.0f) {
        return 0;
    }
    object->end_frame = end_frame;
    return 1;
}

int Object_SetField8_AndDirty(ObjectJObjView *object, float frame) {
    if (object->jobj == 0) {
        return 0;
    }
    if (object->frame < 0.0f) {
        return 0;
    }
    if (frame < 0.0f) {
        return 0;
    }
    object->dirty = 1;
    object->frame = frame;
    return 1;
}

float Object_GetField8(ObjectJObjView *object) {
    float frame;

    if (object->jobj == 0) {
        return 0.0f;
    }
    frame = object->frame;
    if (frame < 0.0f) {
        return 0.0f;
    }
    return frame;
}

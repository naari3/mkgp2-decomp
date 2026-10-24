typedef struct Quat {
    float x;
    float y;
    float z;
    float w;
} Quat;

typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned int pad_18;
    Quat rotation;
} HSD_JObj;

typedef struct ObjectJObjView {
    unsigned char pad[0x2C];
    HSD_JObj *jobj;
} ObjectJObjView;

extern const Quat lbl_802E9780;
extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern void __assert(char *, int, char *);
extern void fn_802D20AC(HSD_JObj *);

static inline void update_matrix(HSD_JObj *jobj) {
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

void JObj_SetRotationQuat(ObjectJObjView *object, float x, float y, float z) {
    HSD_JObj *jobj = object->jobj;

    if (jobj != 0) {
        Quat quat = lbl_802E9780;

        quat.x = x;
        quat.y = y;
        quat.z = z;
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x290, lbl_806D2350);
        }
        jobj->rotation.x = quat.x;
        jobj->rotation.y = quat.y;
        jobj->rotation.z = quat.z;
        jobj->rotation.w = quat.w;
        if (!(jobj->flags & 0x02000000) && jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D2348, 0x25D, lbl_806D2350);
            }
            update_matrix(jobj);
        }
    }
}

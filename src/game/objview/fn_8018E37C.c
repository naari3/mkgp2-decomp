typedef struct HSD_JObj {
    char pad00[0x8];
    struct HSD_JObj *next;
    char pad0c[0x4];
    struct HSD_JObj *child;
    unsigned int flags;
    char pad18[0x4];
    float rotX;
    float rotY;
    float rotZ;
} HSD_JObj;

typedef struct Spinner {
    void *vt;
    HSD_JObj *root;
    float angle;
} Spinner;

extern char lbl_806D9428[7];
extern char lbl_806D9430[5];
extern char lbl_8037809C[];
extern const float lbl_806D9420;
extern const float lbl_806D9424;
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) {
        __assert(lbl_806D9428, 0x25D, lbl_806D9430);
    }
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        clean = 1;
    }
    if (!clean) {
        HSD_JObjSetMtxDirtySub(jobj);
    }
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D9428, 0x2B8, lbl_806D9430);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D9428, 0x2B9, lbl_8037809C);
    }
    jobj->rotY = y;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

static inline HSD_JObj *HSD_JObjGetChild(HSD_JObj *jobj) {
    if (jobj == 0) return 0;
    return jobj->child;
}

static inline HSD_JObj *HSD_JObjGetNext(HSD_JObj *jobj) {
    if (jobj == 0) return 0;
    return jobj->next;
}

void fn_8018E37C(Spinner *s) {
    HSD_JObj *j;
    s->angle += 0.005f;
    if (s->angle >= 6.2831855f) s->angle -= 6.2831855f;
    for (j = HSD_JObjGetChild(s->root); j != 0; j = HSD_JObjGetNext(j)) {
        HSD_JObjSetRotationY(j, s->angle);
    }
}

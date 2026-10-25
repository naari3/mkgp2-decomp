typedef struct HSD_JObj {
    unsigned char pad[0x14];
    unsigned int flags;
    unsigned char pad_18[0x14];
    float scale_x;
    float scale_y;
    float scale_z;
} HSD_JObj;

extern char lbl_806D2348[7];
extern char lbl_806D2350[5];
extern void __assert(char *, int, char *);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *);

static inline void set_mtx_dirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char skip;

    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D2348, 0x25D, lbl_806D2350);
        }
        flags = jobj->flags;
        skip = 0;
        if (!(flags & 0x00800000) && (flags & 0x40)) {
            skip = 1;
        }
        if (!skip) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

static inline void set_scale_x(HSD_JObj *jobj, float x) {
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x325, lbl_806D2350);
    }
    jobj->scale_x = x;
    set_mtx_dirty(jobj);
}

static inline void set_scale_y(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x333, lbl_806D2350);
    }
    jobj->scale_y = y;
    set_mtx_dirty(jobj);
}

static inline void set_scale_z(HSD_JObj *jobj, float z) {
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x341, lbl_806D2350);
    }
    jobj->scale_z = z;
    set_mtx_dirty(jobj);
}

void JObj_SetScale(void *object, HSD_JObj *jobj, float x, float y, float z) {
    if (jobj != 0) {
        set_scale_x(jobj, x);
        set_scale_y(jobj, y);
        set_scale_z(jobj, z);
    }
}

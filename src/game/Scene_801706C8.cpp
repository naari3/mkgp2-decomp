/*
 * 0x801706C8..0x801707FC: per-entry child scale update and tree draw.
 */

struct HSD_JObj {
    char pad00[0x8];
    HSD_JObj *next;
    char pad0C[0x4];
    HSD_JObj *child;
    unsigned int flags;
    char pad18[0x14];
    float scaleX;
    float scaleY;
    float scaleZ;
};

struct GrowEntry {
    HSD_JObj *jobj;
    char pad04[0xC];
    int state;
    char pad14[0x4];
    float scale;
    void *sub;
};

struct GrowSet {
    char pad00[0x8];
    GrowEntry *entries;
    int count;
};

extern "C" {
extern char lbl_806D8CD8[7];
extern char lbl_806D8CE0[5];
void __assert(char *, int, char *);
void fn_802D20AC(HSD_JObj *);
void fn_802CF3B0(HSD_JObj *, int, int, int);
void fn_8016F158(void *);
}

static inline HSD_JObj *HSD_JObjGetChild(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->child;
}

static inline HSD_JObj *HSD_JObjGetNext(HSD_JObj *jobj) {
    if (jobj == 0) {
        return 0;
    }
    return jobj->next;
}

static inline void HSD_JObjSetMtxDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char clean;

    if (jobj == 0) {
        __assert(lbl_806D8CD8, 0x25D, lbl_806D8CE0);
    }
    flags = jobj->flags;
    clean = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        clean = 1;
    }
    if (!clean) {
        fn_802D20AC(jobj);
    }
}

static inline void HSD_JObjSetScaleY(HSD_JObj *jobj, float y) {
    if (jobj == 0) {
        __assert(lbl_806D8CD8, 0x333, lbl_806D8CE0);
    }
    jobj->scaleY = y;
    if (!(jobj->flags & 0x02000000) && jobj != 0) {
        HSD_JObjSetMtxDirty(jobj);
    }
}

extern "C" {

void fn_801706C8(GrowSet *self) {
    int i;
    GrowEntry *e;
    HSD_JObj *jobj;

    for (i = 0; i < self->count; i++) {
        e = &self->entries[i];

        if (e->state >= 2) {
            for (jobj = HSD_JObjGetChild(e->jobj); jobj != 0; jobj = HSD_JObjGetNext(jobj)) {
                HSD_JObjSetScaleY(jobj, e->scale);
            }
            fn_802CF3B0(e->jobj, 0, 7, 0);
        }
        fn_8016F158(e->sub);
    }
}

}

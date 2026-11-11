#ifndef GAME_DLIST_GEOMETRY_PRIVATE_H
#define GAME_DLIST_GEOMETRY_PRIVATE_H
#include "game/types/gx_data.h"
#include "sysdolphin/baselib/jobj.h"

typedef struct DListJObjMatrix { char pad[0x44]; float mtx[3][4]; } DListJObjMatrix;

typedef struct DListVec { float x, y, z; } DListVec;
typedef struct DListFace { DListVec v[4]; int count; } DListFace;
typedef struct DListVtxDesc {
    int attr, type, count, format;
    unsigned char frac, pad11;
    unsigned short stride;
    float *array;
} DListVtxDesc;
typedef struct DListAttrEntry { DListVtxDesc *desc; unsigned int offset; } DListAttrEntry;
typedef struct DListPObj {
    char pad00[8];
    DListVtxDesc *verts;
    unsigned short flags, n_display;
    unsigned char *display;
} DListPObj;

extern DListAttrEntry lbl_80677E18[22];
extern unsigned int lbl_806D1678;
extern const char lbl_80376F9C[], lbl_80376FB0[];
extern const char lbl_806D9280[7], lbl_806D9288[5];
extern void fn_801866DC(DListVtxDesc *);
extern void OSPanic(const char *, int, const char *, ...);
extern void __assert(const char *, int, const char *);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);
extern void PSMTXMultVec(float (*)[4], DListVec *, DListVec *);

static inline void ReadPosition(unsigned char *p, DListVec *out) {
    int i;
    for (i = 0; i < 22; ++i) {
        if (!lbl_80677E18[i].desc || lbl_80677E18[i].desc->attr == 255) break;
        if (lbl_80677E18[i].desc->attr == 9) {
            DListVtxDesc *desc;
            unsigned int index;
            float *v;
            if (lbl_80677E18[i].desc->type == 3) index = GXDATA_U16(p + lbl_80677E18[i].offset);
            else index = *(unsigned char *)(p + lbl_80677E18[i].offset);
            desc = lbl_80677E18[i].desc;
            v = desc->array + index * (desc->stride / 4);
            out->x = GXDATA_F32(v); out->y = GXDATA_F32(v + 1); out->z = GXDATA_F32(v + 2);
            break;
        }
    }
}

static inline unsigned char MatrixDirty(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char dirty;
    if (!jobj) __assert(lbl_806D9280, 0x25d, lbl_806D9288);
    flags = jobj->flags;
    dirty = 0;
    if (!(flags & 0x800000) && (flags & 0x40)) dirty = 1;
    return dirty;
}
static inline void SetupMatrix(HSD_JObj *jobj) {
    if (jobj) {
        if (MatrixDirty(jobj)) HSD_JObjSetupMatrixSub(jobj);
    }
}
static inline float (*GetMatrix(HSD_JObj *jobj))[4] {
    if (!jobj) __assert(lbl_806D9280, 0x47c, lbl_806D9288);
    SetupMatrix(jobj);
    /* The canonical partial HSD_JObj header leaves the matrix opaque. */
    return ((DListJObjMatrix *)jobj)->mtx;
}

static inline unsigned int CmdSize(unsigned char *p) {
    switch (*p) {
    case 0x00:
        return 1;
    case 0x61:
        return 5;
    case 0x08:
        return 6;
    case 0x10:
        return ((unsigned int)(GXDATA_U16(p + 1) + 1) * 32 + 40) / 8;
    case 0x20:
        return 5;
    case 0x28:
        return 5;
    case 0x30:
        return 5;
    case 0x38:
        return 5;
    }
    switch (*p & 0xf8) {
    case 0x80:
    case 0x90:
    case 0x98:
    case 0xa0:
    case 0xa8:
    case 0xb0:
    case 0xb8:
        return 0;
    }
    OSPanic(lbl_80376F9C, 0x103, lbl_80376FB0);
    return 0;
}

#endif

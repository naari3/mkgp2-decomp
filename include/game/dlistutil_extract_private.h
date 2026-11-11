#ifndef GAME_DLISTUTIL_EXTRACT_PRIVATE_H
#define GAME_DLISTUTIL_EXTRACT_PRIVATE_H
#include "game/types/gx_data.h"

#include <sysdolphin/baselib/jobj.h>

/* dolphin/mtx.h pulls in libc headers unavailable to this game flag recipe. */
typedef struct DListVec { float x, y, z; } Vec;
typedef float (*MtxPtr)[4];
extern void PSMTXMultVec(MtxPtr, const Vec *, Vec *);

/* Private views of the display-list descriptors used by these extractors. */
typedef struct DListVtxDesc {
    int attr;
    int type;
    int count;
    int format;
    unsigned char frac;
    unsigned char unused;
    unsigned short stride;
    float *array;
} DListVtxDesc;

typedef struct DListVtxEntry {
    DListVtxDesc *desc;
    unsigned int offset;
} DListVtxEntry;

typedef struct DListPObj {
    unsigned char pad[8];
    DListVtxDesc *verts;
    unsigned short flags;
    unsigned short n_display;
    unsigned char *display;
} DListPObj;

typedef struct DListQuad {
    Vec vertex[4];
} DListQuad;

typedef struct DListQuadInfo {
    Vec vertex[4];
    int flags;
    float value1;
    float value2;
} DListQuadInfo;

extern DListVtxEntry lbl_80677E18[22];
extern unsigned int lbl_806D1678;
extern const char lbl_80376F9C[];
extern const char lbl_80376FB0[];
extern const char lbl_806D9280[7];
extern const char lbl_806D9288[5];
extern const float lbl_806D927C;
extern void fn_801866DC(DListVtxDesc *);
extern void OSPanic(const char *, int, const char *, ...);
extern void __assert(const char *, int, const char *);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);

static inline unsigned int DListCmdSize(unsigned char *p) {
    switch (*p) {
    case 0: return 1;
    case 0x61: return 5;
    case 8: return 6;
    case 0x10: return ((unsigned int)(GXDATA_U16(p + 1) + 1) * 32 + 40) / 8;
    case 0x20: return 5;
    case 0x28: return 5;
    case 0x30: return 5;
    case 0x38: return 5;
    }
    switch (*p & 0xf8) {
    case 0x80: case 0x90: case 0x98: case 0xa0:
    case 0xa8: case 0xb0: case 0xb8: return 0;
    }
    OSPanic(lbl_80376F9C, 0x103, lbl_80376FB0);
    return 0;
}

static inline unsigned char DListGetPosition(unsigned char *p, Vec *out) {
    int i;
    for (i = 0; i < 22; ++i) {
        if (!lbl_80677E18[i].desc || lbl_80677E18[i].desc->attr == 0xff) break;
        if (lbl_80677E18[i].desc->attr == 9) {
            unsigned int index;
            float *src;
            if (lbl_80677E18[i].desc->type == 3)
                index = GXDATA_U16(p + lbl_80677E18[i].offset);
            else
                index = *(unsigned char *)(p + lbl_80677E18[i].offset);
            src = lbl_80677E18[i].desc->array + index * (lbl_80677E18[i].desc->stride / 4);
            out->x = GXDATA_F32(src);
            out->y = GXDATA_F32(src + 1);
            out->z = GXDATA_F32(src + 2);
            return 1;
        }
    }
    return 0;
}

static inline unsigned char DListMatrixDirty(HSD_JObj *jobj) {
    int dirty;
    if (!jobj) __assert(lbl_806D9280, 0x25d, lbl_806D9288);
    dirty = 0;
    if (!(jobj->flags & 0x800000) && (jobj->flags & 0x40)) dirty = 1;
    return dirty;
}

typedef struct DListJObjMatrixView {
    unsigned char pad[0x44];
    float matrix[3][4];
} DListJObjMatrixView;

static inline MtxPtr DListGetMatrix(HSD_JObj *jobj) {
    if (!jobj) __assert(lbl_806D9280, 0x47c, lbl_806D9288);
    if (jobj && DListMatrixDirty(jobj)) HSD_JObjSetupMatrixSub(jobj);
    /* The canonical partial HSD_JObj header leaves the matrix inside _pad_1c. */
    return ((DListJObjMatrixView *)jobj)->matrix;
}

#endif

#ifndef GAME_DLIST_BOUNDS_PRIVATE_H
#define GAME_DLIST_BOUNDS_PRIVATE_H
#include "game/types/gx_data.h"
#include "sysdolphin/baselib/jobj.h"
#include "sysdolphin/baselib/dobj.h"
typedef struct BoundsVec { float x, y, z; } BoundsVec;
typedef struct VtxDesc {
    int attr, type, count, format;
    unsigned char frac, pad;
    unsigned short stride;
    float *array;
} VtxDesc;
typedef struct VtxAttrEntry { VtxDesc *desc; unsigned int offset; } VtxAttrEntry;
struct HSD_PObj {
    void *info;
    HSD_PObj *next;
    VtxDesc *verts;
    unsigned short flags, n_display;
    unsigned char *display;
};
extern VtxAttrEntry lbl_80677E18[22];
extern unsigned int lbl_806D1678;
extern const char lbl_80376F60[];
extern const char lbl_806D9280[8], lbl_806D9288[8];
extern const float lbl_806D927C, lbl_806D9264;
extern void fn_801866DC(VtxDesc *);
extern void OSPanic(const char *, int, const char *, ...);
extern void __assert(const char *, int, const char *);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *);
extern void PSMTXMultVec(void *, BoundsVec *, BoundsVec *);
extern void Vec3_Subtract(BoundsVec *, BoundsVec *, BoundsVec *);
extern float PSVECSquareMag(BoundsVec *);
extern float Vec3_Magnitude(BoundsVec *);
static inline unsigned int CmdSize(unsigned char *p, const char *messages) {
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
    OSPanic(messages + 0x3c, 0x103, messages + 0x50);
    return 0;
}


static inline unsigned char ReadPosition(unsigned char *p, BoundsVec *out) {
    int i;
    for (i=0;i<22;++i) {
        if (!lbl_80677E18[i].desc || lbl_80677E18[i].desc->attr==255) break;
        if (lbl_80677E18[i].desc->attr==9) {
            VtxAttrEntry *entry=&lbl_80677E18[i];
            VtxDesc *d=entry->desc;
            unsigned int index;
            float *v;
            if (d->type==3) index=GXDATA_U16(p+entry->offset);
            else index=p[entry->offset];
            v=d->array+index*(d->stride/4);
            out->x=GXDATA_F32(v);out->y=GXDATA_F32(v + 1);out->z=GXDATA_F32(v + 2);
            return 1;
        }
    }
    return 0;
}
static inline unsigned char MatrixDirty(HSD_JObj *j) {
    unsigned char dirty;
    if (!j) __assert(lbl_806D9280,0x25d,lbl_806D9288);
    dirty=0;
    if (!(j->flags & 0x800000) && (j->flags & 0x40)) dirty=1;
    return dirty;
}
static inline void SetupMatrix(HSD_JObj *j) {
    if (!j) __assert(lbl_806D9280,0x47c,lbl_806D9288);
    if (j && MatrixDirty(j)) HSD_JObjSetupMatrixSub(j);
}
static inline void Transform(HSD_JObj *j, BoundsVec *v) {
    SetupMatrix(j);
    PSMTXMultVec((char *)j+0x44,v,v);
}
static inline void Extend(BoundsVec *lo, BoundsVec *hi, BoundsVec *v) {
    if (lbl_806D927C==lo->x && lbl_806D927C==lo->y && lbl_806D927C==lo->z &&
        lbl_806D927C==hi->x && lbl_806D927C==hi->y && lbl_806D927C==hi->z) {
        lo->x=v->x; lo->y=v->y; lo->z=v->z;
        hi->x=v->x; hi->y=v->y; hi->z=v->z;
    } else {
        if (v->x<lo->x) lo->x=v->x;
        if (v->y<lo->y) lo->y=v->y;
        if (v->z<lo->z) lo->z=v->z;
        if (v->x>hi->x) hi->x=v->x;
        if (v->y>hi->y) hi->y=v->y;
        if (v->z>hi->z) hi->z=v->z;
    }
}
#endif

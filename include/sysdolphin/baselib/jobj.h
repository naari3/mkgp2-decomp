#ifndef SYSDOLPHIN_BASELIB_JOBJ_H
#define SYSDOLPHIN_BASELIB_JOBJ_H

typedef struct HSD_AObj HSD_AObj;
typedef struct HSD_DObj HSD_DObj;
typedef struct HSD_RObj HSD_RObj;

/* Partial layout. Confirmed offsets match SSBM HAL Sysdolphin HSD_JObj. */
typedef struct HSD_JObj {
    char  _pad_00[0x10];   /* +0x00 */
    struct HSD_JObj* child;/* +0x10 */
    unsigned int flags;    /* +0x14 */
    HSD_DObj* dobj;        /* +0x18 (union member in SSBM, flattened here) */
    char  _pad_1c[0x60];   /* +0x1C..+0x7C */
    HSD_AObj* aobj;        /* +0x7C */
    HSD_RObj* robj;        /* +0x80 */
    char  _pad_84[0x4];    /* +0x84..+0x88 */
} HSD_JObj;

#define JOBJ_PTCL   (1 << 5)   /* 0x0020 */
#define JOBJ_SPLINE (1 << 14)  /* 0x4000 */

extern void HSD_AObjReqAnim(HSD_AObj* aobj, float frame);
extern void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float frame, unsigned int flags);
extern void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, float frame, unsigned int flags);

void HSD_JObjReqAnimByFlags(HSD_JObj* jobj, unsigned int flags, float frame);

#endif

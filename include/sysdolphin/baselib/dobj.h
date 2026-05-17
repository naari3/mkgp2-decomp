#ifndef SYSDOLPHIN_BASELIB_DOBJ_H
#define SYSDOLPHIN_BASELIB_DOBJ_H

typedef unsigned int u32;

typedef struct HSD_MObj HSD_MObj;
typedef struct HSD_PObj HSD_PObj;

/* mkgp2 HSD_DObj layout. mobj/pobj are swapped vs SSBM melee — confirmed
 * by call-site signatures (MObj is iterated via *AllByFlags, PObj is single). */
typedef struct HSD_DObj {
    void*             parent;  /* +0x00 (HSD_Class) */
    struct HSD_DObj*  next;    /* +0x04 */
    HSD_PObj*         pobj;    /* +0x08 */
    HSD_MObj*         mobj;    /* +0x0C */
} HSD_DObj;

extern void HSD_MObjReqAnimAllByFlags(HSD_MObj* mobj, float frame, u32 flags);
extern void HSD_PObjReqAnimByFlags(HSD_PObj* pobj, float frame, u32 flags);

void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float frame, u32 flags);

#endif

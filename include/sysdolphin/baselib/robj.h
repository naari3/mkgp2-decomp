#ifndef SYSDOLPHIN_BASELIB_ROBJ_H
#define SYSDOLPHIN_BASELIB_ROBJ_H

typedef unsigned int u32;

typedef struct HSD_AObj HSD_AObj;

/* Layout matches SSBM HAL Sysdolphin HSD_RObj. */
typedef struct HSD_RObj {
    struct HSD_RObj* next;     /* +0x00 */
    u32              flags;    /* +0x04 */
    char             _u_pad[0x10]; /* +0x08 union: jobj/exp/limit/ik_hint */
    HSD_AObj*        aobj;     /* +0x18 */
} HSD_RObj;

extern void HSD_AObjReqAnim(HSD_AObj* aobj, float frame);

void HSD_RObjReqAnimAllByFlags(HSD_RObj* robj, float frame, u32 flags);

#endif

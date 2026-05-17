#ifndef SYSDOLPHIN_BASELIB_AOBJ_H
#define SYSDOLPHIN_BASELIB_AOBJ_H

typedef struct HSD_FObj HSD_FObj;
typedef struct HSD_Obj HSD_Obj;

/* Layout matches SSBM HAL Sysdolphin HSD_AObj (mkgp2 access pattern confirms). */
typedef struct HSD_AObj {
    unsigned int   flags;        /* +0x00 */
    float          curr_frame;   /* +0x04 */
    float          rewind_frame; /* +0x08 */
    float          end_frame;    /* +0x0C */
    float          framerate;    /* +0x10 */
    HSD_FObj*      fobj;         /* +0x14 */
    HSD_Obj*       hsd_obj;      /* +0x18 */
} HSD_AObj;

#define AOBJ_REWINDED   (1 << 26)
#define AOBJ_FIRST_PLAY (1 << 27)
#define AOBJ_NO_UPDATE  (1 << 28)
#define AOBJ_LOOP       (1 << 29)
#define AOBJ_NO_ANIM    (1 << 30)

extern void HSD_FObjReqAnimAll(HSD_FObj* fobj, float frame);

void HSD_AObjReqAnim(HSD_AObj* aobj, float frame);

#endif

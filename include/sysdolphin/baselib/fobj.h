#ifndef SYSDOLPHIN_BASELIB_FOBJ_H
#define SYSDOLPHIN_BASELIB_FOBJ_H

typedef unsigned char  u8;
typedef unsigned short u16;
typedef signed short   s16;
typedef unsigned int   u32;

#define TYPE_ROBJ 1
#define TYPE_JOBJ 12

/* Layout matches SSBM HAL Sysdolphin HSD_FObj. */
typedef struct HSD_FObj {
    struct HSD_FObj* next;    /* +0x00 */
    u8*  ad;                  /* +0x04 */
    u8*  ad_head;             /* +0x08 */
    u32  length;              /* +0x0C */
    u8   flags;               /* +0x10 */
    u8   op;                  /* +0x11 */
    u8   op_intrp;            /* +0x12 */
    u8   obj_type;            /* +0x13 */
    u8   frac_value;          /* +0x14 */
    u8   frac_slope;          /* +0x15 */
    u16  nb_pack;             /* +0x16 */
    s16  startframe;          /* +0x18 */
    u16  fterm;               /* +0x1A */
    float time;               /* +0x1C */
    float p0;                 /* +0x20 */
    float p1;                 /* +0x24 */
    float d0;                 /* +0x28 */
    float d1;                 /* +0x2C */
} HSD_FObj;

void HSD_FObjReqAnimAll(HSD_FObj* fobj, float startframe);

#endif

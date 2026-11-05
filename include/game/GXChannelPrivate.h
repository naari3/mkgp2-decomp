#ifndef GAME_GXCHANNEL_PRIVATE_H
#define GAME_GXCHANNEL_PRIVATE_H

/* GX channel: binds an HSD JObj/DObj pair (with its MObj and first PObj)
 * as the current GX render state.  Shared by the GXChannel_* TUs
 * (0x8007D11C..0x8007DC08).  The HSD types below are minimal views of the
 * sysdolphin baselib objects; GX enums mirror <dolphin/gx/GXEnum.h>. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef float Mtx[3][4];
typedef float (*MtxPtr)[4];

typedef enum _GXAttr {
    GX_VA_PNMTXIDX,
    GX_VA_TEX0MTXIDX,
    GX_VA_TEX1MTXIDX,
    GX_VA_TEX2MTXIDX,
    GX_VA_TEX3MTXIDX,
    GX_VA_TEX4MTXIDX,
    GX_VA_TEX5MTXIDX,
    GX_VA_TEX6MTXIDX,
    GX_VA_TEX7MTXIDX,
    GX_VA_POS,
    GX_VA_NULL = 0xFF
} GXAttr;
typedef enum _GXAttrType { GX_NONE, GX_DIRECT, GX_INDEX8, GX_INDEX16 } GXAttrType;
typedef int GXCompCnt;
typedef int GXCompType;
typedef enum _GXVtxFmt { GX_VTXFMT0 } GXVtxFmt;
typedef enum _GXCullMode { GX_CULL_NONE, GX_CULL_FRONT, GX_CULL_BACK, GX_CULL_ALL } GXCullMode;

extern void GXSetArray(GXAttr attr, void *base_ptr, u8 stride);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(GXAttr attr, GXAttrType type);
extern void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);

typedef struct HSD_VtxDescList {
    GXAttr attr;          /* 0x00 */
    GXAttrType attr_type; /* 0x04 */
    GXCompCnt comp_cnt;   /* 0x08 */
    GXCompType comp_type; /* 0x0C */
    u8 frac;              /* 0x10 */
    u16 stride;           /* 0x12 */
    void *vertex;         /* 0x14 */
} HSD_VtxDescList;

typedef struct HSD_PObj {
    void *class_info;         /* 0x00 */
    struct HSD_PObj *next;    /* 0x04 */
    HSD_VtxDescList *verts;   /* 0x08 */
    u16 flags;                /* 0x0C */
    u16 n_display;            /* 0x0E */
    u8 *display;              /* 0x10 */
} HSD_PObj;

typedef struct HSD_MObj {
    u8 pad00[0x1C];
    void *colors; /* 0x1C: channel colour table for GXChannel_PushChannelColors */
} HSD_MObj;

typedef struct HSD_DObj {
    void *class_info;      /* 0x00 */
    struct HSD_DObj *next; /* 0x04 */
    HSD_MObj *mobj;        /* 0x08 */
    HSD_PObj *pobj;        /* 0x0C */
} HSD_DObj;

typedef struct HSD_JObj {
    u8 pad00[0x14];
    u32 flags;   /* 0x14 */
    u8 pad18[0x44 - 0x18];
    Mtx mtx;     /* 0x44 */
} HSD_JObj;

typedef struct HSD_CObj {
    u8 pad00[0x54];
    Mtx view_mtx; /* 0x54 */
} HSD_CObj;

#define JOBJ_LIGHTING (1 << 7)
#define JOBJ_SPECULAR (1 << 16)

typedef struct GXChannel {
    HSD_JObj *jobj; /* 0x00 */
    HSD_DObj *dobj; /* 0x04 */
    void *arg;      /* 0x08 */
    u8 bound;       /* 0x0C */
    MtxPtr view_mtx; /* 0x10: current CObj view matrix */
} GXChannel;

#define POBJ_CULLFRONT (1 << 14)
#define POBJ_CULLBACK (1 << 15)

extern HSD_CObj *HSD_CObjGetCurrent(void);
extern void HSD_JObjSetCurrent(HSD_JObj *jobj);
extern void HSD_DObjSetCurrent(HSD_DObj *dobj);
extern void HSD_MObjSetCurrent(HSD_MObj *mobj);
extern void HSD_MObjSetup(HSD_MObj *mobj, void *arg);
extern void HSD_StateSetCullMode(GXCullMode mode);

extern int GXChannel_Bind(GXChannel *self);

#endif

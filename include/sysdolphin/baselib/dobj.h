#ifndef SYSDOLPHIN_BASELIB_DOBJ_H
#define SYSDOLPHIN_BASELIB_DOBJ_H

typedef unsigned int u32;

typedef struct HSD_MObj HSD_MObj;
typedef struct HSD_PObj HSD_PObj;
typedef struct HSD_AObj HSD_AObj;
typedef struct HSD_ShapeAnim HSD_ShapeAnim;

typedef struct HSD_MatAnim {
    struct HSD_MatAnim* next;
} HSD_MatAnim;

typedef struct HSD_ShapeAnimDObj {
    struct HSD_ShapeAnimDObj* next;
    HSD_ShapeAnim* shapeanim;
} HSD_ShapeAnimDObj;

/* Same layout as SSBM HSD_DObj. */
typedef struct HSD_DObj {
    void**            class_info; /* +0x00 (HSD_ClassInfo*) */
    struct HSD_DObj*  next;       /* +0x04 */
    HSD_MObj*         mobj;       /* +0x08 */
    HSD_PObj*         pobj;       /* +0x0C */
    HSD_AObj*         aobj;       /* +0x10 */
    u32               flags;      /* +0x14 */
} HSD_DObj;

/* Placeholder symbol names are kept while game code still refers to them. */
void HSD_DObjSetCurrent(HSD_DObj* dobj);                    /* HSD_DObjSetCurrent */
void HSD_DObjSetFlags(HSD_DObj* dobj, u32 flags);         /* HSD_DObjSetFlags */
void HSD_DObjClearFlags(HSD_DObj* dobj, u32 flags);         /* HSD_DObjClearFlags */
void HSD_DObjAddAnimAll(HSD_DObj* dobj, HSD_MatAnim* matanim,
                 HSD_ShapeAnimDObj* shapeanimdobj);  /* HSD_DObjAddAnimAll */
void HSD_DObjReqAnimAllByFlags(HSD_DObj* dobj, float frame, u32 flags);
void HSD_DObjAnimAll(HSD_DObj* dobj);                    /* HSD_DObjAnimAll */

#endif

/* GXChannel_PushTransform @ 0x8007D11C: draw a bound GX channel with a
 * new model matrix.
 *
 * Copies `mtx` into the channel's JObj, builds the position matrix against
 * the current camera view, loads position/normal(/texture) matrices the way
 * HSD pobj.c SetupRigidModelMtx does, pushes the material channel colours
 * and calls the display lists of every PObj of every DObj in the chain.
 * Returns 0 if the channel is not bound (no value otherwise).
 */
#include "game/GXChannelPrivate.h"

typedef enum PObjSetupFlag {
    SETUP_NONE = 0,
    SETUP_NORMAL = 1 << 0,
    SETUP_REFLECTION = 1 << 1,
    SETUP_HIGHLIGHT = 1 << 2,
    SETUP_NORMAL_PROJECTION = SETUP_REFLECTION | SETUP_HIGHLIGHT
} PObjSetupFlag;

#define TEX_COORD_REFLECTION 1
#define TEX_COORD_HILIGHT 2
#define GX_PNMTX0 0
#define GX_TEXMTX0 30
#define GX_MTX3x4 0

/* SETUP_NORMAL, kept as a shared .sdata2 constant by the original build. */
extern const PObjSetupFlag lbl_806D2FB4;

extern void PSMTXCopy(Mtx src, Mtx dst);
extern u32 PSMTXInvXpose(Mtx src, Mtx dst);
extern void HSD_JObjMakePositionMtx(HSD_JObj *jobj, MtxPtr vmtx, Mtx pmtx);
extern void HSD_LObjSetupSpecularInit(Mtx pmtx);
extern void GXSetCurrentMtx(u32 id);
extern void GXLoadPosMtxImm(Mtx mtx, u32 id);
extern void GXLoadNrmMtxImm(Mtx mtx, u32 id);
extern void GXLoadTexMtxImm(Mtx mtx, u32 id, int type);
extern void *_HSD_TObjGetCurrentByType(void *tobj, u32 mapping);
extern void GXChannel_PushChannelColors(void *colors);
extern void GXCallDisplayList(void *list, u32 nbytes);

static inline HSD_DObj *HSD_DObjGetNext(HSD_DObj *dobj)
{
    return dobj ? dobj->next : 0;
}

#pragma exceptions on
int GXChannel_PushTransform(GXChannel *self, Mtx mtx)
{
    HSD_JObj *jobj;
    HSD_PObj *pobj;
    HSD_DObj *dobj;
    PObjSetupFlag flags;
    Mtx pmtx;
    Mtx n;

    if (!self->bound) {
        return 0;
    }

    PSMTXCopy(mtx, self->jobj->mtx);
    HSD_JObjMakePositionMtx(self->jobj, self->view_mtx, pmtx);
    jobj = self->jobj;
    if (jobj->flags & JOBJ_SPECULAR) {
        HSD_LObjSetupSpecularInit(pmtx);
    }

    GXSetCurrentMtx(GX_PNMTX0);
    GXLoadPosMtxImm(pmtx, GX_PNMTX0);

    flags = SETUP_NONE;
    if (jobj->flags & JOBJ_LIGHTING) {
        flags = lbl_806D2FB4;
    }
    if (_HSD_TObjGetCurrentByType(0, TEX_COORD_REFLECTION)) {
        flags |= SETUP_NORMAL | SETUP_REFLECTION;
    }
    if (_HSD_TObjGetCurrentByType(0, TEX_COORD_HILIGHT)) {
        flags |= SETUP_NORMAL | SETUP_HIGHLIGHT;
    }

    if (flags & SETUP_NORMAL) {
        if (!PSMTXInvXpose(pmtx, n)) {
            PSMTXCopy(pmtx, n);
        }
        if (jobj->flags & JOBJ_LIGHTING) {
            GXLoadNrmMtxImm(n, GX_PNMTX0);
        }
        if (flags & SETUP_NORMAL_PROJECTION) {
            GXLoadTexMtxImm(n, GX_TEXMTX0, GX_MTX3x4);
        }
    }

    GXChannel_PushChannelColors(self->dobj->mobj->colors);

    for (dobj = self->dobj; dobj != 0; dobj = HSD_DObjGetNext(dobj)) {
        for (pobj = dobj->pobj; pobj != 0; pobj = pobj->next) {
            GXCallDisplayList(pobj->display, pobj->n_display << 5);
        }
    }
}
#pragma exceptions reset

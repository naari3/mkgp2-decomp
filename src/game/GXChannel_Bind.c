/* GXChannel_Bind @ 0x8007D834: make a GX channel current.
 *
 * Selects the channel's HSD JObj/DObj/MObj, sets up the material, loads the
 * vertex arrays and descriptors of the DObj's first PObj (the HSD pobj.c
 * setupArrayDesc/setupVtxDesc loops without the "previous list" cache) and
 * applies its cull mode.  Returns 0 when the channel is already bound.
 */
#include "game/GXChannelPrivate.h"

#pragma exceptions on
int GXChannel_Bind(GXChannel *self)
{
    HSD_VtxDescList *desc;
    HSD_PObj *pobj;

    if (self->bound == 1) {
        return 0;
    }

    self->view_mtx = HSD_CObjGetCurrent()->view_mtx;
    HSD_JObjSetCurrent(self->jobj);
    HSD_DObjSetCurrent(self->dobj);
    HSD_MObjSetCurrent(self->dobj->mobj);
    HSD_MObjSetup(self->dobj->mobj, self->arg);

    for (desc = self->dobj->pobj->verts; desc->attr != GX_VA_NULL; desc++) {
        if (desc->attr_type != GX_DIRECT) {
            GXSetArray(desc->attr, desc->vertex, desc->stride);
        }
    }

    pobj = self->dobj->pobj;
    GXClearVtxDesc();
    for (desc = pobj->verts; desc->attr != GX_VA_NULL; desc++) {
        GXSetVtxDesc(desc->attr, desc->attr_type);
        switch (desc->attr) {
        case GX_VA_PNMTXIDX:
        case GX_VA_TEX0MTXIDX:
        case GX_VA_TEX1MTXIDX:
        case GX_VA_TEX2MTXIDX:
        case GX_VA_TEX3MTXIDX:
        case GX_VA_TEX4MTXIDX:
        case GX_VA_TEX5MTXIDX:
        case GX_VA_TEX6MTXIDX:
        case GX_VA_TEX7MTXIDX:
            break;
        default:
            GXSetVtxAttrFmt(GX_VTXFMT0, desc->attr, desc->comp_cnt,
                            desc->comp_type, desc->frac);
        }
    }

    switch (self->dobj->pobj->flags & (POBJ_CULLFRONT | POBJ_CULLBACK)) {
    case 0:
        HSD_StateSetCullMode(GX_CULL_NONE);
        break;
    case POBJ_CULLFRONT:
        HSD_StateSetCullMode(GX_CULL_FRONT);
        break;
    case POBJ_CULLBACK:
        HSD_StateSetCullMode(GX_CULL_BACK);
        break;
    case POBJ_CULLFRONT | POBJ_CULLBACK:
        break;
    }

    self->bound = 1;
    return 1;
}
#pragma exceptions reset

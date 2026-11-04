#include "game/DrawSetup801F.h"

#pragma exceptions on
void fn_801F894C(DrawSetup801F *self) {
    const DrawTables801F *tables = &lbl_803BEDC0;
    GXSetNumTexGens(0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 255, 255, 4);
    GXSetTevOp(0, 4);
    GXClearVtxDesc();
    GXSetVtxDescv((const void *)(tables->colorDesc));
    if (self->depth) {
        GXSetVtxAttrFmtv(0, (const void *)(tables->colorDepthFmt));
    } else {
        GXSetVtxAttrFmtv(0, (const void *)(tables->colorFmt));
    }
}
#pragma exceptions reset

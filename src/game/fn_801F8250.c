#include "game/DrawSetup801F.h"

#pragma exceptions on
void fn_801F8250(DrawSetup801F *self) {
    const DrawTables801F *tables = &lbl_803BEDC0;
    int offset;
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    switch (self->mode) {
    case 1:
        GXSetTevColorIn(0,8,9,11,10);
        GXSetTevColorOp(0,0,0,0,1,0);
        break;
    case 2:
        GXSetTevColorIn(0,15,15,11,10);
        GXSetTevColorOp(0,0,0,0,1,0);
        GXSetTevAlphaIn(0,7,4,5,7);
        GXSetTevAlphaOp(0,0,0,0,1,0);
        break;
    default:
        GXSetTevOp(0,0);
        break;
    }
    GXSetTevOrder(0,0,7,4);
    GXClearVtxDesc();
    offset = 0;
    if (self->mode == 1 || self->mode == 2) offset = 4;
    GXSetVtxDescv(tables->mixedDesc);
    if (self->depth) {
        const DrawAttr801F *fmt = tables->mixedDepthFmt;
        fmt += offset;
        GXSetVtxAttrFmtv(0,fmt);
    } else {
        const DrawAttr801F *fmt = tables->mixedFmt;
        fmt += offset;
        GXSetVtxAttrFmtv(0,fmt);
    }
}
#pragma exceptions reset

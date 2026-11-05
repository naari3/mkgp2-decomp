#include "game/DrawSetup801F.h"

#pragma exceptions on
void fn_801F8668(DrawSetup801F *self) {
    const unsigned char *tables = (const unsigned char *)&lbl_803BEDC0;
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(0, 1, 4, 60, 0, 125);
    GXSetNumChans(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0, 7, 255);
    GXSetTevOp(0, 3);
    GXClearVtxDesc();
    GXSetVtxDescv((const void *)(tables + 0xA0));
    if (self->depth) {
        GXSetVtxAttrFmtv(0, (const void *)(tables + 0x100));
    } else {
        GXSetVtxAttrFmtv(0, (const void *)(tables + 0xC0));
    }
}
#pragma exceptions reset

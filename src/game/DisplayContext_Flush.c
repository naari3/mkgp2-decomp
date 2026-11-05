#include <game/DebugTextPrivate.h>

void DisplayContext_Flush(DebugDisplayContext *self)
{
    Mtx texture;
    Mtx position;
    Mtx44 projection;
    const unsigned char *palette = kDbgColorPalette;
    DebugFontHeader *font;
    int count;
    int i;

    if (self->count > 0) {
        GXGetCullMode(&self->cull);
        GXGetProjectionv(self->projection);
        GXGetViewportv(self->viewport);
        GXGetScissor(&self->scissor[0], &self->scissor[1], &self->scissor[2], &self->scissor[3]);
        font = self->font;
        GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
        C_MTXOrtho(projection, lbl_806DA278, lbl_806DA27C, lbl_806DA278,
                   lbl_806DA280, lbl_806DA278, lbl_806DA284);
        GXSetProjection(projection, 1);
        GXSetViewport(lbl_806DA278, lbl_806DA278, lbl_806DA280, lbl_806DA27C,
                      lbl_806DA278, lbl_806DA288);
        GXSetScissor(0, 0, 640, 480);
        PSMTXIdentity(position);
        GXLoadPosMtxImm(position, 0);
        GXSetCurrentMtx(0);
        PSMTXScale(texture, lbl_806DA288 / font->sheetWidth,
                   lbl_806DA288 / font->sheetHeight, lbl_806DA288);
        GXLoadTexMtxImm(texture, 30, 1);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(0, 1, 4, 30, 0, 125);
        GXSetCullMode(2);
        GXSetChanCtrl(4, 0, 1, 1, 1, 0, 2);
        GXSetZMode(0, 7, 0);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        GXSetTevOp(0, 0);
        GXSetTevOrder(0, 0, 7, 4);
        GXSetBlendMode(1, 4, 5, 0);
        GXClearVtxDesc();
        GXSetVtxDescv((const void *)(palette + 0x14));
        GXSetVtxAttrFmtv(0, (const void *)(palette + 0x34));
        GXSetArray(11, (void *)palette, 2);
        count = self->count;
        for (i = 0; i < count; i++) {
            TextRenderer_DrawEntry(self, &self->entries[i]);
        }
        GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
        GXSetScissor(self->scissor[0], self->scissor[1], self->scissor[2], self->scissor[3]);
        GXSetViewport(self->viewport[0], self->viewport[1], self->viewport[2],
                      self->viewport[3], self->viewport[4], self->viewport[5]);
        GXSetProjectionv(self->projection);
        GXSetCullMode(self->cull);
        self->count = 0;
    }
}

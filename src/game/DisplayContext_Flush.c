#include <game/DisplayContextFlushPrivate.h>

static const unsigned short sDebugColors[] = {
    0x000F, 0x00FF, 0x0F0F, 0x0FFF, 0xF00F, 0xF0FF, 0xFF0F, 0xFFFF, 0x888F
};
static const DebugVtxDesc sDebugVtxDesc[] = {
    {9, 1}, {11, 2}, {13, 1}, {255, 1}
};
static const DebugVtxFmt sDebugVtxFmt[] = {
    {9, 0, 3, 0}, {11, 1, 3, 0}, {13, 1, 3, 0}, {255, 1, 3, 0}
};

void DisplayContext_Flush(DebugDisplayContext *self)
{
    Mtx texture;
    Mtx position;
    Mtx44 projection;
    DebugFontHeader *font;
    int offset;
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
        GXSetVtxDescv(sDebugVtxDesc);
        GXSetVtxAttrFmtv(0, sDebugVtxFmt);
        GXSetArray(11, (void *)sDebugColors, 2);
        count = self->count;
        for (i = 0, offset = 0; i < count; offset += sizeof(DebugTextEntry), i++) {
            TextRenderer_DrawEntry(self, (DebugTextEntry *)((char *)self->entries + offset));
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

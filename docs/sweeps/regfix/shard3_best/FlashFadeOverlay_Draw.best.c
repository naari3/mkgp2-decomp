#pragma push
#pragma opt_propagation off
static inline float Add_f(float a, float b) { return a + b; }
void FlashFadeOverlay_Draw(struct FlashOverlay *self, float x0, float y0, float x1, float y1, float u, float v)
{
    struct FlashVectors *vectors = &lbl_8030E598;
    Mtx44 projection;
    Mtx view;
    GXTexObj texture;
    Vec eye, up, target;
    float v1, u1;
    float one, vm, vscale, um, uscale, yc, xc;
    if (GetVBlankFlag() && self->enabled) {
        GXSetZMode(0, 0, 0);
        GXSetZCompLoc(0);
        GXSetCullMode(2);
        C_MTXOrtho(projection, lbl_806D2E18, lbl_806D2E1C, lbl_806D2E20, lbl_806D2E24, lbl_806D2D74, lbl_806D2E28);
        GXSetProjection(projection, 1);
        GXSetViewport(lbl_806D2D70, lbl_806D2D70, lbl_806D2E2C, lbl_806D2E30, lbl_806D2D70, lbl_806D2D44);
        GXSetScissor(0, 0, 640, 480);
        eye = vectors->eye;
        if (!FlashFadeOverlay_Draw_bss_806D0F8C) {
            FlashFadeOverlay_Draw_bss_806D0F88 = lbl_806D2E34;
            FlashFadeOverlay_Draw_bss_806D0F8C = 1;
        }
        up = vectors->up;
        up.x = (float)cos((float)(lbl_806D2E38 * FlashFadeOverlay_Draw_bss_806D0F88));
        up.y = -(float)sin((float)(lbl_806D2E38 * FlashFadeOverlay_Draw_bss_806D0F88));
        target = vectors->target;
        C_MTXLookAt(view, &eye, &up, &target);
        GXLoadPosMtxImm(view, 0);
        GXInitTexObj(&texture, self->texture, 320, 240, 6, 0, 0, 0);
        GXLoadTexObj(&texture, 0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(0, 0, 4, 60, 0, 125);
        GXSetNumTevStages(1);
        GXSetTevOrder(0, 0, 0, 4);
        GXSetTevOp(0, 0);
        GXSetBlendMode(1, 4, 5, 15);
        GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2);
        GXSetNumChans(1);
        GXClearVtxDesc();
        GXSetVtxAttrFmt(0, 9, 0, 4, 0);
        GXSetVtxDesc(9, 1);
        GXSetVtxAttrFmt(0, 11, 1, 5, 0);
        GXSetVtxDesc(11, 1);
        GXSetVtxAttrFmt(0, 13, 1, 4, 0);
        GXSetVtxDesc(13, 1);
        u1 = Add_f(lbl_806D2E44, u);
        v1 = Add_f(lbl_806D2E4C, v);
        um = lbl_806D2E44 - u;
        vm = lbl_806D2E4C - v;
        uscale = lbl_806D2E40;
        vscale = lbl_806D2E48;
        v1 *= vscale;
        u1 *= uscale;
        xc = lbl_806D2E24;
        yc = lbl_806D2E18;
        one = lbl_806D2D44;
        x0 -= xc;
        y0 -= yc;
        x1 -= xc;
        y1 -= yc;
        u = uscale * um;
        v = vscale * vm;
        u1 = one - u1;
        v1 = one - v1;
        GXBegin(0x80, 0, 4);
        GXPosition2f32(x0, y0);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2f32(u, v);
        GXPosition2f32(x1, y0);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2f32(u1, v);
        GXPosition2f32(x1, y1);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2f32(u1, v1);
        GXPosition2f32(x0, y1);
        GXColor1u32(0xFFFFFFFF);
        GXTexCoord2f32(u, v1);
        GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
        HSD_StateInvalidate(0x7F);
    }
}
#pragma pop

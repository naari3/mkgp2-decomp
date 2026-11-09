#include <dolphin/gx.h>
#include <dolphin/mtx.h>
extern unsigned char GetVBlankFlag(void);
extern void HSD_StateInvalidate(unsigned int);
extern double cos(double), sin(double);
#include "game/FlashFadeOverlay_private.h"
extern signed char lbl_806D0F8C;
extern float lbl_806D0F88;
#pragma exceptions on
void FlashFadeOverlay_Draw(struct FlashOverlay *self, float x0, float y0, float x1, float y1, float u, float v)
{
    struct FlashVectors *vectors = &lbl_8030E598;
    Mtx44 projection;
    Mtx view;
    GXTexObj texture;
    Vec eye, up, target;
    float u0, v0, u1, v1, pu, pv;
    if (GetVBlankFlag() && self->enabled) {
        GXSetZMode(0, 0, 0);
        GXSetZCompLoc(0);
        GXSetCullMode(2);
        C_MTXOrtho(projection, 240.0f, -240.0f, -320.0f, 320.0f, 100.0f, 1000.0f);
        GXSetProjection(projection, 1);
        GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
        GXSetScissor(0, 0, 640, 480);
        eye = vectors->eye;
        if (!lbl_806D0F8C) {
            lbl_806D0F88 = 90.0f;
            lbl_806D0F8C = 1;
        }
        up = vectors->up;
        up.x = (float)cos((float)(0.017453292519943295 * lbl_806D0F88));
        up.y = -(float)sin((float)(0.017453292519943295 * lbl_806D0F88));
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
        x0 -= 320.0f;
        y0 -= 240.0f;
        x1 -= 320.0f;
        y1 -= 240.0f;
        u0 = 0.003125f * (16.0f - u);
        v0 = (1.0f / 240.0f) * (12.0f - v);
        pu = 0.003125f * (16.0f + u);
        pv = (1.0f / 240.0f) * (12.0f + v);
        u1 = 1.0f - pu;
        v1 = 1.0f - pv;
        GXBegin(0x80, 0, 4);
        GXPosition2f32(x0, y0); GXColor1u32(0xFFFFFFFF); GXTexCoord2f32(u0, v0);
        GXPosition2f32(x1, y0); GXColor1u32(0xFFFFFFFF); GXTexCoord2f32(u1, v0);
        GXPosition2f32(x1, y1); GXColor1u32(0xFFFFFFFF); GXTexCoord2f32(u1, v1);
        GXPosition2f32(x0, y1); GXColor1u32(0xFFFFFFFF); GXTexCoord2f32(u0, v1);
        GXSetChanCtrl(4, 1, 1, 1, 1, 2, 2);
        HSD_StateInvalidate(0x7F);
    }
}
#pragma exceptions reset

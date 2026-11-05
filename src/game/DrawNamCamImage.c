#include <dolphin/gx.h>
#include <dolphin/mtx.h>
extern double tan(double);
extern void HSD_StateInvalidate(unsigned int);
extern const GXColor lbl_806D2F80;
extern const float lbl_806D2F84, lbl_806D2F88, lbl_806D2F8C, lbl_806D2F90;
extern const float lbl_806D2F94, lbl_806D2F98, lbl_806D2F9C;
#define PIPE (*(volatile float *)0xCC008000)

void DrawNamCamImage(void *dst, void *src, unsigned short width, unsigned short height,
                     int format, unsigned short left, unsigned short top, unsigned short right,
                     unsigned short bottom, unsigned short outWidth, unsigned short outHeight, int outFormat) {
    Mtx44 projection;
    Mtx model;
    GXTexObj texture;
    GXColor color;
    float y, x, s0, t0, s1, t1, aspect;
    unsigned int bytes = GXGetTexBufferSize(outWidth, outHeight, outFormat, 0, 0);
    if (!bytes) return;
    DCFlushRange(dst, bytes);
    aspect = (float)outWidth / (float)outHeight;
    color = lbl_806D2F80;
    GXSetViewport(lbl_806D2F84, lbl_806D2F84, (float)outWidth, (float)outHeight, lbl_806D2F84, lbl_806D2F88);
    GXSetScissor(0, 0, outWidth, outHeight);
    C_MTXPerspective(projection, lbl_806D2F8C, aspect, lbl_806D2F90, lbl_806D2F94);
    GXSetProjection(projection, 0);
    y = (float)tan(lbl_806D2F98);
    x = y * aspect;
    s0 = (float)left / (float)(width - 1);
    s1 = (float)right / (float)(width - 1);
    t0 = (float)top / (float)(height - 1);
    t1 = (float)bottom / (float)(height - 1);
    GXInitTexObj(&texture, src, width, height, format, 0, 0, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetVtxDesc(13, 1);
    GXSetVtxAttrFmt(0, 13, 1, 4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetChanMatColor(4, color);
    GXSetNumTexGens(1);
    GXSetNumTevStages(1);
    GXLoadTexObj(&texture, 0);
    GXSetTevOp(0, 1);
    GXSetTevOrder(0, 0, 0, 4);
    GXSetZMode(0, 7, 0);
    GXSetAlphaUpdate(0);
    GXSetBlendMode(1, 4, 5, 0);
    PSMTXScale(model, lbl_806D2F88, lbl_806D2F88, lbl_806D2F88);
    GXLoadPosMtxImm(model, 0);
    GXBegin(0x80, 0, 4);
    {
        float z, negX, negY;
        negX = -x; z = lbl_806D2F9C; negY = -y;
        PIPE = negX; PIPE = y; PIPE = z; PIPE = s0; PIPE = t0;
        PIPE = x; PIPE = y; PIPE = z; PIPE = s1; PIPE = t0;
        PIPE = x; PIPE = negY; PIPE = z; PIPE = s1; PIPE = t1;
        PIPE = negX; PIPE = negY; PIPE = z; PIPE = s0; PIPE = t1;
    }
    GXDrawDone();
    GXSetTexCopySrc(0, 0, outWidth, outHeight);
    GXSetTexCopyDst(outWidth, outHeight, outFormat, 0);
    GXCopyTex(dst, 0);
    GXPixModeSync();
    GXClearBoundingBox();
    HSD_StateInvalidate(-1);
}

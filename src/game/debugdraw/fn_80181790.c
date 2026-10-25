typedef struct GXColor {
    unsigned char r, g, b, a;
} GXColor;

typedef union WGPipe {
    unsigned char u8;
    float f32;
} WGPipe;

#define GXFIFO (*(volatile WGPipe *)0xCC008000)

extern GXColor lbl_806DCF54;
extern const float lbl_806D9260;
extern const float lbl_806D9264;
extern const float lbl_806D9268;

extern void Scene3D_GetCameraPos(void *scene, float *fov, float *aspect);
extern double tan(double);
extern void GXClearVtxDesc(void);
extern void GXSetVtxDesc(int attr, int type);
extern void GXSetVtxAttrFmt(int fmt, int attr, int cnt, int type, int frac);
extern void GXSetNumChans(int n);
extern void GXSetChanCtrl(int chan, int enable, int amb, int mat, int lights, int diff, int attn);
extern void GXSetChanMatColor(int chan, GXColor color);
extern void GXSetNumTexGens(int n);
extern void GXSetNumTevStages(int n);
extern void GXSetTevOrder(int stage, int coord, int map, int color);
extern void GXSetTevOp(int stage, int mode);
extern void GXSetZMode(int enable, int func, int update);
extern void GXSetBlendMode(int type, int src, int dst, int op);
extern void PSMTXScale(float m[3][4], float x, float y, float z);
extern void GXSetCurrentMtx(int id);
extern void GXLoadPosMtxImm(float m[3][4], int id);
extern void GXBegin(int prim, int fmt, int n);
extern void HSD_StateInvalidate(int mask);

void fn_80181790(void *scene, unsigned char r, unsigned char g, unsigned char b, unsigned char a,
                 float depth, unsigned char additive) {
    float mtx[3][4];
    float fov;
    float aspect;
    GXColor color;
    float w;
    float h;

    if (scene == 0) {
        return;
    }
    color = lbl_806DCF54;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    Scene3D_GetCameraPos(scene, &fov, &aspect);
    h = depth * (float)tan(lbl_806D9260 * (lbl_806D9264 * fov));
    w = h * aspect;
    GXClearVtxDesc();
    GXSetVtxDesc(9, 1);
    GXSetVtxAttrFmt(0, 9, 1, 4, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(4, 0, 0, 0, 0, 0, 2);
    GXSetChanMatColor(4, color);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(0, 0xff, 0xff, 4);
    GXSetTevOp(0, 4);
    GXSetZMode(0, 7, 0);
    if (additive) {
        GXSetBlendMode(1, 4, 1, 0);
    } else {
        GXSetBlendMode(1, 4, 5, 0);
    }
    PSMTXScale(mtx, lbl_806D9268, lbl_806D9268, lbl_806D9268);
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(mtx, 0);
    GXBegin(0x80, 0, 4);
    {
        float nd = -depth;
        float nw = -w;
        float nh = -h;
        GXFIFO.f32 = nw;
        GXFIFO.f32 = h;
        GXFIFO.f32 = nd;
        GXFIFO.f32 = w;
        GXFIFO.f32 = h;
        GXFIFO.f32 = nd;
        GXFIFO.f32 = w;
        GXFIFO.f32 = nh;
        GXFIFO.f32 = nd;
        GXFIFO.f32 = nw;
        GXFIFO.f32 = nh;
        GXFIFO.f32 = nd;
    }
    HSD_StateInvalidate(0x7e);
}

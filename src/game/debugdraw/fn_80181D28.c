typedef struct GXColor {
    unsigned char r, g, b, a;
} GXColor;

typedef union WGPipe {
    unsigned char u8;
    float f32;
} WGPipe;

#define GXFIFO (*(volatile WGPipe *)0xCC008000)

extern GXColor lbl_806DCF48;
typedef struct Vec3f {
    float x, y, z;
} Vec3f;

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
extern void *HSD_CObjGetCurrent(void);
extern float (*HSD_CObjGetViewingMtxPtr(void *cobj))[4];

static inline void GXPosition3f32(float x, float y, float z) {
    GXFIFO.f32 = x;
    GXFIFO.f32 = y;
    GXFIFO.f32 = z;
}


void fn_80181D28(Vec3f *p0, unsigned char r, unsigned char g, unsigned char b,
                  unsigned char a, unsigned char zalways) {
    GXColor color;
    void *cobj;

    if (p0 == 0) {
        return;
    }
    color = lbl_806DCF48;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
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
    if (zalways) {
        GXSetZMode(1, 7, 1);
    } else {
        GXSetZMode(1, 3, 1);
    }
    GXSetBlendMode(1, 4, 5, 0);
    cobj = HSD_CObjGetCurrent();
    if (cobj == 0) {
        return;
    }
    GXSetCurrentMtx(0);
    GXLoadPosMtxImm(HSD_CObjGetViewingMtxPtr(cobj), 0);
    GXBegin(0xb8, 0, 1);
    GXPosition3f32(p0->x, p0->y, p0->z);
    HSD_StateInvalidate(0x7e);
}

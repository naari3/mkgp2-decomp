/* Native work in progress for the indivisible 8007E4CC..800806D4 group.
 * All methods use native C++; the group remains NonMatching pending exact EH and code generation. */
#include "game/TransitionEffectPrivate.h"

void operator delete(void *) throw();
extern "C" void Object_DtorWithGXSync(void *, int);
extern "C" void *lbl_803FE3C0[];
extern "C" const float lbl_806D2FD0, lbl_806D2FDC, lbl_806D3054, lbl_806D3058;
extern "C" {
unsigned long OSGetTick();
void Profiler_RecordFrame(int, float);
extern const float lbl_806D2FD4, lbl_806D2FD8, lbl_806D2FE0, lbl_806D2FE4;
extern const float lbl_806D2FE8, lbl_806D2FEC, lbl_806D2FF0, lbl_806D2FF4;
}

class ScopedTimer {
    unsigned int start;
    int slot;
public:
    ScopedTimer(int id) { slot = id; start = OSGetTick(); }
    ~ScopedTimer() {
        Profiler_RecordFrame(slot, (float)(((OSGetTick() - start) << 3) /
            ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / lbl_806D2FF4);
    }
};

extern "C" void TransitionEffect_Tick(TransitionEffectView *self)
{
    ScopedTimer timer(0x2B);
    unsigned char fadeActive;
    TransitionFade *fade = self->fade;
    if (fade->delay <= lbl_806D2FD0 && fade->remaining <= lbl_806D2FD0) {
        fadeActive = 0;
    } else {
        fade->delay -= lbl_806D2FD4;
        if (fade->delay <= lbl_806D2FD0) {
            fade->delay = lbl_806D2FD0;
            fade->remaining -= lbl_806D2FD4;
            if (fade->remaining <= lbl_806D2FD0) fade->remaining = lbl_806D2FD0;
        }
        fadeActive = 1;
    }
    TransitionIris *iris = self->iris;
    unsigned char irisActive;
    if (iris->remaining <= lbl_806D2FD0) irisActive = 0;
    else {
        iris->remaining -= iris->step;
        if (iris->closing == 1) {
            iris->radius = lbl_806D2FD8 * (lbl_806D2FDC - iris->remaining);
            iris->alpha = (unsigned int)(lbl_806D2FE0 * iris->remaining);
        } else {
            iris->radius = lbl_806D2FD8 * iris->remaining;
            iris->alpha = (unsigned int)(lbl_806D2FE0 * (lbl_806D2FDC - iris->remaining));
            if (iris->remaining <= lbl_806D2FD0) {
                iris->closing = 1;
                iris->remaining = lbl_806D2FDC;
            }
        }
        irisActive = 1;
    }
    TransitionFlash *flash = self->flash;
    unsigned int flashActive;
    flash->remaining -= lbl_806D2FD4;
    if (flash->remaining <= lbl_806D2FD0) {
        flashActive = 0;
        flash->active = flashActive;
        flash->remaining = lbl_806D2FD0;
    } else {
        float alpha = lbl_806D2FE4 * flash->remaining;
        if (alpha > lbl_806D2FE4) alpha = lbl_806D2FE4;
        flashActive = 1;
        flash->r = lbl_806D2FDC;
        flash->g = lbl_806D2FDC;
        flash->b = lbl_806D2FDC;
        flash->alpha = alpha;
        flash->active = flashActive;
    }
    float *shake = self->shake;
    unsigned char shakeActive;
    if (*shake <= lbl_806D2FD0) shakeActive = 0;
    else { *shake -= lbl_806D2FD4; shakeActive = 1; }
    TransitionRoulette *roulette = self->roulette;
    unsigned char quadActive = self->quad->active;
    unsigned char rouletteActive;
    if (roulette->remaining <= lbl_806D2FD0) rouletteActive = 0;
    else {
        roulette->remaining -= lbl_806D2FD4;
        if (roulette->remaining > lbl_806D2FDC) {
            roulette->fade += lbl_806D2FE8;
            if (roulette->fade > lbl_806D2FDC) roulette->fade = lbl_806D2FDC;
        } else {
            roulette->fade -= lbl_806D2FE8;
            if (roulette->fade < lbl_806D2FD0) roulette->fade = lbl_806D2FD0;
        }
        if (roulette->fade >= lbl_806D2FDC) roulette->speed += lbl_806D2FEC;
        if (roulette->speed > lbl_806D2FE8) roulette->speed = lbl_806D2FE8;
        roulette->elapsed += lbl_806D2FD4;
        switch (roulette->phase) {
        case 0:
            if (roulette->elapsed > lbl_806D2FDC) {
                ++roulette->phase;
                roulette->elapsed = lbl_806D2FD0;
                roulette->active = 0;
            }
            break;
        case 1:
            if (roulette->elapsed > lbl_806D2FF0) {
                ++roulette->phase;
                roulette->elapsed = lbl_806D2FD0;
            }
            break;
        }
        rouletteActive = 1;
    }
    if (!fadeActive && !irisActive && !shakeActive && !(unsigned char)flashActive && !quadActive && !rouletteActive)
        self->mode = 0;
}

extern "C" {
void *Alloc(unsigned long);
void clNormal3D_Construct(void *, const char *, int);
void Object_JObjUpdate_870(void *, int);
void Object_SetByte48(void *, int);
void fn_801F6804(void *);
extern TransitionEffectView *lbl_806D109C;
extern void *lbl_803FE37C[];
extern const char lbl_80311DA4[];
}
void *operator new(unsigned long);

struct TransitionFadeInit : TransitionFade {
    TransitionFadeInit() { delay = lbl_806D2FD0; remaining = lbl_806D2FD0; }
};
struct TransitionIrisInit : TransitionIris {
    TransitionIrisInit() { remaining = lbl_806D2FD0; step = lbl_806D2FD0; closing = 1; }
};
struct TransitionShakeInit {
    float remaining;
    TransitionShakeInit() { remaining = lbl_806D2FD0; }
};
struct TransitionFlashInit : TransitionFlash {
    TransitionFlashInit() { remaining = lbl_806D2FD0; active = 0; }
};
struct TransitionQuadInit : TransitionQuad {
    TransitionQuadInit() { active = 0; }
};
struct TransitionModelInit {
    unsigned char opaque[0x5C];
    TransitionModelInit() { clNormal3D_Construct(this, lbl_80311DA4, 1); }
};
struct TransitionRouletteInit : TransitionRoulette {
    TransitionRouletteInit() {
        holder.object = new TransitionModelInit;
        Object_JObjUpdate_870(holder.object, 0x200);
        Object_SetByte48(holder.object, 1);
        remaining = lbl_806D2FD0;
    }
};
/* A constructor keeps allocation failure cleanups native. The owner views
 * above describe the same pointer layout without imposing shared headers. */
template <class T> struct TransitionOwner {
    T *p;
    TransitionOwner() : p(new T) {}
    ~TransitionOwner() { delete p; }
};
struct TransitionInitBase {
    void **vtable;
    TransitionInitBase(void **derivedVtable) {
        vtable = lbl_803FE3C0;
        lbl_806D109C = (TransitionEffectView *)this;
        vtable = derivedVtable;
    }
    ~TransitionInitBase() { vtable = lbl_803FE3C0; }
};
struct TransitionEffectInit : TransitionInitBase {
    TransitionOwner<TransitionFadeInit> fade;
    TransitionOwner<TransitionIrisInit> iris;
    TransitionOwner<TransitionShakeInit> shake;
    TransitionOwner<TransitionFlashInit> flash;
    TransitionOwner<TransitionQuadInit> quad;
    TransitionOwner<TransitionRouletteInit> roulette;
    int mode;
    float duration;
    unsigned char active;
    unsigned char emptyMember;
    unsigned char align[2];
    unsigned char renderState[0x4C];
    TransitionEffectInit() :
        TransitionInitBase(lbl_803FE37C) {
        fn_801F6804(renderState);
        mode = 0;
        duration = lbl_806D2FD0;
    }
};
extern "C" TransitionEffectView *TransitionEffect_GetOrCreate()
{
    if ((lbl_806D109C ? lbl_806D109C : 0) == 0) new TransitionEffectInit;
    return lbl_806D109C ? lbl_806D109C : 0;
}

/* GX setup shared by the screen-space effects. */
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
extern "C" {
double cos(double);
double sin(double);
extern const float lbl_806D3000, lbl_806D3004, lbl_806D3008, lbl_806D300C;
extern const float lbl_806D3010, lbl_806D3014, lbl_806D3018, lbl_806D301C;
extern const float lbl_806D3028, lbl_806D3038, lbl_806D303C, lbl_806D3040;
extern const float lbl_806D3044, lbl_806D3048, lbl_806D304C, lbl_806D3050;
extern const double lbl_806D3020, lbl_806D3030;
extern const Vec lbl_80311CA0[];
extern float lbl_806D1170;
extern signed char lbl_806D1174;
void *GetCourseScene3D();
float (*CObj_GetProjMatrix_Cached(void *))[4];
void Object_SetJObjPositionXYZ(void *, float, float, float);
void Object_SetJObjScaleXYZ(void *, float, float, float);
void Object_SetColorRGBA(void *, int, float, float, float, float);
void JObjTree_TranslateAndMul(void *, int, float, float);
void Object_RenderJObjTree(void *, int);
GXTexObj *BackupBuffer_InitAsTexture();
float Saturate_Double(float, float, float);
}
struct TransitionTextureVertex { float x, y, u, v; unsigned int color; };
extern "C" const TransitionTextureVertex lbl_803FE230[16];

static inline void ScreenProjection(Mtx44 projection)
{
    C_MTXOrtho(projection, lbl_806D3000, lbl_806D3004, lbl_806D3008,
               lbl_806D300C, lbl_806D3010, lbl_806D3014);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetViewport(lbl_806D2FD0, lbl_806D2FD0, lbl_806D3018, lbl_806D2FD8,
                  lbl_806D2FD0, lbl_806D2FDC);
    GXSetScissor(0, 0, 640, 480);
}
static inline void ScreenCamera(Mtx view, const Vec *camera, int index, double angle)
{
    Vec eye = camera[index];
    Vec up = camera[index + 1];
    up.x = (float)cos(angle);
    up.y = -(float)sin(angle);
    Vec target = camera[index + 2];
    C_MTXLookAt(view, &eye, &up, &target);
    GXLoadPosMtxImm(view, 0);
}
static inline void ScreenVertexFormat(bool textured)
{
    GXClearVtxDesc();
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    if (textured) {
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    }
}
static inline void ScreenColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    *(volatile unsigned char *)0xCC008000 = r;
    *(volatile unsigned char *)0xCC008000 = g;
    *(volatile unsigned char *)0xCC008000 = b;
    *(volatile unsigned char *)0xCC008000 = a;
}
static inline void ScreenPosition(float x, float y)
{
    *(volatile float *)0xCC008000 = x;
    *(volatile float *)0xCC008000 = y;
}
static inline void RestoreScreenChannel()
{
    GXSetChanCtrl(GX_COLOR0A0, GX_ENABLE, GX_SRC_VTX, GX_SRC_VTX,
                  GX_LIGHT0, GX_DF_CLAMP, GX_AF_NONE);
}
extern "C" void TransitionEffect_DrawCarRouletteAndQuad(TransitionRoulette *self, float fade, float angle);

extern "C" {
void fn_801F6588(int);
void fn_801F6790(void *);
void HSD_StateInvalidate(unsigned long);
extern float lbl_806D1160, lbl_806D1168;
extern signed char lbl_806D1164, lbl_806D116C;
extern TransitionTextureVertex lbl_803FE0F0[16];
}
extern "C" void TransitionEffect_DrawCarRouletteOverlay(TransitionRoulette *);

static inline void ScreenFlatMaterial(GXBlendFactor dst)
{
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, dst, GX_LO_SET);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
}
static inline void ScreenTexturedMaterial()
{
    GXLoadTexObj(BackupBuffer_InitAsTexture(), GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
}
static inline void ScreenFlatQuad(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    ScreenPosition(lbl_806D3008, lbl_806D3004); ScreenColor(r,g,b,a);
    ScreenPosition(lbl_806D300C, lbl_806D3004); ScreenColor(r,g,b,a);
    ScreenPosition(lbl_806D300C, lbl_806D3000); ScreenColor(r,g,b,a);
    ScreenPosition(lbl_806D3008, lbl_806D3000); ScreenColor(r,g,b,a);
}
static inline void ScreenTableQuad()
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 16);
    TransitionTextureVertex *v = lbl_803FE0F0;
    for (int i = 0; i < 16; ++i) {
        ScreenPosition((v[0].x - lbl_806D300C) + lbl_806D2FD0,
                       (v[0].y - lbl_806D3000) + lbl_806D2FD0);
        *(volatile unsigned int *)0xCC008000 = v[0].color;
        ScreenPosition(lbl_806D303C * v[0].u, lbl_806D3038 * v[0].v);
        ++v;
    }
}
static inline void ScreenRotatedCamera(Mtx view, const Vec *camera, int index, float *angle, signed char *initialized)
{
    Vec eye = camera[index];
    if (!*initialized) { *initialized = 1; *angle = lbl_806D301C; }
    Vec up = camera[index + 1];
    up.x = (float)cos((float)(lbl_806D3020 * *angle));
    up.y = -(float)sin((float)(lbl_806D3020 * *angle));
    Vec target = camera[index + 2];
    C_MTXLookAt(view, &eye, &up, &target);
    GXLoadPosMtxImm(view, 0);
}
extern "C" void TransitionEffect_RenderPass(TransitionEffectView *self, int pass)
{
    const Vec *camera = lbl_80311CA0;
    ScopedTimer timer(0x2C);
    if (self->mode != pass) return;
    if (self->mode != 3) {
        fn_801F6804(self->rest + 3);
        fn_801F6588(0);
    }
    switch (pass) {
    case 0: break;
    case 1: {
        TransitionFade *p = self->fade;
        if (p->delay <= lbl_806D2FD0 && p->remaining <= lbl_806D2FD0) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        Mtx view;
        Mtx44 projection;
        ScreenProjection(projection);
        ScreenRotatedCamera(view, camera, 3, &lbl_806D1160, &lbl_806D1164);
        GXLoadTexObj(BackupBuffer_InitAsTexture(), GX_TEXMAP0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        ScreenVertexFormat(true);
        unsigned int a = (int)Saturate_Double(lbl_806D3028 * p->remaining, lbl_806D2FD0, lbl_806D3028);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        ScreenPosition(lbl_806D3008, lbl_806D3004); ScreenColor(255,255,255,a);
        ScreenPosition(lbl_806D2FD0, lbl_806D2FD0);
        ScreenPosition(lbl_806D300C, lbl_806D3004); ScreenColor(255,255,255,a);
        ScreenPosition(lbl_806D2FDC, lbl_806D2FD0);
        ScreenPosition(lbl_806D300C, lbl_806D3000); ScreenColor(255,255,255,a);
        ScreenPosition(lbl_806D2FDC, lbl_806D2FDC);
        ScreenPosition(lbl_806D3008, lbl_806D3000); ScreenColor(255,255,255,a);
        ScreenPosition(lbl_806D2FD0, lbl_806D2FDC);
        RestoreScreenChannel();
        break;
    }
    case 2: {
        TransitionIris *p = self->iris;
        if (p->remaining <= lbl_806D2FD0 && p->closing == 1) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        Mtx view;
        Mtx44 projection;
        ScreenProjection(projection);
        ScreenCamera(view, camera, 0, lbl_806D3030);
        ScreenFlatMaterial(GX_BL_INVSRCALPHA);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        ScreenPosition(lbl_806D3008, lbl_806D3004);
        *(volatile unsigned int *)0xCC008000 = 255;
        ScreenPosition(lbl_806D300C, lbl_806D3004);
        *(volatile unsigned int *)0xCC008000 = 255;
        ScreenPosition(lbl_806D300C, lbl_806D3000 - p->radius);
        *(volatile unsigned int *)0xCC008000 = 0;
        ScreenPosition(lbl_806D3008, lbl_806D3000 - p->radius);
        *(volatile unsigned int *)0xCC008000 = 0;
        RestoreScreenChannel();
        break;
    }
    case 3: {
        TransitionFlash *p = self->flash;
        if (!p->active) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        Mtx view;
        Mtx44 projection;
        ScreenProjection(projection);
        ScreenCamera(view, camera, 9, lbl_806D3030);
        ScreenFlatMaterial(GX_BL_INVSRCALPHA);
        unsigned int r = (int)Saturate_Double(lbl_806D2FE0 * p->r, lbl_806D2FD0, lbl_806D2FE0);
        unsigned int g = (int)Saturate_Double(lbl_806D2FE0 * p->g, lbl_806D2FD0, lbl_806D2FE0);
        unsigned int b = (int)Saturate_Double(lbl_806D2FE0 * p->b, lbl_806D2FD0, lbl_806D2FE0);
        unsigned int a = (int)Saturate_Double(lbl_806D2FE0 * p->alpha, lbl_806D2FD0, lbl_806D2FE0);
        ScreenFlatQuad(r,g,b,a);
        RestoreScreenChannel();
        break;
    }
    case 4: {
        if (*self->shake <= lbl_806D2FD0) break;
        GXSetZMode(GX_DISABLE, GX_NEVER, GX_DISABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetCullMode(GX_CULL_BACK);
        Mtx view;
        Mtx44 projection;
        ScreenProjection(projection);
        ScreenRotatedCamera(view, camera, 6, &lbl_806D1168, &lbl_806D116C);
        ScreenTexturedMaterial();
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(1);
        ScreenVertexFormat(true);
        ScreenTableQuad();
        RestoreScreenChannel();
        break;
    }
    case 5: {
        TransitionQuad *p = self->quad;
        if (!p->active) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        Mtx view;
        Mtx44 projection;
        ScreenProjection(projection);
        ScreenCamera(view, camera, 9, lbl_806D3030);
        ScreenFlatMaterial(GX_BL_INVSRCALPHA);
        unsigned int r = (int)Saturate_Double(lbl_806D2FE0 * p->r, lbl_806D2FD0, lbl_806D2FE0);
        unsigned int g = (int)Saturate_Double(lbl_806D2FE0 * p->g, lbl_806D2FD0, lbl_806D2FE0);
        unsigned int b = (int)Saturate_Double(lbl_806D2FE0 * p->b, lbl_806D2FD0, lbl_806D2FE0);
        unsigned int a = (int)Saturate_Double(lbl_806D2FE0 * p->alpha, lbl_806D2FD0, lbl_806D2FE0);
        ScreenFlatQuad(r,g,b,a);
        RestoreScreenChannel();
        break;
    }
    case 6: TransitionEffect_DrawCarRouletteOverlay(self->roulette); break;
    }
    if (self->mode != 3) {
        HSD_StateInvalidate(-1);
        GXSetZMode(GX_ENABLE, GX_LEQUAL, GX_ENABLE);
        fn_801F6790(self->rest + 3);
    }
}

extern "C" void TransitionEffect_DrawCarRouletteOverlay(TransitionRoulette *self)
{
    const Vec *camera = lbl_80311CA0;
    if (self->remaining <= lbl_806D2FD0) return;
    TransitionEffect_DrawCarRouletteAndQuad(self, self->fade, self->speed);
    if (self->active != 1) return;
    GXSetZMode(GX_DISABLE, GX_NEVER, GX_DISABLE);
    GXSetZCompLoc(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    Mtx44 projection;
    ScreenProjection(projection);
    Mtx view;
    ScreenRotatedCamera(view, camera, 15, &lbl_806D1170, &lbl_806D1174);
    GXLoadTexObj(BackupBuffer_InitAsTexture(), GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    ScreenVertexFormat(true);
    GXBegin(GX_QUADS, GX_VTXFMT0, 16);
    const TransitionTextureVertex *v = lbl_803FE230;
    for (int i = 0; i < 16; ++i) {
        ScreenPosition((v[0].x - lbl_806D300C) + lbl_806D2FD0,
                       (v[0].y - lbl_806D3000) + lbl_806D2FD0);
        *(volatile unsigned int *)0xCC008000 = v[0].color;
        ScreenPosition(lbl_806D303C * v[0].u, lbl_806D3038 * v[0].v);
        ++v;
    }
    RestoreScreenChannel();
}

extern "C" void TransitionEffect_DrawCarRouletteAndQuad(TransitionRoulette *self, float fade, float angle)
{
    const Vec *camera = lbl_80311CA0;
    MtxPtr matrix = CObj_GetProjMatrix_Cached(GetCourseScene3D());
    Vec position;
    position.x = lbl_806D2FD0;
    position.y = lbl_806D2FD0;
    position.z = lbl_806D3040 * fade + lbl_806D3044 * (lbl_806D2FDC - fade);
    PSMTXMultVec(matrix, &position, &position);
    Object_SetJObjPositionXYZ(self->holder.object, position.x, position.y, position.z);
    Object_SetJObjScaleXYZ(self->holder.object, lbl_806D3048, lbl_806D3048, lbl_806D3048);
    Object_SetColorRGBA(self->holder.object, 0, fade, fade, fade, fade);
    JObjTree_TranslateAndMul(self->holder.object, 0, lbl_806D2FD0, angle);
    Object_RenderJObjTree(self->holder.object, 7);
    float c;
    float alpha = lbl_806D304C * self->fade;
    GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
    GXSetZCompLoc(GX_FALSE);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_BACK);
    Mtx44 projection;
    ScreenProjection(projection);
    Mtx view;
    ScreenCamera(view, camera, 12, lbl_806D3030);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_SET);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    unsigned int a, b, g, r;
    r = (int)Saturate_Double(lbl_806D2FD0, lbl_806D2FD0, lbl_806D2FE0);
    c = lbl_806D2FE0 * alpha;
    g = (int)Saturate_Double(c, lbl_806D2FD0, lbl_806D2FE0);
    b = (int)Saturate_Double(c, lbl_806D2FD0, lbl_806D2FE0);
    a = (int)Saturate_Double(lbl_806D2FE0 * (lbl_806D3050 * alpha), lbl_806D2FD0, lbl_806D2FE0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    ScreenPosition(lbl_806D3008, lbl_806D3004); ScreenColor(r,g,b,a);
    ScreenPosition(lbl_806D300C, lbl_806D3004); ScreenColor(r,g,b,a);
    ScreenPosition(lbl_806D300C, lbl_806D3000); ScreenColor(r,g,b,a);
    ScreenPosition(lbl_806D3008, lbl_806D3000); ScreenColor(r,g,b,a);
    RestoreScreenChannel();
}

extern "C" int ShadowBillboard_SetEffectParams(TransitionEffectView *self, int mode,
                                               float x, float y, float w, float h)
{
    switch (mode) {
    case 0: break;
    case 1: case 2: case 3: case 4: case 6: return 0;
    case 5: {
        TransitionQuad *p = self->quad;
        p->r = x;
        p->g = y;
        p->b = w;
        p->alpha = h;
        p->active = 1;
        break;
    }
    }
    self->mode = mode;
    self->duration = lbl_806D2FD0;
    self->active = 1;
    return 1;
}

extern "C" int CameraEffect_Apply(TransitionEffectView *self, int mode, float duration)
{
    switch (mode) {
    case 0: break;
    case 1: {
        TransitionFade *p = self->fade;
        p->delay = duration;
        p->remaining = lbl_806D2FDC;
        break;
    }
    case 2: {
        TransitionIris *p = self->iris;
        p->closing = 0;
        p->remaining = lbl_806D2FDC;
        p->step = lbl_806D2FDC / (lbl_806D3054 * duration);
        break;
    }
    case 3: self->flash->remaining = duration; break;
    case 4: *self->shake = duration; break;
    case 5: return 0;
    case 6: {
        TransitionRoulette *p = self->roulette;
        if (p->remaining > lbl_806D2FD0) {
            p->remaining = duration;
        } else {
            p->remaining = duration;
            p->speed = lbl_806D3058;
            p->fade = lbl_806D2FD0;
            p->elapsed = lbl_806D2FD0;
            p->phase = 0;
            p->active = 1;
        }
        break;
    }
    }
    self->mode = mode;
    self->duration = duration;
    self->active = 1;
    return 1;
}

extern "C" void *dtor_80080330(void *self, short flag)
{
    if (self && flag > 0) operator delete(self);
    return self;
}
extern "C" void *dtor_8008036C(void *self, short flag)
{
    if (self && flag > 0) operator delete(self);
    return self;
}

inline TransitionOverlayObject::~TransitionOverlayObject() throw()
{
    Object_DtorWithGXSync(object, 1);
}

extern "C" TransitionOverlayObject **dtor_800803A8(TransitionOverlayObject **self, short flag)
{
    if (self) {
        TransitionOverlayObject *p = *self;
        if (p) {
            p->~TransitionOverlayObject();
            operator delete(p);
        }
        if (flag > 0) operator delete(self);
    }
    return self;
}
extern "C" TransitionOverlayObject *dtor_80080444(TransitionOverlayObject *self, short flag) throw()
{
    if (self) {
        Object_DtorWithGXSync(self->object, 1);
        if (flag > 0) operator delete(self);
    }
    return self;
}

#define BUFFER_DTOR(name) \
extern "C" void **name(void **self, short flag) { \
    if (self) { if (*self) operator delete(*self); \
        if (flag > 0) operator delete(self); } return self; }
BUFFER_DTOR(dtor_800804C0)
BUFFER_DTOR(dtor_8008051C)
BUFFER_DTOR(dtor_80080578)
BUFFER_DTOR(dtor_800805D4)
BUFFER_DTOR(dtor_80080630)

extern "C" void *dtor_8008068C(TransitionEffectView *self, short flag)
{
    if (self) {
        self->vtable = lbl_803FE3C0;
        if (flag > 0) operator delete(self);
    }
    return self;
}

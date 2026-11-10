/* Native work in progress for the indivisible 8007E4CC..800806D4 group.
 * All owned EH and data match; RenderPass and the roulette overlay retain
 * register/stack residuals, so the reversed group remains NonMatching. */
#include "game/types/size_t.h"
#include "game/TransitionEffectPrivate.h"
#include "game/singleton.h"

void operator delete(void *) throw();
extern "C" void Object_DtorWithGXSync(void *, int);
extern "C" void *TransitionEffect_vtable_803FE3C0[];
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
            ((*(volatile unsigned int *)0x800000F8 >> 2) / 125000)) / 1e+06f);
    }
};

extern "C" void TransitionEffect_Tick(TransitionEffectView *self)
{
    ScopedTimer timer(0x2B);
    unsigned char fadeActive;
    TransitionFade *fade = self->fade;
    if (fade->delay <= 0.0f && fade->remaining <= 0.0f) {
        fadeActive = 0;
    } else {
        fade->delay -= 0.016666668f;
        if (fade->delay <= 0.0f) {
            fade->delay = 0.0f;
            fade->remaining -= 0.016666668f;
            if (fade->remaining <= 0.0f) fade->remaining = 0.0f;
        }
        fadeActive = 1;
    }
    TransitionIris *iris = self->iris;
    unsigned char irisActive;
    if (iris->remaining <= 0.0f) irisActive = 0;
    else {
        iris->remaining -= iris->step;
        if (iris->closing == 1) {
            iris->radius = 4.8e+02f * (1.0f - iris->remaining);
            iris->alpha = (unsigned int)(255.0f * iris->remaining);
        } else {
            iris->radius = 4.8e+02f * iris->remaining;
            iris->alpha = (unsigned int)(255.0f * (1.0f - iris->remaining));
            if (iris->remaining <= 0.0f) {
                iris->closing = 1;
                iris->remaining = 1.0f;
            }
        }
        irisActive = 1;
    }
    TransitionFlash *flash = self->flash;
    unsigned int flashActive;
    flash->remaining -= 0.016666668f;
    if (flash->remaining <= 0.0f) {
        flash->active = flashActive = 0;
        flash->remaining = 0.0f;
    } else {
        float alpha = 0.9f * flash->remaining;
        if (alpha > 0.9f) alpha = 0.9f;
        flash->r = 1.0f;
        flash->g = 1.0f;
        flash->b = 1.0f;
        flash->alpha = alpha;
        flash->active = flashActive = 1;
    }
    float *shake = self->shake;
    unsigned char shakeActive;
    if (*shake <= 0.0f) shakeActive = 0;
    else { *shake -= 0.016666668f; shakeActive = 1; }
    TransitionRoulette *roulette = self->roulette;
    unsigned char quadActive = self->quad->active;
    unsigned char rouletteActive;
    if (roulette->remaining <= 0.0f) rouletteActive = 0;
    else {
        roulette->remaining -= 0.016666668f;
        if (roulette->remaining > 1.0f) {
            roulette->fade += 0.04f;
            if (roulette->fade > 1.0f) roulette->fade = 1.0f;
        } else {
            roulette->fade -= 0.04f;
            if (roulette->fade < 0.0f) roulette->fade = 0.0f;
        }
        if (roulette->fade >= 1.0f) roulette->speed += 0.0005f;
        if (roulette->speed > 0.04f) roulette->speed = 0.04f;
        roulette->elapsed += 0.016666668f;
        switch (roulette->phase) {
        case 0:
            if (roulette->elapsed > 1.0f) {
                ++roulette->phase;
                roulette->elapsed = 0.0f;
                roulette->active = 0;
            }
            break;
        case 1:
            if (roulette->elapsed > 0.1f) {
                ++roulette->phase;
                roulette->elapsed = 0.0f;
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
extern void *TransitionEffect_data_803FE37C[];
extern const char lbl_80311DA4[];
}
void *operator new(size_t);

struct TransitionFadeInit : TransitionFade {
    TransitionFadeInit() { delay = 0.0f; remaining = 0.0f; }
};
struct TransitionIrisInit : TransitionIris {
    TransitionIrisInit() { remaining = 0.0f; step = 0.0f; closing = 1; }
};
struct TransitionShakeInit {
    float remaining;
    TransitionShakeInit() { remaining = 0.0f; }
};
struct TransitionFlashInit : TransitionFlash {
    TransitionFlashInit() { remaining = 0.0f; active = 0; }
};
struct TransitionQuadInit : TransitionQuad {
    TransitionQuadInit() { active = 0; }
};
struct TransitionModelInit {
    unsigned char opaque[0x5C];
    TransitionModelInit() { clNormal3D_Construct(this, lbl_80311DA4, 1); }
};
/* Destructor declarations bridge to the owned deleting dtors below. The
 * model owner is constructed only after its nested new expression completes. */
struct TransitionModelOwner {
    void *object;
    TransitionModelOwner() : object(new TransitionModelInit) {}
    ~TransitionModelOwner();
};
struct TransitionRouletteInit {
    TransitionModelOwner holder;
    float remaining, speed, fade;
    int phase;
    float elapsed;
    unsigned char active;
    TransitionRouletteInit() {
        Object_JObjUpdate_870(holder.object, 0x200);
        Object_SetByte48(holder.object, 1);
        remaining = 0.0f;
    }
};
/* A constructor keeps allocation failure cleanups native. The owner views
 * above describe the same pointer layout without imposing shared headers. */
template <class T> struct TransitionOwner {
    T *p;
    TransitionOwner() : p(new T) {}
    ~TransitionOwner();
};
struct TransitionInitBase {
    void **vtable;
    TransitionInitBase(void **derivedVtable) {
        vtable = TransitionEffect_vtable_803FE3C0;
        lbl_806D109C = (TransitionEffectView *)this;
        vtable = derivedVtable;
    }
    ~TransitionInitBase();
};
struct TransitionEmptyMember {
    ~TransitionEmptyMember();
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
    TransitionEmptyMember emptyMember;
    unsigned char align[2];
    unsigned char renderState[0x4C];
    TransitionEffectInit() :
        TransitionInitBase(TransitionEffect_data_803FE37C) {
        fn_801F6804(renderState);
        mode = 0;
        duration = 0.0f;
    }
};
extern "C" TransitionEffectView *TransitionEffect_GetOrCreate()
{
    if (SINGLETON_INSTANCE(lbl_806D109C) == 0) new TransitionEffectInit;
    return SINGLETON_INSTANCE(lbl_806D109C);
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
extern const Vec TransitionEffect_rodata_80311CA0[];
extern float TransitionEffect_DrawCarRouletteOverlay_bss_806D1170;
extern signed char TransitionEffect_DrawCarRouletteOverlay_bss_806D1174;
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
#include "game/types/TransitionTextureVertex.h"
extern "C" TransitionTextureVertex TransitionEffect_DrawCarRouletteOverlay_data_803FE230[16];

static inline void ScreenProjection(Mtx44 projection)
{
    C_MTXOrtho(projection, 2.4e+02f, (-2.4e+02f), (-3.2e+02f),
               3.2e+02f, 1e+02f, 1e+03f);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    GXSetViewport(0.0f, 0.0f, 6.4e+02f, 4.8e+02f,
                  0.0f, 1.0f);
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
extern float TransitionEffect_RenderPass_bss_806D1160, TransitionEffect_RenderPass_bss_806D1168;
extern signed char TransitionEffect_RenderPass_bss_806D1164, TransitionEffect_RenderPass_bss_806D116C;
extern TransitionTextureVertex TransitionEffect_RenderPass_data_803FE0F0[16];
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
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
}
static inline void ScreenFlatQuad(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    float y1, x1, y0, x0;
    x0 = -320.0f; y0 = -240.0f; x1 = 320.0f; y1 = 240.0f;
    ScreenPosition(x0, y0); ScreenColor(r,g,b,a);
    ScreenPosition(x1, y0); ScreenColor(r,g,b,a);
    ScreenPosition(x1, y1); ScreenColor(r,g,b,a);
    ScreenPosition(x0, y1); ScreenColor(r,g,b,a);
}
static inline void ScreenTableQuad(float ox, float oy)
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 16);
    TransitionTextureVertex *v = TransitionEffect_RenderPass_data_803FE0F0;
    for (int i = 0; i < 16; ++i) {
        ScreenPosition((v[0].x - 3.2e+02f) + ox, (v[0].y - 2.4e+02f) + oy);
        *(volatile unsigned int *)0xCC008000 = v[0].color;
        ScreenPosition(0.0015625f * v[0].u, 0.0020833334f * v[0].v);
        ++v;
    }
}
static inline void ScreenRotatedCamera(Mtx view, const Vec *camera, int index, float *angle, signed char *initialized)
{
    Vec eye = camera[index];
    if (!*initialized) { *initialized = 1; *angle = 9e+01f; }
    Vec up = camera[index + 1];
    up.x = (float)cos((float)(0.017453292519943295 * *angle));
    up.y = -(float)sin((float)(0.017453292519943295 * *angle));
    Vec target = camera[index + 2];
    C_MTXLookAt(view, &eye, &up, &target);
    GXLoadPosMtxImm(view, 0);
}
static inline void ScreenFlashSetup(const Vec *camera)
{
    Mtx44 projection3;
    Mtx view3;
    ScreenProjection(projection3);
    ScreenCamera(view3, camera, 9, 1.5707963705062866);
}
extern "C" void TransitionEffect_RenderPass(TransitionEffectView *self, int pass)
{
    const Vec *camera = TransitionEffect_rodata_80311CA0;
    unsigned int a1;
    unsigned int r, g, b, a;
    unsigned int r5, g5, b5, a5;
    /* Keep each pass's escaped matrices in the target stack order. */
    Mtx view1;
    Mtx44 projection1;
    Mtx view2;
    Mtx44 projection2;
    Mtx view4;
    Mtx44 projection4;
    Mtx view5;
    Mtx44 projection5;
    ScopedTimer timer(0x2C);
    if (self->mode != pass) return;
    if (self->mode != 3) {
        fn_801F6804(self->rest + 3);
        fn_801F6588(0);
    }
    switch (pass) {
    case 0: break;
    case 1: {
        void *payload;
        payload = self->fade;
        if (((TransitionFade *)payload)->delay <= 0.0f && ((TransitionFade *)payload)->remaining <= 0.0f) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        ScreenProjection(projection1);
        ScreenRotatedCamera(view1, camera, 3, &TransitionEffect_RenderPass_bss_806D1160, &TransitionEffect_RenderPass_bss_806D1164);
        GXLoadTexObj(BackupBuffer_InitAsTexture(), GX_TEXMAP0);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        GXSetNumChans(1);
        GXSetNumTevStages(1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
        GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        ScreenVertexFormat(true);
        a1 = (int)Saturate_Double(2e+02f * ((TransitionFade *)payload)->remaining, 0.0f, 2e+02f);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        float y1, t1, x1, t0, y0, x0;
        x0 = -320.0f; y0 = -240.0f; t0 = 0.0f; x1 = 320.0f; t1 = 1.0f; y1 = 240.0f;
        ScreenPosition(x0, y0); ScreenColor(255,255,255,a1);
        ScreenPosition(t0, t0);
        ScreenPosition(x1, y0); ScreenColor(255,255,255,a1);
        ScreenPosition(t1, t0);
        ScreenPosition(x1, y1); ScreenColor(255,255,255,a1);
        ScreenPosition(t1, t1);
        ScreenPosition(x0, y1); ScreenColor(255,255,255,a1);
        ScreenPosition(t0, t1);
        RestoreScreenChannel();
        break;
    }
    case 2: {
        void *payload;
        payload = self->iris;
        if (((TransitionIris *)payload)->remaining <= 0.0f && ((TransitionIris *)payload)->closing == 1) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        ScreenProjection(projection2);
        ScreenCamera(view2, camera, 0, 1.5707963705062866);
        ScreenFlatMaterial(GX_BL_INVSRCALPHA);
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        float y1, x1, y0, x0;
        x0 = -320.0f; y0 = -240.0f; x1 = 320.0f; y1 = 240.0f;
        ScreenPosition(x0, y0);
        *(volatile unsigned int *)0xCC008000 = 255;
        ScreenPosition(x1, y0);
        *(volatile unsigned int *)0xCC008000 = 255;
        ScreenPosition(x1, y1 - ((TransitionIris *)payload)->radius);
        *(volatile unsigned int *)0xCC008000 = 0;
        ScreenPosition(x0, y1 - ((TransitionIris *)payload)->radius);
        *(volatile unsigned int *)0xCC008000 = 0;
        RestoreScreenChannel();
        break;
    }
    case 3: {
        void *payload;
        payload = self->flash;
        if (!((TransitionFlash *)payload)->active) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        ScreenFlashSetup(camera);
        ScreenFlatMaterial(GX_BL_INVSRCALPHA);
        r = (int)Saturate_Double(255.0f * ((TransitionFlash *)payload)->r, 0.0f, 255.0f);
        g = (int)Saturate_Double(255.0f * ((TransitionFlash *)payload)->g, 0.0f, 255.0f);
        b = (int)Saturate_Double(255.0f * ((TransitionFlash *)payload)->b, 0.0f, 255.0f);
        a = (int)Saturate_Double(255.0f * ((TransitionFlash *)payload)->alpha, 0.0f, 255.0f);
        ScreenFlatQuad(r,g,b,a);
        RestoreScreenChannel();
        break;
    }
    case 4: {
        if (*self->shake <= 0.0f) break;
        GXSetZMode(GX_DISABLE, GX_NEVER, GX_DISABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetCullMode(GX_CULL_BACK);
        ScreenProjection(projection4);
        ScreenRotatedCamera(view4, camera, 6, &TransitionEffect_RenderPass_bss_806D1168, &TransitionEffect_RenderPass_bss_806D116C);
        ScreenTexturedMaterial();
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumChans(1);
        ScreenVertexFormat(true);
        ScreenTableQuad(0.0f, 0.0f);
        RestoreScreenChannel();
        break;
    }
    case 5: {
        void *payload;
        payload = self->quad;
        if (!((TransitionQuad *)payload)->active) break;
        GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
        GXSetZCompLoc(GX_FALSE);
        GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetCullMode(GX_CULL_BACK);
        ScreenProjection(projection5);
        ScreenCamera(view5, camera, 9, 1.5707963705062866);
        ScreenFlatMaterial(GX_BL_INVSRCALPHA);
        r5 = (int)Saturate_Double(255.0f * ((TransitionQuad *)payload)->r, 0.0f, 255.0f);
        g5 = (int)Saturate_Double(255.0f * ((TransitionQuad *)payload)->g, 0.0f, 255.0f);
        b5 = (int)Saturate_Double(255.0f * ((TransitionQuad *)payload)->b, 0.0f, 255.0f);
        a5 = (int)Saturate_Double(255.0f * ((TransitionQuad *)payload)->alpha, 0.0f, 255.0f);
        ScreenFlatQuad(r5,g5,b5,a5);
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

static inline void ScreenRouletteTableQuad(float ox, float oy)
{
    GXBegin(GX_QUADS, GX_VTXFMT0, 16);
    TransitionTextureVertex *v = TransitionEffect_DrawCarRouletteOverlay_data_803FE230;
    
    for (int i = 0; i < 16; ++i) {
        ScreenPosition((v[0].x - 3.2e+02f) + ox, (v[0].y - 2.4e+02f) + oy);
        *(volatile unsigned int *)0xCC008000 = v[0].color;
        ScreenPosition(0.0015625f * v[0].u, 0.0020833334f * v[0].v);
        ++v;
    }
}

extern "C" void TransitionEffect_DrawCarRouletteOverlay(TransitionRoulette *self)
{
    const Vec *camera = TransitionEffect_rodata_80311CA0;
    if (self->remaining <= 0.0f) return;
    TransitionEffect_DrawCarRouletteAndQuad(self, self->fade, self->speed);
    if (self->active != 1) return;
    GXSetZMode(GX_DISABLE, GX_NEVER, GX_DISABLE);
    GXSetZCompLoc(GX_FALSE);
    GXSetCullMode(GX_CULL_BACK);
    Mtx view;
    Mtx44 projection;
    ScreenProjection(projection);
    ScreenRotatedCamera(view, camera, 15, &TransitionEffect_DrawCarRouletteOverlay_bss_806D1170, &TransitionEffect_DrawCarRouletteOverlay_bss_806D1174);
    GXLoadTexObj(BackupBuffer_InitAsTexture(), GX_TEXMAP0);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumChans(1);
    ScreenVertexFormat(true);
    ScreenRouletteTableQuad(0.0f, 0.0f);
    RestoreScreenChannel();
}

/* The target keeps copies that copy propagation would fold here. */
#pragma opt_propagation off
extern "C" void TransitionEffect_DrawCarRouletteAndQuad(TransitionRoulette *self, float fade, float angle)
{
    const Vec *camera = TransitionEffect_rodata_80311CA0;
    MtxPtr matrix = CObj_GetProjMatrix_Cached(GetCourseScene3D());
    Vec position;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = (-5e+02f) * fade + (-1e+03f) * (1.0f - fade);
    PSMTXMultVec(matrix, &position, &position);
    Object_SetJObjPositionXYZ(self->holder.object, position.x, position.y, position.z);
    Object_SetJObjScaleXYZ(self->holder.object, 4e+01f, 4e+01f, 4e+01f);
    Object_SetColorRGBA(self->holder.object, 0, fade, fade, fade, fade);
    JObjTree_TranslateAndMul(self->holder.object, 0, 0.0f, angle);
    Object_RenderJObjTree(self->holder.object, 7);
    float c;
    float alpha = 0.8f * self->fade;
    GXSetZMode(GX_DISABLE, GX_ALWAYS, GX_ENABLE);
    GXSetZCompLoc(GX_FALSE);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_VTX, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetCullMode(GX_CULL_BACK);
    Mtx view;
    Mtx44 projection;
    ScreenProjection(projection);
    ScreenCamera(view, camera, 12, 1.5707963705062866);
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
    r = (int)Saturate_Double(0.0f, 0.0f, 255.0f);
    c = 255.0f * alpha;
    g = (int)Saturate_Double(c, 0.0f, 255.0f);
    b = (int)Saturate_Double(c, 0.0f, 255.0f);
    a = (int)Saturate_Double(255.0f * (0.7f * alpha), 0.0f, 255.0f);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    float y1, x1, y0, x0;
    x0 = -320.0f; y0 = -240.0f; x1 = 320.0f; y1 = 240.0f;
    ScreenPosition(x0, y0); ScreenColor(r,g,b,a);
    ScreenPosition(x1, y0); ScreenColor(r,g,b,a);
    ScreenPosition(x1, y1); ScreenColor(r,g,b,a);
    ScreenPosition(x0, y1); ScreenColor(r,g,b,a);
    RestoreScreenChannel();
}
#pragma opt_propagation reset

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
    self->duration = 0.0f;
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
        p->remaining = 1.0f;
        break;
    }
    case 2: {
        TransitionIris *p = self->iris;
        p->closing = 0;
        p->remaining = 1.0f;
        p->step = 1.0f / (6e+01f * duration);
        break;
    }
    case 3: self->flash->remaining = duration; break;
    case 4: *self->shake = duration; break;
    case 5: return 0;
    case 6: {
        TransitionRoulette *p = self->roulette;
        if (p->remaining > 0.0f) {
            p->remaining = duration;
        } else {
            p->remaining = duration;
            p->speed = -0.01f;
            p->fade = 0.0f;
            p->elapsed = 0.0f;
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
        self->vtable = TransitionEffect_vtable_803FE3C0;
        if (flag > 0) operator delete(self);
    }
    return self;
}

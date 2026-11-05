/*
 * Result-screen cup trophy effect on the shared sprite-effect base
 * (vtable lbl_8048EBCC; ctor, dtor). The base declares a virtual that is
 * not defined here first, so no vtable is emitted.
 *
 * Still asm: the title draw (float register choice).
 */
#pragma cplusplus on

typedef float Mtx[3][4];
struct Vec3f {
    float x, y, z;
};
struct TexMgr {
    unsigned char pad0[0x18];
    int mode;
    unsigned char pad1C[4];
    unsigned int color;
    unsigned char pad24[0x208];
    float fade;
    TexMgr();
    ~TexMgr() {}
    void SetColor(unsigned int c) {
        mode = 1;
        color = c;
    }
};

extern "C" {
extern char lbl_8048EB44[];
extern char lbl_8048EBCC[];
extern char lbl_8048EC9C[];
extern int lbl_803604D8[];
extern int lbl_80360498[][2];
extern unsigned int lbl_80360520[];
extern int lbl_803606C4[];
extern int lbl_803606E4[][3];
extern char lbl_806CF688[4];
extern char lbl_806CF68C[4];
extern int g_cupId;
extern const float lbl_806D77AC, lbl_806D77B0, lbl_806D77B8, lbl_806D7840, lbl_806D7860;
extern const float lbl_806D7868;
extern const float lbl_806D788C, lbl_806D7890, lbl_806D7894, lbl_806D7898;
extern void PreloadResource(int resId);
extern void fn_80120A08(int resId);
extern void SpriteAnimHandle_Destroy(void *h, int flag);
extern void SpriteHandle_Destroy(int h);
extern void SpriteGroup_CreateOrInit(void *out, const char *name, int mode, float a, float b);
extern void TexMgr_Init(void *self);
extern void TexMgr_SetTexture(void *self, const char *fmt, ...);
extern void TexMgr_Apply(void *self);
extern const char *GetTextureByIdAndLang(int id, int lang);
extern int fn_8013C198(int id, int lang);
extern void *fn_8013BC98(void);
extern void *fn_8013C3B8(void);
extern unsigned char fn_8013BC38(void *rt);
extern void fn_8013C34C(void *rt);
extern void fn_8013BBFC(void *rt);
extern void fn_8013C334(void *rt);
extern void fn_8013BB9C(void *rt);
extern void fn_8013BCA0(void);
extern void fn_8013C3C0(void);
extern int fn_8013BD7C(void);
extern int fn_8013C428(void);
extern void HSD_StateSetCullMode(int mode);
extern void HSD_StateInitDirect(int a, int b);
extern void *HSD_CObjGetCurrent(void);
extern void HSD_CObjGetViewingMtx(void *cam, Mtx m);
extern void GXSetCurrentMtx(int id);
extern void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
extern void GXLoadPosMtxImm(Mtx m, int id);
extern void GXBegin(int prim, int fmt, int n);
extern void *FUN_8003b120(unsigned long size);
extern void MemoryManager_Free(void *p);
extern void fn_801A0004(void *p);
extern void *fn_801F8E58(void);
extern void fn_801F8A34(void *p, void *tm, int n);
extern void MemoryManager_TimedFree(void *p);
extern void dtor_800869D0();
}


struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
};

struct ResCtrl {
    int resId;
    int field4, mode, fieldc;
    unsigned char flag, pad11[3];
    float x, y, z, width, height, field28, scaleX, scaleY;
    unsigned int colors[4];
    int tail[5];
    ResCtrl();
    ~ResCtrl() {}
    void SetColor(unsigned int c) {
        colors[0] = c;
        colors[1] = c;
        colors[2] = c;
        colors[3] = c;
    }
};

extern "C" {
extern void fn_801678FC(int layer, float r, float g, float b, float a);
extern void fn_801695E0(int obj, int id, int flag, float x, float y, float a);
extern void fn_8016918C(int obj, int id, int flag, float x, float y, float sx, float sy, float r, float g, float b, float a);
extern void fn_8011FAFC(void *res, int n);
extern const char *fn_8013BFF8(int cup, int line, int lang);
extern unsigned char IsCardValid(void);
extern int MiniGame_GetTimerValue(void);
extern const float *MiniGame_GetCourseData(void);
extern void fn_801F93EC(void *tm, float x, float y);
extern void fn_801F8FCC(void *tm, int on);
extern void fn_801F93D0(void *tm, float sx, float sy);
extern void fn_801F8E90(void *tm);
extern int isJapanese(void);
extern int sprintf(char *buf, const char *fmt, ...);
extern unsigned long strlen(const char *s);
extern unsigned char fn_80192010(int id);
extern unsigned char fn_8019083C(int id);
extern void ClSound_PlayBgmStream(int a, int b);
extern int fn_801932F8(void);
extern void clStream_setVolume(int a, int v);
extern void SpriteAnimParamBlock_Reload(void *p, int id);
extern void fn_801FFFF4(void *h);
extern void fn_8023F1C8(void *p);
extern void SoundMgr_Play(int id);
extern void SpriteAnimParamBlock_SetAnimParamCached(void *p, int id, int v);
extern void fn_8011F744(int h, float sx, float sy);
extern void SpriteHandle_SetCornerAlpha(int h, int a);
extern void SpriteHandle_SetActiveFlag(int h, int f);
extern void fn_80190A70(int a, int b);
extern unsigned char Sprite_AdvanceAnim(void *spr, float dt);
extern void SpriteHandle_RecomputeCull(int h);
extern void *GetInputManager(void);
extern InputPlayer *InputMgr_GetPlayer(void *, int);
extern void SetRumbleMode(unsigned int ch, unsigned int mode, int duration);
extern struct { char pad[0x20]; signed char f20; } lbl_80598A60;
extern char lbl_806CF690[4];
extern const char lbl_806D77C4[4];
extern const char lbl_806D780C[7];
extern const char lbl_806D7824[5];
extern const float lbl_806D77A8, lbl_806D77B4, lbl_806D77BC, lbl_806D77C0, lbl_806D77C8, lbl_806D77CC;
extern const float lbl_806D77D0, lbl_806D77D4, lbl_806D77D8, lbl_806D77DC, lbl_806D77E0, lbl_806D77E4;
extern const float lbl_806D77E8, lbl_806D77EC, lbl_806D77F0, lbl_806D77F4, lbl_806D77F8, lbl_806D77FC;
extern const float lbl_806D7800, lbl_806D7804, lbl_806D7808, lbl_806D7814, lbl_806D7818, lbl_806D781C;
extern const float lbl_806D7820, lbl_806D782C, lbl_806D7830, lbl_806D7844, lbl_806D7848, lbl_806D784C;
extern const float lbl_806D7850, lbl_806D7854, lbl_806D7858, lbl_806D785C;
extern const float lbl_806DA870, lbl_806DA874;
}

struct FxData {
    int obj;
    unsigned char active;
    float x, y;
    float alpha;
};

struct FxBase : FxData {
    FxBase() {
        obj = 0;
        active = 0;
        x = lbl_806D77B0;
        y = lbl_806D77B0;
        alpha = lbl_806D77AC;
    }
    virtual ~FxBase() {}
    virtual void m0C();
    virtual void m10();
    virtual void Update();
    virtual void Draw();
    virtual void m1C();
};

struct Handle {
    virtual ~Handle();
    virtual void Stop();
};

struct HandleF : Handle {
    unsigned char pad[0x18];
    float x, y;
    void SetXY(float a, float b) {
        x = a;
        y = b;
    }
};

extern "C" HandleF *fn_8020007C(int a, int obj, int b);

struct SpriteRef {
    struct Sprite {
        char pad[0x20];
        float t;
    } *spr;
};



struct TrophyFx : FxBase {
    int cup;
    int state;
    float t;
    float t2;
    HandleF *handle;
    void *anims[3];
    int sprite;
    unsigned char done;
    float t3;

    virtual void m0C();
    TrophyFx();
    virtual ~TrophyFx();
    virtual void Draw();
    virtual void Update();
    void DrawCaption(float a);
};

extern "C" {
extern unsigned int lbl_806D7838;
asm void fn_8013F428(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8013F428 = { 0x304A0000, 0x000000F4, 0x01020010, 0x00000000, 0x82000088, (void *)&dtor_800869D0 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013F428 = {
    (void *)&fn_8013F428, 0x00000518, (void *)&extab_fn_8013F428
};

}


void TrophyFx::Draw() {
    switch (state) {
    case 0:
        ((void (*)(TrophyFx *, float))fn_8013F428)(this, t / 15.0f);
        break;
    case 1:
        ((void (*)(TrophyFx *, float))fn_8013F428)(this, 1.0f);
        break;
    case 2:
        ((void (*)(TrophyFx *, float))fn_8013F428)(this, 1.0f);
        fn_801678FC(7, 0.0f, 0.0f, 0.0f, t / 15.0f);
        break;
    case 3:
        fn_801678FC(7, 0.0f, 0.0f, 0.0f, 1.0f);
        break;
    case 4:
        fn_801678FC(7, 0.0f, 0.0f, 0.0f, 1.0f - t / 15.0f);
        break;
    case 5:
        DrawCaption(t / 15.0f);
        break;
    case 6:
        DrawCaption(1.0f);
        break;
    case 7:
        DrawCaption(1.0f);
        break;
    }
}

void TrophyFx::DrawCaption(float a) {
    int alpha;
    float s;
    void *ctx;
    int n;
    float f;

    alpha = (int)(255.0f * a);
    ResCtrl rc;
    rc.resId = lbl_803604D8[cup - 1];
    rc.flag = 1;
    rc.x = 320.0f;
    rc.y = 238.0f;
    rc.z = 1.0f;
    rc.SetColor((unsigned char)alpha | 0xFFFFFF00);
    fn_8011FAFC(&rc, 5);
    TexMgr t0;
    TexMgr t1;
    TexMgr t2;
    s = 0.1f * (1.0f - a) + 1.0f;
    if (lbl_80598A60.f20 == 0) {
        TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1));
        TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1));
        TexMgr_SetTexture(&t2, lbl_806D77C4);
        fn_801F93EC(&t0, 330.0f, 340.0f);
        fn_801F93EC(&t1, 330.0f, 374.0f);
        fn_801F93EC(&t2, 0.0f, 0.0f);
        t0.fade = -4.0f;
        t1.fade = -4.0f;
        t2.fade = -2.0f;
    } else if (IsCardValid() == 1) {
        TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1));
        TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1));
        TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1));
        fn_801F93EC(&t0, 335.0f, 330.0f);
        fn_801F93EC(&t1, 335.0f, 355.0f);
        fn_801F93EC(&t2, 335.0f, 380.0f);
        s *= 0.85f;
    } else {
        switch (g_cupId) {
        case 1:
        case 3:
            TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1));
            TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1));
            TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1), MiniGame_GetTimerValue());
            break;
        case 4:
            TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1));
            TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1), MiniGame_GetTimerValue());
            TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1));
            break;
        case 2: {
            const float *cd = MiniGame_GetCourseData();
            if (cd) {
                n = ((const int *)cd)[1];
            } else {
                n = 15;
            }
            TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1), n);
            TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1));
            TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1), MiniGame_GetTimerValue());
            break;
        }
        case 7: {
            const float *cd = MiniGame_GetCourseData();
            if (cd) {
                f = cd[0];
            } else {
                f = 75.0f;
            }
            TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1), (int)f);
            TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1), MiniGame_GetTimerValue());
            TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1));
            break;
        }
        case 8: {
            const float *cd = MiniGame_GetCourseData();
            if (cd) {
                f = cd[0];
            } else {
                f = 70.0f;
            }
            TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1));
            TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1), (int)f);
            TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1));
            break;
        }
        case 5:
        case 6:
            TexMgr_SetTexture(&t0, fn_8013BFF8(cup, 0, -1));
            TexMgr_SetTexture(&t1, fn_8013BFF8(cup, 1, -1));
            TexMgr_SetTexture(&t2, fn_8013BFF8(cup, 2, -1));
            break;
        }
        fn_801F93EC(&t0, 335.0f, 330.0f);
        fn_801F93EC(&t1, 335.0f, 355.0f);
        fn_801F93EC(&t2, 335.0f, 380.0f);
        s *= 0.85f;
    }
    ctx = fn_801F8E58();
    fn_801F8FCC(&t0, 1);
    fn_801F93D0(&t0, s, s);
    t0.color = (alpha & 0xFF) | 0xFFFFFF00;
    t0.mode = 1;
    fn_801F8E90(&t0);
    fn_801F8A34(ctx, &t0, 5);
    fn_801F8FCC(&t1, 1);
    fn_801F93D0(&t1, s, s);
    t1.SetColor((alpha & 0xFF) | 0xFFFFFF00);
    fn_801F8E90(&t1);
    fn_801F8A34(ctx, &t1, 5);
    fn_801F8FCC(&t2, 1);
    fn_801F93D0(&t2, s, s);
    t2.SetColor((alpha & 0xFF) | 0xFFFFFF00);
    fn_801F8E90(&t2);
    fn_801F8A34(ctx, &t2, 5);
}

extern "C" asm void fn_8013F428(void) { /* 0x8013F428 size:0x518 */
    nofralloc
    stwu r1, -0x300(r1)
    mflr r0
    stw r0, 0x304(r1)
    stfd f31, 0x2f0(r1)
    psq_st f31, 0x2f8(r1), 0, 0
    stmw r26, 0x2d8(r1)
    fmr f31, f1
    lfs f4, lbl_806D77AC(r2)
    mr r28, r3
    lfs f1, lbl_806D77B8(r2)
    fmr f5, f4
    lwz r3, 0x0(r3)
    fmr f6, f4
    lfs f2, lbl_806D77F4(r2)
    fmr f7, f4
    lfs f3, lbl_806D77F8(r2)
    fmr f8, f31
    li r4, 0x14e5
    li r5, 0x0
    bl fn_8016918C
    fmr f3, f31
    lwz r3, 0x0(r28)
    lfs f1, lbl_806D77B8(r2)
    li r4, 0x1cda
    lfs f2, lbl_806D77FC(r2)
    li r5, 0x0
    bl fn_801695E0
    lfs f1, 0x40(r28)
    lfs f0, lbl_806D7800(r2)
    lfs f3, lbl_806D77B0(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8013F428_L_8013F4B4
    stfs f3, 0x40(r28)
    b fn_8013F428_L_8013F4E4
    fn_8013F428_L_8013F4B4:
    lfs f0, lbl_806D7804(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_8013F428_L_8013F4E4
    fsubs f2, f1, f0
    lfs f0, lbl_806D77A8(r2)
    lfs f1, lbl_806D77AC(r2)
    fdivs f3, f2, f0
    fcmpo cr0, f3, f1
    ble fn_8013F428_L_8013F4E4
    fsubs f0, f3, f1
    fsubs f3, f1, f0
    fn_8013F428_L_8013F4E4:
    lwz r3, 0x0(r28)
    li r4, 0x1cda
    lfs f1, lbl_806D77B8(r2)
    li r5, 0x2
    lfs f2, lbl_806D77FC(r2)
    bl fn_801695E0
    bl fn_801F8E58
    mr r0, r3
    addi r3, r1, 0x88
    mr r29, r0
    bl TexMgr_Init
    addi r3, r1, 0x88
    li r4, 0x1
    bl fn_801F8FCC
    lwz r3, 0x18(r28)
    li r4, -0x1
    bl fn_8013C198
    mr r26, r3
    li r3, 0x55
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    mr r5, r26
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    lfs f0, lbl_806D77D8(r2)
    addi r3, r1, 0x88
    lfs f1, lbl_806D77B8(r2)
    stfs f0, 0x2b4(r1)
    lfs f2, lbl_806D77CC(r2)
    bl fn_801F93EC
    lfs f0, lbl_806D77B4(r2)
    li r0, 0x1
    stw r0, 0xa0(r1)
    li r30, -0x100
    fmuls f0, f0, f31
    addi r3, r1, 0x88
    fctiwz f0, f0
    stfd f0, 0x2b8(r1)
    lwz r0, 0x2bc(r1)
    rlwimi r30, r0, 0, 24, 31
    clrlwi r31, r0, 24
    stw r30, 0xa8(r1)
    bl fn_801F8E90
    lwz r5, 0x0(r28)
    mr r3, r29
    addi r4, r1, 0x88
    bl fn_801F8A34
    addi r3, r1, 0x88
    li r4, 0x0
    bl fn_801F8FCC
    addi r3, r1, 0x88
    bl fn_801F8E90
    lfs f0, lbl_806D7808(r2)
    li r0, 0x1
    stw r0, 0xa0(r1)
    stfs f0, 0x2b4(r1)
    bl isJapanese
    cmpwi r3, 0x0
    bne fn_8013F428_L_8013F790
    li r3, 0x58
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r26, r3
    li r3, 0x57
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r27, r3
    li r3, 0x56
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r5, r3
    mr r6, r27
    mr r7, r26
    addi r3, r1, 0x8
    la r4, lbl_806D780C(r2)  /* lbl_806D780C */
    crxor 6, 6, 6
    bl sprintf
    addi r3, r1, 0x8
    bl strlen
    subi r3, r3, 0x1
    lis r0, 0x4330
    xoris r4, r3, 0x8000
    stw r0, 0x2b8(r1)
    lfd f1, lbl_806D7838(r2)
    addi r3, r1, 0x88
    stw r4, 0x2bc(r1)
    lfs f3, lbl_806D7818(r2)
    lfd f0, 0x2b8(r1)
    lfs f4, lbl_806D7814(r2)
    fsubs f1, f0, f1
    lfs f0, lbl_806D77B8(r2)
    lfs f2, lbl_806D781C(r2)
    fmuls f1, f3, f1
    fnmsubs f31, f4, f1, f0
    fmr f1, f31
    bl fn_801F93EC
    li r3, 0x56
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    stw r30, 0xa8(r1)
    mr r3, r29
    addi r4, r1, 0x88
    lwz r5, 0x0(r28)
    bl fn_801F8A34
    li r3, 0x56
    li r4, -0x1
    bl GetTextureByIdAndLang
    bl strlen
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x2c4(r1)
    addi r3, r1, 0x88
    lfd f1, lbl_806D7838(r2)
    stw r0, 0x2c0(r1)
    lfs f3, lbl_806D7814(r2)
    lfd f0, 0x2c0(r1)
    lfs f2, lbl_806D781C(r2)
    fsubs f0, f0, f1
    fmadds f31, f3, f0, f31
    fmr f1, f31
    bl fn_801F93EC
    li r3, 0x57
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    oris r0, r31, 0xe0e0
    mr r3, r29
    ori r0, r0, 0x2000
    addi r4, r1, 0x88
    stw r0, 0xa8(r1)
    lwz r5, 0x0(r28)
    bl fn_801F8A34
    li r3, 0x57
    li r4, -0x1
    bl GetTextureByIdAndLang
    bl strlen
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x2cc(r1)
    addi r3, r1, 0x88
    lfd f1, lbl_806D7838(r2)
    stw r0, 0x2c8(r1)
    lfs f3, lbl_806D7814(r2)
    lfd f0, 0x2c8(r1)
    lfs f2, lbl_806D781C(r2)
    fsubs f0, f0, f1
    fmadds f31, f3, f0, f31
    fmr f1, f31
    bl fn_801F93EC
    li r3, 0x58
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    stw r30, 0xa8(r1)
    mr r3, r29
    addi r4, r1, 0x88
    lwz r5, 0x0(r28)
    bl fn_801F8A34
    b fn_8013F428_L_8013F924
    fn_8013F428_L_8013F790:
    lfs f1, lbl_806D77B8(r2)
    addi r3, r1, 0x88
    lfs f2, lbl_806D7820(r2)
    bl fn_801F93EC
    li r3, 0x59
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    stw r30, 0xa8(r1)
    addi r3, r1, 0x88
    li r4, 0x1
    bl fn_801F8FCC
    addi r3, r1, 0x88
    bl fn_801F8E90
    lwz r5, 0x0(r28)
    mr r3, r29
    addi r4, r1, 0x88
    bl fn_801F8A34
    addi r3, r1, 0x88
    li r4, 0x0
    bl fn_801F8FCC
    li r3, 0x5b
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r27, r3
    li r3, 0x5a
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r5, r3
    mr r6, r27
    addi r3, r1, 0x8
    la r4, lbl_806D7824(r2)  /* lbl_806D7824 */
    crxor 6, 6, 6
    bl sprintf
    addi r3, r1, 0x8
    bl strlen
    subi r3, r3, 0x1
    lis r0, 0x4330
    xoris r4, r3, 0x8000
    stw r0, 0x2c8(r1)
    lfd f1, lbl_806D7838(r2)
    addi r3, r1, 0x88
    stw r4, 0x2cc(r1)
    lfs f3, lbl_806D7818(r2)
    lfd f0, 0x2c8(r1)
    lfs f4, lbl_806D782C(r2)
    fsubs f1, f0, f1
    lfs f0, lbl_806D77B8(r2)
    lfs f2, lbl_806D7830(r2)
    fmuls f1, f3, f1
    fnmsubs f31, f4, f1, f0
    fmr f1, f31
    bl fn_801F93EC
    li r3, 0x5a
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    stw r30, 0xa8(r1)
    addi r3, r1, 0x88
    bl fn_801F8E90
    lwz r5, 0x0(r28)
    mr r3, r29
    addi r4, r1, 0x88
    bl fn_801F8A34
    li r3, 0x5a
    li r4, -0x1
    bl GetTextureByIdAndLang
    bl strlen
    xoris r3, r3, 0x8000
    lis r0, 0x4330
    stw r3, 0x2c4(r1)
    addi r3, r1, 0x88
    lfd f1, lbl_806D7838(r2)
    stw r0, 0x2c0(r1)
    lfs f3, lbl_806D782C(r2)
    lfd f0, 0x2c0(r1)
    lfs f2, lbl_806D7830(r2)
    fsubs f0, f0, f1
    fmadds f31, f3, f0, f31
    fmr f1, f31
    bl fn_801F93EC
    li r3, 0x5b
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    addi r3, r1, 0x88
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    oris r0, r31, 0xe0e0
    mr r3, r29
    ori r0, r0, 0x2000
    addi r4, r1, 0x88
    stw r0, 0xa8(r1)
    lwz r5, 0x0(r28)
    bl fn_801F8A34
    fn_8013F428_L_8013F924:
    psq_l f31, 0x2f8(r1), 0, 0
    lfd f31, 0x2f0(r1)
    lmw r26, 0x2d8(r1)
    lwz r0, 0x304(r1)
    mtlr r0
    addi r1, r1, 0x300
    blr
}

void TrophyFx::Update() {
    unsigned char pressed;
    int i;
    float u;

    if ((t2 += 1.0f) > 120.0f) {
        t2 = 0.0f;
    }
    pressed = 0;
    if (state == 1 || state == 6) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x100) ||
            InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x2000)) {
            SetRumbleMode(0, 1, 1);
            pressed = 1;
        }
    }
    if (!fn_80192010(0x1F) && !fn_8019083C(3) && state <= 6) {
        ClSound_PlayBgmStream(3, 0);
        clStream_setVolume(3, fn_801932F8());
    }
    switch (state) {
    case 0:
        u = t / 15.0f;
        done = (int)(128.0f * u);
        ((SpriteRef *)anims[2])->spr->t = u;
        if ((t += 1.0f) > 15.0f) {
            state++;
            t = 0.0f;
        }
        break;
    case 1:
        if (0.0f == t) {
            SpriteAnimParamBlock_Reload(anims[0], 0x1BC);
            if (handle) {
                handle->Stop();
            }
            handle = fn_8020007C(1, obj, 0);
            handle->SetXY(lbl_806DA870, lbl_806DA874);
        }
        if ((t += 1.0f) > 300.0f || pressed) {
            if (handle) {
                fn_801FFFF4(handle);
            }
            state++;
            t = 0.0f;
        }
        break;
    case 2:
        if ((t += 1.0f) > 15.0f) {
            state++;
            t = 0.0f;
            fn_8023F1C8(anims[0]);
            fn_8023F1C8(anims[2]);
        }
        break;
    case 3:
        if ((t += 1.0f) > 30.0f) {
            done = 0;
            state++;
            t = 0.0f;
            SpriteGroup_CreateOrInit(&anims[1], lbl_806CF690, 0, 320.0f, 240.0f);
            SoundMgr_Play(0x1A);
            int idx = cup - 1;
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], 0xA9C, lbl_80360498[idx][0]);
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], 0xA9D, lbl_80360498[idx][1]);
        }
        break;
    case 4:
        if ((t += 1.0f) > 15.0f) {
            state++;
            t = 0.0f;
            fn_8011F744(sprite, 1.1f, 1.1f);
            SpriteHandle_SetCornerAlpha(sprite, 0);
            SpriteHandle_SetActiveFlag(sprite, 1);
        }
        break;
    case 5:
        u = t / 15.0f;
        fn_8011F744(sprite, 0.1f * (1.0f - u) + 1.0f, 0.1f * (1.0f - u) + 1.0f);
        SpriteHandle_SetCornerAlpha(sprite, (int)(255.0f * u));
        if ((t += 1.0f) > 15.0f) {
            state++;
            t = 0.0f;
        }
        break;
    case 6:
        if (!(((unsigned)(-(int)handle | (int)handle)) >> 31)) {
            if (handle) {
                handle->Stop();
            }
            handle = fn_8020007C(1, obj, 0);
            handle->SetXY(lbl_806DA870, lbl_806DA874);
        }
        if ((t += 1.0f) > 600.0f || pressed) {
            fn_80190A70(3, 5);
            if (handle) {
                fn_801FFFF4(handle);
            }
            state++;
            t = 0.0f;
            active = 1;
        }
        break;
    }
    t3 += 1.0f;
    for (i = 0; i < 3; i++) {
        if (anims[i]) {
            Sprite_AdvanceAnim(*(void **)anims[i], 0.0165f);
        }
    }
    SpriteHandle_RecomputeCull(sprite);
}

TrophyFx::~TrophyFx() {
    int i;

    if (handle) {
        handle->Stop();
    }
    for (i = 0; i < 3; i++) {
        if (anims[i]) {
            SpriteAnimHandle_Destroy(anims[i], 1);
            anims[i] = 0;
        }
    }
    SpriteHandle_Destroy(sprite);
    int idx = cup - 1;
    fn_80120A08(lbl_803604D8[idx]);
    fn_80120A08(lbl_80360498[idx][0]);
    fn_80120A08(lbl_80360498[idx][1]);
    fn_80120A08(0x14E5);
    fn_80120A08(0x14F5);
    fn_80120A08(0x1CDA);
    fn_80120A08(0x1CDD);
}

TrophyFx::TrophyFx() {
    int idx;

    cup = -1;
    state = 0;
    t = lbl_806D77B0;
    t2 = lbl_806D77B0;
    done = 0;
    t3 = lbl_806D77B0;
    cup = g_cupId;
    handle = 0;
    obj = 5;
    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    idx = cup - 1;
    PreloadResource(lbl_803604D8[idx]);
    PreloadResource(lbl_80360498[idx][0]);
    PreloadResource(lbl_80360498[idx][1]);
    PreloadResource(0x14E5);
    PreloadResource(0x14F5);
    PreloadResource(0x1CDA);
    PreloadResource(0x1CDD);
    SpriteGroup_CreateOrInit(&anims[0], lbl_806CF688, 0, lbl_806D77B8, lbl_806D7840);
    SpriteGroup_CreateOrInit(&anims[2], lbl_806CF68C, 1, lbl_806D7860, lbl_806D7840);
    ((SpriteRef *)anims[2])->spr->t = lbl_806D77B0;
    sprite = 0;
    PreloadResource(0x14E5);
    PreloadResource(0x1CDA);
    {
        TexMgr tm;
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x55, -1), fn_8013C198(cup, -1));
        TexMgr_Apply(&tm);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x56, -1));
        TexMgr_Apply(&tm);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x57, -1));
        TexMgr_Apply(&tm);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x58, -1));
        TexMgr_Apply(&tm);
    }
}


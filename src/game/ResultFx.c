/*
 * Result-screen effects on the shared sprite-effect base: the cup trophy
 * effect (vtable lbl_8048EBCC; ctor, dtor), the confetti particle field
 * drawn into the render targets, and the result effect scene
 * (vtable lbl_8048EC9C). The bases declare a virtual that is not defined
 * here first, so no vtable is emitted.
 *
 * Still asm: the particle draw (register choice) and update, the scene
 * update and the scene ctor.
 */
#pragma cplusplus on

typedef float Mtx[3][4];
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
extern void fn_802C7D98(void *cam, Mtx m);
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
}

extern "C" {
extern void PSMTXIdentity();
extern void Vec3_Dot();
extern void fn_8013BA90();
extern void fn_8013BAE8();
extern void PSMTXRotRad();
extern void tan();
extern unsigned int lbl_806D786C;
extern unsigned int lbl_806D7870;
extern unsigned int lbl_806D7874;
extern unsigned int lbl_806D7878;
extern unsigned int lbl_806D787C;
extern unsigned int lbl_806D7880;
extern unsigned int lbl_806D7884;
extern unsigned int lbl_806D7888;
extern unsigned int lbl_80495994[];
extern unsigned int lbl_80495A94[];
extern void ResCtrl_Init();
extern void fn_8013D570();
extern void fn_8013D608();
extern void fn_8013D660();
extern void fn_80192688();
extern void fn_8019FE78();
extern void fn_8019FF8C();
extern unsigned int lbl_806D78A0;
extern unsigned int lbl_806D78A4;
extern unsigned int lbl_806D78A8;
extern unsigned int lbl_806D78AC;
extern unsigned int lbl_806D78B0;
extern unsigned int lbl_806D78B4;
extern unsigned int lbl_806D78B8;
extern unsigned int lbl_806D78BC;
extern unsigned int lbl_806D78C0;
extern unsigned int lbl_806D78C4;
extern unsigned int lbl_806D78C8;
extern unsigned int lbl_806D78CC;
extern unsigned int lbl_806D78D0;
extern unsigned int lbl_806D78D4;
extern unsigned int lbl_806D78D8;
extern unsigned int lbl_806D78DC;
extern unsigned int lbl_806D78E0;
extern unsigned int lbl_806D78E4;
extern unsigned int lbl_80360544[];
extern void dtor_80082960();
extern void Alloc();
extern void fn_8013D50C();
extern void fn_8013D800();
extern void fn_801D5C88();
extern unsigned int g_ccClass;
extern unsigned int g_roundIndex;
extern unsigned int lbl_806D78E8;
extern unsigned int lbl_806D78EC;
extern unsigned int lbl_806D78F0;
extern unsigned int lbl_806D78F4;
extern unsigned int lbl_806D78F8;
extern unsigned int g_playerData[];
extern unsigned int lbl_80360538[];
extern unsigned int lbl_8048EC50[];
extern void dtor_800869D0();
extern void dtor_8013EB50();
asm void fn_8014017C(void);
asm void fn_80140344(void);
asm void fn_80140A38(void);
asm void fn_80140FEC(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_8014017C[8] = {
    0x18, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80140344[8] = {
    0x19, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_80140A38 = { 0x204A0000, 0x000000E4, 0x00DE0010, 0x00000000, 0x82000034, (void *)&dtor_80082960 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; unsigned int f13; void *f14; unsigned int f15; unsigned int f16; void *f17; } extab_fn_80140FEC = { 0x280A0000, 0x0000005C, 0x0000003C, 0x0000008C, 0x006C0030, 0x00000268, 0x00000028, 0x0000027C, 0x00720030, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0780001B, 0x00000040, (void *)&dtor_800869D0, 0x8680001B, 0x00000000, (void *)&dtor_8013EB50 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014017C = {
    (void *)&fn_8014017C, 0x000001C8, (void *)extab_fn_8014017C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80140344 = {
    (void *)&fn_80140344, 0x000004CC, (void *)extab_fn_80140344
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80140A38 = {
    (void *)&fn_80140A38, 0x00000494, (void *)&extab_fn_80140A38
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80140FEC = {
    (void *)&fn_80140FEC, 0x00000464, (void *)&extab_fn_80140FEC
};

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
    addi r4, r2, -0x2A54  /* lbl_806D780C */
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
    addi r4, r2, -0x2A3C  /* lbl_806D7824 */
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

struct Confetti {
    unsigned char active;
    Mtx mtx;
    float rot[3];
    int color;
};

struct ConfettiField {
    int f0;
    int f4;
    float size;
    int count;
    float f10, f14, f18;
    Confetti *pieces;
    int timer;

    ConfettiField();
    ~ConfettiField();
};

extern "C" asm void fn_8014017C(void) { /* 0x8014017C size:0x1C8 */
    nofralloc
    stwu r1, -0x80(r1)
    mflr r0
    stw r0, 0x84(r1)
    stw r31, 0x7c(r1)
    stw r30, 0x78(r1)
    mr r30, r3
    stw r29, 0x74(r1)
    bl fn_8013BC98
    cmplwi r3, 0x0
    beq fn_8014017C_L_80140328
    bl fn_8013C3B8
    cmplwi r3, 0x0
    beq fn_8014017C_L_80140328
    bl fn_8013BC98
    bl fn_8013BC38
    clrlwi. r0, r3, 24
    beq fn_8014017C_L_80140328
    bl fn_8013C3B8
    bl fn_8013C34C
    bl fn_8013BC98
    bl fn_8013BBFC
    li r3, 0x0
    bl HSD_StateSetCullMode
    lis r4, 0x4000
    li r3, 0x0
    addi r4, r4, 0x2
    bl HSD_StateInitDirect
    bl HSD_CObjGetCurrent
    addi r4, r1, 0x3c
    bl fn_802C7D98
    li r3, 0x0
    bl GXSetCurrentMtx
    li r31, 0x0
    li r29, 0x0
    fn_8014017C_L_80140204:
    lwz r0, 0x1c(r30)
    add r4, r0, r29
    lbz r0, 0x0(r4)
    cmplwi r0, 0x0
    beq fn_8014017C_L_80140308
    addi r3, r1, 0x3c
    addi r4, r4, 0x4
    addi r5, r1, 0xc
    bl PSMTXConcat
    addi r3, r1, 0xc
    li r4, 0x0
    bl GXLoadPosMtxImm
    lwz r5, 0x1c(r30)
    addi r0, r29, 0x40
    lis r4, lbl_80360520@ha
    li r3, 0x80
    lwzx r0, r5, r0
    addi r6, r4, lbl_80360520@l
    li r4, 0x0
    li r5, 0x4
    slwi r0, r0, 2
    lwzx r0, r6, r0
    stw r0, 0x8(r1)
    bl GXBegin
    lfs f0, 0x8(r30)
    lis r5, 0xcc01
    lfs f1, lbl_806D7868(r2)
    fneg f0, f0
    lbz r6, 0x8(r1)
    lbz r4, 0x9(r1)
    lbz r3, 0xa(r1)
    stfs f0, -0x8000(r5)
    lbz r0, 0xb(r1)
    stfs f0, -0x8000(r5)
    stfs f1, -0x8000(r5)
    stb r6, -0x8000(r5)
    stb r4, -0x8000(r5)
    stb r3, -0x8000(r5)
    stb r0, -0x8000(r5)
    lfs f2, 0x8(r30)
    fneg f0, f2
    stfs f2, -0x8000(r5)
    stfs f0, -0x8000(r5)
    stfs f1, -0x8000(r5)
    stb r6, -0x8000(r5)
    stb r4, -0x8000(r5)
    stb r3, -0x8000(r5)
    stb r0, -0x8000(r5)
    lfs f0, 0x8(r30)
    stfs f0, -0x8000(r5)
    stfs f0, -0x8000(r5)
    stfs f1, -0x8000(r5)
    stb r6, -0x8000(r5)
    stb r4, -0x8000(r5)
    stb r3, -0x8000(r5)
    stb r0, -0x8000(r5)
    lfs f2, 0x8(r30)
    fneg f0, f2
    stfs f0, -0x8000(r5)
    stfs f2, -0x8000(r5)
    stfs f1, -0x8000(r5)
    stb r6, -0x8000(r5)
    stb r4, -0x8000(r5)
    stb r3, -0x8000(r5)
    stb r0, -0x8000(r5)
    fn_8014017C_L_80140308:
    addi r31, r31, 0x1
    addi r29, r29, 0x44
    cmpwi r31, 0x48
    blt fn_8014017C_L_80140204
    bl fn_8013C3B8
    bl fn_8013C334
    bl fn_8013BC98
    bl fn_8013BB9C
    fn_8014017C_L_80140328:
    lwz r0, 0x84(r1)
    lwz r31, 0x7c(r1)
    lwz r30, 0x78(r1)
    lwz r29, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x80
    blr
}

extern "C" asm void fn_80140344(void) { /* 0x80140344 size:0x4CC */
    nofralloc
    stwu r1, -0xb0(r1)
    mflr r0
    stw r0, 0xb4(r1)
    stfd f31, 0xa0(r1)
    psq_st f31, 0xa8(r1), 0, 0
    stfd f30, 0x90(r1)
    psq_st f30, 0x98(r1), 0, 0
    stfd f29, 0x80(r1)
    psq_st f29, 0x88(r1), 0, 0
    stfd f28, 0x70(r1)
    psq_st f28, 0x78(r1), 0, 0
    stw r31, 0x6c(r1)
    stw r30, 0x68(r1)
    stw r29, 0x64(r1)
    mr r29, r3
    bl fn_8013BC98
    cmplwi r3, 0x0
    beq fn_80140344_L_801407D4
    bl fn_8013C3B8
    cmplwi r3, 0x0
    beq fn_80140344_L_801407D4
    bl fn_8013BC98
    mr r30, r3
    bl fn_8013BAE8
    fmr f28, f1
    mr r3, r30
    bl fn_8013BA90
    lfs f0, lbl_806D786C(r2)
    fmuls f1, f0, f1
    bl tan
    lwz r3, 0x20(r29)
    frsp f31, f1
    cmpwi r3, 0x0
    beq fn_80140344_L_801403D4
    subi r0, r3, 0x1
    stw r0, 0x20(r29)
    fn_80140344_L_801403D4:
    fmuls f30, f31, f28
    li r30, 0x0
    li r31, 0x0
    fn_80140344_L_801403E0:
    lwz r0, 0x1c(r29)
    add r5, r0, r31
    lbz r0, 0x0(r5)
    cmplwi r0, 0x0
    beq fn_80140344_L_801405CC
    lfs f2, 0x30(r5)
    addi r3, r1, 0x20
    lfs f1, 0x10(r29)
    li r4, 0x58
    lfs f0, 0x34(r5)
    fmuls f29, f31, f2
    fmuls f1, f1, f0
    bl PSMTXRotRad
    lwz r0, 0x1c(r29)
    addi r3, r31, 0x4
    addi r4, r1, 0x20
    add r3, r0, r3
    mr r5, r3
    bl PSMTXConcat
    lwz r4, 0x1c(r29)
    addi r0, r31, 0x38
    lfs f1, 0x10(r29)
    addi r3, r1, 0x20
    lfsx f0, r4, r0
    li r4, 0x59
    fmuls f1, f1, f0
    bl PSMTXRotRad
    lwz r0, 0x1c(r29)
    addi r3, r31, 0x4
    addi r4, r1, 0x20
    add r3, r0, r3
    mr r5, r3
    bl PSMTXConcat
    lwz r4, 0x1c(r29)
    addi r0, r31, 0x3c
    lfs f1, 0x10(r29)
    addi r3, r1, 0x20
    lfsx f0, r4, r0
    li r4, 0x5a
    fmuls f1, f1, f0
    bl PSMTXRotRad
    lwz r0, 0x1c(r29)
    addi r3, r31, 0x4
    addi r4, r1, 0x20
    add r3, r0, r3
    mr r5, r3
    bl PSMTXConcat
    lfs f1, lbl_806D7868(r2)
    addi r6, r31, 0xc
    lfs f0, lbl_806D7870(r2)
    addi r5, r31, 0x1c
    stfs f1, 0x8(r1)
    addi r0, r31, 0x2c
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    stfs f0, 0xc(r1)
    stfs f1, 0x10(r1)
    lwz r7, 0x1c(r29)
    lfsx f0, r7, r6
    stfs f0, 0x14(r1)
    lfsx f0, r7, r5
    stfs f0, 0x18(r1)
    lfsx f0, r7, r0
    stfs f0, 0x1c(r1)
    bl Vec3_Dot
    lfs f0, lbl_806D7868(r2)
    lfs f4, 0x18(r29)
    fcmpo cr0, f1, f0
    lfs f3, lbl_806D7874(r2)
    lfs f2, lbl_806D7878(r2)
    bge fn_80140344_L_80140500
    fneg f1, f1
    fn_80140344_L_80140500:
    fsubs f1, f2, f1
    lwz r8, 0x1c(r29)
    addi r7, r31, 0x20
    addi r6, r31, 0x4
    lfsx f0, r8, r7
    addi r5, r31, 0x14
    fadds f1, f3, f1
    addi r0, r31, 0x24
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    fnmsubs f0, f4, f1, f0
    stfsx f0, r8, r7
    lwz r7, 0x1c(r29)
    lfsx f0, r7, r6
    stfs f0, 0x14(r1)
    lfsx f0, r7, r5
    stfs f0, 0x18(r1)
    lfsx f0, r7, r0
    stfs f0, 0x1c(r1)
    bl Vec3_Dot
    lwz r6, 0x1c(r29)
    addi r3, r31, 0x8
    addi r5, r31, 0x18
    addi r0, r31, 0x28
    lfsx f0, r6, r3
    fmr f28, f1
    addi r3, r1, 0x14
    addi r4, r1, 0x8
    stfs f0, 0x14(r1)
    lfsx f0, r6, r5
    stfs f0, 0x18(r1)
    lfsx f0, r6, r0
    stfs f0, 0x1c(r1)
    bl Vec3_Dot
    lwz r3, 0x1c(r29)
    addi r0, r31, 0x10
    fmuls f2, f28, f1
    lfs f1, 0x14(r29)
    lfsx f0, r3, r0
    fnmsubs f0, f1, f2, f0
    stfsx f0, r3, r0
    lwz r0, 0x1c(r29)
    lfs f0, 0x8(r29)
    add r3, r0, r31
    fsubs f0, f29, f0
    lfs f1, 0x20(r3)
    fcmpo cr0, f1, f0
    bge fn_80140344_L_801407C4
    li r0, 0x0
    stb r0, 0x0(r3)
    b fn_80140344_L_801407C4
    fn_80140344_L_801405CC:
    lwz r0, 0x20(r29)
    cmpwi r0, 0x0
    bne fn_80140344_L_801407C4
    li r0, 0x1
    addi r3, r31, 0x4
    stb r0, 0x0(r5)
    lwz r0, 0x1c(r29)
    add r3, r0, r3
    bl PSMTXIdentity
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x4(r29)
    blt fn_80140344_L_8014060C
    li r0, 0x0
    stw r0, 0x4(r29)
    fn_80140344_L_8014060C:
    lwz r0, 0x4(r29)
    lis r3, lbl_80495A94@ha
    addi r3, r3, lbl_80495A94@l
    lfs f2, lbl_806D7880(r2)
    slwi r0, r0, 2
    lfs f0, lbl_806D787C(r2)
    lfsx f1, r3, r0
    addi r0, r31, 0x30
    lwz r3, 0x1c(r29)
    fmadds f0, f2, f1, f0
    stfsx f0, r3, r0
    lwz r4, 0x1c(r29)
    lwz r3, 0x0(r29)
    lfsx f0, r4, r0
    addi r0, r3, 0x1
    fneg f0, f0
    cmpwi r0, 0x40
    stw r0, 0x0(r29)
    fmuls f1, f0, f30
    fmuls f2, f31, f0
    fneg f3, f1
    fsubs f4, f1, f3
    blt fn_80140344_L_80140670
    li r0, 0x0
    stw r0, 0x0(r29)
    fn_80140344_L_80140670:
    lwz r0, 0x0(r29)
    lis r4, lbl_80495994@ha
    lis r3, 0x2aab
    lfs f0, lbl_806D7884(r2)
    slwi r0, r0, 2
    addi r4, r4, lbl_80495994@l
    lfsx f1, r4, r0
    addi r5, r31, 0x10
    lwz r6, 0x1c(r29)
    subi r3, r3, 0x5555
    fmuls f0, f0, f1
    addi r4, r31, 0x20
    fmadds f1, f4, f1, f3
    addi r0, r31, 0x40
    fctiwz f0, f0
    stfsx f1, r6, r5
    stfd f0, 0x50(r1)
    lfs f0, 0x8(r29)
    lwz r6, 0x54(r1)
    fsubs f0, f2, f0
    lwz r7, 0x1c(r29)
    mulhw r5, r3, r6
    stfsx f0, r7, r4
    lwz r3, 0x1c(r29)
    srwi r4, r5, 31
    add r4, r5, r4
    mulli r4, r4, 0x6
    subf r4, r4, r6
    stwx r4, r3, r0
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x4(r29)
    blt fn_80140344_L_80140700
    li r0, 0x0
    stw r0, 0x4(r29)
    fn_80140344_L_80140700:
    lwz r0, 0x4(r29)
    lis r3, lbl_80495A94@ha
    addi r3, r3, lbl_80495A94@l
    lfs f2, lbl_806D7888(r2)
    slwi r0, r0, 2
    lfs f0, lbl_806D7878(r2)
    lfsx f1, r3, r0
    addi r0, r31, 0x34
    lwz r3, 0x1c(r29)
    fmsubs f0, f2, f1, f0
    stfsx f0, r3, r0
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x4(r29)
    blt fn_80140344_L_80140748
    li r0, 0x0
    stw r0, 0x4(r29)
    fn_80140344_L_80140748:
    lwz r0, 0x4(r29)
    lis r3, lbl_80495A94@ha
    addi r3, r3, lbl_80495A94@l
    lfs f2, lbl_806D7888(r2)
    slwi r0, r0, 2
    lfs f0, lbl_806D7878(r2)
    lfsx f1, r3, r0
    addi r0, r31, 0x38
    lwz r3, 0x1c(r29)
    fmsubs f0, f2, f1, f0
    stfsx f0, r3, r0
    lwz r3, 0x4(r29)
    addi r0, r3, 0x1
    cmpwi r0, 0x30
    stw r0, 0x4(r29)
    blt fn_80140344_L_80140790
    li r0, 0x0
    stw r0, 0x4(r29)
    fn_80140344_L_80140790:
    lwz r0, 0x4(r29)
    lis r3, lbl_80495A94@ha
    addi r3, r3, lbl_80495A94@l
    lfs f2, lbl_806D7888(r2)
    slwi r0, r0, 2
    lfs f0, lbl_806D7878(r2)
    lfsx f1, r3, r0
    addi r0, r31, 0x3c
    lwz r3, 0x1c(r29)
    fmsubs f0, f2, f1, f0
    stfsx f0, r3, r0
    lwz r0, 0xc(r29)
    stw r0, 0x20(r29)
    fn_80140344_L_801407C4:
    addi r30, r30, 0x1
    addi r31, r31, 0x44
    cmpwi r30, 0x48
    blt fn_80140344_L_801403E0
    fn_80140344_L_801407D4:
    psq_l f31, 0xa8(r1), 0, 0
    lfd f31, 0xa0(r1)
    psq_l f30, 0x98(r1), 0, 0
    lfd f30, 0x90(r1)
    psq_l f29, 0x88(r1), 0, 0
    lfd f29, 0x80(r1)
    psq_l f28, 0x78(r1), 0, 0
    lfd f28, 0x70(r1)
    lwz r31, 0x6c(r1)
    lwz r30, 0x68(r1)
    lwz r0, 0xb4(r1)
    lwz r29, 0x64(r1)
    mtlr r0
    addi r1, r1, 0xb0
    blr
}

ConfettiField::~ConfettiField() {
    if (pieces) {
        MemoryManager_Free(pieces);
    }
    fn_8013BCA0();
    fn_8013C3C0();
}

ConfettiField::ConfettiField() {
    int i;

    fn_8013BD7C();
    fn_8013C428();
    size = lbl_806D788C;
    count = 10;
    f10 = lbl_806D7890;
    f14 = lbl_806D7894;
    f18 = lbl_806D7898;
    pieces = (Confetti *)FUN_8003b120(72 * sizeof(Confetti));
    for (i = 0; i < 72; i++) {
        pieces[i].active = 0;
    }
    timer = 0;
    f0 = 0;
    f4 = 0;
}

struct ResultFx : FxBase {
    int state;
    float t;
    int f20;
    int f24;
    int f28;
    Handle *handle;
    unsigned char flags[8];
    int f38;
    int f3C;
    TexMgr tm;
    void *anims[5];

    virtual void m0C();
    void Stop();
    virtual void Draw();
    unsigned char IsDone();
    virtual ~ResultFx();
};

void ResultFx::Stop() {
    if (state >= 0 && state != 6 && state >= 2 && state < 4) {
        handle->Stop();
    }
}

void ResultFx::Draw() {
    int i;

    handle->Stop();
    for (i = 0; i < 5; i++) {
        if (anims[i]) {
            fn_801A0004(*(void **)anims[i]);
        }
    }
    fn_801F8A34(fn_801F8E58(), &tm, 4);
}

extern "C" asm void fn_80140A38(void) { /* 0x80140A38 size:0x494 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stw r31, 0xac(r1)
    stw r30, 0xa8(r1)
    stw r29, 0xa4(r1)
    stw r28, 0xa0(r1)
    mr r31, r3
    lwz r0, 0x18(r3)
    cmpwi r0, 0x0
    blt fn_80140A38_L_80140EA4
    addi r3, r1, 0x34
    bl ResCtrl_Init
    lwz r0, 0x18(r31)
    cmpwi r0, 0x2
    beq fn_80140A38_L_80140BC8
    bge fn_80140A38_L_80140A94
    cmpwi r0, 0x0
    beq fn_80140A38_L_80140AA4
    bge fn_80140A38_L_80140B84
    b fn_80140A38_L_80140E28
    fn_80140A38_L_80140A94:
    cmpwi r0, 0x4
    beq fn_80140A38_L_80140D60
    bge fn_80140A38_L_80140E28
    b fn_80140A38_L_80140CFC
    fn_80140A38_L_80140AA4:
    lfs f2, 0x1c(r31)
    lfs f0, lbl_806D78A0(r2)
    fcmpo cr0, f2, f0
    cror eq, lt, eq
    bne fn_80140A38_L_80140AE0
    fdivs f2, f2, f0
    lwz r0, 0x24(r31)
    lis r3, lbl_80360544@ha
    lfs f1, lbl_806D78A4(r2)
    slwi r0, r0, 2
    addi r3, r3, lbl_80360544@l
    lfsx f0, r3, r0
    fmuls f0, f1, f0
    fmuls f1, f2, f0
    b fn_80140A38_L_80140B0C
    fn_80140A38_L_80140AE0:
    lwz r0, 0x24(r31)
    lis r3, lbl_80360544@ha
    addi r3, r3, lbl_80360544@l
    lfs f1, lbl_806D78A8(r2)
    slwi r0, r0, 2
    fsubs f2, f2, f0
    lfsx f3, r3, r0
    lfs f0, lbl_806D78AC(r2)
    fmuls f1, f1, f3
    fmuls f1, f2, f1
    fmadds f1, f1, f0, f3
    fn_80140A38_L_80140B0C:
    fmr f2, f1
    lwz r3, 0x2c(r31)
    fmr f3, f1
    bl fn_8013D608
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D78B0(r2)
    lfs f0, lbl_806D78B4(r2)
    fdivs f2, f2, f1
    fmuls f0, f0, f2
    fctiwz f0, f0
    stfd f0, 0x90(r1)
    lwz r0, 0x94(r1)
    clrlwi r0, r0, 24
    oris r0, r0, 0xe0e0
    ori r0, r0, 0x2000
    stw r0, 0x60(r31)
    lwz r3, 0x27c(r31)
    lwz r3, 0x0(r3)
    stfs f2, 0x20(r3)
    lwz r3, 0x280(r31)
    lwz r3, 0x0(r3)
    stfs f2, 0x20(r3)
    lfs f0, 0x1c(r31)
    fcmpu cr0, f1, f0
    bne fn_80140A38_L_80140E28
    li r0, 0x1
    lfs f0, lbl_806D78B8(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    b fn_80140A38_L_80140E28
    fn_80140A38_L_80140B84:
    lfs f1, lbl_806D78C0(r2)
    lfs f0, 0x1c(r31)
    lfs f2, lbl_806D78BC(r2)
    fmuls f0, f1, f0
    lwz r3, 0x2c(r31)
    fmuls f1, f2, f0
    bl fn_8013D570
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D78C4(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80140A38_L_80140E28
    li r0, 0x2
    lfs f0, lbl_806D78B8(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    b fn_80140A38_L_80140E28
    fn_80140A38_L_80140BC8:
    lwz r5, 0x24(r31)
    lis r3, lbl_803606E4@ha
    lwz r0, 0x3c(r31)
    addi r4, r3, lbl_803606E4@l
    mulli r6, r5, 0xc
    lwz r3, 0x274(r31)
    slwi r0, r0, 2
    lwz r3, 0x0(r3)
    addi r5, r1, 0x8
    add r4, r4, r6
    lwzx r0, r4, r0
    extsh r4, r0
    bl fn_8019FF8C
    lfs f1, 0x1c(r31)
    lis r3, lbl_80360544@ha
    lfs f0, lbl_806D78C8(r2)
    addi r3, r3, lbl_80360544@l
    lwz r0, 0x24(r31)
    fdivs f6, f1, f0
    lfs f4, lbl_806D78CC(r2)
    lfs f1, 0xc(r1)
    slwi r0, r0, 2
    lfs f3, lbl_806D78D0(r2)
    lfs f0, 0x8(r1)
    fsubs f2, f1, f3
    lfs f1, lbl_806D78D4(r2)
    fsubs f5, f4, f6
    lfsx f4, r3, r0
    fsubs f0, f0, f1
    lwz r3, 0x2c(r31)
    fmadds f2, f2, f6, f3
    fmuls f31, f5, f4
    fmadds f1, f0, f6, f1
    bl fn_8013D660
    fmr f1, f31
    lwz r3, 0x2c(r31)
    fmr f2, f31
    fmr f3, f31
    bl fn_8013D608
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D78C8(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80140A38_L_80140E28
    li r0, 0x3
    lfs f0, lbl_806D78B8(r2)
    stw r0, 0x18(r31)
    addi r3, r31, 0x278
    addi r4, r13, -0x7668  /* lbl_806CF6B8 */
    li r5, 0x0
    stfs f0, 0x1c(r31)
    lfs f1, 0x8(r1)
    lfs f2, 0xc(r1)
    bl SpriteGroup_CreateOrInit
    lwz r4, 0x24(r31)
    lis r3, lbl_803606E4@ha
    lwz r0, 0x3c(r31)
    addi r5, r3, lbl_803606E4@l
    mulli r6, r4, 0xc
    lwz r3, 0x278(r31)
    slwi r0, r0, 2
    li r4, 0x1ea2
    add r5, r5, r6
    lwzx r5, r5, r0
    bl SpriteAnimParamBlock_SetAnimParamCached
    lwz r4, 0x24(r31)
    lis r3, lbl_803606E4@ha
    lwz r0, 0x38(r31)
    addi r5, r3, lbl_803606E4@l
    mulli r6, r4, 0xc
    lwz r3, 0x278(r31)
    slwi r0, r0, 2
    li r4, 0x1eaa
    add r5, r5, r6
    lwzx r5, r5, r0
    bl SpriteAnimParamBlock_SetAnimParamCached
    b fn_80140A38_L_80140E28
    fn_80140A38_L_80140CFC:
    lwz r3, 0x278(r31)
    lwz r3, 0x0(r3)
    bl fn_8019FE78
    clrlwi. r0, r3, 24
    bne fn_80140A38_L_80140E28
    lwz r0, 0x24(r31)
    lis r4, lbl_803606E4@ha
    lwz r3, 0x3c(r31)
    addi r5, r4, lbl_803606E4@l
    mulli r6, r0, 0xc
    lwz r0, 0x38(r31)
    slwi r4, r3, 2
    lwz r3, 0x274(r31)
    slwi r0, r0, 2
    add r5, r5, r6
    lwzx r4, r5, r4
    lwzx r5, r5, r0
    bl SpriteAnimParamBlock_SetAnimParamCached
    lfs f0, lbl_806D78B8(r2)
    li r0, 0x4
    stfs f0, 0x1c(r31)
    stw r0, 0x18(r31)
    lwz r3, 0x278(r31)
    bl fn_8023F1C8
    b fn_80140A38_L_80140E28
    fn_80140A38_L_80140D60:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D78D8(r2)
    fcmpo cr0, f1, f0
    ble fn_80140A38_L_80140DD8
    fsubs f1, f1, f0
    lfs f0, lbl_806D78DC(r2)
    lwz r3, 0x274(r31)
    lfs f2, lbl_806D78CC(r2)
    fdivs f1, f1, f0
    lwz r3, 0x0(r3)
    lfs f0, lbl_806D78B4(r2)
    fsubs f1, f2, f1
    stfs f1, 0x20(r3)
    fmuls f0, f0, f1
    lwz r3, 0x270(r31)
    fctiwz f0, f0
    lwz r3, 0x0(r3)
    stfs f1, 0x20(r3)
    lwz r3, 0x280(r31)
    stfd f0, 0x90(r1)
    lwz r3, 0x0(r3)
    lwz r0, 0x94(r1)
    stfs f1, 0x20(r3)
    clrlwi r0, r0, 24
    lwz r3, 0x27c(r31)
    oris r0, r0, 0xe0e0
    ori r0, r0, 0x2000
    lwz r3, 0x0(r3)
    stfs f1, 0x20(r3)
    stw r0, 0x60(r31)
    fn_80140A38_L_80140DD8:
    lfs f1, 0x1c(r31)
    lfs f0, lbl_806D78E0(r2)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne fn_80140A38_L_80140E28
    mr r29, r31
    li r28, 0x0
    li r30, 0x0
    fn_80140A38_L_80140DF8:
    lwz r3, 0x270(r29)
    cmplwi r3, 0x0
    beq fn_80140A38_L_80140E10
    li r4, 0x1
    bl SpriteAnimHandle_Destroy
    stw r30, 0x270(r29)
    fn_80140A38_L_80140E10:
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x5
    blt fn_80140A38_L_80140DF8
    li r0, -0x1
    stw r0, 0x18(r31)
    fn_80140A38_L_80140E28:
    lbz r0, 0x28(r31)
    cmplwi r0, 0x0
    bne fn_80140A38_L_80140E64
    li r3, 0x1f
    bl fn_80192010
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne fn_80140A38_L_80140E54
    li r3, 0x1f
    li r4, 0x1
    bl fn_80192688
    fn_80140A38_L_80140E54:
    li r3, 0x23
    bl SoundMgr_Play
    li r0, 0x1
    stb r0, 0x28(r31)
    fn_80140A38_L_80140E64:
    lfs f1, 0x1c(r31)
    mr r29, r31
    lfs f0, lbl_806D78CC(r2)
    li r28, 0x0
    fadds f0, f1, f0
    stfs f0, 0x1c(r31)
    fn_80140A38_L_80140E7C:
    lwz r3, 0x270(r29)
    cmplwi r3, 0x0
    beq fn_80140A38_L_80140E94
    lwz r3, 0x0(r3)
    lfs f1, lbl_806D78E4(r2)
    bl Sprite_AdvanceAnim
    fn_80140A38_L_80140E94:
    addi r28, r28, 0x1
    addi r29, r29, 0x4
    cmpwi r28, 0x5
    blt fn_80140A38_L_80140E7C
    fn_80140A38_L_80140EA4:
    psq_l f31, 0xb8(r1), 0, 0
    lwz r0, 0xc4(r1)
    lfd f31, 0xb0(r1)
    lwz r31, 0xac(r1)
    lwz r30, 0xa8(r1)
    lwz r29, 0xa4(r1)
    lwz r28, 0xa0(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

unsigned char ResultFx::IsDone() {
    if (state < 0 || state == 6) {
        return 1;
    }
    return 0;
}

ResultFx::~ResultFx() {
    int i;

    if (handle) {
        delete handle;
    }
    for (i = 0; i < 8; i++) {
        fn_80120A08(lbl_803606C4[i]);
        fn_80120A08(lbl_803606E4[i][0]);
        fn_80120A08(lbl_803606E4[i][1]);
    }
    for (int j = 0; j < 5; j++) {
        if (anims[j]) {
            SpriteAnimHandle_Destroy(anims[j], 1);
            anims[j] = 0;
        }
    }
}

extern "C" asm void fn_80140FEC(void) { /* 0x80140FEC size:0x464 */
    nofralloc
    stwu r1, -0x50(r1)
    mflr r0
    lis r4, lbl_8048EB44@ha
    lfs f1, lbl_806D78B8(r2)
    stw r0, 0x54(r1)
    addi r0, r4, lbl_8048EB44@l
    li r4, 0x0
    lfs f0, lbl_806D78CC(r2)
    stmw r27, 0x3c(r1)
    mr r27, r3
    lis r5, lbl_80360538@ha
    lis r3, lbl_8048EC9C@ha
    addi r31, r5, lbl_80360538@l
    stw r0, 0x14(r27)
    addi r0, r3, lbl_8048EC9C@l
    addi r3, r27, 0x40
    stw r4, 0x0(r27)
    stb r4, 0x4(r27)
    stfs f1, 0x8(r27)
    stfs f1, 0xc(r27)
    stfs f0, 0x10(r27)
    stw r0, 0x14(r27)
    bl TexMgr_Init
    li r0, -0x1
    lis r3, g_playerData@ha
    stw r0, 0x18(r27)
    addi r3, r3, g_playerData@l
    lfs f0, lbl_806D78B8(r2)
    stfs f0, 0x1c(r27)
    stw r0, 0x20(r27)
    stw r0, 0x24(r27)
    lwz r30, g_ccClass(r13)
    lwz r29, g_cupId(r13)
    mr r4, r30
    bl fn_801D5C88
    clrlwi r3, r3, 24
    lwz r0, g_roundIndex(r13)
    subfic r3, r3, 0x1
    cntlzw r3, r3
    cmpwi r0, 0x3
    srwi r0, r3, 5
    mr r28, r0
    bgt fn_80140FEC_L_8014109C
    li r28, 0x0
    fn_80140FEC_L_8014109C:
    cmpwi r28, 0x1
    bne fn_80140FEC_L_801410B8
    li r3, 0x0
    li r0, 0x2
    stw r3, 0x3c(r27)
    stw r0, 0x38(r27)
    b fn_80140FEC_L_801410C8
    fn_80140FEC_L_801410B8:
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x3c(r27)
    stw r0, 0x38(r27)
    fn_80140FEC_L_801410C8:
    subic. r0, r29, 0x1
    blt fn_80140FEC_L_801410DC
    subi r0, r29, 0x1
    cmpwi r0, 0x8
    blt fn_80140FEC_L_801410E4
    fn_80140FEC_L_801410DC:
    mr r3, r27
    b fn_80140FEC_L_8014143C
    fn_80140FEC_L_801410E4:
    addi r0, r29, 0x9a4
    cmpwi r28, 0x1
    stw r0, 0x20(r27)
    li r7, 0x4
    bne fn_80140FEC_L_801410FC
    li r7, 0x9
    fn_80140FEC_L_801410FC:
    lis r3, g_playerData@ha
    slwi r4, r30, 3
    addi r3, r3, g_playerData@l
    li r0, 0x2
    addi r8, r31, 0x2c
    srwi r5, r7, 31
    add r9, r3, r4
    subi r3, r29, 0x1
    li r10, 0x0
    mtctr r0
    fn_80140FEC_L_80141124:
    lwz r4, 0x0(r8)
    addi r0, r10, 0x30
    subi r6, r4, 0x1
    addi r4, r6, 0x1ba
    lbzx r4, r9, r4
    cmpw r6, r3
    srawi r6, r4, 31
    subfc r4, r7, r4
    adde r4, r6, r5
    stbx r4, r27, r0
    bne fn_80140FEC_L_80141154
    stw r10, 0x24(r27)
    fn_80140FEC_L_80141154:
    lwzu r4, 0x4(r8)
    addi r0, r10, 0x31
    addi r10, r10, 0x1
    subi r6, r4, 0x1
    addi r4, r6, 0x1ba
    lbzx r4, r9, r4
    cmpw r6, r3
    srawi r6, r4, 31
    subfc r4, r7, r4
    adde r4, r6, r5
    stbx r4, r27, r0
    bne fn_80140FEC_L_80141188
    stw r10, 0x24(r27)
    fn_80140FEC_L_80141188:
    lwzu r4, 0x4(r8)
    addi r0, r10, 0x31
    addi r10, r10, 0x1
    subi r6, r4, 0x1
    addi r4, r6, 0x1ba
    lbzx r4, r9, r4
    cmpw r6, r3
    srawi r6, r4, 31
    subfc r4, r7, r4
    adde r4, r6, r5
    stbx r4, r27, r0
    bne fn_80140FEC_L_801411BC
    stw r10, 0x24(r27)
    fn_80140FEC_L_801411BC:
    lwzu r4, 0x4(r8)
    addi r0, r10, 0x31
    addi r10, r10, 0x1
    subi r6, r4, 0x1
    addi r4, r6, 0x1ba
    lbzx r4, r9, r4
    cmpw r6, r3
    srawi r6, r4, 31
    subfc r4, r7, r4
    adde r4, r6, r5
    stbx r4, r27, r0
    bne fn_80140FEC_L_801411F0
    stw r10, 0x24(r27)
    fn_80140FEC_L_801411F0:
    addi r8, r8, 0x4
    addi r10, r10, 0x1
    bdnz fn_80140FEC_L_80141124
    lwz r0, 0x24(r27)
    li r4, 0x0
    add r3, r27, r0
    stb r4, 0x30(r3)
    lwz r0, 0x24(r27)
    cmpwi r0, 0x0
    bge fn_80140FEC_L_80141220
    mr r3, r27
    b fn_80140FEC_L_8014143C
    fn_80140FEC_L_80141220:
    li r3, 0x20
    bl Alloc
    mr. r29, r3
    beq fn_80140FEC_L_80141254
    lwz r5, 0x24(r27)
    lis r4, lbl_8048EC50@ha
    addi r4, r4, lbl_8048EC50@l
    slwi r0, r28, 2
    slwi r6, r5, 3
    li r5, 0x1
    add r4, r4, r6
    lwzx r4, r4, r0
    bl fn_8013D800
    fn_80140FEC_L_80141254:
    stw r29, 0x2c(r27)
    lfs f1, lbl_806D78D4(r2)
    lwz r3, 0x2c(r27)
    lfs f2, lbl_806D78D0(r2)
    bl fn_8013D660
    lfs f1, lbl_806D78B8(r2)
    lwz r3, 0x2c(r27)
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lfs f1, lbl_806D78E8(r2)
    lwz r3, 0x2c(r27)
    fmr f2, f1
    lfs f4, lbl_806D78CC(r2)
    fmr f3, f1
    bl fn_8013D50C
    li r0, 0x0
    lfs f0, lbl_806D78B8(r2)
    stw r0, 0x18(r27)
    addi r3, r27, 0x270
    lfs f1, lbl_806D78D4(r2)
    addi r4, r13, -0x7678  /* lbl_806CF6A8 */
    stfs f0, 0x1c(r27)
    li r5, 0x0
    lfs f2, lbl_806D78EC(r2)
    stw r0, 0x270(r27)
    stw r0, 0x274(r27)
    stw r0, 0x278(r27)
    stw r0, 0x27c(r27)
    stw r0, 0x280(r27)
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D78D4(r2)
    addi r3, r27, 0x274
    lfs f2, lbl_806D78F0(r2)
    addi r4, r13, -0x7674  /* lbl_806CF6AC */
    li r5, 0x0
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D78D4(r2)
    addi r3, r27, 0x27c
    lfs f2, lbl_806D78EC(r2)
    addi r4, r13, -0x7670  /* lbl_806CF6B0 */
    li r5, 0x1
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D78D4(r2)
    addi r3, r27, 0x280
    lfs f2, lbl_806D78F0(r2)
    addi r4, r13, -0x766C  /* lbl_806CF6B4 */
    li r5, 0x1
    bl SpriteGroup_CreateOrInit
    lwz r0, 0x24(r27)
    addi r5, r31, 0x18c
    lwz r3, 0x270(r27)
    li r4, 0x1529
    slwi r0, r0, 2
    lwzx r5, r5, r0
    bl SpriteAnimParamBlock_SetAnimParamCached
    lwz r3, 0x27c(r27)
    addi r4, r31, 0x1ac
    lfs f0, lbl_806D78B8(r2)
    addi r5, r1, 0x8
    lwz r3, 0x0(r3)
    stfs f0, 0x20(r3)
    lwz r3, 0x280(r27)
    lwz r3, 0x0(r3)
    stfs f0, 0x20(r3)
    lwz r3, 0x24(r27)
    lwz r0, 0x3c(r27)
    mulli r6, r3, 0xc
    lwz r3, 0x274(r27)
    slwi r0, r0, 2
    lwz r3, 0x0(r3)
    add r0, r6, r0
    lwzx r0, r4, r0
    extsh r4, r0
    bl fn_8019FF8C
    li r29, 0x0
    addi r28, r31, 0x1ac
    fn_80140FEC_L_80141388:
    addi r0, r29, 0x30
    lbzx r0, r27, r0
    cmplwi r0, 0x1
    bne fn_80140FEC_L_801413B0
    lwz r0, 0x38(r27)
    lwz r3, 0x274(r27)
    slwi r0, r0, 2
    lwz r4, 0x0(r28)
    lwzx r5, r28, r0
    bl SpriteAnimParamBlock_SetAnimParamCached
    fn_80140FEC_L_801413B0:
    addi r29, r29, 0x1
    addi r28, r28, 0xc
    cmpwi r29, 0x8
    blt fn_80140FEC_L_80141388
    li r0, 0x1
    addi r3, r27, 0x40
    stw r0, 0x58(r27)
    li r4, 0x1
    bl fn_801F8FCC
    lfs f0, lbl_806D78F4(r2)
    lis r3, 0xe0e0
    addi r0, r3, 0x2000
    lfs f1, lbl_806D78D4(r2)
    stfs f0, 0x26c(r27)
    addi r3, r27, 0x40
    lfs f2, lbl_806D78F8(r2)
    stw r0, 0x60(r27)
    bl fn_801F93EC
    lwz r3, g_cupId(r13)
    li r4, -0x1
    bl fn_8013C198
    mr r28, r3
    li r3, 0x5c
    li r4, -0x1
    bl GetTextureByIdAndLang
    mr r4, r3
    mr r5, r28
    addi r3, r27, 0x40
    crxor 6, 6, 6
    bl TexMgr_SetTexture
    addi r3, r27, 0x40
    bl fn_801F8E90
    li r0, 0x0
    mr r3, r27
    stb r0, 0x28(r27)
    fn_80140FEC_L_8014143C:
    lmw r27, 0x3c(r1)
    lwz r0, 0x54(r1)
    mtlr r0
    addi r1, r1, 0x50
    blr
}

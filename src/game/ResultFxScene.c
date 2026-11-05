/* sdata symbols referenced from asm */
extern unsigned char lbl_806CF6A8[4];
extern unsigned char lbl_806CF6AC[4];
extern unsigned char lbl_806CF6B0[4];
extern unsigned char lbl_806CF6B4[4];
extern char lbl_806CF6B8[4];
/*
 * Result effect scene on the shared sprite-effect base (vtable
 * lbl_8048EC9C): trophy model zoom/spin, cup sprites and the caption
 * text. The base declares a virtual that is not defined here first, so no
 * vtable is emitted.
 *
 * Still asm: the scene ctor. It reaches the cup tables through one pooled
 * .rodata base (lbl_80360538 + 0x2C/0x18C/0x1AC), i.e. the tables were
 * file-static data of this unit; that rodata is not owned here.
 */
#pragma cplusplus on

typedef float Mtx[3][4];
struct SpritePos {
    float x, y;
    float rest[9];
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
}

extern "C" {
extern void ResCtrl_Init();
extern void fn_8013D570(void *h, float rot);
extern void fn_8013D608(void *h, float sx, float sy, float sz);
extern void fn_8013D660(void *h, float x, float y);
extern void fn_80192688(int id, int on);
extern unsigned char fn_8019FE78(void *spr);
extern void fn_8019FF8C(void *spr, short id, struct SpritePos *out);
extern float lbl_80360544[];
extern const float lbl_806D78B8, lbl_806D78CC, lbl_806D78D0, lbl_806D78D4;
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
asm void fn_80140FEC(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; unsigned int f13; void *f14; unsigned int f15; unsigned int f16; void *f17; } extab_fn_80140FEC = { 0x280A0000, 0x0000005C, 0x0000003C, 0x0000008C, 0x006C0030, 0x00000268, 0x00000028, 0x0000027C, 0x00720030, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x0780001B, 0x00000040, (void *)&dtor_800869D0, 0x8680001B, 0x00000000, (void *)&dtor_8013EB50 };

#pragma section R ".extabindex_user"
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

static inline float Lerp(float a, float b, float cur, float end) {
    return (b - a) * (cur / end) + a;
}

struct ResultFx : FxBase {
    int state;
    float t;
    int f20;
    int f24;
    unsigned char bgmStarted;
    Handle *handle;
    unsigned char flags[8];
    int f38;
    int f3C;
    TexMgr tm;
    void *anims[5];

    virtual void m0C();
    void Stop();
    virtual void Draw();
    virtual void Update();
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

void ResultFx::Update() {
    SpritePos pos;
    float u;
    float s;
    float sc;
    int i;

    if (state < 0) {
        return;
    }
    ResCtrl rc;
    switch (state) {
    case 0:
        if (t <= 18.0f) {
            s = (t / 18.0f) * (1.1f * lbl_80360544[f24]);
        } else {
            s = (t - 18.0f) * (0.1f * lbl_80360544[f24]) / 4.0f + lbl_80360544[f24];
        }
        fn_8013D608(handle, s, s, s);
        u = t / 22.0f;
        tm.color = ((int)(255.0f * u) & 0xFF) | 0xE0E02000;
        ((SpriteRef *)anims[3])->spr->t = u;
        ((SpriteRef *)anims[4])->spr->t = u;
        if (22.0f == t) {
            state = 1;
            t = 0.0f;
        }
        break;
    case 1:
        fn_8013D570(handle, 0.017453292f * (3.0f * t));
        if (t >= 360.0f) {
            state = 2;
            t = 0.0f;
        }
        break;
    case 2:
        fn_8019FF8C(*(void **)anims[1], lbl_803606E4[f24][f3C], &pos);
        sc = (1.0f - t / 30.0f) * lbl_80360544[f24];
        fn_8013D660(handle, Lerp(320.0f, pos.x, t, 30.0f), Lerp(300.0f, pos.y, t, 30.0f));
        fn_8013D608(handle, sc, sc, sc);
        if (t >= 30.0f) {
            state = 3;
            t = 0.0f;
            SpriteGroup_CreateOrInit(&anims[2], lbl_806CF6B8, 0, pos.x, pos.y);
            SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1EA2, lbl_803606E4[f24][f3C]);
            SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1EAA, lbl_803606E4[f24][f38]);
        }
        break;
    case 3:
        if (!fn_8019FE78(*(void **)anims[2])) {
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], lbl_803606E4[f24][f3C], lbl_803606E4[f24][f38]);
            t = 0.0f;
            state = 4;
            fn_8023F1C8(anims[2]);
        }
        break;
    case 4:
        if (t > 70.0f) {
            u = 1.0f - (t - 70.0f) / 10.0f;
            ((SpriteRef *)anims[1])->spr->t = u;
            ((SpriteRef *)anims[0])->spr->t = u;
            ((SpriteRef *)anims[4])->spr->t = u;
            ((SpriteRef *)anims[3])->spr->t = u;
            tm.color = ((int)(255.0f * u) & 0xFF) | 0xE0E02000;
        }
        if (t >= 80.0f) {
            for (i = 0; i < 5; i++) {
                if (anims[i]) {
                    SpriteAnimHandle_Destroy(anims[i], 1);
                    anims[i] = 0;
                }
            }
            state = -1;
        }
        break;
    }
    if (!bgmStarted) {
        if (fn_80192010(0x1F) == 1) {
            fn_80192688(0x1F, 1);
        }
        SoundMgr_Play(0x23);
        bgmStarted = 1;
    }
    t += 1.0f;
    for (int k = 0; k < 5; k++) {
        if (anims[k]) {
            Sprite_AdvanceAnim(*(void **)anims[k], 0.0165f);
        }
    }
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
    la r4, lbl_806CF6A8(r13)  /* lbl_806CF6A8 */
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
    la r4, lbl_806CF6AC(r13)  /* lbl_806CF6AC */
    li r5, 0x0
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D78D4(r2)
    addi r3, r27, 0x27c
    lfs f2, lbl_806D78EC(r2)
    la r4, lbl_806CF6B0(r13)  /* lbl_806CF6B0 */
    li r5, 0x1
    bl SpriteGroup_CreateOrInit
    lfs f1, lbl_806D78D4(r2)
    addi r3, r27, 0x280
    lfs f2, lbl_806D78F0(r2)
    la r4, lbl_806CF6B4(r13)  /* lbl_806CF6B4 */
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

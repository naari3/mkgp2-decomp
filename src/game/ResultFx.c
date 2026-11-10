/* --- owned .rodata 0x80360498..0x803604F8 (tools/own_data.py) --- */
#pragma force_active on
const int ResultFx_rodata_80360498[8][2] = { 2720, 2721, 2692, 2693, 2678, 2679, 2734, 2735, 2706, 2707, 2752, 2753, 2772, 2773, 2762, 2763 };
const int ResultFx_rodata_803604D8[8] = { 5286, 5284, 5283, 5287, 5285, 5288, 5290, 5289 };
#pragma force_active reset
/*
 * Result-screen cup trophy effect on the shared sprite-effect base
 * (vtable TrophyFx_vtable_8048EBCC; ctor, dtor). The base declares a virtual that is
 * not defined here first, so no vtable is emitted.
 */
#pragma cplusplus on

typedef float Mtx[3][4];
#include "game/types/Vec3f.h"
#include "game/types/TexMgr.h"

extern "C" {
extern char lbl_8048EB44[];
extern char TrophyFx_vtable_8048EBCC[];
extern char ResultFx_vtable_8048EC9C[];
extern unsigned int ConfettiField_rodata_80360520[];
extern int ResultFxScene_rodata_803606C4[];
extern int ResultFxScene_rodata_803606E4[][3];
extern char ResultFx_data_806CF688[4];
extern char ResultFx_data_806CF68C[4];
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


#include "game/types/InputPlayer.h"

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
extern char ResultFx_data_806CF690[4];
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

#include "game/types/FxData.h"

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

#include "game/types/Handle.h"

#include "game/types/HandleF.h"

extern "C" HandleF *fn_8020007C(int a, int obj, int b);

#include "game/types/SpriteRef.h"



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
    void DrawTitle(float a);
};



void TrophyFx::Draw() {
    switch (state) {
    case 0:
        DrawTitle(t / 15.0f);
        break;
    case 1:
        DrawTitle(1.0f);
        break;
    case 2:
        DrawTitle(1.0f);
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
    rc.resId = ResultFx_rodata_803604D8[cup - 1];
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

void TrophyFx::DrawTitle(float a) {
    unsigned char alpha;
    unsigned int color;
    float k;
    void *ctx;
    float x;
    char buf[0x80];
    int len;

    fn_8016918C(obj, 0x14E5, 0, 320.0f, 373.0f, 1.25f, 1.0f, 1.0f,
                1.0f, 1.0f, a);
    fn_801695E0(obj, 0x1CDA, 0, 320.0f, 266.0f, a);
    k = 0.0f;
    if (t3 >= 90.0f) {
        t3 = 0.0f;
    } else if (t3 >= 60.0f) {
        k = (t3 - 60.0f) / 15.0f;
        if (k > 1.0f) {
            k = 1.0f - (k - 1.0f);
        }
    }
    fn_801695E0(obj, 0x1CDA, 2, 320.0f, 266.0f, k);
    ctx = fn_801F8E58();
    TexMgr tm;
    fn_801F8FCC(&tm, 1);
    TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x55, -1), fn_8013C198(cup, -1));
    tm.fade = -2.0f;
    fn_801F93EC(&tm, 320.0f, 340.0f);
    alpha = (int)(255.0f * a);
    color = alpha | 0xFFFFFF00;
    tm.SetColor(color);
    fn_801F8E90(&tm);
    fn_801F8A34(ctx, &tm, obj);
    fn_801F8FCC(&tm, 0);
    fn_801F8E90(&tm);
    tm.mode = 1;
    tm.fade = -3.0f;
    if (isJapanese() == 0) {
        sprintf(buf, lbl_806D780C, GetTextureByIdAndLang(0x56, -1), GetTextureByIdAndLang(0x57, -1),
                GetTextureByIdAndLang(0x58, -1));
        len = strlen(buf);
        x = 320.0f - 10.5f * (0.5f * (len - 1));
        fn_801F93EC(&tm, x, 377.0f);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x56, -1));
        tm.color = color;
        fn_801F8A34(ctx, &tm, obj);
        len = strlen(GetTextureByIdAndLang(0x56, -1));
        x += 10.5f * len;
        fn_801F93EC(&tm, x, 377.0f);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x57, -1));
        tm.color = alpha | 0xE0E02000;
        fn_801F8A34(ctx, &tm, obj);
        len = strlen(GetTextureByIdAndLang(0x57, -1));
        x += 10.5f * len;
        fn_801F93EC(&tm, x, 377.0f);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x58, -1));
        tm.color = color;
        fn_801F8A34(ctx, &tm, obj);
    } else {
        fn_801F93EC(&tm, 320.0f, 370.0f);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x59, -1));
        tm.color = color;
        fn_801F8FCC(&tm, 1);
        fn_801F8E90(&tm);
        fn_801F8A34(ctx, &tm, obj);
        fn_801F8FCC(&tm, 0);
        sprintf(buf, lbl_806D7824, GetTextureByIdAndLang(0x5A, -1), GetTextureByIdAndLang(0x5B, -1));
        len = strlen(buf);
        x = 320.0f - 15.5f * (0.5f * (len - 1));
        fn_801F93EC(&tm, x, 400.0f);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x5A, -1));
        tm.color = color;
        fn_801F8E90(&tm);
        fn_801F8A34(ctx, &tm, obj);
        len = strlen(GetTextureByIdAndLang(0x5A, -1));
        x += 15.5f * len;
        fn_801F93EC(&tm, x, 400.0f);
        TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x5B, -1));
        tm.color = alpha | 0xE0E02000;
        fn_801F8A34(ctx, &tm, obj);
    }
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
            SpriteGroup_CreateOrInit(&anims[1], ResultFx_data_806CF690, 0, 320.0f, 240.0f);
            SoundMgr_Play(0x1A);
            int idx = cup - 1;
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], 0xA9C, ResultFx_rodata_80360498[idx][0]);
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], 0xA9D, ResultFx_rodata_80360498[idx][1]);
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
    fn_80120A08(ResultFx_rodata_803604D8[idx]);
    fn_80120A08(ResultFx_rodata_80360498[idx][0]);
    fn_80120A08(ResultFx_rodata_80360498[idx][1]);
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
    PreloadResource(ResultFx_rodata_803604D8[idx]);
    PreloadResource(ResultFx_rodata_80360498[idx][0]);
    PreloadResource(ResultFx_rodata_80360498[idx][1]);
    PreloadResource(0x14E5);
    PreloadResource(0x14F5);
    PreloadResource(0x1CDA);
    PreloadResource(0x1CDD);
    SpriteGroup_CreateOrInit(&anims[0], ResultFx_data_806CF688, 0, lbl_806D77B8, lbl_806D7840);
    SpriteGroup_CreateOrInit(&anims[2], ResultFx_data_806CF68C, 1, lbl_806D7860, lbl_806D7840);
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


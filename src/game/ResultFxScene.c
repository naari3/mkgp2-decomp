/* sdata symbols referenced from asm */
extern unsigned char ResultFxScene_data_806CF6A8[4];
extern unsigned char ResultFxScene_data_806CF6AC[4];
extern unsigned char ResultFxScene_data_806CF6B0[4];
extern unsigned char ResultFxScene_data_806CF6B4[4];
extern char ResultFxScene_data_806CF6B8[4];
/*
 * Result effect scene on the shared sprite-effect base (vtable
 * ResultFx_vtable_8048EC9C): trophy model zoom/spin, cup sprites and the caption
 * text. The base declares a virtual that is not defined here first, so no
 * vtable is emitted.
 *
 * The cup tables are file-static data of this unit: the scene ctor reaches
 * them through one pooled .rodata base (+0x2C/0x18C/0x1AC). The two zero
 * tables are not referenced by any code that survives in this unit.
 */
#pragma cplusplus on

typedef float Mtx[3][4];
struct SpritePos {
    float x, y;
    float rest[9];
};
#include "game/types/TexMgr.h"

extern "C" {
extern char lbl_8048EB44[];
extern char TrophyFx_vtable_8048EBCC[];
extern char ResultFx_vtable_8048EC9C[];
extern int ResultFx_rodata_803604D8[];
extern int ResultFx_rodata_80360498[][2];
extern unsigned int ConfettiField_rodata_80360520[];
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
}

extern "C" {
extern void ResCtrl_Init();
extern void fn_8013D570(void *h, float rot);
extern void fn_8013D608(void *h, float sx, float sy, float sz);
extern void fn_8013D660(void *h, float x, float y);
extern void fn_80192688(int id, int on);
extern unsigned char fn_8019FE78(void *spr);
extern void fn_8019FF8C(void *spr, short id, struct SpritePos *out);
extern void dtor_80082960();


extern unsigned char fn_801D5C88(void *data, int cc);
extern void fn_8013D50C(void *h, float sx, float sy, float sz, float a);
extern int g_ccClass;
extern int g_roundIndex;
extern struct PlayerDataView {
    unsigned char pad[0x1BA];
    unsigned char cupRank[4][8];
} g_playerData;
}

static const int s_unk_80360538[3] = {0, 0, 0};
static const float s_cupScale[8] = {0.03f, 0.03f, 0.026f, 0.03f, 0.03f, 0.03f, 0.03f, 0.03f};
static const int s_cupOrder[8] = {7, 1, 8, 2, 3, 4, 5, 6};
static const int s_unk_80360584[16] = {0};
#pragma readonly_strings on
static const char *s_trophyFiles[8][2] = {
    {"trpy_YI_A.dat", "trpy_YI_B.dat"},
    {"trpy_MR_A.dat", "trpy_MR_B.dat"},
    {"trpy_WS_A.dat", "trpy_WS_B.dat"},
    {"trpy_DK_A.dat", "trpy_DK_B.dat"},
    {"trpy_WA_A.dat", "trpy_WA_B.dat"},
    {"trpy_PA_A.dat", "trpy_PA_B.dat"},
    {"trpy_KP_A.dat", "trpy_KP_B.dat"},
    {"trpy_SP_A.dat", "trpy_SP_B.dat"},
};
#pragma readonly_strings reset
static const int s_cupAnim[8] = {0x1529, 0x1521, 0x1527, 0x151B, 0x1519, 0x1523, 0x151F, 0x1525};
static const int s_cupParam[8][3] = {
    {0x1EA2, 0x1EAA, 0x1EB2}, {0x1EA3, 0x1EAB, 0x1EB3}, {0x1EA4, 0x1EAC, 0x1EB4}, {0x1EA5, 0x1EAD, 0x1EB5},
    {0x1EA6, 0x1EAE, 0x1EB6}, {0x1EA7, 0x1EAF, 0x1EB7}, {0x1EA8, 0x1EB0, 0x1EB8}, {0x1EA9, 0x1EB1, 0x1EB9},
};


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

#include "game/types/FxBase.h"

#include "game/types/Handle.h"

#include "game/types/HandleF.h"

extern "C" HandleF *fn_8020007C(int a, int obj, int b);

#include "game/types/SpriteRef.h"

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
    ResultFx();
};

struct PreviewModel : Handle {
    unsigned char body[0x1C];
    PreviewModel(const char *name, int flag);
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
            s = (t / 18.0f) * (1.1f * s_cupScale[f24]);
        } else {
            s = (t - 18.0f) * (0.1f * s_cupScale[f24]) / 4.0f + s_cupScale[f24];
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
        fn_8019FF8C(*(void **)anims[1], s_cupParam[f24][f3C], &pos);
        sc = (1.0f - t / 30.0f) * s_cupScale[f24];
        fn_8013D660(handle, Lerp(320.0f, pos.x, t, 30.0f), Lerp(300.0f, pos.y, t, 30.0f));
        fn_8013D608(handle, sc, sc, sc);
        if (t >= 30.0f) {
            state = 3;
            t = 0.0f;
            SpriteGroup_CreateOrInit(&anims[2], ResultFxScene_data_806CF6B8, 0, pos.x, pos.y);
            SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1EA2, s_cupParam[f24][f3C]);
            SpriteAnimParamBlock_SetAnimParamCached(anims[2], 0x1EAA, s_cupParam[f24][f38]);
        }
        break;
    case 3:
        if (!fn_8019FE78(*(void **)anims[2])) {
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], s_cupParam[f24][f3C], s_cupParam[f24][f38]);
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
        fn_80120A08(s_cupAnim[i]);
        fn_80120A08(s_cupParam[i][0]);
        fn_80120A08(s_cupParam[i][1]);
    }
    for (int j = 0; j < 5; j++) {
        if (anims[j]) {
            SpriteAnimHandle_Destroy(anims[j], 1);
            anims[j] = 0;
        }
    }
}

ResultFx::ResultFx() {
    int cc;
    int cup;
    int special;
    int need;
    int i;

    state = -1;
    t = 0.0f;
    f20 = -1;
    f24 = -1;
    cc = g_ccClass;
    cup = g_cupId;
    special = fn_801D5C88(&g_playerData, cc) == 1 ? 1 : 0;
    if (g_roundIndex <= 3) {
        special = 0;
    }
    if (special == 1) {
        f3C = 0;
        f38 = 2;
    } else {
        f3C = 0;
        f38 = 1;
    }
    if (cup - 1 < 0 || cup - 1 >= 8) {
        return;
    }
    f20 = cup + 0x9A4;
    need = special == 1 ? 9 : 4;
    for (i = 0; i < 8; i++) {
        int c = s_cupOrder[i] - 1;
        flags[i] = g_playerData.cupRank[cc][c] >= need;
        if (c == cup - 1) {
            f24 = i;
        }
    }
    flags[f24] = 0;
    if (f24 < 0) {
        return;
    }
    handle = new PreviewModel(s_trophyFiles[f24][special], 1);
    fn_8013D660(handle, 320.0f, 300.0f);
    fn_8013D608(handle, 0.0f, 0.0f, 0.0f);
    fn_8013D50C(handle, 1.17f, 1.17f, 1.17f, 1.0f);
    state = 0;
    t = 0.0f;
    anims[0] = 0;
    anims[1] = 0;
    anims[2] = 0;
    anims[3] = 0;
    anims[4] = 0;
    SpriteGroup_CreateOrInit(&anims[0], (const char *)ResultFxScene_data_806CF6A8, 0, 320.0f, 85.0f);
    SpriteGroup_CreateOrInit(&anims[1], (const char *)ResultFxScene_data_806CF6AC, 0, 320.0f, 384.0f);
    SpriteGroup_CreateOrInit(&anims[3], (const char *)ResultFxScene_data_806CF6B0, 1, 320.0f, 85.0f);
    SpriteGroup_CreateOrInit(&anims[4], (const char *)ResultFxScene_data_806CF6B4, 1, 320.0f, 384.0f);
    SpriteAnimParamBlock_SetAnimParamCached(anims[0], 0x1529, s_cupAnim[f24]);
    ((SpriteRef *)anims[3])->spr->t = 0.0f;
    ((SpriteRef *)anims[4])->spr->t = 0.0f;
    {
        SpritePos pos;
        fn_8019FF8C(*(void **)anims[1], s_cupParam[f24][f3C], &pos);
    }
    for (i = 0; i < 8; i++) {
        if (flags[i] == 1) {
            SpriteAnimParamBlock_SetAnimParamCached(anims[1], s_cupParam[i][0], s_cupParam[i][f38]);
        }
    }
    tm.mode = 1;
    fn_801F8FCC(&tm, 1);
    tm.fade = -3.0f;
    tm.color = 0xE0E02000;
    fn_801F93EC(&tm, 320.0f, 326.0f);
    TexMgr_SetTexture(&tm, GetTextureByIdAndLang(0x5C, -1), fn_8013C198(g_cupId, -1));
    fn_801F8E90(&tm);
    bgmStarted = 0;
}

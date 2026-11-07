/* clFlowChara (character select flow), merged TU.
 * .text 0x801C3470..0x801C53A0, .data 0x8049AA58..0x8049AC90, .rodata 0x8039AA40..0x8039B1F4.
 * The original source was one C++ TU; functions use CSE'd pool bases into the
 * .data/.rodata of this TU, so they have to live together. */
#include "game/singleton.h"

#include "game/CharaDisplayPrivate.h"
/* Character selection constant pool, 8039AA40..8039B1F4. */
extern "C" { extern const float lbl_8039AA40[255]; }
extern const float lbl_8039AA40[255] = {
    1.0f, 0.699999988079071f, 0.8999999761581421f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f,
    66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
    83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
    83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
    83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
    83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
    83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f,
    83.33333587646484f, 5000.0f, 83.33333587646484f
};
static const int partialThresholds[13] = { 30, 1470, 1230, 150, 750, 1350, 270, 630, 990, 390, 1110, 510, 870 };
static const int fullThresholds[13] = { 1590, 3030, 2790, 1710, 2310, 2910, 1830, 2190, 2550, 1950, 2670, 2070, 2430 };
static const int textureIds[13] = { 2, 2, 3, 1, 3, 0, 3, 1, 2, 0, 1, 2, 0 };
static const float displayOrigin[3] = { 0.0f, 0.0f, 0.0f };
static const float displayScale[4] = { 0.0f, 120.0f, 140.0f, 220.0f };
static const char modelName0[20] = "kart_demo_mario.dat";
static const char modelName1[20] = "kart_demo_luigi.dat";
static const char modelName2[21] = "kart_demo_pacman.dat";
static const char modelName3[22] = "kart_demo_waluigi.dat";
static const char modelName4[20] = "kart_demo_peach.dat";
static const char modelName5[20] = "kart_demo_yoshi.dat";
static const char modelName6[22] = "kart_demo_monster.dat";
static const char modelName7[22] = "kart_demo_mametch.dat";
static const char modelName8[23] = "kart_demo_mspacman.dat";
static const char modelName9[22] = "kart_demo_kinopio.dat";
static const char modelName10[20] = "kart_demo_wario.dat";
static const char modelName11[21] = "kart_demo_donkey.dat";
static const char modelName12[20] = "kart_demo_koopa.dat";
static const char *const demoModels[13] = { modelName0, modelName1, modelName2, modelName3, modelName4, modelName5, modelName6, modelName7, modelName8, modelName9, modelName10, modelName11, modelName12 };
static const char modelName13[17] = "select_mario.dat";
static const char modelName14[17] = "select_luigi.dat";
static const char modelName15[18] = "select_pacman.dat";
static const char modelName16[19] = "select_waluigi.dat";
static const char modelName17[17] = "select_peach.dat";
static const char modelName18[17] = "select_yoshi.dat";
static const char modelName19[19] = "select_monster.dat";
static const char modelName20[19] = "select_mametch.dat";
static const char modelName21[20] = "select_mspacman.dat";
static const char modelName22[19] = "select_kinopio.dat";
static const char modelName23[17] = "select_wario.dat";
static const char modelName24[18] = "select_donkey.dat";
static const char modelName25[20] = "select_koopa.dat";
static const char *const selectModels[13] = { modelName13, modelName14, modelName15, modelName16, modelName17, modelName18, modelName19, modelName20, modelName21, modelName22, modelName23, modelName24, modelName25 };
static const float selectScale[3] = { 3.5999999046325684f, 0.0f, 0.0f };
static const short characterAnims[14] = { 7486, 7487, 7488, 7489, 7490, 7491, 7492, 7493, 7494, 7495, 7496, 5785, 5786, 0 };
static const int statAnims[5] = { 5812, 5811, 5810, 5809, 5808 };
static const char className[12] = "clFlowChara";
static const char baseClassName[16] = "clFlowProcess";
static const char jointName[28] = "demo_chara_kart_null_joint";

extern "C" {
extern signed char g_charaStatTable[3][13][3];
extern const float FLOAT_FULL_ALPHA, FLOAT_SPRITE_INIT_TIME;
extern const float lbl_806D9B60, lbl_806D9B64, lbl_806D9B68, lbl_806D9B6C;
extern const float FLOAT_ARROW_RIGHT_OFFSET, lbl_806D9B74, lbl_806D9B78, lbl_806D9B7C;
void clNormal3D_SetScale(void*, int, float, float, float, float);
void *ResolveJointByName(void*, const char*);
void Sprite_Destroy(void*, int);
void Sprite_SetAnimParam(void*, int, int);
void *GetTextureByIdAndLang(int, int);
void TexMgr_SetTexture(void*, void*, ...);
void fn_801F93EC(DisplayTexture*, float, float);
int isJapanese();
}
#pragma use_lmw_stmw on
/* Declaration order below is load-bearing: it decides the register colouring of the three stat loops. */
extern "C" void CharaSelect_SetupCharacterDisplay(CharaDisplay *self, int character) {
    signed char *stat2;
    const int *cursor;
    signed char *stat3;
    signed char *stat;
    const int *cursor2;
    int j;
    const int *anims;
    int i;
    int k;
    if (character <= -1 || character >= 13) self->character = 0;
    else self->character = character;
    const float *scale = displayScale;
    clNormal3D_SetScale(self->normals[self->selection], 0, scale[0], FLOAT_FULL_ALPHA, scale[0], scale[1]);
    if (self->alternateNormals[self->selection]) {
        float fullAlpha = FLOAT_FULL_ALPHA;
        float initialTime = FLOAT_SPRITE_INIT_TIME;
        clNormal3D_SetScale(self->alternateNormals[self->selection], 0, fullAlpha, fullAlpha, initialTime, initialTime);
    }
    self->joint = ResolveJointByName(self->normals[self->selection], jointName);
    Sprite_Destroy(self->stats[0], 1);
    Sprite_Destroy(self->stats[1], 1);
    Sprite_Destroy(self->stats[2], 1);
    self->stats[0] = new DisplaySprite(0x16B, 1, lbl_806D9B60, lbl_806D9B64);
    self->stats[1] = new DisplaySprite(0x16B, 1, lbl_806D9B60, lbl_806D9B68);
    self->stats[2] = new DisplaySprite(0x16B, 1, lbl_806D9B60, lbl_806D9B6C);
    anims = statAnims;
    cursor = anims;
    stat = g_charaStatTable[self->variants[self->character]][character];
    i = 0;
    while (i < 5 - stat[0]) { Sprite_SetAnimParam(self->stats[0], (short)*cursor, -1); ++cursor; ++i; }
    cursor2 = anims;
    stat2 = stat + 1;
    j = 0;
    while (j < 5 - *stat2) { Sprite_SetAnimParam(self->stats[1], (short)*cursor2, -1); ++cursor2; ++j; }
    k = 0;
    stat3 = stat + 2;
    while (k < 5 - *stat3) { Sprite_SetAnimParam(self->stats[2], (short)*anims, -1); ++anims; ++k; }
    TexMgr_SetTexture(self->texture, GetTextureByIdAndLang(textureIds[character] + 0x95, -1));
    fn_801F93EC(self->texture, FLOAT_ARROW_RIGHT_OFFSET, lbl_806D9B74);
    float width = isJapanese() == 0 ? lbl_806D9B78 : lbl_806D9B7C;
    self->texture->width = width;
}
#pragma use_lmw_stmw reset

/* ------------------------------------------------------------------ */
/* .data 0x8049AA58..0x8049AC90 (jumptable_8049AC90 of clFlowChara_Update
 * follows; it is generated once Update is native). */
struct FrameParam {
    short animA;   /* 0x00 */
    short animB;   /* 0x02 */
    short icon;    /* 0x04 */
    short pad06;
    int index;     /* 0x08 */
    float step;    /* 0x0C */
    float baseX;   /* 0x10 */
    float y;       /* 0x14 */
};

extern "C" {
extern char lbl_806CFDC0[8]; /* .sdata - clFlowBase RTTI */
extern char lbl_806CFDC8[8]; /* .sdata - clFlowChara RTTI {name, bases} */
struct DtorView;
DtorView *clFlowChara_Destructor(DtorView *self, short del);
asm void clFlowChara_Update(void);
struct CharaDrawView;
void fn_801C3AA4(CharaDrawView *self);

signed char g_charaStatTable[3][13][3] = {
    { { 3, 3, 3 }, { 3, 3, 3 }, { 2, 4, 4 }, { 5, 2, 2 }, { 2, 4, 4 }, { 4, 2, 3 }, { 2, 4, 4 }, { 5, 2, 2 }, { 3, 3, 3 }, { 4, 2, 3 }, { 5, 2, 2 }, { 3, 3, 3 }, { 4, 2, 3 } },
    { { 2, 3, 4 }, { 2, 3, 4 }, { 1, 4, 5 }, { 4, 2, 3 }, { 1, 4, 5 }, { 3, 2, 4 }, { 1, 4, 5 }, { 4, 2, 3 }, { 2, 3, 4 }, { 3, 2, 4 }, { 4, 2, 3 }, { 2, 3, 4 }, { 3, 2, 4 } },
    { { 3, 3, 4 }, { 3, 3, 4 }, { 2, 4, 5 }, { 5, 2, 3 }, { 2, 4, 5 }, { 4, 2, 4 }, { 2, 4, 5 }, { 5, 2, 3 }, { 3, 3, 4 }, { 4, 2, 4 }, { 5, 2, 3 }, { 3, 3, 4 }, { 4, 2, 4 } },
};

FrameParam FrameParam_ARRAY_8049aad0[13] = {
    { 0x169B, 0x16A9, 0x167F, 0, 0, -40.0f, 132.0f, 134.0f },
    { 0x169C, 0x16A9, 0x1680, 0, 0, -40.0f, 196.0f, 134.0f },
    { 0x169D, 0x16A9, 0x1681, 0, 0, -40.0f, 260.0f, 134.0f },
    { 0x169E, 0x16A9, 0x1682, 0, 0, -40.0f, 324.0f, 134.0f },
    { 0x169F, 0x16AA, 0x1683, 0, 0, -40.0f, 388.0f, 134.0f },
    { 0x16A0, 0x16AA, 0x1684, 0, 0, -40.0f, 452.0f, 134.0f },
    { 0x16A1, 0x16AA, 0x1685, 0, 0, -40.0f, 516.0f, 134.0f },
    { 0x16A2, 0x16AB, 0x1687, 0, 0, 40.0f, 165.0f, 202.0f },
    { 0x16A3, 0x16AB, 0x1686, 0, 0, 40.0f, 229.0f, 202.0f },
    { 0x16A4, 0x16AB, 0x1688, 0, 0, 40.0f, 293.0f, 202.0f },
    { 0x16A5, 0x16A8, 0x1689, 0, 0, 40.0f, 364.0f, 204.0f },
    { 0x16A6, 0x16A8, 0x168A, 0, 0, 40.0f, 428.0f, 204.0f },
    { 0x16A7, 0x16A8, 0x168B, 0, 0, 40.0f, 492.0f, 204.0f },
};

float g_tierCursorPosTable[13][2] = {
    { 82.0f, 135.0f }, { 146.0f, 135.0f }, { 210.0f, 135.0f }, { 274.0f, 135.0f },
    { 338.0f, 135.0f }, { 402.0f, 135.0f }, { 466.0f, 135.0f }, { 115.0f, 203.0f },
    { 179.0f, 203.0f }, { 243.0f, 203.0f }, { 314.0f, 203.0f }, { 378.0f, 203.0f },
    { 442.0f, 203.0f },
};

/* clFlowChara RTTI base list / vtable { rtti, offset, dtor, Update, Draw } */
void *lbl_8049AC70[3] = { lbl_806CFDC0, 0, 0 };
/* Only reached through FrameSelection_Init's pool base (g_charaStatTable+0x224). */
#pragma force_active on
void *lbl_8049AC7C[5] = {
    lbl_806CFDC8, 0, (void *)clFlowChara_Destructor, (void *)clFlowChara_Update, (void *)fn_801C3AA4
};
#pragma force_active reset
}

/* ------------------------------------------------------------------ */
/* GetFrameIdxFromVisualIdx (0x801C3714) */
#pragma exceptions off
extern "C" int GetFrameIdxFromVisualIdx(void *self, int visualIdx) {
    int frame = 0;
    if (visualIdx == 0) {
        frame = 0;
    } else if (visualIdx == 1) {
        frame = 1;
    } else if (visualIdx == 2) {
        frame = 8;
    } else if (visualIdx == 3) {
        frame = 11;
    } else if (visualIdx == 4) {
        frame = 3;
    } else if (visualIdx == 5) {
        frame = 7;
    } else if (visualIdx == 6) {
        frame = 10;
    } else if (visualIdx == 7) {
        frame = 12;
    } else if (visualIdx == 8) {
        frame = 9;
    } else if (visualIdx == 9) {
        frame = 5;
    } else if (visualIdx == 10) {
        frame = 2;
    } else if (visualIdx == 11) {
        frame = 6;
    } else if (visualIdx == 12) {
        frame = 4;
    }
    return frame;
}
#pragma exceptions reset

/* ------------------------------------------------------------------ */
/* fn_801C37E8 (0x801C37E8): (re)create one frame sprite. */
struct Sprite {
    char pad00[0xC];
    float x;
    float y;
    float scaleX;
    float scaleY;
    char pad1C[0x14];
    Sprite(int anim, int loop, int flags);
    void SetPos(float px, float py) { x = px; y = py; }
    void SetScale(float s) { scaleX = s; scaleY = s; }
};

struct FrameSet {
    char pad00[0x14];
    Sprite *sprites[1];
};

extern "C" {
void Sprite_SetupAnim(Sprite *sprite, int anim, int loop, int flags);
void fn_801A0550(Sprite *sprite);
}

#pragma exceptions on
extern "C" void fn_801C37E8(FrameSet *self, int slot, int anim, int index, float scale) {
    if (index >= 0) {
        FrameParam_ARRAY_8049aad0[slot].index = index;
    }
    if (self->sprites[slot] == 0) {
        self->sprites[slot] = new Sprite(anim, 0, 0);
    } else {
        Sprite_SetupAnim(self->sprites[slot], anim, 0, 0);
    }
    Sprite_SetAnimParam(self->sprites[slot], 0x169B, FrameParam_ARRAY_8049aad0[slot].animA);
    Sprite_SetAnimParam(self->sprites[slot], 0x16A8, FrameParam_ARRAY_8049aad0[slot].animB);
    fn_801A0550(self->sprites[slot]);
    self->sprites[slot]->SetPos(FrameParam_ARRAY_8049aad0[slot].step * FrameParam_ARRAY_8049aad0[slot].index + FrameParam_ARRAY_8049aad0[slot].baseX,
                                FrameParam_ARRAY_8049aad0[slot].y);
    self->sprites[slot]->SetScale(scale);
}
#pragma exceptions reset

/* ------------------------------------------------------------------ */
/* clFlowChara_HandleConfirm (0x801C393C): character select confirm; picks the next flow state. */
typedef struct {
    char pad00[0x4];
    int visualIdx;
    char pad08[0x60 - 0x8];
    int next;
    char pad64[0x68 - 0x64];
    int cursor;
    float timer;
    char pad70[0xA8 - 0x70];
    int locked[1];
} ConfirmView;

extern "C" {
extern const float lbl_806D9B90;
extern const float FLOAT_BRIGHTNESS_DARK;
extern char *g_pInputState;
extern int g_characterId;
extern int g_gameMode;
extern unsigned char g_playerData[];
extern void *GetInputManager(void);
extern void InputMgr_GetPlayer(void *mgr, int idx);
extern void SetRumbleMode(int a, int b, int c);
extern void SetKartVariant(int v);
extern void fn_801B7B64(int chara);
extern void SetScreenBrightness(float b);
}

#pragma exceptions on
extern "C" int clFlowChara_HandleConfirm(ConfirmView *self) {
    char *input;
    unsigned char *pd;
    unsigned char flag;

    if (self->next != -1) {
        return self->next;
    }
    self->timer -= lbl_806D9B90;
    InputMgr_GetPlayer(GetInputManager(), 0);
    if ((input = g_pInputState) == 0) {
        input = 0;
    }
    if (*(int *)(input + 0x18) == 1 || self->timer < FLOAT_SPRITE_INIT_TIME) {
        SetRumbleMode(0, 1, 1);
        pd = g_playerData;
        g_characterId = GetFrameIdxFromVisualIdx(self, self->visualIdx);
        if (self->locked[self->cursor] >= 1) {
            SetKartVariant(2);
            self->next = 0xF;
        } else {
            SetKartVariant(0);
            flag = 0;
            if (g_gameMode != 2) {
                if (pd[0x19F] == 0) {
                    flag = 1;
                }
                if (pd[0x19D] == 1) {
                    flag = 1;
                }
            } else {
                flag = 1;
            }
            if (!flag) {
                if (g_gameMode == 0) {
                    self->next = 0x15;
                } else {
                    self->next = 0x17;
                }
            } else {
                self->next = 0x13;
            }
        }
        self->timer = FLOAT_BRIGHTNESS_DARK;
        fn_801B7B64(g_characterId);
    }
    SetScreenBrightness(self->timer);
    return self->next;
}
#pragma exceptions reset

/* ------------------------------------------------------------------ */
/* fn_801C3AA4 (0x801C3AA4): character selection draw pass. */
struct CharaDrawable { virtual void unused(); virtual unsigned char Draw(); virtual void Finish(); };

struct CharaDrawView {
    int v, selection, state, pending, frame;
    void* sprites[13];
    void *left, *right, *stats[3], *header;
    int result;
    unsigned char complete, display, pad[2];
    int cursor; float brightness;
    CharaDrawable* camera; void* lights;
    char matrix[0x30];
    int variants[13];
    void* normals[13]; void* alternate[13]; void* models[13];
    int extra; char tail[0x24];
};
extern "C" {

extern const float lbl_806D9B98, lbl_806D9B9C, lbl_806D9BA0, FLOAT_TEX_POS_X;
extern const float lbl_806D9BA8, lbl_806D9BAC;
void fn_801A1174(int,int,int,int,int);
void fn_801A1128(float,float);
void fn_801A0DF0();
void fn_801A0004(void*);
void fn_8011FAB8(); void fn_801A1280();
void LObjList_ApplyForCObj(void*); void CObj_DebugVizPathFlush(void*);
void Object_RenderJObjTree(void*,int);
void* fn_801F8E58(); void fn_801F8A34(void*,int,int); void fn_8011FAFC(void*,int);
void fn_801C3AA4(CharaDrawView* self) {
    int i;
    if (self->state == 1 || self->state == 2 || self->state == 3) {
        fn_801A1174(0x16ac,4,0,0,0);
        fn_801A1128(lbl_806D9B98,lbl_806D9B9C); fn_801A0DF0();
        fn_801A1174(FrameParam_ARRAY_8049aad0[self->selection].icon,5,0,0,0);
        fn_801A1128(lbl_806D9BA0,FLOAT_TEX_POS_X); fn_801A0DF0();
    }
    for (i=0;i<13;i++) if(i != self->selection && self->sprites[i]) fn_801A0004(self->sprites[i]);
    if (self->sprites[self->selection]) fn_801A0004(self->sprites[self->selection]);
    if(self->header) fn_801A0004(self->header);
    fn_8011FAB8(); fn_801A1280();
    if(self->display) {
        if(self->left) fn_801A0004(self->left);
        if(self->right) fn_801A0004(self->right);
        if(self->stats[0]) fn_801A0004(self->stats[0]);
        if(self->stats[1]) fn_801A0004(self->stats[1]);
        if(self->stats[2]) fn_801A0004(self->stats[2]);
        if(self->camera && self->camera->Draw()) {
            LObjList_ApplyForCObj(self->lights); CObj_DebugVizPathFlush(self->camera);
            if(self->alternate[self->selection]) Object_RenderJObjTree(self->alternate[self->selection],7);
            if(self->models[self->selection]) ((CharaDrawable*)self->models[self->selection])->Draw();
            if(self->normals[self->selection]) Object_RenderJObjTree(self->normals[self->selection],7);
            self->camera->Finish();
        }
    }
    if(self->state == 1 || self->state == 2 || self->state == 3) {
        fn_801A1174(0x16ad,5,0,0,0);
        fn_801A1128(lbl_806D9BA8,lbl_806D9BAC); fn_801A0DF0();
        fn_801F8A34(fn_801F8E58(),self->extra,6);
        if(self->variants[self->cursor] == 2) fn_8011FAFC((char*)self+0x17c,5);
    }
}
}

/* ------------------------------------------------------------------ */
/* clFlowChara_Update (0x801C3D48) - asm; the native draft is
 * /mnt/project-files/wip/clflowchara_update_draft.cpp */
extern "C" {
extern unsigned char lbl_806D9BCC[5];
extern unsigned char lbl_806D9BC4[7];
extern unsigned char lbl_806D184C;
extern unsigned char lbl_806D184D;
extern const float FLOAT_ARROW_SCALE, lbl_806D9B80, lbl_806D9BA8, lbl_806D9BB0, lbl_806D9BB4, lbl_806D9BBC, lbl_806D9BC0;
extern const double lbl_806D9B88;
extern unsigned int jumptable_8049AC90[];
extern void Alloc();
extern void FileLoader_Open();
extern void GetKartModelNameEntry();
extern void LObjList_Destroy(void *l, int del);
extern void PSMTXIdentity();
extern void Object_DriveAnimMatrix();
extern void Object_GetField8();
extern void Object_SetAnimBinding();
extern void PSMTXConcat();
extern void PSMTXScale();
extern void PSMTXTrans();
extern void RumbleUpdate();
extern void Sprite_AdvanceAnim();
extern void Sprite_InitWithAnim();
extern void __assert();
extern void clNormal3D_Construct();
extern void clNormal3D_Exec();
extern void fn_801699D8();
extern void fn_8019FF6C();
extern void fn_801A024C();
extern void fn_801B7CAC();
extern void fn_801B8398();
extern void fn_801B84B4();
extern void fn_801B8540();
extern void fn_801B85DC();
extern void fn_801B87D8();
extern void fn_801B8918();
extern void fn_8021A660();
extern void fn_8021A71C();
extern void fn_8021A9E8();
extern void fn_8021ABFC();
extern void PSMTXRotRad();
extern void HSD_JObjSetupMatrixSub();
extern void MemoryManager_TimedFree(void *p);

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_clFlowChara_Update = { 0x300A0000, 0x0000016C, 0x00000028, 0x000001E8, 0x00060030, 0x0000024C, 0x00000038, 0x00000438, 0x00000040, 0x00000000, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree, 0x8A80001A, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_clFlowChara_Update = {
    (void *)&clFlowChara_Update, 0x00000F5C, (void *)&extab_clFlowChara_Update
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void clFlowChara_Update(void) { /* 0x801C3D48 size:0xF5C */
    nofralloc
    stwu r1, -0xe0(r1)
    mflr r0
    lis r4, lbl_8039AA40@ha
    stw r0, 0xe4(r1)
    stmw r26, 0xc8(r1)
    addi r30, r4, lbl_8039AA40@l
    mr r31, r3
    lwz r8, 0x74c(r30)
    lwz r7, 0x750(r30)
    lwz r6, 0x754(r30)
    lwz r5, 0x758(r30)
    lwz r4, 0x75c(r30)
    lwz r3, 0x760(r30)
    lhz r0, 0x764(r30)
    stw r8, 0x8(r1)
    stw r7, 0xc(r1)
    stw r6, 0x10(r1)
    stw r5, 0x14(r1)
    stw r4, 0x18(r1)
    stw r3, 0x1c(r1)
    sth r0, 0x20(r1)
    bl RumbleUpdate
    lbz r0, 0xc(r31)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C3DC0
    lwz r3, 0x8(r31)
    li r0, 0x0
    addi r3, r3, 0x1
    stw r3, 0x8(r31)
    stb r0, 0xc(r31)
    clFlowChara_Update_L_801C3DC0:
    lwz r3, 0x10(r31)
    addi r0, r3, 0x1
    stw r0, 0x10(r31)
    lwz r0, 0x8(r31)
    cmplwi r0, 0x6
    bgt clFlowChara_Update_L_801C49DC
    lis r3, jumptable_8049AC90@ha
    slwi r0, r0, 2
    addi r3, r3, jumptable_8049AC90@l
    lwzx r0, r3, r0
    mtctr r0
    bctr
    lwz r0, 0x10(r31)
    cmpwi r0, 0x2
    blt clFlowChara_Update_L_801C3E18
    cmpwi r0, 0xe
    bgt clFlowChara_Update_L_801C3E18
    addi r3, r30, 0x70c
    slwi r0, r0, 2
    add r3, r3, r0
    lwz r3, -0x8(r3)
    bl FileLoader_Open
    clFlowChara_Update_L_801C3E18:
    lwz r3, 0x10(r31)
    cmpwi r3, 0xf
    blt clFlowChara_Update_L_801C3E80
    cmpwi r3, 0x1b
    bgt clFlowChara_Update_L_801C3E80
    subi r28, r3, 0xf
    mr r3, r31
    mr r4, r28
    bl GetFrameIdxFromVisualIdx
    slwi r0, r3, 2
    add r3, r31, r0
    lwz r0, 0xa8(r3)
    cmpwi r0, 0x1
    blt clFlowChara_Update_L_801C3E70
    mr r3, r31
    mr r4, r28
    bl GetFrameIdxFromVisualIdx
    li r4, 0x2
    bl GetKartModelNameEntry
    lwz r3, 0x0(r3)
    bl FileLoader_Open
    b clFlowChara_Update_L_801C3E80
    clFlowChara_Update_L_801C3E70:
    slwi r0, r28, 2
    addi r3, r30, 0x5d4
    lwzx r3, r3, r0
    bl FileLoader_Open
    clFlowChara_Update_L_801C3E80:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1c
    bne clFlowChara_Update_L_801C3EDC
    mr r28, r31
    addi r29, r30, 0x70c
    li r27, 0x0
    clFlowChara_Update_L_801C3E98:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C3EB4
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    clFlowChara_Update_L_801C3EB4:
    stw r26, 0xdc(r28)
    addi r4, r31, 0x78
    li r5, 0x0
    lwz r3, 0xdc(r28)
    bl Object_SetAnimBinding
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    addi r29, r29, 0x4
    blt clFlowChara_Update_L_801C3E98
    clFlowChara_Update_L_801C3EDC:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1d
    bne clFlowChara_Update_L_801C3FAC
    mr r28, r31
    addi r29, r30, 0x5d4
    li r27, 0x0
    clFlowChara_Update_L_801C3EF4:
    mr r3, r31
    mr r4, r27
    bl GetFrameIdxFromVisualIdx
    slwi r3, r3, 2
    addi r0, r3, 0xa8
    lwzx r0, r31, r0
    cmpwi r0, 0x1
    blt clFlowChara_Update_L_801C3F78
    li r3, 0x64
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C3F48
    mr r3, r31
    mr r4, r27
    bl GetFrameIdxFromVisualIdx
    mr r4, r3
    mr r3, r26
    li r5, 0x2
    li r6, 0x0
    li r7, 0x0
    bl fn_8021ABFC
    clFlowChara_Update_L_801C3F48:
    lfs f1, lbl_806D9BB0(r2)
    stw r26, 0x144(r28)
    fmr f2, f1
    fmr f3, f1
    lwz r3, 0x144(r28)
    bl fn_8021A660
    lwz r3, 0x144(r28)
    lfs f1, lbl_806D9B7C(r2)
    lfs f2, FLOAT_BRIGHTNESS_DARK(r2)
    lfs f3, lbl_806D9BB4(r2)
    bl fn_8021A71C
    b clFlowChara_Update_L_801C3F98
    clFlowChara_Update_L_801C3F78:
    li r3, 0x5c
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C3F94
    lwz r4, 0x0(r29)
    li r5, 0x0
    bl clNormal3D_Construct
    clFlowChara_Update_L_801C3F94:
    stw r26, 0x110(r28)
    clFlowChara_Update_L_801C3F98:
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0xd
    addi r28, r28, 0x4
    blt clFlowChara_Update_L_801C3EF4
    clFlowChara_Update_L_801C3FAC:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1
    bne clFlowChara_Update_L_801C3FE8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x6
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x7
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C3FE8:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x3
    bne clFlowChara_Update_L_801C4024
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x5
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x8
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C4024:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x5
    bne clFlowChara_Update_L_801C4060
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x4
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x9
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C4060:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x7
    bne clFlowChara_Update_L_801C409C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x3
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xa
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C409C:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x9
    bne clFlowChara_Update_L_801C40D8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x2
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xb
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C40D8:
    lwz r0, 0x10(r31)
    cmpwi r0, 0xb
    bne clFlowChara_Update_L_801C4114
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x1
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xc
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    clFlowChara_Update_L_801C4114:
    lwz r0, 0x10(r31)
    cmpwi r0, 0xd
    bne clFlowChara_Update_L_801C4154
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x0
    li r5, 0x169
    li r6, 0x10
    bl fn_801C37E8
    lwz r0, 0x4(r31)
    addi r5, r1, 0x8
    li r3, 0xd
    li r4, 0x0
    slwi r0, r0, 1
    lhax r5, r5, r0
    bl fn_801B85DC
    clFlowChara_Update_L_801C4154:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x16
    bne clFlowChara_Update_L_801C41A8
    li r3, 0x30
    bl Alloc
    mr. r26, r3
    beq clFlowChara_Update_L_801C4180
    li r4, 0x16a
    li r5, 0x1
    li r6, 0x0
    bl Sprite_InitWithAnim
    clFlowChara_Update_L_801C4180:
    stw r26, 0x5c(r31)
    li r3, 0x1
    lfs f1, lbl_806D9BA8(r2)
    li r0, 0x0
    lwz r4, 0x5c(r31)
    lfs f0, lbl_806D9BBC(r2)
    stfs f1, 0xc(r4)
    stfs f0, 0x10(r4)
    stb r3, lbl_806D184C(r13)
    stb r0, lbl_806D184D(r13)
    clFlowChara_Update_L_801C41A8:
    lis r3, FrameParam_ARRAY_8049aad0@ha
    li r0, 0xd
    addi r5, r3, FrameParam_ARRAY_8049aad0@l
    mr r4, r31
    li r7, 0x1
    mtctr r0
    clFlowChara_Update_L_801C41C0:
    lwz r6, 0x14(r4)
    cmplwi r6, 0x0
    beq clFlowChara_Update_L_801C421C
    lwz r3, 0x8(r5)
    lis r0, 0x4330
    stw r0, 0xb8(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D9B88(r2)
    stw r0, 0xbc(r1)
    lfs f3, 0xc(r5)
    lfd f1, 0xb8(r1)
    lfs f0, 0x10(r5)
    fsubs f1, f1, f2
    lfs f2, 0x14(r5)
    fmadds f0, f3, f1, f0
    stfs f0, 0xc(r6)
    stfs f2, 0x10(r6)
    lwz r3, 0x8(r5)
    cmpwi r3, 0x0
    beq clFlowChara_Update_L_801C421C
    subi r0, r3, 0x1
    li r7, 0x0
    stw r0, 0x8(r5)
    clFlowChara_Update_L_801C421C:
    addi r4, r4, 0x4
    addi r5, r5, 0x18
    bdnz clFlowChara_Update_L_801C41C0
    clrlwi. r0, r7, 24
    beq clFlowChara_Update_L_801C49DC
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1e
    blt clFlowChara_Update_L_801C49DC
    li r27, 0x0
    clFlowChara_Update_L_801C4240:
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x20
    li r6, -0x1
    bl fn_801C37E8
    addi r27, r27, 0x1
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C4240
    li r3, 0x1ae1
    bl fn_801B8918
    lfs f1, lbl_806D9B80(r2)
    addi r3, r1, 0x24
    fmr f2, f1
    fmr f3, f1
    bl PSMTXScale
    lfs f1, FLOAT_SPRITE_INIT_TIME(r2)
    addi r3, r1, 0x54
    li r4, 0x79
    bl PSMTXRotRad
    addi r4, r30, 0x740
    lfs f1, 0x740(r30)
    lfs f2, 0x4(r4)
    addi r3, r1, 0x84
    lfs f3, 0x8(r4)
    bl PSMTXTrans
    addi r3, r31, 0x78
    bl PSMTXIdentity
    addi r4, r31, 0x78
    addi r3, r1, 0x24
    mr r5, r4
    bl PSMTXConcat
    addi r4, r31, 0x78
    addi r3, r1, 0x54
    mr r5, r4
    bl PSMTXConcat
    addi r4, r31, 0x78
    addi r3, r1, 0x84
    mr r5, r4
    bl PSMTXConcat
    lwz r4, 0x4(r31)
    mr r3, r31
    bl GetFrameIdxFromVisualIdx
    mr r4, r3
    mr r3, r31
    bl CharaSelect_SetupCharacterDisplay
    li r0, 0x1
    stb r0, 0x65(r31)
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    li r27, 0x0
    mr r28, r31
    clFlowChara_Update_L_801C4310:
    lwz r3, 0x14(r28)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4344
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clrlwi. r0, r3, 24
    beq clFlowChara_Update_L_801C4344
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x169
    li r6, 0x0
    bl fn_801C37E8
    clFlowChara_Update_L_801C4344:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C4310
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1e
    ble clFlowChara_Update_L_801C49DC
    li r27, 0x0
    mr r28, r31
    clFlowChara_Update_L_801C4368:
    lwz r0, 0x4(r31)
    cmpw r27, r0
    bne clFlowChara_Update_L_801C4390
    lfs f1, FLOAT_FULL_ALPHA(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x1e
    li r6, 0x0
    bl fn_801C37E8
    b clFlowChara_Update_L_801C43A8
    clFlowChara_Update_L_801C4390:
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    mr r4, r27
    li r5, 0x168
    li r6, 0x0
    bl fn_801C37E8
    clFlowChara_Update_L_801C43A8:
    lwz r3, 0x14(r28)
    li r4, 0x1
    bl fn_8019FF6C
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C4368
    lfs f1, 0x6c(r31)
    bl SetScreenBrightness
    li r0, 0x1
    li r3, 0x0
    stb r0, 0xc(r31)
    li r4, 0x1
    bl fn_801699D8
    b clFlowChara_Update_L_801C49DC
    lwz r5, g_pInputState(r13)
    cmplwi r5, 0x0
    bne clFlowChara_Update_L_801C43F8
    li r0, 0x0
    b clFlowChara_Update_L_801C43FC
    clFlowChara_Update_L_801C43F8:
    mr r0, r5
    clFlowChara_Update_L_801C43FC:
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C451C
    cmplwi r5, 0x0
    lwz r4, 0x4(r31)
    bne clFlowChara_Update_L_801C4414
    li r5, 0x0
    clFlowChara_Update_L_801C4414:
    lwz r3, 0x4(r31)
    lwz r0, 0x14(r5)
    add r0, r3, r0
    stw r0, 0x4(r31)
    lwz r0, 0x4(r31)
    cmpwi r0, 0xc
    ble clFlowChara_Update_L_801C4438
    li r0, 0x0
    stw r0, 0x4(r31)
    clFlowChara_Update_L_801C4438:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    bge clFlowChara_Update_L_801C444C
    li r0, 0xc
    stw r0, 0x4(r31)
    clFlowChara_Update_L_801C444C:
    lwz r0, 0x4(r31)
    cmpw r4, r0
    beq clFlowChara_Update_L_801C451C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r5, 0x168
    li r6, -0x1
    bl fn_801C37E8
    lwz r4, 0x4(r31)
    mr r3, r31
    lfs f1, FLOAT_FULL_ALPHA(r2)
    li r5, 0x1e
    li r6, -0x1
    bl fn_801C37E8
    lwz r4, 0x4(r31)
    mr r3, r31
    bl GetFrameIdxFromVisualIdx
    mr r4, r3
    mr r3, r31
    bl CharaSelect_SetupCharacterDisplay
    lwz r0, 0x4(r31)
    addi r3, r1, 0x8
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_801B84B4
    bl fn_801B7CAC
    lwz r5, 0x48(r31)
    cmplwi r5, 0x0
    beq clFlowChara_Update_L_801C44E4
    lwz r0, 0x4(r31)
    lis r3, g_tierCursorPosTable@ha
    addi r4, r3, g_tierCursorPosTable@l
    slwi r0, r0, 3
    add r3, r4, r0
    lfsx f0, r4, r0
    lfs f1, 0x4(r3)
    stfs f0, 0xc(r5)
    stfs f1, 0x10(r5)
    clFlowChara_Update_L_801C44E4:
    lwz r4, 0x4c(r31)
    cmplwi r4, 0x0
    beq clFlowChara_Update_L_801C451C
    lwz r0, 0x4(r31)
    lis r3, g_tierCursorPosTable@ha
    addi r3, r3, g_tierCursorPosTable@l
    lfs f1, FLOAT_ARROW_RIGHT_OFFSET(r2)
    slwi r0, r0, 3
    lfsx f0, r3, r0
    add r3, r3, r0
    lfs f2, 0x4(r3)
    fadds f0, f1, f0
    stfs f0, 0xc(r4)
    stfs f2, 0x10(r4)
    clFlowChara_Update_L_801C451C:
    mr r3, r31
    bl clFlowChara_HandleConfirm
    cmpwi r3, -0x1
    beq clFlowChara_Update_L_801C49DC
    lwz r4, 0x4(r31)
    mr r3, r31
    lfs f1, FLOAT_FULL_ALPHA(r2)
    li r5, 0x1f
    li r6, -0x1
    bl fn_801C37E8
    addi r5, r30, 0x4a4
    lwz r0, 0x4(r31)
    lfs f1, 0x8(r5)
    li r4, 0x0
    slwi r0, r0, 2
    lfs f2, FLOAT_FULL_ALPHA(r2)
    add r3, r31, r0
    fmr f3, f1
    lwz r3, 0xdc(r3)
    lfs f4, 0xc(r5)
    bl clNormal3D_SetScale
    li r0, -0x1
    li r4, 0x1
    stb r0, lbl_806D184C(r13)
    lwz r3, 0x48(r31)
    bl Sprite_Destroy
    lwz r3, 0x4c(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x48(r31)
    stw r3, 0x4c(r31)
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    lbz r0, 0x64(r31)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C49DC
    li r0, 0x1
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x14(r3)
    bl fn_801A024C
    clrlwi. r0, r3, 24
    bne clFlowChara_Update_L_801C4608
    lwz r4, 0x4(r31)
    mr r3, r31
    lfs f1, FLOAT_FULL_ALPHA(r2)
    li r5, 0x1d
    li r6, -0x1
    bl fn_801C37E8
    bl fn_801B87D8
    li r3, 0x0
    li r0, 0x1
    stw r3, 0x10(r31)
    stb r0, 0xc(r31)
    clFlowChara_Update_L_801C4608:
    lis r3, FrameParam_ARRAY_8049aad0@ha
    li r0, 0xd
    addi r4, r3, FrameParam_ARRAY_8049aad0@l
    li r5, 0x0
    li r3, 0x0
    mtctr r0
    clFlowChara_Update_L_801C4620:
    lwz r0, 0x4(r31)
    cmpw r5, r0
    beq clFlowChara_Update_L_801C4630
    stw r3, 0x8(r4)
    clFlowChara_Update_L_801C4630:
    addi r4, r4, 0x18
    addi r5, r5, 0x1
    bdnz clFlowChara_Update_L_801C4620
    b clFlowChara_Update_L_801C49DC
    lwz r0, 0x10(r31)
    cmpwi r0, 0xe
    bne clFlowChara_Update_L_801C4714
    lwz r0, 0x60(r31)
    cmpwi r0, 0xf
    bne clFlowChara_Update_L_801C4670
    lwz r0, 0x4(r31)
    addi r3, r1, 0x8
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_801B8540
    b clFlowChara_Update_L_801C4684
    clFlowChara_Update_L_801C4670:
    lwz r0, 0x4(r31)
    addi r3, r1, 0x8
    slwi r0, r0, 1
    lhax r3, r3, r0
    bl fn_801B8398
    clFlowChara_Update_L_801C4684:
    lwz r3, 0x70(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C46A4
    lwz r12, 0x0(r3)
    li r4, 0x1
    lwz r12, 0x8(r12)
    mtctr r12
    bctrl
    clFlowChara_Update_L_801C46A4:
    lwz r3, 0x74(r31)
    li r4, 0x1
    bl LObjList_Destroy
    li r0, 0x0
    li r4, 0x1
    stw r0, 0x70(r31)
    stw r0, 0x74(r31)
    stb r0, 0x65(r31)
    lwz r3, 0x5c(r31)
    bl Sprite_Destroy
    li r0, 0x0
    li r4, 0x1
    stw r0, 0x5c(r31)
    lwz r3, 0x50(r31)
    bl Sprite_Destroy
    lwz r3, 0x54(r31)
    li r4, 0x1
    bl Sprite_Destroy
    lwz r3, 0x58(r31)
    li r4, 0x1
    bl Sprite_Destroy
    li r0, 0x0
    li r3, 0x0
    stw r0, 0x50(r31)
    li r4, 0x0
    stw r0, 0x54(r31)
    stw r0, 0x58(r31)
    bl fn_801699D8
    clFlowChara_Update_L_801C4714:
    lwz r0, 0x10(r31)
    cmpwi r0, 0xe
    bne clFlowChara_Update_L_801C4768
    lwz r0, 0x4(r31)
    cmpwi r0, 0x6
    beq clFlowChara_Update_L_801C4744
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x6
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4744:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x7
    beq clFlowChara_Update_L_801C4768
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x7
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4768:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x12
    bne clFlowChara_Update_L_801C47BC
    lwz r0, 0x4(r31)
    cmpwi r0, 0x5
    beq clFlowChara_Update_L_801C4798
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x5
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4798:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x8
    beq clFlowChara_Update_L_801C47BC
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x8
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C47BC:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x16
    bne clFlowChara_Update_L_801C4810
    lwz r0, 0x4(r31)
    cmpwi r0, 0x4
    beq clFlowChara_Update_L_801C47EC
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x4
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C47EC:
    lwz r0, 0x4(r31)
    cmpwi r0, 0x9
    beq clFlowChara_Update_L_801C4810
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x9
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4810:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x18
    bne clFlowChara_Update_L_801C4864
    lwz r0, 0x4(r31)
    cmpwi r0, 0x3
    beq clFlowChara_Update_L_801C4840
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x3
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4840:
    lwz r0, 0x4(r31)
    cmpwi r0, 0xa
    beq clFlowChara_Update_L_801C4864
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xa
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4864:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x1c
    bne clFlowChara_Update_L_801C48B8
    lwz r0, 0x4(r31)
    cmpwi r0, 0x2
    beq clFlowChara_Update_L_801C4894
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x2
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C4894:
    lwz r0, 0x4(r31)
    cmpwi r0, 0xb
    beq clFlowChara_Update_L_801C48B8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xb
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C48B8:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x20
    bne clFlowChara_Update_L_801C490C
    lwz r0, 0x4(r31)
    cmpwi r0, 0x1
    beq clFlowChara_Update_L_801C48E8
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x1
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C48E8:
    lwz r0, 0x4(r31)
    cmpwi r0, 0xc
    beq clFlowChara_Update_L_801C490C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0xc
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C490C:
    lwz r0, 0x10(r31)
    cmpwi r0, 0x24
    bne clFlowChara_Update_L_801C493C
    lwz r0, 0x4(r31)
    cmpwi r0, 0x0
    beq clFlowChara_Update_L_801C493C
    lfs f1, FLOAT_ARROW_SCALE(r2)
    mr r3, r31
    li r4, 0x0
    li r5, 0x169
    li r6, 0x1
    bl fn_801C37E8
    clFlowChara_Update_L_801C493C:
    lis r3, FrameParam_ARRAY_8049aad0@ha
    li r0, 0xd
    addi r5, r3, FrameParam_ARRAY_8049aad0@l
    mr r4, r31
    mtctr r0
    clFlowChara_Update_L_801C4950:
    lwz r6, 0x14(r4)
    cmplwi r6, 0x0
    beq clFlowChara_Update_L_801C49B0
    lwz r3, 0x8(r5)
    lis r0, 0x4330
    stw r0, 0xb8(r1)
    xoris r0, r3, 0x8000
    lfd f2, lbl_806D9B88(r2)
    stw r0, 0xbc(r1)
    lfs f3, 0xc(r5)
    lfd f1, 0xb8(r1)
    lfs f0, 0x10(r5)
    fsubs f1, f1, f2
    lfs f2, 0x14(r5)
    fnmsubs f0, f3, f1, f0
    stfs f0, 0xc(r6)
    stfs f2, 0x10(r6)
    lwz r3, 0x8(r5)
    cmpwi r3, 0x0
    beq clFlowChara_Update_L_801C49B0
    cmpwi r3, -0x10
    beq clFlowChara_Update_L_801C49B0
    addi r0, r3, 0x1
    stw r0, 0x8(r5)
    clFlowChara_Update_L_801C49B0:
    addi r4, r4, 0x4
    addi r5, r5, 0x18
    bdnz clFlowChara_Update_L_801C4950
    lwz r0, 0x10(r31)
    cmpwi r0, 0x3c
    bne clFlowChara_Update_L_801C49DC
    li r0, 0x1
    stb r0, 0xc(r31)
    b clFlowChara_Update_L_801C49DC
    lwz r3, 0x60(r31)
    b clFlowChara_Update_L_801C4C90
    clFlowChara_Update_L_801C49DC:
    li r27, 0x0
    mr r28, r31
    clFlowChara_Update_L_801C49E4:
    lwz r3, 0x14(r28)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C49F8
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C49F8:
    addi r27, r27, 0x1
    addi r28, r28, 0x4
    cmpwi r27, 0xd
    blt clFlowChara_Update_L_801C49E4
    lwz r3, 0x5c(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A1C
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A1C:
    lbz r0, 0x65(r31)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C4C8C
    lwz r3, 0x48(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A3C
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A3C:
    lwz r3, 0x4c(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A50
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A50:
    lwz r3, 0x50(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A64
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A64:
    lwz r3, 0x54(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A78
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A78:
    lwz r3, 0x58(r31)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4A8C
    lfs f1, lbl_806D9BC0(r2)
    bl Sprite_AdvanceAnim
    clFlowChara_Update_L_801C4A8C:
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xdc(r3)
    cmplwi r3, 0x0
    beq clFlowChara_Update_L_801C4B20
    bl clNormal3D_Exec
    lwz r0, 0x8(r31)
    cmpwi r0, 0x3
    blt clFlowChara_Update_L_801C4B0C
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xdc(r3)
    bl Object_GetField8
    addi r3, r30, 0x4a4
    lfs f0, 0xc(r3)
    fcmpo cr0, f1, f0
    cror eq, gt, eq
    bne clFlowChara_Update_L_801C4B0C
    li r0, 0x1
    lfs f2, FLOAT_FULL_ALPHA(r2)
    stb r0, 0x64(r31)
    li r4, 0x0
    fsubs f1, f0, f2
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    fmr f3, f1
    add r3, r31, r0
    fmr f4, f1
    lwz r3, 0xdc(r3)
    bl clNormal3D_SetScale
    clFlowChara_Update_L_801C4B0C:
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0xdc(r3)
    bl Object_DriveAnimMatrix
    clFlowChara_Update_L_801C4B20:
    lwz r0, 0x4(r31)
    slwi r4, r0, 2
    add r3, r31, r4
    lwz r0, 0x110(r3)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C4BE8
    lwz r28, 0x1d4(r31)
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4BE8
    bne clFlowChara_Update_L_801C4B58
    la r3, lbl_806D9BC4(r2)  /* lbl_806D9BC4 */
    li r4, 0x47c
    la r5, lbl_806D9BCC(r2)  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4B58:
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4BA0
    bne clFlowChara_Update_L_801C4B74
    la r3, lbl_806D9BC4(r2)  /* lbl_806D9BC4 */
    li r4, 0x25d
    la r5, lbl_806D9BCC(r2)  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4B74:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne clFlowChara_Update_L_801C4B90
    rlwinm. r0, r4, 0, 25, 25
    beq clFlowChara_Update_L_801C4B90
    li r3, 0x1
    clFlowChara_Update_L_801C4B90:
    clrlwi. r0, r3, 24
    beq clFlowChara_Update_L_801C4BA0
    mr r3, r28
    bl HSD_JObjSetupMatrixSub
    clFlowChara_Update_L_801C4BA0:
    lwz r0, 0x4(r31)
    addi r4, r28, 0x44
    li r5, 0x0
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x110(r3)
    bl Object_SetAnimBinding
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x110(r3)
    bl clNormal3D_Exec
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x110(r3)
    bl Object_DriveAnimMatrix
    b clFlowChara_Update_L_801C4C8C
    clFlowChara_Update_L_801C4BE8:
    add r3, r31, r4
    lwz r0, 0x144(r3)
    cmplwi r0, 0x0
    beq clFlowChara_Update_L_801C4C8C
    lwz r28, 0x1d4(r31)
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4C8C
    bne clFlowChara_Update_L_801C4C18
    la r3, lbl_806D9BC4(r2)  /* lbl_806D9BC4 */
    li r4, 0x47c
    la r5, lbl_806D9BCC(r2)  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4C18:
    cmplwi r28, 0x0
    beq clFlowChara_Update_L_801C4C60
    bne clFlowChara_Update_L_801C4C34
    la r3, lbl_806D9BC4(r2)  /* lbl_806D9BC4 */
    li r4, 0x25d
    la r5, lbl_806D9BCC(r2)  /* lbl_806D9BCC */
    bl __assert
    clFlowChara_Update_L_801C4C34:
    lwz r4, 0x14(r28)
    li r3, 0x0
    rlwinm. r0, r4, 0, 8, 8
    bne clFlowChara_Update_L_801C4C50
    rlwinm. r0, r4, 0, 25, 25
    beq clFlowChara_Update_L_801C4C50
    li r3, 0x1
    clFlowChara_Update_L_801C4C50:
    clrlwi. r0, r3, 24
    beq clFlowChara_Update_L_801C4C60
    mr r3, r28
    bl HSD_JObjSetupMatrixSub
    clFlowChara_Update_L_801C4C60:
    lwz r0, 0x4(r31)
    addi r4, r28, 0x44
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x144(r3)
    stw r4, 0x58(r3)
    lwz r0, 0x4(r31)
    slwi r0, r0, 2
    add r3, r31, r0
    lwz r3, 0x144(r3)
    bl fn_8021A9E8
    clFlowChara_Update_L_801C4C8C:
    li r3, -0x1
    clFlowChara_Update_L_801C4C90:
    lmw r26, 0xc8(r1)
    lwz r0, 0xe4(r1)
    mtlr r0
    addi r1, r1, 0xe0
    blr
}
}

/* ------------------------------------------------------------------ */
/* clFlowChara_Destructor (0x801C4CA4): character select flow teardown. */

struct VObj { virtual ~VObj(); };
struct DtorView {
    void *vt;
    char pad04[0x14 - 0x4];
    void *icons[13];
    void *x48[5];
    void *x5C;
    char pad60[0x65 - 0x60];
    unsigned char x65;
    char pad66[0x70 - 0x66];
    VObj *x70;
    void *x74;
    char pad78[0xDC - 0x78];
    void *modelA[13];
    void *modelB[13];
    VObj *holders[13];
    void *x178;
};

extern "C" {
extern void fn_80169C44(void);
extern void Object_DtorWithGXSync(void *o, int del);
extern void clRom_PurgeAll(void);
extern void fn_80120A08(int id);
extern void fn_801A1678(void);
extern void dtor_801BA14C(void *self, int del);




}

extern "C" {
#pragma exceptions on
DtorView *clFlowChara_Destructor(DtorView *self, short del) {
    int i;

    if (self != 0) {
        self->vt = lbl_8049AC7C;
        if ((g_pInputState == 0 ? 0 : g_pInputState) != 0) {
            char *in;
            if ((in = g_pInputState) == 0) {
                in = 0;
            }
            *(unsigned char *)(in + 0x4) = 0;
            *(int *)(in + 0x18) = 0;
            *(int *)(in + 0x1C) = 0;
        }
        SetScreenBrightness(FLOAT_BRIGHTNESS_DARK);
        fn_80169C44();
        Sprite_Destroy(self->x48[0], 1);
        Sprite_Destroy(self->x48[1], 1);
        Sprite_Destroy(self->x48[2], 1);
        Sprite_Destroy(self->x48[3], 1);
        Sprite_Destroy(self->x48[4], 1);
        if (self->x178 != 0) {
            MemoryManager_TimedFree(self->x178);
        }
        for (i = 0; i < 13; i++) {
            Object_DtorWithGXSync(self->modelA[i], 1);
            Object_DtorWithGXSync(self->modelB[i], 1);
            delete self->holders[i];
        }
        clRom_PurgeAll();
        delete self->x70;
        LObjList_Destroy(self->x74, 1);
        self->x70 = 0;
        self->x74 = 0;
        self->x65 = 0;
        fn_80120A08(0x167F);
        fn_80120A08(0x169B);
        fn_80120A08(0x16AC);
        fn_80120A08(0x16AE);
        fn_80120A08(0x16AD);
        fn_80120A08(0x16AF);
        fn_80120A08(0x16A8);
        for (i = 0; i < 13; i++) {
            Sprite_Destroy(self->icons[i], 1);
        }
        Sprite_Destroy(self->x5C, 1);
        fn_801A1678();
        dtor_801BA14C(self, 0);
        if (del > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset
}

/* ------------------------------------------------------------------ */
/* FrameSelection_Init (0x801C4EA8) = clFlowChara ctor. */
extern "C" {
extern const float FLOAT_ARROW_LEFT_SCALE_X, FLOAT_ARROW_LEFT_X, FLOAT_ARROW_RIGHT_X, FLOAT_ARROW_Y;
extern const float FLOAT_INIT_Z_DEPTH, FLOAT_TEX_POS_X, FLOAT_TEX_POS_Y, FLOAT_TEX_SCALE;
extern void SpriteSystem_EnsureInit(void);
extern void SetSyncTarget(int);
extern void SetCourseParams(int, int, int, int);
extern void PreloadResource(int);
extern int GetCoinMilage(void *playerData);
extern unsigned char IsCardValid(void);
extern void TexMgr_Apply(void *self);
extern void InitBGM(void);
extern void SetupBgSprites(int);
extern void InitRumbleController(int);
}

struct InitSprite {
    int field_0x00;
    int field_0x04;
    char _pad8[4];
    float posX;
    float posY;
    float scaleX;
    float scaleY;
    char _pad1C[4];
    float alpha;
    char _pad24[0x30 - 0x24];
    InitSprite(int id, int flag, float x, float y, float sx, float sy, float t, float a);
};

struct InputState {
    char _pad0[4];
    unsigned char field_0x04;
    char _pad5[0x14 - 0x5];
    int field_0x14;
    int field_0x18;
    int field_0x1c;
};

static inline InputState *GetInput(void) {
    return SINGLETON_INSTANCE((InputState *)g_pInputState);
}

#pragma use_lmw_stmw on
struct clFlowBase {
    clFlowBase();
    ~clFlowBase();
};

struct ResCtrl {
    int resId;      /* 0x00 */
    char _pad4[4];
    int mode;       /* 0x08 */
    char _padC[4];
    unsigned char flag;        /* 0x10 */
    char _pad11[3];
    float posY;       /* 0x14 */
    float posX;       /* 0x18 */
    float alpha;      /* 0x1C */
    float fD;         /* 0x20 */
    float fE;         /* 0x24 */
    float fF;         /* 0x28 */
    float scaleX;     /* 0x2C */
    float scaleY;     /* 0x30 */
    ResCtrl();
    ~ResCtrl();
}; /* size 0x34 */

struct TexMgr {
    char _opaque[0x230];
    TexMgr();
    ~TexMgr() {}
};

struct Scene3D {
    char _opaque[0x3084];
    Scene3D(const char *path);
};

struct SceneModel {
    char _opaque[0x28];
    SceneModel(const char *path, int);
};

struct FrameSelection : clFlowBase {
    void *vptr;                    /* 0x000 */
    int visualIdx;                 /* 0x004 */
    int field_0x08;                /* 0x008 */
    unsigned char flag_0x0c;                  /* 0x00C */
    char _pad0D[3];
    int field_0x10;                /* 0x010 */
    int unk_0x14[13];              /* 0x014..0x048 */
    InitSprite *cursorL;               /* 0x048 */
    InitSprite *cursorR;               /* 0x04C */
    InitSprite *spr_0x50;              /* 0x050 */
    InitSprite *spr_0x54;              /* 0x054 */
    InitSprite *spr_0x58;              /* 0x058 */
    int field_0x5c;                /* 0x05C */
    int field_0x60;                /* 0x060 */
    unsigned char flag_0x64;                  /* 0x064 */
    unsigned char flag_0x65;                  /* 0x065 */
    char _pad66[0x6C - 0x66];
    float field_0x6c;                /* 0x06C */
    Scene3D *scene3D;              /* 0x070 */
    SceneModel *sceneModel;        /* 0x074 */
    char _pad78[0xA8 - 0x78];
    int states_0xa8[13];           /* 0x0A8 */
    int arr_0xdc[13];              /* 0x0DC */
    int arr_0x110[13];             /* 0x110 */
    int arr_0x144[13];             /* 0x144 */
    TexMgr *texMgr;                /* 0x178 */
    ResCtrl resCtrl;               /* 0x17C */

    FrameSelection();
}; /* size 0x1B0 */

FrameSelection::FrameSelection() : vptr(lbl_8049AC7C) {
    int i;
    int j;
    int mileage;

    SpriteSystem_EnsureInit();
    SetSyncTarget(0xd);
    SetCourseParams(7, 0, 0, 0);
    PreloadResource(0x167f);
    PreloadResource(0x169b);
    PreloadResource(0x16ac);
    PreloadResource(0x16ae);
    PreloadResource(0x16ad);
    PreloadResource(0x16af);
    for (i = 0; i < 0xd; i++) {
        PreloadResource((int)FrameParam_ARRAY_8049aad0[i].animA);
        PreloadResource((int)FrameParam_ARRAY_8049aad0[i].animB);
    }
    PreloadResource(0x16af);
    PreloadResource(0x16a8);
    PreloadResource(0x1d55);
    PreloadResource(0x1d3e);
    PreloadResource(0x186c);
    PreloadResource(0x16b0);
    PreloadResource(0x16cc);
    PreloadResource(0x1d5c);
    for (i = 0; i < 0xd; i++) {
        unk_0x14[i] = 0;
        FrameParam_ARRAY_8049aad0[i].index = 0;
    }
    visualIdx = 0;
    field_0x60 = -1;
    field_0x08 = 0;
    flag_0x0c = 0;
    field_0x10 = 0;
    field_0x5c = 0;
    scene3D = 0;
    sceneModel = 0;
    field_0x6c = FLOAT_INIT_Z_DEPTH;
    flag_0x64 = 0;
    flag_0x65 = 0;
    cursorL = new InitSprite(0x9c, 1, FLOAT_ARROW_LEFT_X, FLOAT_ARROW_Y,
                         FLOAT_ARROW_LEFT_SCALE_X, FLOAT_ARROW_SCALE,
                         FLOAT_SPRITE_INIT_TIME, FLOAT_FULL_ALPHA);
    cursorR = new InitSprite(0x9c, 1, FLOAT_ARROW_RIGHT_X, FLOAT_ARROW_Y,
                         FLOAT_ARROW_SCALE, FLOAT_ARROW_SCALE,
                         FLOAT_SPRITE_INIT_TIME, FLOAT_FULL_ALPHA);
    spr_0x50 = 0;
    spr_0x54 = 0;
    spr_0x58 = 0;
    texMgr = new TexMgr;
    for (i = 0; i < 0xd; i++) {
        int f = GetFrameIdxFromVisualIdx(this, i);
        if (f == (signed char)g_playerData[0x1b8]) {
            visualIdx = i;
            break;
        }
    }
    if (cursorL != 0) {
        InitSprite *spr = cursorL;
        float x = g_tierCursorPosTable[visualIdx][0];
        float y = g_tierCursorPosTable[visualIdx][1];

        spr->posX = x;
        spr->posY = y;
        cursorL->field_0x04 = 5;
    }
    if (cursorR != 0) {
        InitSprite *spr = cursorR;
        float x = FLOAT_ARROW_RIGHT_OFFSET + g_tierCursorPosTable[visualIdx][0];
        float y = g_tierCursorPosTable[visualIdx][1];

        spr->posX = x;
        spr->posY = y;
        cursorR->field_0x04 = 5;
    }
    mileage = GetCoinMilage(g_playerData);
    for (int k = 0; k < 0xd; k++) {
        arr_0xdc[k] = 0;
        arr_0x110[k] = 0;
        arr_0x144[k] = 0;
        j = GetFrameIdxFromVisualIdx(this, k);
        if (mileage >= fullThresholds[j]) {
            states_0xa8[j] = 2;
        } else if (mileage >= partialThresholds[j]) {
            states_0xa8[j] = 1;
        } else {
            states_0xa8[j] = 0;
        }
        if (IsCardValid() == 0) {
            states_0xa8[j] = 1;
        }
    }
    scene3D = new Scene3D(modelName13);
    sceneModel = new SceneModel(modelName13, 1);
    TexMgr tm;

    TexMgr_SetTexture(&tm, GetTextureByIdAndLang(
                               textureIds[GetFrameIdxFromVisualIdx(this, visualIdx)] + 0x95, -1));
    TexMgr_Apply(&tm);
    resCtrl.resId = 0x1d5c;
    resCtrl.scaleX = FLOAT_TEX_SCALE;
    resCtrl.scaleY = FLOAT_TEX_SCALE;
    resCtrl.flag = 1;
    resCtrl.posY = FLOAT_TEX_POS_Y;
    resCtrl.posX = FLOAT_TEX_POS_X;
    resCtrl.alpha = FLOAT_FULL_ALPHA;
    {
        InputState *in = GetInput();

        if (in != 0) {
            in = GetInput();
            in->field_0x04 = 1;
            in->field_0x18 = 0;
            in->field_0x1c = 0;
        }
    }
    SetScreenBrightness(FLOAT_BRIGHTNESS_DARK);
    InitBGM();
    SetupBgSprites(1);
    InitRumbleController(1);
}

#pragma use_lmw_stmw reset

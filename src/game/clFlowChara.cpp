/* clFlowChara (character select flow), merged TU.
 * .text 0x801C3470..0x801C53A0, .data 0x8049AA58..0x8049ACB0, .rodata 0x8039AA40..0x8039B1F4.
 * The original source was one C++ TU; functions use CSE'd pool bases into the
 * .data/.rodata of this TU, so they have to live together. */
#include "game/singleton.h"

#include "game/CharaDisplayPrivate.h"
/* Character selection constant pool, 8039AA40..8039B1F4. */
static const float motionCurves[255] = {
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
/* .data 0x8049AA58..0x8049ACB0 (the last 0x20 bytes are the switch table
 * the compiler generates for clFlowChara_Update). */
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
extern char clFlowChara_data_806CFDC0[8]; /* .sdata - clFlowBase RTTI */
extern char clFlowChara_data_806CFDC8[8]; /* .sdata - clFlowChara RTTI {name, bases} */
struct DtorView;
DtorView *clFlowChara_Destructor(DtorView *self, short del);
struct CharaView;
int clFlowChara_Update(CharaView *self);
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
void *clFlowChara_data_8049AC70[3] = { clFlowChara_data_806CFDC0, 0, 0 };
/* Only reached through FrameSelection_Init's pool base (g_charaStatTable+0x224). */
#pragma force_active on
void *clFlowChara_Destructor_data_8049AC7C[5] = {
    clFlowChara_data_806CFDC8, 0, (void *)clFlowChara_Destructor, (void *)clFlowChara_Update, (void *)fn_801C3AA4
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
/* clFlowChara_Update (0x801C3D48) */
extern "C" {
void LObjList_Destroy(void *l, int del);
void MemoryManager_TimedFree(void *p);
}
#pragma use_lmw_stmw on
typedef float CharaMatrix[3][4];
class CharaNormal {
    unsigned char storage[92];
public:
    CharaNormal(const char*, int);
};
class CharaModel {
public:
    unsigned char beforeMatrix[0x58];
    CharaMatrix* matrix;
    unsigned char tail[8];
    CharaModel(int, int, unsigned char, unsigned char);
};
class CharaSprite {
public:
    unsigned char beforePosition[12];
    float x, y;
    unsigned char remaining[28];
    void SetPos(float px, float py) { x = px; y = py; }
    CharaSprite(int, unsigned char, int);
};
struct CharaInput { unsigned char pad[0x14]; int delta; };
struct CharaJoint {
    unsigned char pad[0x14]; unsigned int flags;
    unsigned char pad18[0x2C]; CharaMatrix matrix;
};
struct CharaOwner { virtual void Destroy(short); };
struct CharaView {
    unsigned int unknown;
    int selection, state;
    unsigned char pending, padD[3];
    int frame;
    CharaSprite* sprites[13];
    CharaSprite* leftArrow;
    CharaSprite* rightArrow;
    CharaSprite* stats[3];
    CharaSprite* header;
    int result;
    unsigned char complete, display, pad66[2];
    int unknown68;
    float brightness;
    CharaOwner* owner;
    void* lightList;
    CharaMatrix matrix;
    int variants[13];
    CharaNormal* normals[13];
    CharaNormal* alternateNormals[13];
    CharaModel* models[13];
    unsigned char pad178[0x5C];
    CharaJoint* joint;
};
extern "C" {
extern signed char lbl_806D184C, lbl_806D184D;
extern const float FLOAT_ARROW_RIGHT_OFFSET, FLOAT_ARROW_SCALE;
extern const float FLOAT_BRIGHTNESS_DARK, FLOAT_FULL_ALPHA, FLOAT_SPRITE_INIT_TIME;
extern const float lbl_806D9B7C, lbl_806D9B80, lbl_806D9BA8;
extern const float lbl_806D9BB0, lbl_806D9BB4, lbl_806D9BBC, lbl_806D9BC0;
extern const char lbl_806D9BC4[7], lbl_806D9BCC[5];
void RumbleUpdate();
void* FileLoader_Open(const char*);
const char** GetKartModelNameEntry(int, int);
int fn_801B85DC(int, unsigned char, short);
int fn_801B8918(int);
void PSMTXScale(CharaMatrix*, float, float, float);
void PSMTXRotRad(CharaMatrix*, int, float);
void PSMTXTrans(CharaMatrix*, float, float, float);
void PSMTXIdentity(CharaMatrix*);
void PSMTXConcat(CharaMatrix*, CharaMatrix*, CharaMatrix*);
int Sprite_AdvanceAnim(CharaSprite*, float);
int fn_8019FF6C(CharaSprite*, unsigned char);
void fn_801699D8(unsigned int, unsigned char);
int fn_801B84B4(int);
void fn_801B7CAC();
int fn_801A024C(CharaSprite*);
int fn_801B87D8();
int fn_801B8540(int);
int fn_801B8398(int);
int clNormal3D_Exec(CharaNormal*);
float Object_GetField8(CharaNormal*);
int Object_DriveAnimMatrix(CharaNormal*);
int Object_SetAnimBinding(CharaNormal*, CharaMatrix*, CharaJoint*);
void fn_8021A660(CharaModel*, float, float, float);
void fn_8021A71C(CharaModel*, float, float, float);
void fn_8021A9E8(CharaModel*);
void __assert(const char*, int, const char*);
void HSD_JObjSetupMatrixSub(CharaJoint*);
}
static inline CharaInput* CurrentCharaInput()
{
    return SINGLETON_INSTANCE((CharaInput*)g_pInputState);
}
static inline int ApplyCharaInput(CharaView* self, CharaInput* input)
{
    int previous = self->selection;
    self->selection += input->delta;
    return previous;
}
static inline CharaMatrix* CharaJointMatrix(CharaJoint* joint)
{
    if (!joint) __assert(lbl_806D9BC4, 0x47C, lbl_806D9BCC);
    if (joint) {
        if (!joint) __assert(lbl_806D9BC4, 0x25D, lbl_806D9BCC);
        unsigned char update = 0;
        if (!(joint->flags & 0x00800000) && (joint->flags & 0x40)) update = 1;
        if (update) HSD_JObjSetupMatrixSub(joint);
    }
    return &joint->matrix;
}
extern "C" int clFlowChara_Update(CharaView* self)
{
    struct SoundIds { short ids[13]; };
    SoundIds soundCopy = *(const SoundIds*)characterAnims;
    CharaMatrix translation, rotation, scale;
    RumbleUpdate();
    if (self->pending) { ++self->state; self->pending = 0; }
    ++self->frame;
    switch (self->state) {
    case 0: {
        if (self->frame >= 2 && self->frame <= 14)
            FileLoader_Open(selectModels[self->frame - 2]);
        if (self->frame >= 15 && self->frame <= 27) {
            int visual = self->frame - 15;
            if (self->variants[GetFrameIdxFromVisualIdx(self, visual)] >= 1)
                FileLoader_Open(*GetKartModelNameEntry(GetFrameIdxFromVisualIdx(self, visual), 2));
            else FileLoader_Open(demoModels[visual]);
        }
        if (self->frame == 28) {
            for (int i = 0; i < 13; ++i) {
                self->normals[i] = new CharaNormal(selectModels[i], 0);
                Object_SetAnimBinding(self->normals[i], &self->matrix, 0);
            }
        }
        if (self->frame == 29) {
            for (int i = 0; i < 13; ++i) {
                if (self->variants[GetFrameIdxFromVisualIdx(self, i)] >= 1) {
                    self->models[i] = new CharaModel(GetFrameIdxFromVisualIdx(self, i), 2, 0, 0);
                    fn_8021A660(self->models[i], lbl_806D9BB0, lbl_806D9BB0, lbl_806D9BB0);
                    fn_8021A71C(self->models[i], lbl_806D9B7C, FLOAT_BRIGHTNESS_DARK, lbl_806D9BB4);
                } else {
                    self->alternateNormals[i] = new CharaNormal(demoModels[i], 0);
                }
            }
        }
        if (self->frame == 1) {
            fn_801C37E8((FrameSet*)self, 6, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8((FrameSet*)self, 7, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 3) {
            fn_801C37E8((FrameSet*)self, 5, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8((FrameSet*)self, 8, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 5) {
            fn_801C37E8((FrameSet*)self, 4, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8((FrameSet*)self, 9, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 7) {
            fn_801C37E8((FrameSet*)self, 3, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8((FrameSet*)self, 10, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 9) {
            fn_801C37E8((FrameSet*)self, 2, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8((FrameSet*)self, 11, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 11) {
            fn_801C37E8((FrameSet*)self, 1, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801C37E8((FrameSet*)self, 12, 0x169, 16, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 13) {
            fn_801C37E8((FrameSet*)self, 0, 0x169, 16, FLOAT_ARROW_SCALE);
            fn_801B85DC(13, 0, soundCopy.ids[self->selection]);
        }
        if (self->frame == 22) {
            self->header = new CharaSprite(0x16A, 1, 0);
            self->header->SetPos(lbl_806D9BA8, lbl_806D9BBC);
            lbl_806D184C = 1; lbl_806D184D = 0;
        }
        unsigned char done = 1;
        for (int i = 0; i < 13; ++i) {
            if (self->sprites[i]) {
                self->sprites[i]->SetPos(FrameParam_ARRAY_8049aad0[i].step * (float)FrameParam_ARRAY_8049aad0[i].index + FrameParam_ARRAY_8049aad0[i].baseX, FrameParam_ARRAY_8049aad0[i].y);
                if (FrameParam_ARRAY_8049aad0[i].index) { --FrameParam_ARRAY_8049aad0[i].index; done = 0; }
            }
        }
        if (done && self->frame >= 30) {
            for (int i = 0; i < 13; ++i) fn_801C37E8((FrameSet*)self, i, 0x20, -1, FLOAT_ARROW_SCALE);
            fn_801B8918(0x1AE1);
            PSMTXScale(&scale, lbl_806D9B80, lbl_806D9B80, lbl_806D9B80);
            PSMTXRotRad(&rotation, 'y', FLOAT_SPRITE_INIT_TIME);
            const float* pos = selectScale;
            PSMTXTrans(&translation, pos[0], pos[1], pos[2]);
            PSMTXIdentity(&self->matrix);
            PSMTXConcat(&scale, &self->matrix, &self->matrix);
            PSMTXConcat(&rotation, &self->matrix, &self->matrix);
            PSMTXConcat(&translation, &self->matrix, &self->matrix);
            CharaSelect_SetupCharacterDisplay((CharaDisplay*)self, GetFrameIdxFromVisualIdx(self, self->selection));
            self->display = 1; self->pending = 1;
        }
        break;
    }
    case 1:
        for (int i = 0; i < 13; ++i)
            if (self->sprites[i] && (unsigned char)Sprite_AdvanceAnim(self->sprites[i], lbl_806D9BC0))
                fn_801C37E8((FrameSet*)self, i, 0x169, 0, FLOAT_ARROW_SCALE);
        if (self->frame > 30) {
            for (int i = 0; i < 13; ++i) {
                if (i == self->selection) fn_801C37E8((FrameSet*)self, i, 0x1E, 0, FLOAT_FULL_ALPHA);
                else fn_801C37E8((FrameSet*)self, i, 0x168, 0, FLOAT_ARROW_SCALE);
                fn_8019FF6C(self->sprites[i], 1);
            }
            SetScreenBrightness(self->brightness); self->pending = 1;
            fn_801699D8(0, 1);
        }
        break;
    case 2:
        if (CurrentCharaInput()) {
            int previous = self->selection;
            CharaInput *in = CurrentCharaInput();
            self->selection += in->delta;
            if (self->selection > 12) self->selection = 0;
            if (self->selection < 0) self->selection = 12;
            if (previous != self->selection) {
                fn_801C37E8((FrameSet*)self, previous, 0x168, -1, FLOAT_ARROW_SCALE);
                fn_801C37E8((FrameSet*)self, self->selection, 0x1E, -1, FLOAT_FULL_ALPHA);
                CharaSelect_SetupCharacterDisplay((CharaDisplay*)self, GetFrameIdxFromVisualIdx(self, self->selection));
                fn_801B84B4(soundCopy.ids[self->selection]); fn_801B7CAC();
            if (self->leftArrow) {
                self->leftArrow->SetPos(g_tierCursorPosTable[self->selection][0], g_tierCursorPosTable[self->selection][1]);
            }
            if (self->rightArrow) {
                self->rightArrow->SetPos(FLOAT_ARROW_RIGHT_OFFSET + g_tierCursorPosTable[self->selection][0], g_tierCursorPosTable[self->selection][1]);
            }
            }
        }
        if (clFlowChara_HandleConfirm((ConfirmView*)self) != -1) {
            fn_801C37E8((FrameSet*)self, self->selection, 0x1F, -1, FLOAT_FULL_ALPHA);
            const float* range = displayScale;
            clNormal3D_SetScale(self->normals[self->selection], 0, range[2], FLOAT_FULL_ALPHA, range[2], range[3]);
            lbl_806D184C = -1;
            Sprite_Destroy(self->leftArrow, 1); Sprite_Destroy(self->rightArrow, 1);
            self->leftArrow = 0; self->rightArrow = 0; self->pending = 1;
        }
        break;
    case 3:
        if (self->complete) self->pending = 1;
        break;
    case 4:
        if ((unsigned char)fn_801A024C(self->sprites[self->selection]) == 0) {
            fn_801C37E8((FrameSet*)self, self->selection, 0x1D, -1, FLOAT_FULL_ALPHA);
            fn_801B87D8(); self->frame = 0; self->pending = 1;
        }
        for (int i = 0; i < 13; ++i) if (i != self->selection) FrameParam_ARRAY_8049aad0[i].index = 0;
        break;
    case 5:
        if (self->frame == 14) {
            if (self->result == 15) fn_801B8540(soundCopy.ids[self->selection]);
            else fn_801B8398(soundCopy.ids[self->selection]);
            if (self->owner) self->owner->Destroy(1);
            LObjList_Destroy(self->lightList, 1);
            self->owner = 0; self->lightList = 0; self->display = 0;
            Sprite_Destroy(self->header, 1); self->header = 0;
            Sprite_Destroy(self->stats[0], 1); Sprite_Destroy(self->stats[1], 1); Sprite_Destroy(self->stats[2], 1);
            self->stats[0] = 0; self->stats[1] = 0; self->stats[2] = 0;
            fn_801699D8(0, 0);
        }
        if (self->frame == 14) {
            if (self->selection != 6) fn_801C37E8((FrameSet*)self, 6, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 7) fn_801C37E8((FrameSet*)self, 7, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 18) {
            if (self->selection != 5) fn_801C37E8((FrameSet*)self, 5, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 8) fn_801C37E8((FrameSet*)self, 8, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 22) {
            if (self->selection != 4) fn_801C37E8((FrameSet*)self, 4, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 9) fn_801C37E8((FrameSet*)self, 9, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 24) {
            if (self->selection != 3) fn_801C37E8((FrameSet*)self, 3, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 10) fn_801C37E8((FrameSet*)self, 10, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 28) {
            if (self->selection != 2) fn_801C37E8((FrameSet*)self, 2, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 11) fn_801C37E8((FrameSet*)self, 11, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 32) {
            if (self->selection != 1) fn_801C37E8((FrameSet*)self, 1, 0x169, 1, FLOAT_ARROW_SCALE);
            if (self->selection != 12) fn_801C37E8((FrameSet*)self, 12, 0x169, 1, FLOAT_ARROW_SCALE);
        }
        if (self->frame == 36 && self->selection != 0) fn_801C37E8((FrameSet*)self, 0, 0x169, 1, FLOAT_ARROW_SCALE);
        for (int i = 0; i < 13; ++i) {
            if (self->sprites[i]) {
                self->sprites[i]->SetPos(FrameParam_ARRAY_8049aad0[i].baseX - FrameParam_ARRAY_8049aad0[i].step * (float)FrameParam_ARRAY_8049aad0[i].index, FrameParam_ARRAY_8049aad0[i].y);
                if (FrameParam_ARRAY_8049aad0[i].index != 0 && FrameParam_ARRAY_8049aad0[i].index != -16) ++FrameParam_ARRAY_8049aad0[i].index;
            }
        }
        if (self->frame == 60) self->pending = 1;
        break;
    case 6: return self->result;
    }
    for (int i = 0; i < 13; ++i)
        if (self->sprites[i]) Sprite_AdvanceAnim(self->sprites[i], lbl_806D9BC0);
    if (self->header) Sprite_AdvanceAnim(self->header, lbl_806D9BC0);
    if (self->display) {
        if (self->leftArrow) Sprite_AdvanceAnim(self->leftArrow, lbl_806D9BC0);
        if (self->rightArrow) Sprite_AdvanceAnim(self->rightArrow, lbl_806D9BC0);
        if (self->stats[0]) Sprite_AdvanceAnim(self->stats[0], lbl_806D9BC0);
        if (self->stats[1]) Sprite_AdvanceAnim(self->stats[1], lbl_806D9BC0);
        if (self->stats[2]) Sprite_AdvanceAnim(self->stats[2], lbl_806D9BC0);
        if (self->normals[self->selection]) {
            clNormal3D_Exec(self->normals[self->selection]);
            if (self->state >= 3 && Object_GetField8(self->normals[self->selection]) >= (displayScale)[3]) {
                self->complete = 1;
                float end = (displayScale)[3] - FLOAT_FULL_ALPHA;
                clNormal3D_SetScale(self->normals[self->selection], 0, end, FLOAT_FULL_ALPHA, end, end);
            }
            Object_DriveAnimMatrix(self->normals[self->selection]);
        }
        if (self->alternateNormals[self->selection] && self->joint) {
            CharaMatrix* matrix = CharaJointMatrix(self->joint);
            Object_SetAnimBinding(self->alternateNormals[self->selection], matrix, 0);
            clNormal3D_Exec(self->alternateNormals[self->selection]);
            Object_DriveAnimMatrix(self->alternateNormals[self->selection]);
        } else if (self->models[self->selection] && self->joint) {
            CharaMatrix* matrix = CharaJointMatrix(self->joint);
            self->models[self->selection]->matrix = matrix;
            fn_8021A9E8(self->models[self->selection]);
        }
    }
    return -1;
}
#pragma use_lmw_stmw reset

/* ------------------------------------------------------------------ */
/* clFlowChara_Destructor (0x801C4CA4): character select flow teardown. */

#include "game/types/VObj.h"
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
        self->vt = clFlowChara_Destructor_data_8049AC7C;
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

#include "game/types/TexMgr.h"

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

FrameSelection::FrameSelection() : vptr(clFlowChara_Destructor_data_8049AC7C) {
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

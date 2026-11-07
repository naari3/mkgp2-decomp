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
extern signed char g_charaStatTable[][13][3];
extern const float FLOAT_FULL_ALPHA, FLOAT_SPRITE_INIT_TIME;
extern const float lbl_806D9B60, lbl_806D9B64, lbl_806D9B68, lbl_806D9B6C;
extern const float FLOAT_ARROW_RIGHT_OFFSET, lbl_806D9B74, lbl_806D9B78, lbl_806D9B7C;
void clNormal3D_SetScale(void*, int, float, float, float, float);
void *ResolveJointByName(void*, const char*);
void Sprite_Destroy(DisplaySprite*, short);
void Sprite_SetAnimParam(DisplaySprite*, short, int);
void *GetTextureByIdAndLang(int, int);
void TexMgr_SetTexture(DisplayTexture*, void*, ...);
void fn_801F93EC(DisplayTexture*, float, float);
int isJapanese();
}
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

#include "game/CharaDisplayPrivate.h"
extern "C" {
extern const unsigned char lbl_8039AA40[];
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
extern "C" void CharaSelect_SetupCharacterDisplay(CharaDisplay *self, int character) {
    const unsigned char *data = lbl_8039AA40;
    if (character <= -1 || character >= 13) self->character = 0;
    else self->character = character;
    const float (&scale)[4] = *(const float (*)[4])(data + 0x4A4);
    clNormal3D_SetScale(self->normals[self->selection], 0, scale[0], FLOAT_FULL_ALPHA, scale[0], scale[1]);
    if (self->alternateNormals[self->selection]) {
        clNormal3D_SetScale(self->alternateNormals[self->selection], 0, FLOAT_FULL_ALPHA, FLOAT_FULL_ALPHA, FLOAT_SPRITE_INIT_TIME, FLOAT_SPRITE_INIT_TIME);
    }
    self->joint = ResolveJointByName(self->normals[self->selection], (const char*)(data + 0x798));
    Sprite_Destroy(self->stats[0], 1);
    Sprite_Destroy(self->stats[1], 1);
    Sprite_Destroy(self->stats[2], 1);
    self->stats[0] = new DisplaySprite(0x16B, 1, lbl_806D9B60, lbl_806D9B64);
    self->stats[1] = new DisplaySprite(0x16B, 1, lbl_806D9B60, lbl_806D9B68);
    self->stats[2] = new DisplaySprite(0x16B, 1, lbl_806D9B60, lbl_806D9B6C);
    const int *anims = (const int*)(data + 0x768);
    signed char *stat = g_charaStatTable[self->variants[self->character]][character];
    const int *cursor = anims;
    int i = 0;
    while (i < 5 - stat[0]) { Sprite_SetAnimParam(self->stats[0], (short)*cursor, -1); ++cursor; ++i; }
    const int *cursor2 = anims;
    signed char *stat2 = stat + 1;
    int j = 0;
    while (j < 5 - *stat2) { Sprite_SetAnimParam(self->stats[1], (short)*cursor2, -1); ++cursor2; ++j; }
    signed char *stat3 = stat + 2;
    int k = 0;
    while (k < 5 - *stat3) { Sprite_SetAnimParam(self->stats[2], (short)*anims, -1); ++anims; ++k; }
    TexMgr_SetTexture(self->texture, GetTextureByIdAndLang((*(const int (*)[13])(data + 0x464))[character] + 0x95, -1));
    fn_801F93EC(self->texture, FLOAT_ARROW_RIGHT_OFFSET, lbl_806D9B74);
    float width = isJapanese() == 0 ? lbl_806D9B78 : lbl_806D9B7C;
    self->texture->width = width;
}

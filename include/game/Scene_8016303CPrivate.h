#ifndef GAME_SCENE_8016303C_PRIVATE_H
#define GAME_SCENE_8016303C_PRIVATE_H

/* Credit panel labels, positioned through its two transform slots. */
struct CreditLabels162 {
    char pad0[0x84];
    int credits;
    unsigned char pad88[2];
    unsigned char multiple;
    unsigned char changed;
};

extern "C" {
extern const char Scene_8016303C_rodata_80369288[];
extern const char lbl_806D88DC[8];
extern const float lbl_806D8890;
extern const float lbl_806D88CC, lbl_806D88D0, lbl_806D88D4;
extern const float lbl_806D88D8, lbl_806D88E4, lbl_806D88E8;
int isJapanese();
const char *GetTextureByIdAndLang(int, int);
void fn_801473DC(void *, int, int, int, float, float, float, float, float, float, float, float);
void fn_80147200(void *, int, const char *, float, float, float, float, float, float, float, float, ...);
}

#define LABEL(p, slot, text, y) fn_80147200(p, slot, text, lbl_806D88D4, y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)
#define COUNT_LABEL(p, text, y) fn_80147200(p, 0, text, lbl_806D88D4, y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, p->credits)
#define TEXTURE(p, slot, text, x) fn_80147200(p, slot, text, x, lbl_806D8890, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f)

#endif

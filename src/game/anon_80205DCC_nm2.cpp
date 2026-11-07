#include "game/YesNoButtonDrawPrivate.h"

/*
 * Left-hand selector credit display (0x8020615C..0x802064D8).
 */

extern "C" {
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
extern unsigned char lbl_80598A60[];
extern const char lbl_803C25A8[];
extern const float lbl_806DAB34;
extern const float lbl_806DAB38;
extern const float lbl_806DAB3C;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB68;
extern const float lbl_806DAB78;
extern const float lbl_806DAB7C;
extern const float lbl_806DAB80;
extern const float lbl_806DAB84;
extern const float lbl_806DAB88;
extern const float lbl_806DAB8C;
extern const float lbl_806DAB90;
extern const float lbl_806DAB94;
extern const float lbl_806DAB98;
extern const float lbl_806DAB9C;
extern const float lbl_806DABA0;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C2688[3];
extern const float lbl_803C2694[3];
}

#pragma push
#pragma opt_lifetimes off
void YesNoButtonL::DrawCredits() {
    const char *pool = lbl_803C25A8;
    int lay = layer;
    float oy;
    float f = -fn_8020A6CC(fade.p);
    oy = lbl_806DAB10;
    unsigned int col = Color();
    if (kind == 1) {
        oy = lbl_806DAB60;
    }
    bool show = 0;
    int credits = 0;
    if (kind == 1) {
        if (CreditMgr_GetPlayState(2) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(2);
        }
    } else if (kind == 2 || kind == 10) {
        if (CreditMgr_GetPlayState(3) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(3);
        }
    } else if (kind == 11 || kind == 12) {
        if (CreditMgr_GetPlayState(4) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(4);
        }
    } else if (kind == 3 || kind == 4) {
        if (CreditMgr_GetPlayState(1) == 3) {
            show = 0;
        } else {
            show = 1;
            credits = CreditMgr_GetCreditCount(1);
        }
    }
    if (credits <= 0) {
        field80 = 1;
    }
    if (show) {
        if (!field80) {
            if (!isJapanese()) {
                if (lbl_80598A60[0x27] == 0) {
                    if (CreditMgr_GetCoinCount(0, -1) == 0) {
                        TexMgr_SetTexture(&texts[0], pool + 0x148, credits);
                    } else {
                        TexMgr_SetTexture(&texts[0], pool + 0x158, credits);
                    }
                } else if (CreditMgr_GetCoinCount(0, -1) == 0) {
                    TexMgr_SetTexture(&texts[0], pool + 0x16C, credits);
                } else {
                    TexMgr_SetTexture(&texts[0], pool + 0x178, credits);
                }
                TexMgr_SetTexture(&texts[1], pool + 0x188);
            } else {
                TexMgr_SetTexture(&texts[0], pool + 0x19C);
                TexMgr_SetTexture(&texts[1], pool + 0x1AC, credits);
            }
        } else {
            TexMgr_SetTexture(&texts[0], text0);
            TexMgr_SetTexture(&texts[1], text1);
        }
    }
    oy = lbl_806DAB84 + oy;
    f = lbl_806DAB88 + f;
    for (int i = 0; i < 2; i++) {
        float dy = (float)(i * 0x1C);
        texts[i].color = col;
        fn_801F93EC(&texts[i], scaleX * f + (x + field34), scaleY * (dy + oy) + (y + field38));
        fn_801F93D0(&texts[i], scaleX, scaleY);
        fn_801F8A34(fn_801F8E58(), &texts[i], lay);
    }
}
#pragma pop


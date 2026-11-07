#include "game/YesNoButtonDrawPrivate.h"

/*
 * Left-hand selector button and the shared button animation
 * (0x80205DCC..0x80207324).
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

void YesNoButtonL::Update() {
    ResCtrl c;
    int lay = layer;
    unsigned int col = Color();
    float f = -fn_8020A6CC(fade.p);
    YN_PUT(c, 0x72F, col, lbl_806DAB00[0], lbl_806DAB08[0], lay);
    YN_PUT(c, 0x72E, col, lbl_806DAB00[1] + f, lbl_806DAB08[1], lay);
    DrawLabel();
    if (field6D) {
        DrawCredits();
    }
    Animate();
    if (field6C) {
        fader70.p->Step();
        fader74.p->Step();
        fader78.p->Step();
        if (fader74.p->Done()) {
            float v = fn_8020A6CC(fader74.p);
            if (lbl_806DAB38 == v) {
                fn_8020A734(fader74.p, 5, lbl_806DAB38, lbl_806DAB3C);
                fn_8020A734(fader78.p, 5, lbl_806DAB3C, lbl_806DAB38);
                return;
            }
            if (lbl_806DAB3C == v) {
                fn_8020A734(fader74.p, 0xF, lbl_806DAB3C, lbl_806DAB78);
                fn_8020A734(fader78.p, 0xF, lbl_806DAB38, lbl_806DAB7C);
                return;
            }
            if (lbl_806DAB78 == v) {
                fn_8020A7CC(fader70.p, 0xFF, 0, 0xF);
                fn_8020A734(fader74.p, 5, lbl_806DAB78, lbl_806DAB7C);
                fn_8020A734(fader78.p, 5, lbl_806DAB7C, lbl_806DAB78);
                return;
            }
            if (lbl_806DAB7C == v) {
                fn_8020A7CC(fader70.p, 0xFF, 0, 0xF);
                fn_8020A734(fader74.p, 0xA, lbl_806DAB7C, lbl_806DAB80);
                fn_8020A734(fader78.p, 0xA, lbl_806DAB78, lbl_806DAB80);
                return;
            }
            fn_8020A7CC(fader70.p, 0, 0xFF, 0x14);
            fn_8020A734(fader74.p, 0xF, lbl_806DAB34, lbl_806DAB38);
            fn_8020A734(fader78.p, 0xF, lbl_806DAB34, lbl_806DAB3C);
        }
    }
}

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
        texts[i].color = col;
        fn_801F93EC(&texts[i], scaleX * f + (x + field34), scaleY * (oy + (float)(i * 0x1C)) + (y + field38));
        fn_801F93D0(&texts[i], scaleX, scaleY);
        fn_801F8A34(fn_801F8E58(), &texts[i], lay);
    }
}

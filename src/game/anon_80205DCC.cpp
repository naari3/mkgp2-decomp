#include "game/FlowYesNo.h"

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
        fn_801F93EC(&texts[i], scaleX * f + (x + field34), scaleY * ((float)(i * 0x1C) + oy) + (y + field38));
        fn_801F93D0(&texts[i], scaleX, scaleY);
        fn_801F8A34(fn_801F8E58(), &texts[i], lay);
    }
}

void YesNoButtonL::DrawLabel() {
    ResCtrl c;
    int lay = layer;
    float f = -fn_8020A6CC(fade.p);
    float oy = lbl_806DAB10;
    unsigned int col = Color();
    if (kind == 1) {
        oy = lbl_806DAB8C;
    }
    if (field6C && state <= 1) {
        fn_80121E10(&c);
        c.resId = 0x730;
        c.SetColor((col & ~0xFF) | fn_8020A788(fader70.p));
        float sy = scaleY * fn_8020A6CC(fader78.p);
        float sx = scaleX * fn_8020A6CC(fader74.p);
        c.SetScaleXY(sx, sy);
        c.Show(scaleX * (lbl_803C2688[0] + f) + (x + field34), scaleY * (lbl_803C2694[0] + oy) + (y + field38),
               lbl_806DAB20);
        fn_8011FAFC(&c, lay);
    }
    if (!isJapanese()) {
        int res = 0x729;
        float py;
        float px = scaleX * (lbl_803C2688[1] + f) + (x + field34);
        py = scaleY * (lbl_803C2694[1] + oy) + (y + field38);
        if (kind == 0) {
            res = 0x74C;
            px += lbl_806DAB68 * scaleX;
        } else if (kind == 1) {
            res = 0x74E;
            px += lbl_806DAB68 * scaleX;
        }
        PutAbs(c, res, col, px, py, lay);
    } else {
        float px = scaleX * (lbl_803C2688[1] + f) + (x + field34);
        float py = scaleY * (lbl_803C2694[1] + oy) + (y + field38);
        PutAbs(c, 0x729, col, px, py, lay);
    }
    YN_PUT(c, field18, col, lbl_803C2688[2] + f, lbl_803C2694[2] + oy, lay);
}

extern "C" void fn_8020688C(VObject *obj) {
    delete obj;
}

YesNoButtonL::~YesNoButtonL() {
    delete[] texts;
}

void YesNoButton::Animate() {
    bool sel = selected;
    field34 = fn_8020A6CC(offX.p);
    field38 = fn_8020A6CC(offY.p);
    FlowFaderF *ap = appear.p;
    float p = fn_8020A6CC(pulse.p);
    scale = lbl_806DAB18 * (fn_8020A6CC(ap) * p);
    scaleX = scale * fn_8020A6CC(zoomX.p);
    scaleY = scale * fn_8020A6CC(zoomY.p);
    alpha = fn_8020A788(alphaF.p);
    fade.p->Step();
    pulse.p->Step();
    if (pulse.p->Done()) {
        float v = fn_8020A6CC(pulse.p);
        if (lbl_806DAB24 == v) {
            if (sel) {
                fn_8020A734(fade.p, 5, lbl_806DAB30, lbl_806DAB2C);
                fn_8020A734(pulse.p, 5, lbl_806DAB24, lbl_806DAB20);
            } else {
                fn_8020A734(fade.p, 5, lbl_806DAB30, lbl_806DAB14);
                fn_8020A734(pulse.p, 5, lbl_806DAB24, lbl_806DAB1C);
            }
        } else if (lbl_806DAB1C == v) {
            if (sel) {
                fn_8020A734(fade.p, 5, lbl_806DAB14, lbl_806DAB30);
                fn_8020A734(pulse.p, 5, lbl_806DAB1C, lbl_806DAB24);
            } else {
                fn_8020A734(fade.p, 5, lbl_806DAB14, lbl_806DAB10);
                fn_8020A734(pulse.p, 5, lbl_806DAB1C, lbl_806DAB18);
            }
        }
    }
    zoomX.p->Step();
    zoomY.p->Step();
    if (sel) {
        if (zoomX.p->Done()) {
            float v = fn_8020A6CC(zoomX.p);
            if (lbl_806DAB24 == v) {
                fn_8020A734(zoomX.p, 5, lbl_806DAB24, lbl_806DAB28);
                fn_8020A734(zoomY.p, 5, lbl_806DAB28, lbl_806DAB24);
            } else if (lbl_806DAB28 == v) {
                fn_8020A734(zoomX.p, 0xF, lbl_806DAB28, lbl_806DAB90);
                fn_8020A734(zoomY.p, 0xF, lbl_806DAB24, lbl_806DAB94);
            } else if (lbl_806DAB90 == v) {
                fn_8020A734(zoomX.p, 5, lbl_806DAB90, lbl_806DAB94);
                fn_8020A734(zoomY.p, 5, lbl_806DAB94, lbl_806DAB90);
            } else if (lbl_806DAB94 == v) {
                fn_8020A734(zoomX.p, 0xA, lbl_806DAB94, lbl_806DAB20);
                fn_8020A734(zoomY.p, 0xA, lbl_806DAB90, lbl_806DAB20);
            } else {
                fn_8020A734(zoomX.p, 0xF, lbl_806DAB20, lbl_806DAB24);
                fn_8020A734(zoomY.p, 0xF, lbl_806DAB20, lbl_806DAB28);
            }
        }
    }
    appear.p->Step();
    offX.p->Step();
    offY.p->Step();
    alphaF.p->Step();
    if (appear.p->Done()) {
        float v = fn_8020A6CC(appear.p);
        switch (state) {
        case 0:
            if (lbl_806DAB98 == v) {
                fn_8020A734(appear.p, 5, lbl_806DAB98, lbl_806DAB20);
                return;
            }
            fn_8020A734(appear.p, 1, lbl_806DAB20, lbl_806DAB20);
            state = 1;
            return;
        case 2:
            if (lbl_806DAB18 == v) {
                fn_8020A734(appear.p, 5, lbl_806DAB18, lbl_806DAB9C);
                return;
            }
            if (lbl_806DAB9C == v) {
                fn_8020A734(appear.p, 0xF, lbl_806DAB9C, lbl_806DAB34);
                fn_8020A734(offX.p, 0xF, lbl_806DAB10, lbl_806DABA0 - x);
                fn_8020A734(offY.p, 0xF, lbl_806DAB10, lbl_806DAB4C - y);
                fn_8020A7CC(alphaF.p, 0xFF, 0, 0xF);
                return;
            }
            state = 3;
            return;
        case 3:
            field0C = 1;
            state = -1;
            break;
        }
    }
}

/* Out-of-line deleting dtor of the abstract YesNoButton (vtable lbl_804EC54C). */
extern "C" YesNoButton *dtor_802070EC(YesNoButton *self, short flag) {
    if (self) {
        self->~YesNoButton();
        if (flag > 0) {
            operator delete(self);
        }
    }
    return self;
}

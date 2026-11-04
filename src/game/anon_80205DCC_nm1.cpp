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
    self->~YesNoButton();
    if (flag > 0) {
        operator delete(self);
    }
    return self;
}

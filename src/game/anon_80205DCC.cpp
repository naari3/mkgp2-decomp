#include "game/YesNoButtonDrawPrivate.h"

/*
 * Left-hand selector button background and update (0x80205DCC..0x8020615C).
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

static inline float LocalX(const YesNoButton *button, float offset) {
    return offset * button->scaleX + (button->x + button->field34);
}

static inline float LocalY(const YesNoButton *button, float offset) {
    return offset * button->scaleY + (button->y + button->field38);
}

static inline float SlidingX(const YesNoButton *button, float offset, float slide) {
    return button->scaleX * (offset + slide) + (button->x + button->field34);
}

static inline void DrawBackground(YesNoButtonL *button) {
    ResCtrl c;
    int lay = button->layer;
    unsigned int col = button->Color();
    float f = -fn_8020A6CC(button->fade.p);
    fn_80121E10(&c);
    c.resId = 0x72F;
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float px = LocalX(button, lbl_806DAB00[0]);
    float py = LocalY(button, lbl_806DAB08[0]);
    c.Show(px, py, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
    fn_80121E10(&c);
    c.resId = 0x72E;
    c.SetColor(col);
    c.SetScaleXY(button->scaleX, button->scaleY);
    float px2 = SlidingX(button, lbl_806DAB00[1], f);
    float py2 = LocalY(button, lbl_806DAB08[1]);
    c.Show(px2, py2, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
}

void YesNoButtonL::Update() {
    DrawBackground(this);
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

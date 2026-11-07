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

static inline float ButtonX(const YesNoButton *button, float offset) {
    return button->scaleX * offset + (button->x + button->field34);
}

static inline float ButtonY(const YesNoButton *button, float offset) {
    return button->scaleY * offset + (button->y + button->field38);
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
        float px = scaleX * (lbl_803C2688[0] + f) + (x + field34);
        float py = scaleY * (lbl_803C2694[0] + oy) + (y + field38);
        c.Show(px, py, lbl_806DAB20);
        fn_8011FAFC(&c, lay);
    }
    if (!isJapanese()) {
        int res = 0x729;
        float px;
        float py;
        px = scaleX * (lbl_803C2688[1] + f) + (x + field34);
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
        float py;
        float px;
        px = scaleX * (lbl_803C2688[1] + f) + (x + field34);
        py = scaleY * (lbl_803C2694[1] + oy) + (y + field38);
        PutAbs(c, 0x729, col, px, py, lay);
    }
    fn_80121E10(&c);
    c.resId = field18;
    c.SetColor(col);
    c.SetScaleXY(scaleX, scaleY);
    float px = ButtonX(this, lbl_803C2688[2] + f);
    float py = ButtonY(this, lbl_803C2694[2] + oy);
    c.Show(px, py, lbl_806DAB20);
    fn_8011FAFC(&c, lay);
}

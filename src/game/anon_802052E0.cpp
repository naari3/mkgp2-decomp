#include "game/FlowYesNoRescue.h"

/*
 * Selector sparkle and right-hand button drawing (0x802052E0..0x80205DCC).
 */

extern "C" {
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
float fn_8020A6CC(FlowFader *fader);
void *fn_801F8E58(void);
void fn_801F8A34(void *a, TextManager *tm, int layer);
void fn_801F93D0(TextManager *tm, float sx, float sy);
void fn_80270C78(void *arr, void *dtor);
extern const float lbl_806DAB58;
extern const float lbl_806DAB5C;
extern const float lbl_806DAB60;
extern const float lbl_806DAB64;
extern const float lbl_806DAB68;
extern const float lbl_806DAB00[2];
extern const float lbl_806DAB08[2];
extern const float lbl_803C26A0[3];
extern const float lbl_803C26AC[3];
}

void YesNoSpark::Draw() {}

void YesNoSpark::Update() {
    ResCtrl c;
    float off = fn_8020A6CC(offset.p);
    float s = fn_8020A6CC(scale.p);
    unsigned int col = (unsigned int)(lbl_806DAB58 * fn_8020A6CC(alpha.p)) | ~0xFF;
    float px;
    if (flag) {
        px = x + off;
    } else {
        px = x - off;
    }
    c.resId = 0x8A3;
    c.Show(px, y, lbl_806DAB20);
    c.SetColor(col);
    c.SetScale(s);
    c.flipX = flag == 0;
    c.flipY = 0;
    fn_8011FAFC(&c, layer);
    offset.p->Step();
    scale.p->Step();
    alpha.p->Step();
    if (alpha.p->Done()) {
        if (lbl_806DAB20 == fn_8020A6CC(alpha.p)) {
            fn_8020A734(alpha.p, 0xA, lbl_806DAB20, lbl_806DAB5C);
            return;
        }
        field0C = 1;
    }
}

extern "C" void fn_80205498(VObject *obj) {
    delete obj;
}

YesNoSpark::~YesNoSpark() {}

void YesNoButtonR::Draw() {}

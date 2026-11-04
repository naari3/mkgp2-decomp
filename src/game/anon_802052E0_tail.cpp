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

extern "C" void fn_80205B34(VObject *obj) {
    delete obj;
}

YesNoButtonR::~YesNoButtonR() {
    delete[] texts;
}

void YesNoButtonL::Draw() {}

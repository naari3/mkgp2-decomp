#include "game/FlowScene.h"
extern "C" {
extern const float lbl_806D89E8, lbl_806D89EC, lbl_806D8A04, lbl_806D8A08, lbl_806D8A0C, lbl_806D8A10;
void fn_8011FAFC(ResCtrl *, void *);
void fn_801678FC(void *dst, float red, float green, float blue, float alpha) {
    ResCtrl r;
    r.mode = 2;
    r.SetSize(lbl_806D89E8, lbl_806D89EC);
    r.Show(lbl_806D8A04, lbl_806D8A08, lbl_806D8A0C);
    r.SetColor(((unsigned char)(int)(lbl_806D8A10 * red) << 24) |
               ((unsigned char)(int)(lbl_806D8A10 * green) << 16) |
               ((unsigned char)(int)(lbl_806D8A10 * blue) << 8) |
               (unsigned char)(int)(lbl_806D8A10 * alpha));
    fn_8011FAFC(&r, dst);
}
}

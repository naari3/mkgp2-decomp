#include "game/FlowScene.h"
extern "C" {
extern const float lbl_806D8A0C, lbl_806D8A10;
void fn_8011FAFC(ResCtrl *, void *);
void fn_8016918C(void *dst, int id, float x, float y, float sx, float sy, float red, float green, float blue, float alpha, unsigned int flags) {
    if (id < 0) return;
    ResCtrl r;
    r.resId = id;
    r.Show(x, y, lbl_806D8A0C);
    r.SetScaleXY(sx, sy);
    r.SetColor(((unsigned char)(int)(lbl_806D8A10 * red) << 24) | ((unsigned char)(int)(lbl_806D8A10 * green) << 16) | ((unsigned char)(int)(lbl_806D8A10 * blue) << 8) | (unsigned char)(int)(lbl_806D8A10 * alpha));
    if (flags & 1) { r.tail[0] = 1; r.tail[1] = 4; r.tail[2] = 1; }
    if (flags & 2) r.mode = 3;
    fn_8011FAFC(&r, dst);
}
}

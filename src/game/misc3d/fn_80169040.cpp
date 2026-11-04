#include "game/FlowScene.h"
extern "C" {
extern const float lbl_806D8A0C, lbl_806D8A10;
void fn_8011FAFC(ResCtrl *, void *);
void fn_80169040(void *dst, int id, float x, float y, float sx, float sy, float rotation, float alpha, unsigned int flags) {
    if (id < 0) return;
    ResCtrl r;
    r.resId = id;
    r.Show(x, y, lbl_806D8A0C);
    r.SetScaleXY(sx, sy);
    r.field28 = rotation;
    r.SetColor(0xFFFFFF00 + ((int)(lbl_806D8A10 * alpha) & 255));
    if (flags & 1) { r.tail[0] = 1; r.tail[1] = 4; r.tail[2] = 1; }
    if (flags & 2) r.mode = 3;
    fn_8011FAFC(&r, dst);
}
}

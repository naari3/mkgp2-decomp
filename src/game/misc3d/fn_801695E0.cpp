#include "game/FlowScene.h"
extern "C" {
void fn_8011FAFC(ResCtrl *, void *);
void fn_801695E0(void *dst, int id, float x, float y, float alpha, unsigned int flags) {
    if (id < 0) return;
    ResCtrl r;
    r.resId = id;
    r.Show(x, y, 1.0f);
    r.SetColor(0xFFFFFF00 | (unsigned char)(int)(255.0f * alpha));
    if (flags & 1) { r.tail[0] = 1; r.tail[1] = 4; r.tail[2] = 1; }
    if (flags & 2) r.mode = 3;
    fn_8011FAFC(&r, dst);
}
}


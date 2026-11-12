/*
 * 0x8020E3D0..0x8020F220: fading logo task (resource 0x2AFA) and the task
 * list that runs it.
 */

#include "game/types/clTimeup.h"
#include "game/FadeLogoFactory.h"

#pragma auto_inline off

#include "game/types/clTimeupTime.h"

extern "C" {
extern const float lbl_806DACD8;
extern const float lbl_806DACDC;
extern const float lbl_806DACE0;
extern const float lbl_806DACE4;
extern const float lbl_806DACE8;
extern const float lbl_806DACEC;
extern const float lbl_806DACF0;
extern const float lbl_806DACF4;
extern const float lbl_806DACF8;
void fn_8011FAFC(ResCtrl *ctrl, int layer);
}

inline clTimeupDisp::clTimeupDisp(int layer_, int id_) : clCTaskInterface(id_), layer(layer_), list(new TaskListImpl) {
    TaskListImpl *l = list.p;
    l->Add(new clTimeupTime(layer_, 0), 0);
}

extern "C" clTimeupDisp *fn_8020E3D0(int layer, int id) {
    return new clTimeupDisp(layer, id);
}

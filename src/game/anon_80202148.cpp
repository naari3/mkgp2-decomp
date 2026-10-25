/*
 * Character-class selector flow task @ 0x80202148..0x80202BCC.
 */

#include "game/FlowCountdown.h"

extern "C" {
extern const float lbl_806DA8C8;
extern const float lbl_806DA8CC;
extern const float lbl_806DA8D0;
extern const float lbl_806DA8D4;
extern const float lbl_806DA8D8;
extern const float lbl_806DA8DC;
extern const float lbl_806DA8E0;
extern const float lbl_806DA8E4;
extern const float lbl_806DA8E8;
extern const float lbl_806DA8EC;
extern const float lbl_806DA8F0;
extern const float lbl_806DA8F4;
extern const float lbl_806DA8F8;
extern const float lbl_806DA8FC;
extern const float lbl_806DA900;
extern const float lbl_806DA904;
extern const float lbl_806DA908;
extern const float lbl_806DA90C;
extern int lbl_803C0300[22];
extern FlowSceneList *lbl_806D19E0;
extern int lbl_806D19E4;
extern int g_ccClass;
void fn_80120A08(int id);
}

/* Character-class selector (vtable lbl_804EC358). */
struct ClassSelTask : FlowTask {
    VHolder<FlowSceneList> list;
    int cur;
    int prev;
    int layer;
    VHolder<FlowFaderF> fade;
    VHolder<FlowFaderF> slideOut;
    VHolder<FlowFaderF> slideIn;
    VHolder<FlowFaderF> scale;
    FlowFaderF *bg;
    ClassSelTask(int cur_, int layer_, int id);
    ~ClassSelTask();
    virtual void _key3();
};

static inline void SetScaleXY(ResCtrl &c, float sx, float sy) {
    c.scaleX = sx;
    c.scaleY = sy;
}

extern "C" void fn_80202180(ClassSelTask *self) {
    self->list.p->Draw();
}

extern "C" void fn_802021B0(ClassSelTask *self) {
    ResCtrl ctrl;
    int col = -1;
    if (self->cur == 0) {
        col = -0x100;
    }
    if (self->prev != self->cur) {
        int res = lbl_803C0300[self->prev];
        float px = lbl_806DA8D0 + fn_8020A6CC(self->slideOut.p);
        float s = fn_8020A6CC(self->scale.p);
        fn_80121E10(&ctrl);
        ctrl.resId = res;
        ctrl.Show(px, lbl_806DA8D4, 1.0f);
        SetScaleXY(ctrl, s, 1.0f);
        if (self->prev == 0) {
            ctrl.SetColor(-0x100);
        } else {
            ctrl.SetColor(-1);
        }
        fn_8011FAFC(&ctrl, self->layer);
        res = lbl_803C0300[self->cur];
        fn_80121E10(&ctrl);
        ctrl.resId = res;
        ctrl.Show(lbl_806DA8D0 + fn_8020A6CC(self->slideIn.p), lbl_806DA8D4, 1.0f);
        ctrl.SetColor(col);
        fn_8011FAFC(&ctrl, self->layer);
    } else {
        int res = lbl_803C0300[self->cur];
        fn_80121E10(&ctrl);
        ctrl.resId = res;
        ctrl.Show(lbl_806DA8D0, lbl_806DA8D4, 1.0f);
        ctrl.SetColor(col);
        fn_8011FAFC(&ctrl, self->layer);
    }
    self->slideOut.p->Step();
    self->slideIn.p->Step();
    self->scale.p->Step();
    if (self->slideOut.p->Done()) {
        float v = fn_8020A6CC(self->slideOut.p);
        if (lbl_806DA8D8 == v) {
            fn_8020A734(self->slideOut.p, 6, lbl_806DA8D8, lbl_806DA8DC);
            fn_8020A734(self->scale.p, 6, lbl_806DA8E0, 1.0f);
        } else if (lbl_806DA8DC == v) {
            fn_8020A734(self->slideOut.p, 4, lbl_806DA8DC, lbl_806DA8E4);
            fn_8020A734(self->scale.p, 1, 1.0f, 1.0f);
        } else if (lbl_806DA8E4 == v) {
            fn_8020A734(self->slideOut.p, 3, lbl_806DA8E4, lbl_806DA8E8);
        } else if (lbl_806DA8E8 == v) {
            fn_8020A734(self->slideOut.p, 0xA, lbl_806DA8E8, lbl_806DA8EC);
        } else if (lbl_806DA8EC == v) {
            fn_8020A734(self->slideOut.p, 1, lbl_806DA8CC, lbl_806DA8CC);
        }
    }
    if (self->slideIn.p->Done()) {
        float v = fn_8020A6CC(self->slideIn.p);
        if (lbl_806DA8F0 == v) {
            fn_8020A734(self->slideIn.p, 0xF, lbl_806DA8F0, lbl_806DA8F4);
        } else if (lbl_806DA8F4 == v) {
            fn_8020A734(self->slideIn.p, 5, lbl_806DA8F8, lbl_806DA8FC);
        } else if (lbl_806DA8FC == v) {
            fn_8020A734(self->slideIn.p, 1, lbl_806DA8CC, lbl_806DA8CC);
            self->prev = self->cur;
        }
    }
    self->list.p->Update();
}

extern "C" void fn_8020258C(VObject *obj) {
    delete obj;
}

ClassSelTask::~ClassSelTask() {
    if (g_ccClass != 0) {
        fn_80120A08(0x8C5);
    }
    fn_801F4D3C(list.p);
    delete[] bg;
}

ClassSelTask::ClassSelTask(int cur_, int layer_, int id)
    : FlowTask(id), list(new SceneListImpl), cur(cur_), prev(cur_), layer(layer_),
      fade(new FlowFaderF(lbl_806DA8CC)), slideOut(new FlowFaderF(lbl_806DA8CC)),
      slideIn(new FlowFaderF(lbl_806DA8CC)), scale(new FlowFaderF(lbl_806DA8CC)) {
    if (g_ccClass != 0) {
        PreloadResource(0x8C5);
    }
    bg = new FlowFaderF[2];
    fn_8020A734(bg, 0x1E0, lbl_806DA904, lbl_806DA908);
    fn_8020A734(bg + 1, 0x1E0, lbl_806DA90C, lbl_806DA904);
    fn_8020A734(fade.p, 0x3C, lbl_806DA8C8, lbl_806DA900);
    fn_8020A734(slideOut.p, 1, lbl_806DA8CC, lbl_806DA8CC);
    fn_8020A734(slideIn.p, 1, lbl_806DA8CC, lbl_806DA8CC);
    fn_8020A734(scale.p, 1, lbl_806DA8C8, lbl_806DA8C8);
}

extern "C" void fn_802029EC(void) {
    if (lbl_806D19E0) {
        lbl_806D19E0->Draw();
    }
}

extern "C" void fn_80202A24(void) {
    if (lbl_806D19E0) {
        lbl_806D19E0->Update();
    }
}

extern "C" int fn_80202A5C(int sel) {
    if (lbl_806D19E0 == 0) {
        return 0;
    }
    FlowTask *t = fn_801F4DC0(lbl_806D19E0, 0);
    if (t) {
        ClassSelTask *c = dynamic_cast<ClassSelTask *>(t);
        int next = 0;
        int old = c->cur;
        if (old > -1 && old < 22) {
            next = sel;
        }
        c->prev = old;
        c->cur = next;
        if (c->prev != c->cur) {
            fn_8020A734(c->slideOut.p, 7, lbl_806DA8CC, lbl_806DA8D8);
            fn_8020A734(c->slideIn.p, 0xA, lbl_806DA8F0, lbl_806DA8F0);
            fn_8020A734(c->scale.p, 7, lbl_806DA8C8, lbl_806DA8E0);
        }
        return 1;
    }
    return 0;
}

extern "C" int fn_80202B48(int cur) {
    if (lbl_806D19E0 == 0) {
        return 0;
    }
    int layer = lbl_806D19E4;
    fn_801F4DF0(lbl_806D19E0, new ClassSelTask(cur, layer, 0), 2);
    return 1;
}

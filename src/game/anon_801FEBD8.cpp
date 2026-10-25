/*
 * Countdown timer display tasks @ 0x801FEBD8..0x801FF670.
 */

#include "game/FlowCountdown.h"

extern "C" void fn_801FEBD8(Countdown *self) {
    self->list.p->Draw();
}

extern "C" void fn_801FEC08(Countdown *self) {
    ResCtrl ctrl;
    if (self->timer > 0) {
        int frac;
        ctrl.resId = 0x869;
        ctrl.Show(self->x, self->y, lbl_806DA878);
        fn_8011FAFC(&ctrl, self->layer);
        frac = self->timer % 60;
        if (frac % 4 == 0) {
            FlowTask *t = fn_801F4DC0(self->list.p, frac / 4);
            if (t) {
                CountdownDot *dot = dynamic_cast<CountdownDot *>(t);
                dot->active = 1;
                fn_8020A734(dot->scale.p, 8, lbl_806DA87C, lbl_806DA878);
                fn_8020A7CC(dot->fade.p, 0xFF, 0, 8);
            }
        }
        if (frac == 0) {
            FlowSceneList *list;
            int secs = self->timer / 60;
            int id = secs + 10000;
            if (fn_801F4DC0(self->list.p, id) == 0) {
                list = self->list.p;
                int layer = self->layer;
                fn_801F4DF0(list, new CountdownDigit(id, layer, secs), 0);
                FlowTask *t = fn_801F4DC0(self->list.p, id);
                if (t) {
                    dynamic_cast<CountdownDigit *>(t)->SetPos(self->x, self->y);
                }
            }
        }
    }
    if (self->field0C >= 2) {
        fn_801F4D3C(self->list.p);
    }
    self->list.p->Update();
}

extern "C" void fn_801FEF18(Countdown *self, int timer) {
    if (timer < 0 || timer > 5999) {
        timer = 0;
    }
    self->timer = timer;
}

extern "C" void fn_801FEF34(Countdown *self, float x, float y) {
    int i;
    self->x = x;
    self->y = y;
    for (i = 0; i < 15; i++) {
        FlowTask *t = fn_801F4DC0(self->list.p, i);
        if (t) {
            dynamic_cast<CountdownDot *>(t)->SetPos(self->x, self->y);
        }
    }
}

extern "C" void fn_801FEFD4(VObject *obj) {
    delete obj;
}

extern "C" Countdown *fn_801FF00C(int layer, int id) {
    return new Countdown(layer, id);
}

Countdown::~Countdown() {
    fn_801F4D3C(list.p);
}

Countdown::Countdown(int layer_, int id)
    : FlowTask(id), list(new SceneListImpl), layer(layer_), x(lbl_806DA884), y(lbl_806DA888),
      fade(new FlowFaderI), timer(0), field28(0) {
    FlowSceneList *l;
    int lay;
    int i;
    PreloadResource(0x869);
    for (i = 0; i < 15; i++) {
        l = list.p;
        lay = layer;
        fn_801F4DF0(l, new CountdownDot(i, lay), 0);
        FlowTask *t = fn_801F4DC0(list.p, i);
        if (t) {
            dynamic_cast<CountdownDot *>(t)->SetPos(x, y);
        }
    }
}

extern "C" void fn_801FF3E4(void) {
}

extern "C" void fn_801FF3E8(CountdownDot *self) {
    ResCtrl c[2];
    float s = fn_8020A6CC(self->scale.p);
    int col = fn_8020A788(self->fade.p) | ~0xFF;
    c[0].resId = lbl_803C01C4[self->index];
    c[1].resId = lbl_803C01C4[self->index];
    c[1].mode = 3;
    c[0].SetScale(s);
    c[1].SetScale(s);
    float px = s * lbl_803C014C[self->index][0] + self->x;
    float py = s * lbl_803C014C[self->index][1] + self->y;
    c[0].Show(px, py, lbl_806DA878);
    c[1].Show(px, py, lbl_806DA878);
    switch (self->active) {
    case 1:
        c[1].SetColor(col);
        self->scale.p->Step();
        self->fade.p->Step();
        if (self->scale.p->Done()) {
            c[0].SetScale(lbl_806DA878);
            c[1].SetScale(lbl_806DA878);
            c[1].SetColor(0xFFFFFF00);
            fn_8020A7CC(self->fade.p, 0xFF, 0, 0x30);
            self->active = 2;
        }
        fn_8011FAFC(&c[0], self->layer);
        fn_8011FAFC(&c[1], self->layer);
        break;
    case 2:
        c[0].SetColor(col);
        self->fade.p->Step();
        if (self->fade.p->Done()) {
            c[0].SetColor(0xFFFFFF00);
            self->active = 3;
        }
        fn_8011FAFC(&c[0], self->layer);
        break;
    case 3:
        self->active = 0;
        fn_8020A734(self->scale.p, 1, lbl_806DA878, lbl_806DA878);
        fn_8020A7CC(self->fade.p, 0, 0, 1);
        break;
    }
}

/*
 * Countdown timer display tasks (part 2) @ 0x801FF670..0x8020007C.
 */

#include "game/FlowCountdown.h"

extern "C" void fn_801FF670(VObject *obj) {
    delete obj;
}

CountdownDot::~CountdownDot() {
}

extern "C" void fn_801FF790(void) {
}

extern "C" void fn_801FF794(CountdownDigit *self) {
    ResCtrl ctrl;
    float s = fn_8020A6CC(self->scale.p);
    int col = (fn_8020A788(self->fade.p) & 0xFF) | ~0xFF;
    int d;
    d = fn_8020A900(self->seconds, 1);
    fn_80121E10(&ctrl);
    ctrl.resId = lbl_803C0200[d];
    {
        float px = lbl_803C0228[0][0] * s + self->x;
        float py = lbl_803C0228[0][1] * s + self->y;
        ctrl.Show(px, py, lbl_806DA878);
    }
    ctrl.SetScale(s);
    ctrl.SetColor(col);
    fn_8011FAFC(&ctrl, self->layer);
    d = fn_8020A900(self->seconds, 0);
    fn_80121E10(&ctrl);
    ctrl.resId = lbl_803C0200[d];
    {
        float px = lbl_803C0228[1][0] * s + self->x;
        float py = lbl_803C0228[1][1] * s + self->y;
        ctrl.Show(px, py, lbl_806DA878);
    }
    ctrl.SetScale(s);
    ctrl.SetColor(col);
    fn_8011FAFC(&ctrl, self->layer);
    self->scale.p->Step();
    self->fade.p->Step();
    if (self->scale.p->Done()) {
        if (lbl_806DA87C == fn_8020A6CC(self->scale.p)) {
            fn_8020A734(self->scale.p, 0x1E, lbl_806DA87C, lbl_806DA878);
        } else {
            self->field0C = 1;
        }
    }
}

extern "C" void fn_801FF99C(VObject *obj) {
    delete obj;
}

CountdownDigit::~CountdownDigit() {
}

extern "C" void fn_801FFABC(void) {
}

#define LOOKUP_BANNER_RES()                         \
    for (i = 0; i < 14; i++) {                      \
        if (count < lbl_803C00DC[i].threshold) {    \
            break;                                  \
        }                                           \
        res = lbl_803C00DC[i].resId;                \
    }

extern "C" void fn_801FFAC0(CountdownBanner *self) {
    int count;
    int type;
    int res;
    res = 0x883;
    type = self->type;
    count = self->counter;
    int i;
    CountdownResStep *e;
    switch (type) {
    case 0:
        LOOKUP_BANNER_RES();
        break;
    case 3:
    case 4:
    case 5:
        LOOKUP_BANNER_RES();
        break;
    case 1:
        LOOKUP_BANNER_RES();
        break;
    case 2:
        LOOKUP_BANNER_RES();
        break;
    }
    {
        ResCtrl ctrl;
        float s = fn_8020A6CC(self->scale.p);
        int col;
        fn_80121E10(&ctrl);
        ctrl.resId = res;
        ctrl.Show(self->x, self->y, lbl_806DA878);
        ctrl.SetScale(s);
        fn_8011FAFC(&ctrl, self->layer);
        switch (count) {
        case 0x12:
            self->resId = 0x88B;
            fn_8020A7CC(self->fade.p, 0, 0xFF, 0xC);
            break;
        case 0x4E:
            self->resId = 0x88A;
            fn_8020A7CC(self->fade.p, 0, 0xFF, 0xC);
            break;
        }
        col = fn_8020A788(self->fade.p) | ~0xFF;
        fn_80121E10(&ctrl);
        ctrl.resId = self->resId;
        ctrl.Show(self->x, self->y, lbl_806DA878);
        ctrl.SetScale(s);
        ctrl.SetColor(col);
        fn_8011FAFC(&ctrl, self->layer);
        self->partA.p->SetPos(self->x, self->y);
        self->partB.p->SetPos(self->x, self->y);
        self->partA.p->mul = s;
        self->partB.p->mul = s;
        fn_80200A48(self->partA.p);
        fn_80200654(self->partB.p);
        self->fade.p->Step();
        if (self->fade.p->Done() && fn_8020A788(self->fade.p) == 0xFF) {
            fn_8020A7CC(self->fade.p, 0xFF, 0, 0xE);
        }
        self->scale.p->Step();
        if (self->scale.p->Done()) {
            switch (self->state) {
            case 0:
                self->state = 1;
                break;
            case 1:
                break;
            case 2:
                self->field0C = 1;
                self->state = 3;
                break;
            }
        }
    }
    {
        int limit = 60;
        self->counter++;
        int c = self->counter;
        if (type == 3 || type == 4 || type == 5) {
            limit = 120;
        }
        if (c >= limit) {
            self->counter = 0;
        }
    }
}

extern "C" void fn_801FFFF4(CountdownBanner *self) {
    if (self->state <= 1) {
        fn_8020A734(self->scale.p, 0xF, lbl_806DA878, lbl_806DA880);
        self->state = 2;
    }
}

extern "C" void fn_80200044(VObject *obj) {
    delete obj;
}

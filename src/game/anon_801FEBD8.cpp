/*
 * clMnTimeSprTask timer display tasks @ 0x801FEBD8..0x801FF670.
 */

#include "game/types/clMnTimeSprTask.h"

/* Reuse the original RTTI records through the CW cast runtime. */
extern "C" {
void *fn_80271340(void *, int, void *, void *, int);
extern unsigned char FlowTask_RTTI_806D01E8[8];
extern unsigned char CountdownDot_RTTI_806D01F0[8];
extern unsigned char CountdownDigit_RTTI_806D01F8[8];
}

static inline clMnTimeLightsSpr *CastCountdownDot(FlowTask *task) {
    return dynamic_cast<clMnTimeLightsSpr *>((clMnTaskInterface *)task);
}

static inline clMnTimeNumSpr *CastCountdownDigit(FlowTask *task) {
    return dynamic_cast<clMnTimeNumSpr *>((clMnTaskInterface *)task);
}

#define LOOKUP_BANNER_RES()                         \
    for (i = 0; i < 14; i++) {                      \
        if (count < lbl_803C00DC[i].threshold) {    \
            break;                                  \
        }                                           \
        res = lbl_803C00DC[i].resId;                \
    }


/* Deferred definitions follow reverse target address order. */
extern "C" void fn_80200044(VObject *obj) {
    delete obj;
}

extern "C" void fn_801FFFF4(CountdownBanner *self) {
    if (self->state <= 1) {
        fn_8020A734(self->scale.p, 0xF, lbl_806DA878, lbl_806DA880);
        self->state = 2;
    }
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

extern "C" void fn_801FFABC(void) {
}

clMnTimeNumSpr::~clMnTimeNumSpr() {
}

void clMnTimeNumSpr::Finish() {
    delete this;
}

void clMnTimeNumSpr::Update() {
    clMnTimeNumSpr *self = this;
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

void clMnTimeNumSpr::Draw() {
}

clMnTimeLightsSpr::~clMnTimeLightsSpr() {
}

/*
 * clMnTimeSprTask timer display tasks (part 2) @ 0x801FF670..0x8020007C.
 */



void clMnTimeLightsSpr::Finish() {
    delete this;
}

void clMnTimeLightsSpr::Update() {
    clMnTimeLightsSpr *self = this;
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

void clMnTimeLightsSpr::Draw() {
}

clMnTimeSprTask::clMnTimeSprTask(int layer_, int id)
    : clMnTaskInterface(id), list(new SceneListImpl), layer(layer_), x(lbl_806DA884), y(lbl_806DA888),
      fade(new FlowFaderI), timer(0), field28(0) {
    FlowSceneList *l;
    int lay;
    int i;
    PreloadResource(0x869);
    for (i = 0; i < 15; i++) {
        l = list.p;
        lay = layer;
        fn_801F4DF0(l, (FlowTask *)new clMnTimeLightsSpr(i, lay), 0);
        FlowTask *t = fn_801F4DC0(list.p, i);
        if (t) {
            CastCountdownDot(t)->SetPos(x, y);
        }
    }
}

clMnTimeSprTask::~clMnTimeSprTask() {
    fn_801F4D3C(list.p);
}

extern "C" clMnTimeSprTask *fn_801FF00C(int layer, int id) {
    return new clMnTimeSprTask(layer, id);
}

void clMnTimeSprTask::Finish() {
    delete this;
}

extern "C" void fn_801FEF34(clMnTimeSprTask *self, float x, float y) {
    int i;
    self->x = x;
    self->y = y;
    for (i = 0; i < 15; i++) {
        FlowTask *t = fn_801F4DC0(self->list.p, i);
        if (t) {
            CastCountdownDot(t)->SetPos(self->x, self->y);
        }
    }
}

extern "C" void fn_801FEF18(clMnTimeSprTask *self, int timer) {
    if (timer < 0 || timer > 5999) {
        timer = 0;
    }
    self->timer = timer;
}

void clMnTimeSprTask::Update() {
    clMnTimeSprTask *self = this;
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
                clMnTimeLightsSpr *dot = CastCountdownDot(t);
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
                fn_801F4DF0(list, (FlowTask *)new clMnTimeNumSpr(id, layer, secs), 0);
                FlowTask *t = fn_801F4DC0(self->list.p, id);
                if (t) {
                    CastCountdownDigit(t)->SetPos(self->x, self->y);
                }
            }
        }
    }
    if (self->field0C >= 2) {
        fn_801F4D3C(self->list.p);
    }
    self->list.p->Update();
}

void clMnTimeSprTask::Draw() {
    clMnTimeSprTask *self = this;
    self->list.p->Draw();
}

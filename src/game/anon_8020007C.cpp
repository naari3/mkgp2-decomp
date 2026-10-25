/*
 * Countdown banner, gauge and character-class model tasks @ 0x8020007C..0x80202148.
 */

#include "game/FlowCountdown.h"

extern "C" {
extern const float lbl_806DA89C;
extern const float lbl_806DA8A0;
extern const float lbl_806DA8A4;
extern const float lbl_806DA8A8;
extern const float lbl_806DA8AC;
extern const float lbl_806DA8B0;
extern const float lbl_806DA8B4;
extern const float lbl_806DA8B8;
extern const float lbl_806DA8BC;
extern const float lbl_806DA8C0;
extern CountdownResStep lbl_803C0074[13];
extern const char *lbl_803C0064[4];
extern int g_ccClass;
void HSD_StateInvalidate(int);
void Scene3D_Init(void *, const char *);
void LObjList_ApplyForCObj(void *);
void CObj_DebugVizPathFlush(void *);
void Object_RenderJObjTree(void *, int);
void clNormal3D_Exec(void *);
void Object_DriveAnimMatrix(void *);
void clNormal3D_SetScale(void *, int, float, float, float, float);
void Object_SetColorRGBA(void *, int, float, float, float, float);
}

/* Gauge sprite (vtable lbl_804EC300). */
struct GaugePart {
    virtual ~GaugePart();
    virtual void _key();
    int layer;
    int field08;
    float x;
    float y;
    float mul;
    int counter;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    GaugePart(int layer_)
        : layer(layer_), field08(0), x(lbl_806DA880), y(lbl_806DA880), mul(lbl_806DA878), counter(0),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        PreloadResource(0x8A2);
        fn_8020A734(scale.p, 0xA, lbl_806DA894, lbl_806DA898);
        fn_8020A7CC(fade.p, 0xCC, 0xCC, 0xA);
    }
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

extern "C" void fn_8020157C(GaugePart *self);

/* Gauge task (vtable lbl_804EC2E8). */
struct CountdownGauge : FlowTask {
    int layer;
    int state;
    VHolder<GaugePart> part;
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderF> scale;
    float x;
    float y;
    int counter;
    CountdownGauge(int layer_, int id);
    ~CountdownGauge();
    virtual void _key3();
};

struct CcScene {
    virtual ~CcScene();
    virtual bool IsReady();
    virtual void Finish();
    char pad[0x3080];
    CcScene(const char *name);
};

struct CcLObjList {
    char pad[0x28];
    CcLObjList(const char *name, int mode);
    ~CcLObjList();
};

struct CcNormal3D {
    char pad[0x5C];
    CcNormal3D(const char *name, int mode);
    ~CcNormal3D();
};

/* Character-class 3D badge (vtable lbl_804EC320). */
struct CcClassModel : FlowTask {
    VHolder<CcScene> scene;
    VHolder<CcLObjList> lobj;
    VHolder<CcNormal3D> model0;
    VHolder<CcNormal3D> model1;
    VHolder<FlowFaderF> fade;
    int ccClass;
    CcClassModel(int id);
    ~CcClassModel();
    virtual void _key3();
};

extern "C" CountdownBanner *fn_8020007C(int type, int layer, int id) {
    return new CountdownBanner(type, layer, id);
}

CountdownBanner::~CountdownBanner() {
}

CountdownBanner::CountdownBanner(int type_, int layer_, int id)
    : FlowTask(id), layer(layer_), state(0), x(lbl_806DA88C), y(lbl_806DA890), counter(0),
      partA(new BannerPartA(type_, layer_)), partB(new BannerPartB(type_, layer_)),
      scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI), resId(0x88B) {
    if (type_ <= -1 || type_ >= 6) {
        type = 0;
    } else {
        type = type_;
    }
    PreloadResource(0x883);
    PreloadResource(0x884);
    PreloadResource(0x885);
    PreloadResource(0x886);
    PreloadResource(0x887);
    PreloadResource(0x888);
    PreloadResource(0x889);
    PreloadResource(0x88A);
    PreloadResource(0x88B);
    PreloadResource(0x88C);
    PreloadResource(0x88D);
    PreloadResource(0x88E);
    PreloadResource(0x890);
    fn_8020A734(scale.p, 0xA, lbl_806DA880, lbl_806DA878);
    fn_8020A7CC(fade.p, 0, 0, 1);
}

extern "C" void fn_80200654(BannerPartB *self) {
    int type;
    bool visible = 0;
    type = self->type;
    if (type == 3 || type == 4 || type == 5) {
        visible = 1;
    }
    ResCtrl ctrl;
    float s = self->mul * fn_8020A6CC(self->scale.p);
    float offX;
    float offY;
    int col = fn_8020A788(self->fade.p) | ~0xFF;
    offY = lbl_806DA89C * s;
    offX = lbl_806DA880;
    int res = 0x88C;
    if (type == 4) {
        res = 0x890;
    } else if (type == 5) {
        res = 0x8A7;
    }
    if (res == 0x88C) {
        offX += lbl_806DA8A0 * s;
    } else if (res == 0x88E) {
        offX += lbl_806DA8A4 * s;
    } else if (res == 0x88F) {
        offX += lbl_806DA8A8 * s;
    } else if (res == 0x890) {
        offX += lbl_806DA8A0 * s;
    } else if (res == 0x8A7) {
        offX += lbl_806DA8A0 * s;
    } else {
        offX += lbl_806DA8AC * s;
    }
    if (visible) {
        fn_80121E10(&ctrl);
        ctrl.resId = res;
        ctrl.Show(self->x + offX, self->y + offY, lbl_806DA878);
        ctrl.SetScale(s);
        ctrl.SetColor(col);
        fn_8011FAFC(&ctrl, self->layer);
    }
    self->counter++;
    if (self->counter >= 120) {
        self->counter = 0;
    }
    self->fade.p->Step();
    self->scale.p->Step();
    switch (self->counter) {
    case 0x3C:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA898);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 0x46:
        fn_8020A734(self->scale.p, 0x10, lbl_806DA898, lbl_806DA87C);
        fn_8020A7CC(self->fade.p, 0xCC, 0xFF, 0x10);
        break;
    case 0x56:
        fn_8020A734(self->scale.p, 0xE, lbl_806DA87C, lbl_806DA898);
        fn_8020A7CC(self->fade.p, 0xFF, 0xCC, 0xE);
        break;
    case 0x64:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA898, lbl_806DA894);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 0x6E:
        fn_8020A734(self->scale.p, 0x46, lbl_806DA894, lbl_806DA894);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0x46);
        break;
    }
}

BannerPartB::~BannerPartB() {
}

extern "C" void fn_80200A48(BannerPartA *self) {
    int type = self->type;
    ResCtrl ctrl;
    float s = self->mul * fn_8020A6CC(self->scale.p);
    float offX;
    float offY;
    int col = fn_8020A788(self->fade.p) | ~0xFF;
    offY = lbl_806DA89C * s;
    offX = lbl_806DA880;
    int res = 0x88D;
    if (type == 1) {
        res = 0x88E;
    } else if (type == 2) {
        res = 0x88F;
    }
    if (res == 0x88C) {
        offX += lbl_806DA8B0 * s;
    } else if (res == 0x88E) {
        offX += lbl_806DA8A4 * s;
    } else if (res == 0x88F) {
        offX += lbl_806DA8A8 * s;
    } else if (res == 0x890) {
        offX += lbl_806DA8A0 * s;
    } else if (res == 0x8A7) {
        offX += lbl_806DA8A0 * s;
    } else {
        offX += lbl_806DA8AC * s;
    }
    fn_80121E10(&ctrl);
    ctrl.resId = res;
    ctrl.Show(self->x + offX, self->y + offY, lbl_806DA878);
    ctrl.SetScale(s);
    ctrl.SetColor(col);
    fn_8011FAFC(&ctrl, self->layer);
    self->counter++;
    if (self->counter >= 120) {
        self->counter = 0;
    }
    bool repeat = 0;
    if (type == 0 || type == 1 || type == 2) {
        repeat = 1;
    }
    self->fade.p->Step();
    self->scale.p->Step();
    switch (self->counter) {
    case 0x0:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA898);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 0xA:
        fn_8020A734(self->scale.p, 0x10, lbl_806DA898, lbl_806DA87C);
        fn_8020A7CC(self->fade.p, 0xCC, 0xFF, 0x10);
        break;
    case 0x1A:
        fn_8020A734(self->scale.p, 0xE, lbl_806DA87C, lbl_806DA898);
        fn_8020A7CC(self->fade.p, 0xFF, 0xCC, 0xE);
        break;
    case 0x28:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA898, lbl_806DA894);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 0x32:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA894);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 0x3C:
        if (repeat) {
            fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA898);
            fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        }
        break;
    case 0x46:
        if (repeat) {
            fn_8020A734(self->scale.p, 0x10, lbl_806DA898, lbl_806DA87C);
            fn_8020A7CC(self->fade.p, 0xCC, 0xFF, 0x10);
        }
        break;
    case 0x56:
        if (repeat) {
            fn_8020A734(self->scale.p, 0xE, lbl_806DA87C, lbl_806DA898);
            fn_8020A7CC(self->fade.p, 0xFF, 0xCC, 0xE);
        }
        break;
    case 0x64:
        if (repeat) {
            fn_8020A734(self->scale.p, 0xA, lbl_806DA898, lbl_806DA894);
            fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        }
        break;
    case 0x6E:
        if (repeat) {
            fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA894);
            fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        }
        break;
    }
}

BannerPartA::~BannerPartA() {
}

extern "C" void fn_80200F88(CountdownGauge *self) {
    self->list.p->Draw();
}

extern "C" void fn_80200FB8(CountdownGauge *self) {
    int i;
    CountdownResStep *e = lbl_803C0074;
    int res = 0;
    for (i = 0; i < 13; i++, e++) {
        if (self->counter < e->threshold) {
            break;
        }
        res = e->resId;
    }
    ResCtrl ctrl;
    float s = fn_8020A6CC(self->scale.p);
    ctrl.resId = res;
    ctrl.Show(self->x, self->y, lbl_806DA878);
    ctrl.SetScale(s);
    fn_8011FAFC(&ctrl, self->layer);
    self->part.p->SetPos(self->x, self->y);
    self->part.p->mul = s;
    fn_8020157C(self->part.p);
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
    self->counter++;
    if (self->counter >= 60) {
        self->counter = 0;
    }
    self->list.p->Update();
}

extern "C" void fn_80201148(CountdownGauge *self) {
    if (self->state <= 1) {
        fn_8020A734(self->scale.p, 0xF, lbl_806DA878, lbl_806DA880);
        self->state = 2;
    }
}

extern "C" void fn_80201198(VObject *obj) {
    delete obj;
}

extern "C" CountdownGauge *fn_802011D0(int layer, int id) {
    return new CountdownGauge(layer, id);
}

CountdownGauge::~CountdownGauge() {
}

CountdownGauge::CountdownGauge(int layer_, int id)
    : FlowTask(id), layer(layer_), state(0), part(new GaugePart(layer_)), list(new SceneListImpl),
      scale(new FlowFaderF(lbl_806DA880)), x(lbl_806DA8B4), y(lbl_806DA8B8), counter(0) {
    PreloadResource(0x89B);
    PreloadResource(0x89C);
    PreloadResource(0x89D);
    PreloadResource(0x89E);
    PreloadResource(0x89F);
    fn_8020A734(scale.p, 0xA, lbl_806DA880, lbl_806DA878);
}

extern "C" void fn_8020157C(GaugePart *self) {
    ResCtrl ctrl;
    float s = self->mul * fn_8020A6CC(self->scale.p);
    int col = fn_8020A788(self->fade.p) | ~0xFF;
    fn_80121E10(&ctrl);
    ctrl.resId = 0x8A2;
    {
        float px = lbl_806DA8BC * s + self->x;
        float py = lbl_806DA89C * s + self->y;
        ctrl.Show(px, py, lbl_806DA878);
    }
    ctrl.SetScale(s);
    ctrl.SetColor(col);
    fn_8011FAFC(&ctrl, self->layer);
    self->counter++;
    if (self->counter >= 60) {
        self->counter = 0;
    }
    self->fade.p->Step();
    self->scale.p->Step();
    switch (self->counter) {
    case 0:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA898);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 10:
        fn_8020A734(self->scale.p, 0x10, lbl_806DA898, lbl_806DA87C);
        fn_8020A7CC(self->fade.p, 0xCC, 0xFF, 0x10);
        break;
    case 26:
        fn_8020A734(self->scale.p, 0xE, lbl_806DA87C, lbl_806DA898);
        fn_8020A7CC(self->fade.p, 0xFF, 0xCC, 0xE);
        break;
    case 40:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA898, lbl_806DA894);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    case 50:
        fn_8020A734(self->scale.p, 0xA, lbl_806DA894, lbl_806DA894);
        fn_8020A7CC(self->fade.p, 0xCC, 0xCC, 0xA);
        break;
    }
}

GaugePart::~GaugePart() {
}

extern "C" void fn_802018A4(CcClassModel *self) {
    HSD_StateInvalidate(-1);
    if (self->scene.p->IsReady()) {
        LObjList_ApplyForCObj(self->lobj.p);
        CObj_DebugVizPathFlush(self->scene.p);
        Object_RenderJObjTree(self->model0.p, 7);
        Object_RenderJObjTree(self->model1.p, 7);
        self->scene.p->Finish();
    }
}

static inline void SetModelAlpha(CcNormal3D *m, float a) {
    Object_SetColorRGBA(m, 0, lbl_806DA878, lbl_806DA878, lbl_806DA878, a);
}

extern "C" void fn_8020192C(CcClassModel *self) {
    int cc = g_ccClass;
    if (self->ccClass != cc) {
        if (cc != 0) {
            fn_8020A734(self->fade.p, 0xA, lbl_806DA880, lbl_806DA878);
        } else {
            fn_8020A734(self->fade.p, 0xA, lbl_806DA878, lbl_806DA880);
        }
        self->ccClass = cc;
    }
    {
        CcNormal3D *m = self->model1.p;
        SetModelAlpha(m, fn_8020A6CC(self->fade.p));
    }
    clNormal3D_Exec(self->model0.p);
    clNormal3D_Exec(self->model1.p);
    Object_DriveAnimMatrix(self->model0.p);
    Object_DriveAnimMatrix(self->model1.p);
    self->fade.p->Step();
}

extern "C" void fn_80201A10(VObject *obj) {
    delete obj;
}

extern "C" CcClassModel *fn_80201A48(int id) {
    return new CcClassModel(id);
}

CcClassModel::~CcClassModel() {
}

CcClassModel::CcClassModel(int id) : FlowTask(id), fade(new FlowFaderF(lbl_806DA880)) {
    const char *name = lbl_803C0064[0];
    ccClass = g_ccClass;
    scene.Reset(new CcScene(name));
    lobj.Reset(new CcLObjList(name, 1));
    model0.Reset(new CcNormal3D(name, 0));
    clNormal3D_SetScale(model0.p, 0, lbl_806DA880, lbl_806DA8C0, lbl_806DA880, lbl_806DA880);
    name = lbl_803C0064[1];
    model1.Reset(new CcNormal3D(name, 1));
    clNormal3D_SetScale(model1.p, 0, lbl_806DA880, lbl_806DA8C0, lbl_806DA880, lbl_806DA880);
    if (ccClass != 0) {
        fn_8020A734(fade.p, 1, lbl_806DA878, lbl_806DA878);
        Object_SetColorRGBA(model1.p, 0, lbl_806DA878, lbl_806DA878, lbl_806DA878, lbl_806DA878);
    } else {
        fn_8020A734(fade.p, 1, lbl_806DA880, lbl_806DA880);
        Object_SetColorRGBA(model1.p, 0, lbl_806DA878, lbl_806DA878, lbl_806DA878, lbl_806DA880);
    }
}

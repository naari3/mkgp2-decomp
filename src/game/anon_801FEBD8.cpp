/*
 * Countdown banner, gauge and character-class model tasks @ 0x80200240..0x80202148.
 */

#include "game/types/clMnTimeSprTask.h"
#include "game/types/clMnPedalTasks.h"

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
extern const char *const lbl_803C0064[4];
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
struct clMnHandleFont {
    virtual ~clMnHandleFont();
    void Draw();
    int layer;
    int field08;
    float x;
    float y;
    float mul;
    int counter;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    clMnHandleFont(int layer_)
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



/* Gauge task (vtable CountdownGauge_vtable_804EC2E8). */
struct clMnHandleTask : clMnTaskInterface {
    int layer;
    int state;
    VHolder<clMnHandleFont> part;
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderF> scale;
    float x;
    float y;
    int counter;
    clMnHandleTask(int layer_, int id);
    ~clMnHandleTask();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
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

/* Character-class 3D badge (vtable CcClassModel_vtable_804EC320). */
struct clMnBackTask : clMnTaskInterface {
    VHolder<CcScene> scene;
    VHolder<CcLObjList> lobj;
    VHolder<CcNormal3D> model0;
    VHolder<CcNormal3D> model1;
    VHolder<FlowFaderF> fade;
    int ccClass;
    clMnBackTask(int id);
    ~clMnBackTask();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

static inline void SetModelAlpha(CcNormal3D *m, float a) {
    Object_SetColorRGBA(m, 0, lbl_806DA878, lbl_806DA878, lbl_806DA878, a);
}

inline void VHolder<CcLObjList>::Reset(CcLObjList *q) throw() {
    if (p != q) {
        delete p;
        p = q;
    }
}

inline void VHolder<CcScene>::Reset(CcScene *q) throw() {
    if (p != q) {
        delete p;
        p = q;
    }
}

/* MWCC deferred code generation emits definitions in reverse source order. */
VHolder<CcScene>::~VHolder() throw() {
    delete p;
}

VHolder<CcLObjList>::~VHolder() throw() {
    delete p;
}

VHolder<clMnHandleFont>::~VHolder() throw() {
    delete p;
}

VHolder<clMnPedalFontRight>::~VHolder() throw() {
    delete p;
}

VHolder<clMnPedalFontLeft>::~VHolder() throw() {
    delete p;
}

clMnBackTask::clMnBackTask(int id) : clMnTaskInterface(id), fade(new FlowFaderF(lbl_806DA880)) {
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

clMnBackTask::~clMnBackTask() {
}

extern "C" clMnBackTask *fn_80201A48(int id) {
    return new clMnBackTask(id);
}

void clMnBackTask::Finish() {
    delete this;
}

void clMnBackTask::Update() {
    clMnBackTask *self = this;
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

void clMnBackTask::Draw() {
    clMnBackTask *self = this;
    HSD_StateInvalidate(-1);
    if (self->scene.p->IsReady()) {
        LObjList_ApplyForCObj(self->lobj.p);
        CObj_DebugVizPathFlush(self->scene.p);
        Object_RenderJObjTree(self->model0.p, 7);
        Object_RenderJObjTree(self->model1.p, 7);
        self->scene.p->Finish();
    }
}

clMnHandleFont::~clMnHandleFont() {
}

void clMnHandleFont::Draw() {
    clMnHandleFont *self = this;
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

clMnHandleTask::clMnHandleTask(int layer_, int id)
    : clMnTaskInterface(id), layer(layer_), state(0), part(new clMnHandleFont(layer_)), list(new SceneListImpl),
      scale(new FlowFaderF(lbl_806DA880)), x(lbl_806DA8B4), y(lbl_806DA8B8), counter(0) {
    PreloadResource(0x89B);
    PreloadResource(0x89C);
    PreloadResource(0x89D);
    PreloadResource(0x89E);
    PreloadResource(0x89F);
    fn_8020A734(scale.p, 0xA, lbl_806DA880, lbl_806DA878);
}

clMnHandleTask::~clMnHandleTask() {
}

extern "C" clMnHandleTask *fn_802011D0(int layer, int id) {
    return new clMnHandleTask(layer, id);
}

void clMnHandleTask::Finish() {
    delete this;
}

extern "C" void fn_80201148(clMnHandleTask *self) {
    if (self->state <= 1) {
        fn_8020A734(self->scale.p, 0xF, lbl_806DA878, lbl_806DA880);
        self->state = 2;
    }
}

void clMnHandleTask::Update() {
    clMnHandleTask *self = this;
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
    self->part.p->Draw();
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

void clMnHandleTask::Draw() {
    clMnHandleTask *self = this;
    self->list.p->Draw();
}

clMnPedalFontRight::~clMnPedalFontRight() {
}

void clMnPedalFontRight::Draw() {
    clMnPedalFontRight *self = this;
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

clMnPedalFontLeft::~clMnPedalFontLeft() {
}

void clMnPedalFontLeft::Draw() {
    clMnPedalFontLeft *self = this;
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

clMnPedalSprTask::clMnPedalSprTask(int type_, int layer_, int id)
    : clMnTaskInterface(id), layer(layer_), state(0), x(lbl_806DA88C), y(lbl_806DA890), counter(0),
      partA(new clMnPedalFontRight(type_, layer_)), partB(new clMnPedalFontLeft(type_, layer_)),
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



clMnPedalSprTask::~clMnPedalSprTask() {
}

extern "C" clMnPedalSprTask *fn_8020007C(int type, int layer, int id) {
    return new clMnPedalSprTask(type, layer, id);
}

/*
 * clMnTimeSprTask timer display tasks @ 0x801FEBD8..0x801FF670.
 */



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
void clMnPedalSprTask::Finish() {
    delete this;
}

extern "C" void fn_801FFFF4(clMnPedalSprTask *self) {
    if (self->state <= 1) {
        fn_8020A734(self->scale.p, 0xF, lbl_806DA878, lbl_806DA880);
        self->state = 2;
    }
}

void clMnPedalSprTask::Update() {
    clMnPedalSprTask *self = this;
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
        self->partA.p->Draw();
        self->partB.p->Draw();
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

void clMnPedalSprTask::Draw() {
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

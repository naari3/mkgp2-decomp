/*
 * 0x8021550C..0x8021617C: coin challenge result popup (vtable lbl_804EDAD0)
 * and the start countdown HUD (vtable lbl_804EDAF4, base lbl_804EDB28).
 * The popup's empty Draw lives in fn_80215508.c and the countdown base
 * dtor in dtor_8021617C.c.
 */

#include "game/FadeLogo.h"

extern "C" {
extern const int lbl_803C3E50[6];
extern const float lbl_806DAE60;
extern const float lbl_806DAE64;
extern const float lbl_806DAE68;
extern const float lbl_806DAE6C;
extern const float lbl_806DAE70;
extern const float lbl_806DAE74;
extern const float lbl_806DAE78;
extern const float lbl_806DAE7C;
extern const float lbl_806DAE80;
extern const float lbl_806DAE88;
extern const float lbl_806DAE8C;
extern const float lbl_806DAE90;
extern const float lbl_806DAE94;
extern int g_countdownPhase;
extern int g_gameMode;
void PreloadResource(int res);
void fn_80120A08(int res);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_RecomputeCull(int sprite);
void SpriteLayer_SetResource(int sprite, int res);
void fn_8011F804(int sprite, float x, float y);
void fn_8011F744(int sprite, float sx, float sy);
int fn_8020A900(int value, int digit);
void Tachometer_SetDisplaySpeedRef(float v);
void Tachometer_SetMaxSpeedRef(float v);
}

/* ---- result popup ---- */

struct ScorePopup : PopupTask {
    int layer;
    int kind;
    VHolder<FlowFaderI> alpha;
    VHolder<FlowFaderF> scale;
    ScorePopup(int kind_, int layer_, int id_)
        : PopupTask(id_), layer(layer_), kind(kind_), alpha(new FlowFaderI),
          scale(new FlowFaderF(lbl_806DAE7C)) {
        if (kind_ < 1 || kind_ > 5) {
            kind = 1;
        }
        alpha.p->Set(0, 0xFF, 15);
        scale.p->Set(lbl_806DAE80, lbl_806DAE6C, 15);
    }
    ~ScorePopup();
    void Finish();
    void Update();
    void Draw();
};

void ScorePopup::Update() {
    ResCtrl rc;
    unsigned int c = alpha.p->Value() | 0xFFFFFF00;
    float s = scale.p->Value();
    rc.resId = lbl_803C3E50[kind];
    rc.Show(lbl_806DAE60, lbl_806DAE64, lbl_806DAE68);
    rc.SetColor(c);
    rc.SetScale(s);
    fn_8011FAFC(&rc, layer);
    alpha.p->Step();
    scale.p->Step();
    if (scale.p->Done()) {
        float v = scale.p->Value();
        if (lbl_806DAE6C == v) {
            scale.p->Set(lbl_806DAE6C, lbl_806DAE68, 5);
        } else if (lbl_806DAE68 == v) {
            scale.p->Set(lbl_806DAE68, lbl_806DAE70, 20);
        } else if (lbl_806DAE70 == v) {
            scale.p->Set(lbl_806DAE70, lbl_806DAE74, 5);
        } else if (lbl_806DAE74 == v) {
            alpha.p->Set(0xFF, 0, 15);
            scale.p->Set(lbl_806DAE74, lbl_806DAE78, 15);
        } else {
            field0C = 1;
        }
    }
}

extern "C" void fn_802156C4(void) {
    fn_80120A08(0xB1E);
    fn_80120A08(0xB1F);
    fn_80120A08(0xB20);
    fn_80120A08(0xB21);
    fn_80120A08(0xB22);
}

extern "C" void fn_80215708(void) {
    PreloadResource(0xB1E);
    PreloadResource(0xB1F);
    PreloadResource(0xB20);
    PreloadResource(0xB21);
    PreloadResource(0xB22);
}

void ScorePopup::Finish() {
    delete this;
}

extern "C" ScorePopup *fn_80215784(int kind, int layer, int id) {
    return new ScorePopup(kind, layer, id);
}

ScorePopup::~ScorePopup() {
}

/* ---- start countdown ---- */

struct CountBase {
    virtual ~CountBase() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Start(int delay) = 0;
    virtual void _keyB();
    int delay;
    CountBase() : delay(-1) {}
};

struct CountPos {
    float x;
    float y;
    float scale;
};

extern "C" const CountPos lbl_803C3EA0[2][6];

struct CountdownHud : CountBase {
    int layer;
    int sprites[6];
    int state;
    int value;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderF> zoom;
    CountdownHud(int layer_);
    ~CountdownHud();
    void Update();
    void Draw();
    void Start(int delay);
    void SetValue(int v);
};

void CountdownHud::Start(int n) {
    if (state < 4) {
        delay = n + 1;
    }
}

void CountdownHud::Draw() {
}

void CountdownHud::Update() {
    switch (state) {
    case -1:
        if (g_countdownPhase <= 3) {
            state = 0;
        }
        return;
    case 0:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 1;
        }
        break;
    case 1:
        if (g_countdownPhase <= 2) {
            zoom.p->Set(lbl_806DAE88, lbl_806DAE8C, 4);
            state = 2;
        }
        break;
    case 2:
        if (zoom.p->Done() && lbl_806DAE88 == zoom.p->Value()) {
            state = 3;
        }
        break;
    case 3:
        break;
    case 4:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 5;
            fn_80120A08(0xB74);
            fn_80120A08(0xB73);
            fn_80120A08(0xBD4);
            for (int i = 0; i < 6; i++) {
                SpriteHandle_SetActiveFlag(sprites[i], 0);
                SpriteHandle_RecomputeCull(sprites[i]);
            }
            return;
        }
        break;
    case 5:
        return;
    }
    if (delay > 0) {
        delay--;
        if (delay <= 0) {
            delay = 0;
            state = 4;
            slide.p->Set(lbl_806DAE90, lbl_806DAE94, 7);
        }
    }
    if (state >= 5) {
        return;
    }
    float off = slide.p->Value();
    int big = 0;
    if (g_gameMode == 2) {
        big = 1;
    }
    SpriteLayer_SetResource(sprites[2], fn_8020A900(value, 1) + 0xB69);
    SpriteLayer_SetResource(sprites[3], fn_8020A900(value, 0) + 0xB69);
    for (int i = 0; i < 6; i++) {
        const CountPos *p = &lbl_803C3EA0[big][i];
        float x = p->x - off;
        float s = p->scale * zoom.p->Value();
        fn_8011F804(sprites[i], x, p->y);
        fn_8011F744(sprites[i], s, s);
        SpriteHandle_SetActiveFlag(sprites[i], 1);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
    Tachometer_SetDisplaySpeedRef(off);
    Tachometer_SetMaxSpeedRef(zoom.p->Value());
    zoom.p->Step();
    if (zoom.p->Done()) {
        float v = zoom.p->Value();
        if (lbl_806DAE8C == v) {
            zoom.p->Set(lbl_806DAE8C, lbl_806DAE88, 4);
        } else if (lbl_806DAE88 == v) {
            zoom.p->Set(lbl_806DAE88, lbl_806DAE88, 1);
        }
    }
}

void CountdownHud::SetValue(int v) {
    if (v > 99) {
        v = 99;
    } else if (v < 0) {
        v = 0;
    }
    value = v;
}

extern "C" void fn_80215DB0(void) {
    PreloadResource(0xB74);
    PreloadResource(0xB73);
    PreloadResource(0xBD4);
}

extern "C" CountdownHud *fn_80215DE4(int layer) {
    return new CountdownHud(layer);
}

CountdownHud::~CountdownHud() {
    for (int i = 0; i < 6; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}

CountdownHud::CountdownHud(int layer_)
    : layer(layer_), state(-1), value(0), slide(new FlowFaderF(lbl_806DAE90)),
      zoom(new FlowFaderF(lbl_806DAE90)) {
    PreloadResource(0xB74);
    PreloadResource(0xB73);
    PreloadResource(0xBD4);
    slide.p->Set(lbl_806DAE94, lbl_806DAE90, 7);
    zoom.p->Set(lbl_806DAE88, lbl_806DAE88, 1);
    Tachometer_SetDisplaySpeedRef(slide.p->Value());
    if (g_gameMode == 2) {
        ResCtrl a;
        a.resId = 0xBD4;
        sprites[4] = SpriteHandle_CreateDefault(&a, layer);
        ResCtrl b;
        b.resId = 0xBD5;
        sprites[5] = SpriteHandle_CreateDefault(&b, layer);
    } else {
        sprites[4] = 0;
        sprites[5] = 0;
    }
    ResCtrl c;
    c.resId = 0xB73;
    sprites[0] = SpriteHandle_CreateDefault(&c, layer);
    ResCtrl d;
    d.resId = 0xB74;
    sprites[1] = SpriteHandle_CreateDefault(&d, layer);
    ResCtrl e;
    e.resId = 0xB69;
    sprites[2] = SpriteHandle_CreateDefault(&e, layer);
    sprites[3] = SpriteHandle_CreateDefault(&e, layer);
    for (int i = 0; i < 6; i++) {
        SpriteHandle_SetActiveFlag(sprites[i], 0);
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

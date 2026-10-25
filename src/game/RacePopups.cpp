/*
 * Two sprite popup flow tasks @ 0x80250F38..0x80251CD0.
 *
 *   PopupRoot (vtable lbl_8048ECF8, inline) -> PopupTask (vtable lbl_8048ED10, inline)
 *     KindPopup  (vtable lbl_804EF160): resource 0x13A2 + kind, slides two halves together.
 *     FlashPopup (vtable lbl_804EF18C): resource 0x13A6, zoom and fade.
 *
 * KindPopup::Draw is the separate fn_80250F34 unit.
 */

#include "game/FlowScene.h"

struct Vec2 {
    float x;
    float y;
};

extern "C" {
extern const Vec2 lbl_806DC0F8;
extern const float lbl_806DC100;
extern const float lbl_806DC110;
extern const float lbl_806DC114;
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_RecomputeCull(int sprite);
void SpriteHandle_SetCornerAlpha(int sprite, unsigned char alpha);
void fn_8011F804(int sprite, float x, float y);
void fn_8011F744(int sprite, float sx, float sy);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
int fn_8020A788(FlowFader *fader);
void PreloadResource(int id);
void fn_80120A08(int id);
}

struct PopupRoot {
    virtual ~PopupRoot() {}
    virtual void Finish() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void _keyR();
    int id;
    int field08;
    int done;
    PopupRoot(int id_) : id(id_), field08(0), done(0) {}
};

struct PopupTask : PopupRoot {
    PopupTask(int id_) : PopupRoot(id_) {}
    virtual ~PopupTask() {}
    virtual void _keyT();
};

struct KindPopup : PopupTask {
    int layer;
    int state;
    int sprites[3];
    int kind;
    VHolder<FlowFaderI> fade;
    VHolder<FlowFaderI> scale;
    KindPopup(int kind_, int layer_, int id_)
        : PopupTask(id_), layer(layer_), state(0), kind(kind_), fade(new FlowFaderI),
          scale(new FlowFaderI) {
        if (kind > 3 && kind < 1) {
            kind = 3;
        }
        fn_8020A7CC(fade.p, 0x190, 0, 10);
        {
            ResCtrl rc;
            rc.resId = kind + 0x13A2;
            sprites[0] = SpriteHandle_CreateDefault(&rc, layer);
            sprites[1] = SpriteHandle_CreateDefault(&rc, layer);
            rc.mode = 3;
            sprites[2] = SpriteHandle_CreateDefault(&rc, layer);
            SpriteHandle_SetActiveFlag(sprites[2], 0);
        }
    }
    ~KindPopup();
    void Finish();
    void Update();
    void Draw();
    virtual void _key();
};

struct FlashPopup : PopupTask {
    int layer;
    int state;
    int sprites[2];
    VHolder<FlowFaderI> scale;
    VHolder<FlowFaderI> fade1;
    VHolder<FlowFaderI> fade2;
    FlashPopup(int layer_, int id_);
    ~FlashPopup();
    void Finish();
    void Update();
    void Draw();
    virtual void _key();
};

void FlashPopup::Finish() {
    delete this;
}

void KindPopup::Finish() {
    delete this;
}

FlashPopup::FlashPopup(int layer_, int id_)
    : PopupTask(id_), layer(layer_), state(0), scale(new FlowFaderI), fade1(new FlowFaderI),
      fade2(new FlowFaderI) {
    PreloadResource(0x13A6);
    fn_8020A7CC(scale.p, 0x1900, 0x6400, 10);
    {
        ResCtrl rc;
        rc.resId = 0x13A6;
        rc.Show(lbl_806DC0F8.x, lbl_806DC0F8.y, lbl_806DC114);
        sprites[0] = SpriteHandle_CreateDefault(&rc, layer);
        rc.mode = 3;
        sprites[1] = SpriteHandle_CreateDefault(&rc, layer);
        SpriteHandle_SetActiveFlag(sprites[0], 0);
        SpriteHandle_SetActiveFlag(sprites[1], 0);
    }
}

FlashPopup::~FlashPopup() {
    for (int i = 0; i < 2; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}

#pragma dont_inline on
extern "C" FlashPopup *fn_802518EC(int layer, int id) {
    return new FlashPopup(layer, id);
}
#pragma dont_inline reset

extern "C" void fn_802518C8(void) {
    PreloadResource(0x13A6);
}

extern "C" void fn_8025189C(void) {
    fn_80120A08(0x13A6);
    fn_80120A08(0x13AF);
}

void FlashPopup::Update() {
    int i;
    switch (state) {
    case 0: {
        float s = (float)fn_8020A788(scale.p);
        s *= lbl_806DC110;
        fn_8011F744(sprites[0], s, s);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        SpriteHandle_SetActiveFlag(sprites[1], 0);
        scale.p->Step();
        if (scale.p->Done()) {
            fn_8020A7CC(scale.p, 0x7F, 0, 5);
            state = 1;
        }
        break;
    }
    case 1:
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        SpriteHandle_SetActiveFlag(sprites[1], 1);
        SpriteHandle_SetCornerAlpha(sprites[1], fn_8020A788(scale.p));
        scale.p->Step();
        if (scale.p->Done()) {
            fn_8020A7CC(scale.p, 0x6400, 0xC800, 0xF);
            fn_8020A7CC(fade1.p, 0, 0, 1);
            fn_8020A7CC(fade2.p, 0xFF, 0, 0xF);
            state = 2;
        }
        break;
    case 2: {
        float s = (float)fn_8020A788(scale.p);
        s *= lbl_806DC110;
        SpriteHandle_SetCornerAlpha(sprites[0], fn_8020A788(fade2.p));
        fn_8011F744(sprites[0], s, s);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        SpriteHandle_SetActiveFlag(sprites[1], 0);
        scale.p->Step();
        fade2.p->Step();
        if (fade2.p->Done()) {
            fn_8020A7CC(scale.p, 0, 0, 1);
            fn_8020A7CC(fade2.p, 0, 0, 1);
            state = 3;
            for (i = 0; i < 2; i++) {
                SpriteHandle_SetActiveFlag(sprites[i], 0);
            }
        }
        break;
    }
    case 3:
        done = 1;
        break;
    }
    for (i = 0; i < 2; i++) {
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

void FlashPopup::Draw() {
}

KindPopup::~KindPopup() {
    for (int i = 0; i < 3; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
}

extern "C" KindPopup *fn_802512D0(int kind, int layer, int id) {
    return new KindPopup(kind, layer, id);
}

extern "C" void fn_802512AC(void) {
    PreloadResource(0x13A3);
}

extern "C" void fn_80251288(void) {
    fn_80120A08(0x13A3);
}

void KindPopup::Update() {
    float cx = lbl_806DC0F8.x;
    float cy = lbl_806DC0F8.y;
    int i;
    switch (state) {
    case 0: {
        float d = (float)fn_8020A788(fade.p);
        SpriteHandle_SetCornerAlpha(sprites[0], 0x7F);
        SpriteHandle_SetCornerAlpha(sprites[1], 0x7F);
        fn_8011F804(sprites[0], cx - d, cy);
        fn_8011F804(sprites[1], cx + d, cy);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        SpriteHandle_SetActiveFlag(sprites[1], 1);
        fade.p->Step();
        if (fade.p->Done()) {
            fn_8020A7CC(fade.p, 0x7F, 0, 5);
            state = 1;
        }
        break;
    }
    case 1:
        fn_8011F804(sprites[0], cx, cy);
        fn_8011F804(sprites[2], cx, cy);
        SpriteHandle_SetCornerAlpha(sprites[0], 0xFF);
        SpriteHandle_SetActiveFlag(sprites[0], 1);
        SpriteHandle_SetActiveFlag(sprites[1], 0);
        SpriteHandle_SetActiveFlag(sprites[2], 1);
        state = 2;
    case 2:
        SpriteHandle_SetCornerAlpha(sprites[2], fn_8020A788(fade.p));
        fade.p->Step();
        if (fade.p->Done()) {
            fn_8020A7CC(fade.p, 0xFF, 0, 0x2D);
            fn_8020A7CC(scale.p, 0x100, 0x200, 0x2D);
            state = 3;
        }
        break;
    case 3: {
        float s = (float)fn_8020A788(scale.p);
        s *= lbl_806DC100;
        SpriteHandle_SetCornerAlpha(sprites[0], fn_8020A788(fade.p));
        fn_8011F744(sprites[0], s, s);
        SpriteHandle_SetActiveFlag(sprites[2], 0);
        fade.p->Step();
        scale.p->Step();
        if (fade.p->Done()) {
            state = 4;
            for (i = 0; i < 3; i++) {
                SpriteHandle_SetActiveFlag(sprites[i], 0);
            }
        }
        break;
    }
    case 4:
        done = 1;
        break;
    }
    for (i = 0; i < 3; i++) {
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

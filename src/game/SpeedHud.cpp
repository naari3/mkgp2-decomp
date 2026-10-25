/*
 * Three-digit gauge HUD part @ 0x80251CD0..0x802529C8 (vtable lbl_804EF1B4).
 *
 * HudPart (vtable lbl_804EDB28, dtor dtor_8021617C) is the base. The gauge
 * slides in once the countdown reaches phase 2, shows the value with up to
 * three digits (resources 0xB2A + digit), and pops a GaugeMark (resource
 * 0xB35 + digit) whenever the low range value changes.
 */

#include "game/FlowScene.h"

struct Vec2 {
    float x;
    float y;
};

extern "C" {
extern const float lbl_806DC118;
extern const float lbl_806DC11C;
extern const float lbl_806DC120;
extern const float lbl_806DC124;
extern const float lbl_806DC128;
extern const float lbl_806DC12C;
extern const float lbl_806DC130;
extern const float lbl_806DC134;
extern const float lbl_806DC138;
extern const float lbl_806DC13C;
extern const Vec2 lbl_803F10B0[2];
extern const Vec2 lbl_803F10C0[2][9];
extern int g_countdownPhase;
extern int g_gameMode;
int SpriteHandle_CreateDefault(ResCtrl *ctrl, int layer);
void SpriteHandle_Destroy(int sprite);
void SpriteHandle_SetActiveFlag(int sprite, int active);
void SpriteHandle_RecomputeCull(int sprite);
void SpriteHandle_SetCornerAlpha(int sprite, unsigned char alpha);
void SpriteLayer_SetResource(int sprite, int id);
void fn_8011F804(int sprite, float x, float y);
void fn_8011F744(int sprite, float sx, float sy);
void fn_8011F610(int sprite, unsigned char r, unsigned char g, unsigned char b);
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
float fn_8020A6CC(FlowFader *fader);
int fn_8020A788(FlowFader *fader);
int fn_8020A900(int value, int digit);
void PreloadResource(int id);
}

struct HudPart {
    virtual ~HudPart() {}
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void SetDelay(int n) = 0;
    virtual void _keyH();
    int delay;
    HudPart() : delay(-1) {}
};

struct GaugeMark {
    int sprite;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    unsigned char active;
    float x;
    GaugeMark(int layer)
        : scale(new FlowFaderF(lbl_806DC128)), fade(new FlowFaderI), active(0), x(lbl_806DC128) {
        ResCtrl rc;
        rc.resId = 0xB35;
        rc.mode = 4;
        sprite = SpriteHandle_CreateDefault(&rc, layer);
        SpriteHandle_SetActiveFlag(sprite, 0);
        SpriteHandle_RecomputeCull(sprite);
    }
    ~GaugeMark() { SpriteHandle_Destroy(sprite); }
    void Start(int d) {
        active = 1;
        fn_8020A734(scale.p, 0x1E, lbl_806DC138, lbl_806DC120);
        fn_8020A7CC(fade.p, -0x100, 0x100, 0x1E);
        if (d >= 0 && d <= 5) {
            SpriteLayer_SetResource(sprite, d + 0xB35);
        }
    }
    void Hide() {
        active = 0;
        SpriteHandle_SetActiveFlag(sprite, 0);
        SpriteHandle_RecomputeCull(sprite);
    }
    void Update() {
        if (active) {
            int side;
            float px, s;
            scale.p->Step();
            fade.p->Step();
            if (scale.p->Done()) {
                fn_8020A734(scale.p, 1, lbl_806DC120, lbl_806DC120);
            }
            if (fade.p->Done()) {
                fn_8020A7CC(fade.p, 0xFF, 0xFF, 1);
            }
            SpriteHandle_SetCornerAlpha(sprite, fn_8020A788(fade.p) < 0 ? 0 : (unsigned char)fn_8020A788(fade.p));
            {
                unsigned char c = 0x100 - ((fn_8020A788(fade.p) + 0x100) >> 1);
                fn_8011F610(sprite, c, c, c);
            }
            side = g_gameMode == 1 ? 1 : 0;
            px = x + lbl_803F10C0[side][6].x;
            s = fn_8020A6CC(scale.p);
            fn_8011F804(sprite, px, lbl_803F10C0[side][6].y);
            fn_8011F744(sprite, s, s);
            SpriteHandle_SetActiveFlag(sprite, 1);
            SpriteHandle_RecomputeCull(sprite);
        }
    }
};

struct SpeedHud : HudPart {
    int layer;
    int sprites[4];
    int state;
    VHolder<FlowFaderF> slide;
    VHolder<FlowFaderF> digitScale;
    VHolder<FlowFaderF> iconScale;
    float value;
    unsigned char showDigits;
    unsigned char low;
    int lastDigit;
    GaugeMark *mark;
    SpeedHud(int layer_);
    ~SpeedHud();
    void SetValue(float v);
    void Update();
    void Draw();
    void SetDelay(int n);
    virtual void _key();
};

SpeedHud::SpeedHud(int layer_)
    : layer(layer_), state(-1), slide(new FlowFaderF(lbl_806DC128)),
      digitScale(new FlowFaderF(lbl_806DC128)), iconScale(new FlowFaderF(lbl_806DC128)),
      value(lbl_806DC128), mark(0) {
    int i;
    PreloadResource(0xB29);
    PreloadResource(0xB34);
    PreloadResource(0xB2A);
    PreloadResource(0xB35);
    fn_8020A734(slide.p, 7, lbl_806DC12C, lbl_806DC128);
    fn_8020A734(digitScale.p, 4, lbl_806DC118, lbl_806DC11C);
    fn_8020A734(iconScale.p, 4, lbl_806DC120, lbl_806DC124);
    {
        ResCtrl rc;
        rc.resId = 0xB29;
        for (i = 0; i < 4; i++) {
            sprites[i] = SpriteHandle_CreateDefault(&rc, layer);
            SpriteHandle_SetActiveFlag(sprites[i], 0);
            SpriteHandle_RecomputeCull(sprites[i]);
        }
    }
    mark = new GaugeMark(layer);
}

SpeedHud::~SpeedHud() {
    for (int i = 0; i < 4; i++) {
        SpriteHandle_Destroy(sprites[i]);
    }
    delete mark;
}

#pragma dont_inline on
extern "C" SpeedHud *fn_802524C8(int layer) {
    return new SpeedHud(layer);
}
#pragma dont_inline reset

void SpeedHud::SetValue(float v) {
    if (v > lbl_806DC13C) {
        v = lbl_806DC13C;
    }
    if (v < lbl_806DC128) {
        v = lbl_806DC128;
    }
    value = v;
}

void SpeedHud::Update() {
    int side;
    int j;
    int i;
    switch (state) {
    case -1:
        if (g_countdownPhase < 4) {
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
            state = 2;
            fn_8020A734(digitScale.p, 4, lbl_806DC118, lbl_806DC11C);
            fn_8020A734(iconScale.p, 4, lbl_806DC120, lbl_806DC124);
        }
        break;
    case 2:
        digitScale.p->Step();
        iconScale.p->Step();
        if (digitScale.p->Done()) {
            state = 3;
            fn_8020A734(digitScale.p, 4, lbl_806DC11C, lbl_806DC118);
            fn_8020A734(iconScale.p, 4, lbl_806DC124, lbl_806DC120);
        }
        break;
    case 3:
        digitScale.p->Step();
        iconScale.p->Step();
        if (digitScale.p->Done()) {
            state = 4;
        }
        break;
    case 4:
        break;
    case 5:
        slide.p->Step();
        if (slide.p->Done()) {
            state = 6;
            for (j = 0; j < 4; j++) {
                SpriteHandle_SetActiveFlag(sprites[j], 0);
                SpriteHandle_RecomputeCull(sprites[j]);
            }
            return;
        }
        break;
    case 6:
        return;
    default:
        return;
    }
    if (delay > 0) {
        delay--;
        if (delay <= 0) {
            delay = 0;
            state = 5;
            fn_8020A734(slide.p, 7, lbl_806DC128, lbl_806DC12C);
        }
    }
    {
        float off, x;
        float v = value;
        float ds, is;
        if (v > lbl_806DC130) {
            low = 0;
            if (v >= lbl_806DC134) {
                showDigits = 1;
            } else {
                showDigits = 0;
            }
        } else {
            showDigits = 0;
            low = 1;
        }
        side = 0;
        if (g_gameMode == 1) {
            side = 1;
        }
        if (side == 0) {
            off = fn_8020A6CC(slide.p);
        } else {
            off = -fn_8020A6CC(slide.p);
        }
        ds = fn_8020A6CC(digitScale.p);
        is = fn_8020A6CC(iconScale.p);
        {
            int res = 0xB29;
            if (low) {
                res = 0xB34;
            }
            x = lbl_803F10B0[side].x - off;
            SpriteLayer_SetResource(sprites[0], res);
            fn_8011F804(sprites[0], x, lbl_803F10B0[side].y);
            fn_8011F744(sprites[0], is, is);
            SpriteHandle_SetActiveFlag(sprites[0], 1);
            SpriteHandle_SetActiveFlag(sprites[3], 1);
        }
        if (showDigits) {
            for (int i = 0; i < 3; i++) {
                int d = fn_8020A900((int)v, i);
                x = lbl_803F10C0[side][i].x - off;
                SpriteLayer_SetResource(sprites[3 - i], d + 0xB2A);
                fn_8011F804(sprites[3 - i], x, lbl_803F10C0[side][i].y);
                fn_8011F744(sprites[3 - i], ds, ds);
            }
            SpriteHandle_SetActiveFlag(sprites[1], 1);
            SpriteHandle_SetActiveFlag(sprites[2], 1);
        } else if (low) {
            int d = fn_8020A900((int)v, 0);
            if (d != lastDigit) {
                mark->Start(d);
            }
            lastDigit = d;
            mark->x = -off;
            SpriteHandle_SetActiveFlag(sprites[3], 0);
            SpriteHandle_SetActiveFlag(sprites[1], 0);
            SpriteHandle_SetActiveFlag(sprites[2], 0);
        } else {
            for (i = 0; i < 2; i++) {
                int d = fn_8020A900((int)v, i);
                x = lbl_803F10C0[side][i + 3].x - off;
                SpriteLayer_SetResource(sprites[3 - i], d + 0xB2A);
                fn_8011F804(sprites[3 - i], x, lbl_803F10C0[side][i + 3].y);
                fn_8011F744(sprites[3 - i], ds, ds);
            }
            SpriteHandle_SetActiveFlag(sprites[1], 0);
            SpriteHandle_SetActiveFlag(sprites[2], 1);
        }
    }
    if (!low) {
        mark->Hide();
    }
    mark->Update();
    for (int i = 0; i < 4; i++) {
        SpriteHandle_RecomputeCull(sprites[i]);
    }
}

void SpeedHud::Draw() {
}

void SpeedHud::SetDelay(int n) {
    if (state < 5) {
        delay = n + 1;
    }
}

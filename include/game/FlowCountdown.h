#ifndef GAME_FLOWCOUNTDOWN_H
#define GAME_FLOWCOUNTDOWN_H

/* Countdown timer display tasks (0x801FEBD8..0x80200044). */

#include "game/FlowScene.h"

extern "C" {
extern const float lbl_806DA878;
extern const float lbl_806DA87C;
extern const float lbl_806DA880;
extern const float lbl_806DA884;
extern const float lbl_806DA888;
extern int lbl_803C0200[10];
extern int lbl_803C01C4[15];
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void PreloadResource(int id);
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
float fn_8020A6CC(FlowFader *fader);
int fn_8020A788(FlowFader *fader);
extern float lbl_803C014C[15][2];
}

/* One of the fifteen blinking timer dots (vtable lbl_804EC260). */
struct CountdownDot : FlowTask {
    int active;
    int index;
    int layer;
    float x;
    float y;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
    CountdownDot(int idx, int layer_)
        : FlowTask(idx), active(0), layer(layer_), x(lbl_806DA880), y(lbl_806DA880),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        if (idx < 0 || idx > 14) {
            index = 0;
        } else {
            index = idx;
        }
        PreloadResource(lbl_803C01C4[index]);
        fn_8020A734(scale.p, 1, lbl_806DA878, lbl_806DA878);
        fn_8020A7CC(fade.p, 0, 0, 1);
    }
    ~CountdownDot();
    virtual void _key3();
};

/* Big seconds numeral (vtable lbl_804EC278). */
struct CountdownDigit : FlowTask {
    int layer;
    float x;
    float y;
    int seconds;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
    CountdownDigit(int id, int layer_, int secs)
        : FlowTask(id), layer(layer_), x(lbl_806DA880), y(lbl_806DA880), seconds(secs),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        int i;
        int *res;
        if (secs < 0 || secs > 99) {
            seconds = 0;
        }
        for (i = 0, res = lbl_803C0200; i < 10; i++, res++) {
            PreloadResource(*res);
        }
        fn_8020A734(scale.p, 0x1E, lbl_806DA878, lbl_806DA87C);
        fn_8020A7CC(fade.p, 0xFF, 0, 0x3C);
    }
    ~CountdownDigit();
    virtual void _key3();
};

/* Countdown host (vtable lbl_804EC248). */
struct Countdown : FlowTask {
    VHolder<FlowSceneList> list;
    int layer;
    float x;
    float y;
    VHolder<FlowFaderI> fade;
    int timer;
    int field28;
    Countdown(int layer_, int id);
    ~Countdown();
    virtual void _key3();
};

#endif

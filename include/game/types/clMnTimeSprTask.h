#ifndef GAME_TYPES_CLMNTIMESPRTASK_H
#define GAME_TYPES_CLMNTIMESPRTASK_H
#include "game/FlowCountdown.h"
#include "game/types/clMnTaskInterface.h"
/* One of the fifteen blinking timer dots (vtable CountdownDot_vtable_804EC260). */
struct clMnTimeLightsSpr : clMnTaskInterface {
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
    clMnTimeLightsSpr(int idx, int layer_)
        : clMnTaskInterface(idx), active(0), layer(layer_), x(lbl_806DA880), y(lbl_806DA880),
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
    ~clMnTimeLightsSpr();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

/* Big seconds numeral (vtable CountdownDigit_vtable_804EC278). */
struct clMnTimeNumSpr : clMnTaskInterface {
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
    clMnTimeNumSpr(int id, int layer_, int secs)
        : clMnTaskInterface(id), layer(layer_), x(lbl_806DA880), y(lbl_806DA880), seconds(secs),
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
    ~clMnTimeNumSpr();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

/* clMnTimeSprTask host (vtable Countdown_vtable_804EC248). */
struct clMnTimeSprTask : clMnTaskInterface {
    VHolder<FlowSceneList> list;
    int layer;
    float x;
    float y;
    VHolder<FlowFaderI> fade;
    int timer;
    int field28;
    clMnTimeSprTask(int layer_, int id);
    ~clMnTimeSprTask();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

#endif

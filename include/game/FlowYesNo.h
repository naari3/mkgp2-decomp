#ifndef GAME_FLOWYESNO_H
#define GAME_FLOWYESNO_H

#include "game/FlowScene.h"

/*
 * Two-choice selector (0x80204474..0x80207324): YesNoTask owns a task list
 * holding the two option buttons and a blinking cursor.
 *
 *   FlowTask
 *     YesNoTask    (vtable lbl_804EC4C0, size 0x24)
 *     YesNoCursor  (vtable lbl_804EC4D8, size 0x28)
 *     YesNoSpark   (vtable lbl_804EC504, size 0x2C)
 *     YesNoButton  (ctor fn_80207324, vtable lbl_804EC54C, size 0x6C)
 *       YesNoButtonL (vtable lbl_804EC534, size 0x84)
 *       YesNoButtonR (vtable lbl_804EC51C, size 0x74)
 */

extern "C" {
extern const float lbl_806DAB10;
extern const float lbl_806DAB14;
extern const float lbl_806DAB18;
extern const float lbl_806DAB1C;
extern const float lbl_806DAB20;
extern const float lbl_806DAB24;
extern const float lbl_806DAB28;
extern const float lbl_806DAB2C;
extern const float lbl_806DAB30;
extern const float lbl_806DAB40;
extern const float lbl_806DAB44;
extern const float lbl_806DAB48;
extern const float lbl_806DAB4C;
extern const float lbl_806DAB50;
extern const float lbl_806DAB54;

struct YesNoPos {
    float x;
    float y;
};
extern const YesNoPos lbl_806DAAF8;

void fn_8020A734(FlowFader *fader, int frames, float from, float to);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
int fn_8020A788(FlowFader *fader);
void PreloadResource(int id);
void fn_80120A08(int id);
}

struct YesNoButton : FlowTask {
    int layer;
    int kind;
    int field18;
    const char *text0;
    const char *text1;
    int field24;
    VHolder<FlowFaderF> fade;
    float x;
    float y;
    float field34;
    float field38;
    float color[3];
    int alpha;
    bool selected;
    VHolder<FlowFaderF> fader50;
    VHolder<FlowFaderF> fader54;
    VHolder<FlowFaderF> fader58;
    VHolder<FlowFaderI> fader5C;
    VHolder<FlowFaderF> glow;
    VHolder<FlowFaderF> scaleX;
    VHolder<FlowFaderF> scaleY;
    YesNoButton(int kind_, bool flag, int layer_, int id);
    ~YesNoButton();
    virtual void _key2();

    void SetSelected(bool sel) {
        if (selected != sel) {
            if (sel) {
                fn_8020A734(fade.p, 5, lbl_806DAB10, lbl_806DAB14);
                fn_8020A734(glow.p, 5, lbl_806DAB18, lbl_806DAB1C);
                fn_8020A734(scaleX.p, 0xF, lbl_806DAB20, lbl_806DAB24);
                fn_8020A734(scaleY.p, 0xF, lbl_806DAB20, lbl_806DAB28);
            } else {
                fn_8020A734(fade.p, 5, lbl_806DAB2C, lbl_806DAB30);
                fn_8020A734(glow.p, 5, lbl_806DAB20, lbl_806DAB24);
                fn_8020A734(scaleX.p, 1, lbl_806DAB20, lbl_806DAB20);
                fn_8020A734(scaleY.p, 1, lbl_806DAB20, lbl_806DAB20);
            }
        }
        selected = sel;
    }
};

/* Same as YesNoButton::SetSelected, with the condition re-evaluated in place. */
#define YESNO_SET_SELECTED(b, cond)                                                     \
    do {                                                                                \
        if ((b)->selected != (bool)(cond)) {                                            \
            if (cond) {                                                                 \
                fn_8020A734((b)->fade.p, 5, lbl_806DAB10, lbl_806DAB14);                \
                fn_8020A734((b)->glow.p, 5, lbl_806DAB18, lbl_806DAB1C);                \
                fn_8020A734((b)->scaleX.p, 0xF, lbl_806DAB20, lbl_806DAB24);            \
                fn_8020A734((b)->scaleY.p, 0xF, lbl_806DAB20, lbl_806DAB28);            \
            } else {                                                                    \
                fn_8020A734((b)->fade.p, 5, lbl_806DAB2C, lbl_806DAB30);                \
                fn_8020A734((b)->glow.p, 5, lbl_806DAB20, lbl_806DAB24);                \
                fn_8020A734((b)->scaleX.p, 1, lbl_806DAB20, lbl_806DAB20);              \
                fn_8020A734((b)->scaleY.p, 1, lbl_806DAB20, lbl_806DAB20);              \
            }                                                                           \
        }                                                                               \
        (b)->selected = (cond);                                                         \
    } while (0)

struct YesNoButtonL : YesNoButton {
    unsigned char field6C;
    unsigned char field6D;
    VHolder<FlowFaderI> fader70;
    VHolder<FlowFaderF> fader74;
    VHolder<FlowFaderF> fader78;
    TextManager *texts;
    int field80;
    YesNoButtonL(int kind_, int layer_) : YesNoButton(kind_, 1, layer_, 0), field6C(0), field6D(1),
        fader70(new FlowFaderI), fader74(new FlowFaderF(lbl_806DAB10)), fader78(new FlowFaderF(lbl_806DAB10)) {
        PreloadResource(0x729);
        PreloadResource(0x730);
        fn_8020A7CC(fader70.p, 0, 0, 1);
        fn_8020A734(fader74.p, 1, lbl_806DAB40, lbl_806DAB40);
        fn_8020A734(fader78.p, 1, lbl_806DAB40, lbl_806DAB40);
        texts = new TextManager[2];
        texts[0].visible = 1;
        TexMgr_SetTexture(&texts[0], text0);
        texts[1].visible = 1;
        TexMgr_SetTexture(&texts[1], text1);
        field80 = 0;
    }
    ~YesNoButtonL();
    virtual void _key3();
};

struct YesNoButtonR : YesNoButton {
    TextManager *texts;
    int field70;
    YesNoButtonR(int kind_, int layer_) : YesNoButton(kind_, 0, layer_, 1), field70(1) {
        PreloadResource(0x72A);
        texts = new TextManager[2];
        texts[0].visible = 1;
        TexMgr_SetTexture(&texts[0], text0);
        texts[1].visible = 1;
        TexMgr_SetTexture(&texts[1], text1);
    }
    ~YesNoButtonR();
    virtual void _key3();
};

struct YesNoSpark : FlowTask {
    VHolder<FlowFaderF> alpha;
    VHolder<FlowFaderF> scaleX;
    VHolder<FlowFaderF> scaleY;
    int layer;
    float x;
    float y;
    unsigned char flag;
    YesNoSpark(int id, int layer_, float x_, float y_, unsigned char flag_)
        : FlowTask(id), alpha(new FlowFaderF(lbl_806DAB10)), scaleX(new FlowFaderF(lbl_806DAB10)), scaleY(new FlowFaderF(lbl_806DAB10)),
          layer(layer_), x(x_), y(y_), flag(flag_) {
        fn_8020A734(alpha.p, 0x14, lbl_806DAB10, lbl_806DAB54);
        fn_8020A734(scaleX.p, 0xA, lbl_806DAB18, lbl_806DAB20);
        fn_8020A734(scaleY.p, 0xA, lbl_806DAB10, lbl_806DAB20);
    }
    ~YesNoSpark();
    virtual void _key2();
};

struct YesNoCursor : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> timer;
    int layer;
    float x;
    float y;
    bool visible;
    YesNoCursor(int layer_)
        : FlowTask(0xA), list(new SceneListImpl), timer(new FlowFaderI), layer(layer_),
          x(lbl_806DAAF8.x), y(lbl_806DAAF8.y), visible(1) {
        PreloadResource(0x8A3);
        fn_8020A7CC(timer.p, 0, 0x3C, 0x3C);
    }
    ~YesNoCursor();
    virtual void Update();
    virtual void Draw();
    virtual void _key2();
};

struct YesNoTask : FlowTask {
    VHolder<FlowSceneList> list;
    int layer;
    int kind;
    int choice;
    unsigned char field20;
    YesNoTask(int kind_, unsigned char defYes, int layer_, int id);
    ~YesNoTask();
    virtual void Update();
    virtual void Draw();
    virtual void _key2();
};

#endif

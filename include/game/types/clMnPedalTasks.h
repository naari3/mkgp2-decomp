#ifndef GAME_TYPES_CLMNPEDALTASKS_H
#define GAME_TYPES_CLMNPEDALTASKS_H

/* Pedal banner and its font sprites; shared legacy countdown views remain available. */

#include "game/FlowScene.h"
#include "game/types/clMnTaskInterface.h"

struct CcLObjList;

template <> struct VHolder<CcLObjList> {
    CcLObjList *p;
    VHolder() : p(0) {}
    VHolder(CcLObjList *q) : p(q) {}
    ~VHolder() throw();
    void Reset(CcLObjList *q) throw();
};
struct CcScene;

template <> struct VHolder<CcScene> {
    CcScene *p;
    VHolder() : p(0) {}
    VHolder(CcScene *q) : p(q) {}
    ~VHolder() throw();
    void Reset(CcScene *q) throw();
};


struct clMnPedalFontLeft;
struct clMnPedalFontRight;
struct clMnHandleFont;

template <> struct VHolder<clMnPedalFontLeft> {
    clMnPedalFontLeft *p;
    VHolder() : p(0) {}
    VHolder(clMnPedalFontLeft *q) : p(q) {}
    ~VHolder() throw();
};

template <> struct VHolder<clMnPedalFontRight> {
    clMnPedalFontRight *p;
    VHolder() : p(0) {}
    VHolder(clMnPedalFontRight *q) : p(q) {}
    ~VHolder() throw();
};

template <> struct VHolder<clMnHandleFont> {
    clMnHandleFont *p;
    VHolder() : p(0) {}
    VHolder(clMnHandleFont *q) : p(q) {}
    ~VHolder() throw();
};


extern "C" {
extern const float lbl_806DA878;
extern const float lbl_806DA87C;
extern const float lbl_806DA880;
extern const float lbl_806DA88C;
extern const float lbl_806DA890;
extern const float lbl_806DA894;
extern const float lbl_806DA898;
extern const float lbl_806DA884;
extern const float lbl_806DA888;
extern int lbl_803C0200[10];
extern int lbl_803C01C4[15];
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void PreloadResource(int id);
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
void fn_8020A7CC(FlowFader *fader, int a, int b, int c);
float fn_8020A6CC(FlowFader *fader);
int fn_8020A788(FlowFader *fader);
extern float lbl_803C014C[15][2];
extern float lbl_803C0228[2][2];
void fn_80121E10(ResCtrl *ctrl);
int fn_8020A900(int value, int digit);
}

/* Sprite overlay drawn on top of clMnPedalSprTask (types 0..2). */
struct clMnPedalFontRight {
    void Draw();
    virtual ~clMnPedalFontRight();
    int type;
    int layer;
    int field0C;
    float x;
    float y;
    float mul;
    int counter;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    clMnPedalFontRight(int type_, int layer_)
        : layer(layer_), field0C(0), x(lbl_806DA880), y(lbl_806DA880), counter(0),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        if (type_ <= -1 || type_ >= 6) {
            type = 0;
        } else {
            type = type_;
        }
        PreloadResource(0x88D);
        PreloadResource(0x88E);
        PreloadResource(0x88F);
        fn_8020A734(scale.p, 0xA, lbl_806DA894, lbl_806DA898);
        fn_8020A7CC(fade.p, 0xCC, 0xCC, 0xA);
    }
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

/* Sprite overlay drawn on top of clMnPedalSprTask (types 3..5). */
struct clMnPedalFontLeft {
    void Draw();
    virtual ~clMnPedalFontLeft();
    int type;
    int layer;
    int field0C;
    float x;
    float y;
    float mul;
    int counter;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    clMnPedalFontLeft(int type_, int layer_)
        : layer(layer_), field0C(0), x(lbl_806DA880), y(lbl_806DA880), counter(0),
          scale(new FlowFaderF(lbl_806DA880)), fade(new FlowFaderI) {
        if (type_ <= -1 || type_ >= 6) {
            type = 0;
        } else {
            type = type_;
        }
        PreloadResource(0x88C);
        PreloadResource(0x890);
        PreloadResource(0x8A7);
        fn_8020A734(scale.p, 0x46, lbl_806DA894, lbl_806DA894);
        fn_8020A7CC(fade.p, 0xCC, 0xCC, 0x46);
    }
    void SetPos(float px, float py) {
        x = px;
        y = py;
    }
};

#include "game/types/CountdownResStep.h"

extern "C" {
extern CountdownResStep lbl_803C00DC[14];



}

/* Animated countdown banner. */
struct clMnPedalSprTask : clMnTaskInterface {
    int type;
    int layer;
    int state;
    float x;
    float y;
    int counter;
    VHolder<clMnPedalFontRight> partA;
    VHolder<clMnPedalFontLeft> partB;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderI> fade;
    int resId;
    clMnPedalSprTask(int type_, int layer_, int id);
    ~clMnPedalSprTask();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

#endif

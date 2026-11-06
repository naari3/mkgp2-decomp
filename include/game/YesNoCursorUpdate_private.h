#ifndef GAME_YESNOCURSORUPDATE_PRIVATE_H
#define GAME_YESNOCURSORUPDATE_PRIVATE_H

#include "game/FlowScene.h"

extern "C" {
extern const float lbl_806DAB10;
extern const float lbl_806DAB18;
extern const float lbl_806DAB20;
extern const float lbl_806DAB54;
void fn_8020A734(FlowFader *fader, int frames, float from, float to);
int fn_8020A788(FlowFader *fader);
}

struct YesNoSpark : FlowTask {
    VHolder<FlowFaderF> offset;
    VHolder<FlowFaderF> scale;
    VHolder<FlowFaderF> alpha;
    int layer;
    float x;
    float y;
    unsigned char flag;
    YesNoSpark(int id, int layer_, float x_, float y_, unsigned char flag_)
        : FlowTask(id), offset(new FlowFaderF(lbl_806DAB10)), scale(new FlowFaderF(lbl_806DAB10)), alpha(new FlowFaderF(lbl_806DAB10)),
          layer(layer_), x(x_), y(y_), flag(flag_) {
        fn_8020A734(offset.p, 0x14, lbl_806DAB10, lbl_806DAB54);
        fn_8020A734(scale.p, 0xA, lbl_806DAB18, lbl_806DAB20);
        fn_8020A734(alpha.p, 0xA, lbl_806DAB10, lbl_806DAB20);
    }
    ~YesNoSpark();
    virtual void Update();
    virtual void Draw();
    virtual void _key2();
};

/* TU-local declaration view: the undefined key keeps the existing vtable external. */
struct YesNoCursor : FlowTask {
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> timer;
    int layer;
    float x;
    float y;
    bool visible;
    virtual void _key2();
    ~YesNoCursor();
    virtual void Update();
    virtual void Draw();
};

#endif

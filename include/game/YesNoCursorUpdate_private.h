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

#include "game/types/YesNoSpark.h"

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

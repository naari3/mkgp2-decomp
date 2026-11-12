#ifndef GAME_TYPES_CLRSCARDT1_H
#define GAME_TYPES_CLRSCARDT1_H
#include "game/types/clMnCardClasses.h"
struct PrintKart {
    int busy, layout;
    char pad08[0x18];
    unsigned char visible, active;
    char pad22[0x68 - 0x22];
    PrintKart();
    ~PrintKart();
};

struct clRsCardT1 : clMnTaskInterface {
    // Finish is the vtable key in SceneRoleTransitions.cpp. The setup and
    // transition units retain their nondeferred/deferred generation modes.
    virtual void Finish();
    virtual ~clRsCardT1();
    virtual void Update();
    virtual void Draw();
    VHolder<FlowSceneList> list;
    VHolder<FlowFaderI> fader;
    VHolder<PrintKart> kart;
    int phase, error;
    clRsCardT1();
    void DrawError();
    void CheckErrors();
};
#endif

#ifndef GAME_RACEHUDSCENECTORPRIVATE_H
#define GAME_RACEHUDSCENECTORPRIVATE_H
#include "game/FlowScene.h"
#include "game/types/SceneBase.h"
struct FlowSceneHost {
    virtual ~FlowSceneHost();
    virtual void HostUpdate()=0;
    virtual void HostDraw()=0;
    VHolder<FlowSceneList> list;
    FlowSceneHost();
};
struct RaceHudScene : SceneBase, FlowSceneHost {
    int position,state;
    RaceHudScene();
    virtual ~RaceHudScene();
};
struct InputImpl {
    void *vt;
    unsigned char enabled,flag5,flag6,pad7;
    int fields[8];
};
struct ItemMsgWnd { char opaque[0x5C]; ItemMsgWnd(); };
extern "C" {
extern void *lbl_803FDF28[],*lbl_803FDF40[];
void *Alloc(unsigned long);
struct HudDisplayFlags { unsigned char active; char pad01[0x11]; unsigned char other; void SetActive(unsigned char v) { active=v; } void SetOther(unsigned char v) { other=v; } };
HudDisplayFlags *fn_801DAEC0();
void fn_8021A354();
void *ItemDisplay_GetOrCreate();
extern ItemMsgWnd *lbl_806D1A88;
}
static inline void CreateHudInput() {
    InputImpl *p=(InputImpl *)Alloc(0x28);
    if(p) {
        p->vt=lbl_803FDF28;
        g_pInputState=(InputState *)p;
        p->vt=lbl_803FDF40;
        p->enabled=0; p->flag5=1; p->flag6=1;
        p->fields[0]=0; p->fields[1]=0; p->fields[2]=0; p->fields[3]=0;
        p->fields[4]=0; p->fields[5]=0; p->fields[6]=0; p->fields[7]=0;
    }
}
#endif

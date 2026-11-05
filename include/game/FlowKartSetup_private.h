#ifndef GAME_FLOWKARTSETUP_PRIVATE_H
#define GAME_FLOWKARTSETUP_PRIVATE_H
#include "game/FlowScene.h"
#include "game/FlowKartPosition_private.h"
struct FKPanelSprite {
    int field0,layer,field8; float x,y; char pad14[0x1C];
    FKPanelSprite(int,int,int);
    void SetPosition(FKPosition p) { x=p.x; y=p.y; }
    void SetPosition(float a,float b) { x=a; y=b; }
};
struct FKPanelEntry { int resource[2]; const char *text[3]; int mode,state; };
struct FKSetupPanel {
    int state,kind,timer,fieldC,alpha,layer,mode,iconMode;
    int field20; FKPanelEntry pending; int otherKind; unsigned char queued; char pad45[3];
    FKPanelSprite *labelB,*labelA; ResCtrl *icons[3]; TextManager *texts[3];
};
extern "C" {
extern const float lbl_806DA1B0,lbl_806DA1BC,lbl_806DA1C0;
void *memcpy(void *,const void *,unsigned long);
void Sprite_SetupAnim(FKPanelSprite *,int,int,int);
void fn_801F93D0(TextManager *,float,float);
void fn_80121E10(ResCtrl *);
void fn_8019FF6C(FKPanelSprite *,int);
void fn_801FE1D4();
}
static inline void FKShowIcon(ResCtrl *r,FKPosition p) { r->Show(p.x,p.y,lbl_806DA1C0); }
#endif

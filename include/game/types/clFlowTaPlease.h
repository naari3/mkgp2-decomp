#ifndef CLFLOWTAPLEASE_PRIVATE_H
#define CLFLOWTAPLEASE_PRIVATE_H
#include "game/CreditHud.h"
#include "game/FlowScene.h"
#include "game/types/clFlowProcess.h"
#include "game/singleton.h"
struct C8Prompt { char pad[0x20]; C8Prompt(int,int,int,int,int); ~C8Prompt(); };
struct C8PromptHolder {
    C8Prompt *p;
    C8PromptHolder(C8Prompt *q):p(q) {}
    ~C8PromptHolder() throw() { delete p; }
};
struct C8ParamSprite {
    int a,layer,b; float x,y,sx,sy,alpha; float scale; char pad[0xC];
    C8ParamSprite(int,int); ~C8ParamSprite();
};
struct C8SpriteBox {
    C8ParamSprite *sprite;
    unsigned char enabled,mode; int timer;
    C8SpriteBox();
    ~C8SpriteBox() { delete sprite; }
};
struct C8BoxHolder {
    C8SpriteBox *p;
    C8BoxHolder(C8SpriteBox *q):p(q) {}
    ~C8BoxHolder() throw() { delete p; }
};
typedef TextManager C8Text;
typedef InputState C8Input;
struct clFlowTaPlease : clFlowProcess {
    int state,selection;
    AnimSprite *sprite;
    C8Text *text;
    C8Text *texts[3];
    short *params[4];
    unsigned char flag;
    C8PromptHolder prompt;
    C8BoxHolder box;
    virtual ~clFlowTaPlease();
    virtual int Update();
    virtual void Draw();
    clFlowTaPlease();
};
extern "C" {
extern C8Input *g_pInputState;
extern int g_cupId,g_longRoundFlag,g_reverseRoundFlag;
extern const float lbl_806D9EB8,lbl_806D9EA8,lbl_806D9EBC;
extern const float lbl_806D9EC0,lbl_806D9EC4,lbl_806D9EC8,lbl_806D9ECC,lbl_806D9ED0;
void Sprite_CreateWithParams(C8ParamSprite *,int,int,float,float,float,float,float,float);
void SetSyncTarget(int);
void SetupBgSprites(int);
const char *fn_8023DAA8(int);
const char *Item_GetLocalizedAsset(int,int);

short *fn_801A0310(AnimSprite *,int);
void Sprite_SetAnimParam(AnimSprite *,short,short);
float TaRecord_GetTime_Current(int);
int fn_80167744(int,float);
void fn_801A0550(AnimSprite *);
void fn_8023CD3C(C8Prompt *,float,float);
void fn_8023CCF8(C8Prompt *,float,float);
float fn_801D8D3C(int,int);
void InitRumbleController(int);
}
inline C8Input *C8GetInput() { return SINGLETON_INSTANCE(g_pInputState); }
inline C8ParamSprite::C8ParamSprite(int resource,int mode) {
    float pos=lbl_806D9EB8;
    float scale=lbl_806D9EA8;
    float alpha=lbl_806D9EBC;
    Sprite_CreateWithParams(this,resource,mode,pos,pos,scale,scale,alpha,alpha);
}
inline C8SpriteBox::C8SpriteBox() {
    enabled=0; mode=0; timer=0;
    sprite=new C8ParamSprite(0x9E,1);
}
#endif

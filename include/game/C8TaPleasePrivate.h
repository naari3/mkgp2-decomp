#ifndef C8_TA_PLEASE_PRIVATE_H
#define C8_TA_PLEASE_PRIVATE_H
#include "game/CreditHud.h"
#include "game/singleton.h"
struct C8FlowBase { virtual void Key(); C8FlowBase(); ~C8FlowBase(); };
struct C8Prompt { char pad[0x20]; C8Prompt(int,int,int,int,int); };
struct C8PromptHolder {
    C8Prompt *p;
    C8PromptHolder(C8Prompt *q):p(q) {}
    ~C8PromptHolder() throw();
};
struct C8ParamSprite {
    int a,layer,b; float x,y,sx,sy,alpha; char pad[0x10];
    C8ParamSprite(int,int);
};
struct C8SpriteBox {
    C8ParamSprite *sprite;
    unsigned char enabled,mode; int timer;
    C8SpriteBox();
};
struct C8BoxHolder {
    C8SpriteBox *p;
    C8BoxHolder(C8SpriteBox *q):p(q) {}
    ~C8BoxHolder() throw();
};
struct C8Text {
    char pad[0x20]; unsigned int color; char tail[0x20C];
    C8Text();
};
struct C8Input { char pad[4]; unsigned char enabled; char pad5[0x13]; int held,edge; };
struct C8TaPlease : C8FlowBase {
    int state,selection;
    AnimSprite *sprite;
    C8Text *text;
    C8Text *texts[3];
    short *params[4];
    unsigned char flag;
    C8PromptHolder prompt;
    C8BoxHolder box;
    virtual void Key();
    C8TaPlease();
};
extern "C" {
extern void *C8TaPlease_vtable_8049B1CC[];
struct C8TaTables { char pad[0x3FC]; int labels[8][2][2]; int symbols[8][2]; int rounds[8][2]; };
extern const C8TaTables clFlowTaPlease_Init_rodata_8039B470;
extern C8Input *g_pInputState;
extern int g_cupId,g_longRoundFlag,g_reverseRoundFlag;
extern const float lbl_806D9EB8,lbl_806D9EA8,lbl_806D9EBC;
extern const float lbl_806D9EC0,lbl_806D9EC4,lbl_806D9EC8,lbl_806D9ECC,lbl_806D9ED0;
void Sprite_CreateWithParams(C8ParamSprite *,int,int,float,float,float,float,float,float);
void SetSyncTarget(int);
void SetupBgSprites(int);
int fn_8023DAA8(int);
int Item_GetLocalizedAsset(int,int);
void TexMgr_SetTexture(C8Text *, int, ...);
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

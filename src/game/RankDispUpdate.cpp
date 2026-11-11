/* Rank HUD entrance, pulse, fade-out and resource refresh. */
#include "game/FlowScene.h"
struct RankDispView {
    void *vt;
    int request,unused;
    int sprites[2];
    int state,position;
    float offset;
    int countdown;
    FlowFaderF *fade,*scale,*rotation;
    FlowFaderI *alpha;
};
extern "C" {
extern int g_countdownPhase;
extern const float lbl_806DBF58[2];
extern const float lbl_806DBF60,lbl_806DBF64,lbl_806DBF68,lbl_806DBF6C,lbl_806DBF70,lbl_806DBF74,lbl_806DBF78;
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFaderF *,int,float,float);
float fn_8020A6CC(FlowFaderF *);
int fn_8020A788(FlowFaderI *);
void fn_8020A7CC(FlowFaderI *,int,int,int);
void fn_80120A08(int);
void SpriteHandle_SetActiveFlag(int,int);
void SpriteHandle_RecomputeCull(int);
void SpriteHandle_SetCornerAlpha(int,unsigned char);
void SpriteLayer_SetResource(int,int);
void fn_8011F804(int,float,float);
void fn_8011F744(int,float,float);
void fn_8011F7AC(int,float);
void fn_802494E0(RankDispView *p) {
    switch(p->state) {
    case -1: if(g_countdownPhase<4) p->state=0; return;
    case 0:
        p->offset=fn_8020A6CC(p->fade);
        p->fade->Step();
        if(p->fade->Done()) { p->offset=lbl_806DBF60; p->state=1; }
        break;
    case 1:
        if(g_countdownPhase<=2) { fn_8020A734(p->scale,4,lbl_806DBF64,lbl_806DBF68); p->state=2; }
        break;
    case 2:
        if(p->scale->Done() && lbl_806DBF64==fn_8020A6CC(p->scale)) p->state=3;
        break;
    case 7:
        if(--p->countdown==0) { p->state=3; fn_8020A7CC(p->alpha,0,255,2); }
        break;
    case 4:
        if(p->scale->Done()) {
            p->state=5;
            fn_8020A734(p->scale,15,lbl_806DBF6C,lbl_806DBF70);
            fn_8020A734(p->rotation,1,lbl_806DBF60,lbl_806DBF60);
        }
        break;
    case 5:
        if(p->scale->Done()) { p->state=6; fn_8020A734(p->fade,5,lbl_806DBF70,lbl_806DBF74); }
        break;
    case 6:
        if(p->scale->Done()) {
            p->state=8;
            fn_80120A08(0xB23);
            for(int i=0;i<2;i++) { SpriteHandle_SetActiveFlag(p->sprites[i],0); SpriteHandle_RecomputeCull(p->sprites[i]); }
            return;
        }
        break;
    case 8: return;
    default: return;
    case 3: break;
    }
    if(p->request>0) {
        p->request--;
        if(p->request<=0) {
            p->request=0; p->state=4;
            fn_8020A734(p->scale,15,lbl_806DBF64,lbl_806DBF6C);
            fn_8020A734(p->rotation,15,lbl_806DBF60,lbl_806DBF78);
        }
    }
    int resource;
    int active=0;
    resource=p->position+0xB23;
    if(resource) {
        SpriteHandle_SetCornerAlpha(p->sprites[1],(unsigned char)fn_8020A788(p->alpha));
        float x=lbl_806DBF58[0]-p->offset;
        float y=lbl_806DBF58[1];
        active=1;
        float rotation=fn_8020A6CC(p->rotation);
        float scale=fn_8020A6CC(p->scale);
        for(int i=0;i<2;i++) {
            SpriteLayer_SetResource(p->sprites[i],resource);
            fn_8011F804(p->sprites[i],x,y);
            fn_8011F744(p->sprites[i],scale,scale);
            fn_8011F7AC(p->sprites[i],rotation);
        }
    }
    for(int i=0;i<2;i++) { SpriteHandle_SetActiveFlag(p->sprites[i],active); SpriteHandle_RecomputeCull(p->sprites[i]); }
    p->scale->Step(); p->rotation->Step();
    if(p->scale->Done()) {
        float value=fn_8020A6CC(p->scale);
        if(lbl_806DBF68==value) fn_8020A734(p->scale,4,lbl_806DBF68,lbl_806DBF64);
        else if(lbl_806DBF64==value) fn_8020A734(p->scale,1,lbl_806DBF64,lbl_806DBF64);
    }
    p->alpha->Step();
    if(p->alpha->Done()) {
        unsigned char value=(unsigned char)fn_8020A788(p->alpha);
        if(value==255) fn_8020A7CC(p->alpha,255,0,2);
        else if(value==0) fn_8020A7CC(p->alpha,0,0,1);
    }
}
}

/* Countdown-driven lap HUD animation and sprite activation. */
#include "game/FlowScene.h"
struct LapDispView {
    void *vt;
    int timer,unused;
    int sprites[3];
    int state,position;
    FlowFaderF *fade,*scale;
};
extern "C" {
extern int g_countdownPhase;
extern const float lbl_806DBDC8,lbl_806DBDCC,lbl_806DBDD0,lbl_806DBDD4;
extern const float LapDispUpdate_rodata_803E5CE8[][2],LapDispUpdate_rodata_803E5D00[][2];
#include "game/types/tween_set_order.h"
void fn_8020A734(FlowFaderF *,int,float,float);
float fn_8020A6CC(FlowFaderF *);
void SpriteHandle_SetActiveFlag(int,int);
void SpriteHandle_RecomputeCull(int);
void fn_8011F804(int,float,float);
void fn_8011F744(int,float,float);
void fn_8023F790(LapDispView *p) {
    switch(p->state) {
    case -1:
        if(g_countdownPhase<4) p->state=0;
        return;
    case 0:
        p->fade->Step();
        if(p->fade->Done()) p->state=1;
        break;
    case 1:
        if(g_countdownPhase<=2) { p->state=2; fn_8020A734(p->scale,4,lbl_806DBDC8,lbl_806DBDCC); }
        break;
    case 2:
        p->scale->Step();
        if(p->scale->Done()) { p->state=3; fn_8020A734(p->scale,4,lbl_806DBDCC,lbl_806DBDC8); }
        break;
    case 3:
        p->scale->Step();
        if(p->scale->Done()) p->state=4;
        break;
    case 5:
        p->fade->Step();
        if(p->fade->Done()) {
            p->state=6;
            for(int i=0;i<3;i++) { SpriteHandle_SetActiveFlag(p->sprites[i],0); SpriteHandle_RecomputeCull(p->sprites[i]); }
        }
        break;
    case 6: return;
    default: return;
    case 4: break;
    }
    if(p->timer>0) {
        p->timer--;
        if(p->timer<=0) {
            p->timer=0; p->state=5;
            fn_8020A734(p->fade,7,lbl_806DBDD0,lbl_806DBDD4);
        }
    }
    if(p->state!=4) {
        int position=p->position;
        float offset=fn_8020A6CC(p->fade);
        float scale=fn_8020A6CC(p->scale);
        for(int i=0;i<3;i++) {
            fn_8011F804(p->sprites[i],LapDispUpdate_rodata_803E5CE8[position][0]+LapDispUpdate_rodata_803E5D00[i][0]-offset,LapDispUpdate_rodata_803E5CE8[position][1]+LapDispUpdate_rodata_803E5D00[i][1]);
            fn_8011F744(p->sprites[i],scale,scale);
        }
    }
    for(int i=0;i<3;i++) { SpriteHandle_SetActiveFlag(p->sprites[i],1); SpriteHandle_RecomputeCull(p->sprites[i]); }
}
}

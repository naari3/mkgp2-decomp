#include "game/RaceDigitGapPrivate.h"
extern "C" void fn_80246484(DigitHud *self) {
    switch(self->state) {
    case -1: if(g_countdownPhase<4) self->state=0; return;
    case 0:
        self->offset=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) { self->state=1; self->offset=lbl_806DBF28; }
        break;
    case 1:
        if(g_countdownPhase<=2) { self->state=2; self->slide.p->Set(lbl_806DBF2C,lbl_806DBF30,4); }
        break;
    case 2:
        self->scale=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) {
            self->state=3; self->slide.p->Set(lbl_806DBF30,lbl_806DBF2C,4); self->scale=lbl_806DBF30;
        }
        break;
    case 3:
        self->scale=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) { self->state=4; self->scale=lbl_806DBF2C; }
        break;
    case 4: break;
    case 5:
        self->offset=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) {
            self->state=6; self->offset=lbl_806DBF34;
            for(int i=0;i<4;i++) { SpriteHandle_SetActiveFlag(self->sprites[i],0); SpriteHandle_RecomputeCull(self->sprites[i]); }
        }
        break;
    case 6:
    default: return;
    }
    if(self->id>0) {
        self->id--;
        if(self->id<=0) {
            self->id=0; self->state=5;
            self->slide.p->Set(lbl_806DBF28,lbl_806DBF34,7);
            HideDigitPanel(self->main.p);
            for(int i=0;i<5;i++) HideDigitPanel(self->others[i].p);
        }
    }
    int variant=0;
    if(g_gameMode==1) variant=1;
    if(self->state!=4) {
        for(int i=0;i<4;i++) {
            float y=lbl_803EF7C0[variant][i].y;
            float x=lbl_803EF7C0[variant][i].x-self->offset;
            fn_8011F744(self->sprites[i],self->scale,self->scale);
            SpriteHandle_SetActiveFlag(self->sprites[i],1);
            fn_8011F804(self->sprites[i],x,y);
        }
    }
    for(int i=0;i<4;i++) SpriteHandle_RecomputeCull(self->sprites[i]);
    LapNode *end=(LapNode *)&self->list.last;
    LapNode *node=(LapNode *)self->list.first;
    if(self->main.p) {
        float total=lbl_806DBF28;
        for(;node!=end;node=node->next) total+=node->value;
        if(total<lbl_806DBF28) total=lbl_806DBF28;
        if(total>lbl_806DBF38) total=lbl_806DBF38;
        self->main.p->number=total;
        fn_80247258(self->main.p);
    }
    node=(LapNode *)self->list.first;
    for(int i=0;i<5;i++,node=node->next) {
        if(self->others[i].p) {
            float value=node->value;
            if(value<lbl_806DBF28) value=lbl_806DBF28;
            if(value>lbl_806DBF38) value=lbl_806DBF38;
            self->others[i].p->number=value;
            fn_80247258(self->others[i].p);
        }
    }
}

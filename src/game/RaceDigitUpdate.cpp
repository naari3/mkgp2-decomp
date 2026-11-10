#include "game/RaceDigitGapPrivate.h"
#include "game/RaceDigitListPrivate.h"
static inline RaceDigitIterator LapBegin(DigitList *list) {
    return ((RaceDigitList *)list)->Begin();
}
static inline RaceDigitIterator LapEnd(DigitList *list) {
    return ((RaceDigitList *)list)->Finish();
}
static inline void LapNext(RaceDigitIterator &it) { it.node=it.node->next; }
static inline float LapValue(const RaceDigitIterator &it) { return it.node->value; }
static inline void BeginHidePanel(DigitPanel &panel) {
    if(panel.state<5) {
        panel.state=5;
        panel.slide.p->Set(lbl_806DBF28,lbl_806DBF34,7);
        for(int i=0;i<10;i++) panel.tweens[i].Set(lbl_806DBF28,lbl_806DBF34,7);
        panel.reveal.p->Set(10,0,20);
    }
}
static inline void ShowHudSprites(DigitHud &hud, int variant) {
    for(int renderIndex=0;renderIndex<4;renderIndex++) {
        float x;
        float y;
        y=RaceDigitUpdate_rodata_803EF7C0[variant][renderIndex].y;
        x=RaceDigitUpdate_rodata_803EF7C0[variant][renderIndex].x-hud.offset;
        fn_8011F744(hud.sprites[renderIndex],hud.scale,hud.scale);
        SpriteHandle_SetActiveFlag(hud.sprites[renderIndex],1);
        fn_8011F804(hud.sprites[renderIndex],x,y);
    }
}
extern "C" void fn_80246484(DigitHud *self) {
    int cullIndex;
    switch(self->state) {
    case -1: if(g_countdownPhase<4) self->state=0; return;
    case 0:
        self->offset=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) { self->state=1; self->offset=0.0f; }
        break;
    case 1:
        if(g_countdownPhase<=2) { self->state=2; self->slide.p->Set(1.0f,1.2f,4); }
        break;
    case 2:
        self->scale=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) {
            self->state=3; self->slide.p->Set(1.2f,1.0f,4); self->scale=1.2f;
        }
        break;
    case 3:
        self->scale=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) { self->state=4; self->scale=1.0f; }
        break;
    case 4: break;
    case 5:
        self->offset=self->slide.p->Value(); self->slide.p->Step();
        if(self->slide.p->Done()) {
            self->state=6; self->offset=220.0f;
            for(int i=0;i<4;i++) { SpriteHandle_SetActiveFlag(self->sprites[i],0); SpriteHandle_RecomputeCull(self->sprites[i]); }
        }
        break;
    case 6: break;
    default: return;
    }
    if(self->id>0) {
        self->id--;
        if(self->id<=0) {
            self->id=0; self->state=5;
            self->slide.p->Set(0.0f,220.0f,7);
            if(self->main.p) BeginHidePanel(*self->main.p);
            for(int i=0;i<5;i++) if(self->others[i].p) BeginHidePanel(*self->others[i].p);
        }
    }
    int variant=0;
    if(g_gameMode==1) variant=1;
    if(self->state!=4) ShowHudSprites(*self,variant);
    for(cullIndex=0;cullIndex<4;cullIndex++) SpriteHandle_RecomputeCull(self->sprites[cullIndex]);
    RaceDigitIterator end=LapEnd(&self->list);
    RaceDigitIterator node=LapBegin(&self->list);
    if(self->main.p) {
        float total=0.0f;
        for(;node.node!=end.node;LapNext(node)) total+=LapValue(node);
        if(total<0.0f) total=0.0f;
        if(total>599.999f) total=599.999f;
        self->main.p->number=total;
        fn_80247258(self->main.p);
    }
    node=LapBegin(&self->list);
    for(int i=0;i<5;i++,LapNext(node)) {
        if(self->others[i].p) {
            float value=LapValue(node);
            if(value<0.0f) value=0.0f;
            if(value>599.999f) value=599.999f;
            self->others[i].p->number=value;
            fn_80247258(self->others[i].p);
        }
    }
}

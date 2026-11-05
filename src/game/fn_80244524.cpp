#include "game/FlowScene.h"
extern "C" {
void fn_8011FAFC(ResCtrl *, int);
void fn_80121E10(ResCtrl *);
int ItemUseStats_GetCountCat5_6_8(void *);
int ItemUseStats_GetCountBanana(void *);
int ItemUseStats_GetCountShell(void *);
}
struct GaugeStatsView { char pad[0x344]; void *stats; };
struct GaugeMarkView {
    virtual ~GaugeMarkView();
    int field04;
    float x,y,scale;
    void SetPosition(float px,float py) { x=px; y=py; }
};
struct GaugeDisplay {
    void *vt;
    GaugeStatsView *owner;
    int layer,state,resource,count14,count18,count1c,count20,mode;
    float x,y,scale;
    FlowFaderF *f34;
    FlowFaderI *f38;
    FlowFaderF *f3c;
    FlowFaderI *f40,*f44;
    FlowFaderF *f48;
    GaugeMarkView *mark;
};
extern "C" {
void fn_80244CE0(GaugeDisplay *);
void fn_80244840(GaugeDisplay *);
unsigned char fn_80245420(GaugeMarkView *,unsigned char);
}
static inline unsigned int MaskColor(int value) { int mask=-256; return value | mask; }
extern "C" void fn_80244524(GaugeDisplay *self,unsigned char visible) {
    fn_80244CE0(self);
    if (self->state == 2 || self->state == 3) {
        unsigned char changed=0;
        void *stats=self->owner->stats;
        int count=ItemUseStats_GetCountCat5_6_8(stats);
        int banana=ItemUseStats_GetCountBanana(stats);
        int shell=ItemUseStats_GetCountShell(stats);
        switch(self->mode) {
        case 1:
            if (count < self->count14) { self->count14=count; changed=1; }
            break;
        case 3:
            if (banana < self->count1c) { changed=1; self->count1c=banana; }
            if (shell < self->count20) { changed=1; self->count20=shell; }
            break;
        }
        if (changed) {
            self->mode=4;
            self->f34->Set(0.0f,0.0f,1);
            self->f3c->Set(0.0f,0.0f,1);
            self->f44->Set(0,0,1);
            self->state=5;
        }
    }
    ResCtrl r;
    int layer=self->layer;
    float scale=self->scale;
    float offset=self->f48->Value();
    if (self->mark) {
        self->mark->SetPosition(self->x,offset*scale+self->y);
        self->mark->scale=scale;
        if (!fn_80245420(self->mark,visible)) { delete self->mark; self->mark=0; }
    }
    float size;
    size=scale*self->f34->Value();
    fn_80121E10(&r);
    r.resId=0xc2d;
    offset=offset*scale;
    r.Show(self->x,self->y+offset,1.0f);
    r.SetScale(size);
    r.SetColor(MaskColor(self->f38->Value()));
    if (visible) fn_8011FAFC(&r,layer);
    size=scale*self->f3c->Value();
    fn_80121E10(&r);
    r.resId=self->resource;
    r.Show(self->x,self->y+offset,1.0f);
    r.SetScale(size);
    r.SetColor(MaskColor(self->f40->Value()));
    if (visible) fn_8011FAFC(&r,layer);
    r.mode=3;
    r.SetColor(MaskColor(self->f44->Value()));
    if (visible) fn_8011FAFC(&r,layer);
    fn_80244840(self);
}

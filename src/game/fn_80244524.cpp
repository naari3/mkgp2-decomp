#include "game/types/clMrrItem.h"
extern "C" {
void fn_8011FAFC(ResCtrl *, int);
void fn_80121E10(ResCtrl *);
}
inline void MrrTweenTick(FlowFader *t) { t->b++; short limit=t->a; if(t->b>=limit) t->b=limit; }
static inline unsigned int MaskColor(int value) { int mask=-256; return value | mask; }
clMrrItemEffect::~clMrrItemEffect() {}

bool clMrrItemEffect::Draw(unsigned char draw) {
    bool result=1;
    ResCtrl c;
    int layer=(int)this->context;
    float scale=this->scale * this->fade.p->Value();
    fn_80121E10(&c);
    c.resId=0x1CD3;
    float x=this->x;
    float y=this->y;
    c.Show(x,y,lbl_806DBE90);
    c.SetScale(scale);
    c.field28=this->size.p->Value();
    c.tail[0]=1; c.tail[1]=1; c.tail[2]=1;
    unsigned int color=(unsigned char)this->alpha.p->Value();
    c.SetColor((color<<24)|(color<<16)|(color<<8)|255);
    if (draw) fn_8011FAFC(&c,layer);
    MrrTweenTick(this->fade.p);
    MrrTweenTick(this->size.p);
    MrrTweenTick(this->alpha.p);
    if (this->fade.p->b >= this->fade.p->a) {
        if (lbl_806DBE90 == this->fade.p->Value()) {
            this->fade.p->Set(lbl_806DBE90,lbl_806DBE64,10);
            this->alpha.p->Set(255,0,10);
        } else result=1;
    }
    return result;
}


clMrrItem::clMrrItem(ItemUseOwner *o, int id, void *c)
 : owner(o), context(c), state(0), item(fn_8023DBEC(id)),
 cat568(ItemUseStats_GetCountCat5_6_8(owner->stats)),
 cat79(ItemUseStats_GetCountCat7_9(owner->stats)),
 bananas(ItemUseStats_GetCountBanana(owner->stats)),
 shells(ItemUseStats_GetCountShell(owner->stats)), category(0),
 x(0.0f), y(0.0f), scale(1.0f), fade(new FlowFaderF(0.0f)),
 alpha(new FlowFaderI), size(new FlowFaderF(0.0f)), color(new FlowFaderI),
 flash(new FlowFaderI), offset(new FlowFaderF(0.0f)), burst(0) {
 fade.p->Set(0.0f, lbl_806DBEC0,8);
 alpha.p->Set(255,255,8);
 size.p->Set(0.0f,lbl_806DBEC0,8);
 color.p->Set(255,255,8);
 flash.p->Set(0,0,1);
 offset.p->Set(0.0f,0.0f,1);
}


clMrrItem::~clMrrItem() { delete burst; burst = 0; }


void clMrrItem::Trigger() {
 if (this->state < 5) {
  ItemUseStats *s = this->owner->stats;
  if (ItemUseStats_GetItemIdIfFlag14(s) > 0) {
   int a = ItemUseStats_GetCountCat5_6_8(s);
   int b = ItemUseStats_GetCountCat7_9(s);
   int c = ItemUseStats_GetCountBanana(s);
   int d = ItemUseStats_GetCountShell(s);
   if (a > this->cat568) { this->category=1; this->cat568=a; }
   if (b > this->cat79) { this->category=2; this->cat79=b; }
   if (c > this->bananas) { this->category=3; this->bananas=c; }
   if (d > this->shells) { this->category=3; this->shells=d; }
   this->fade.p->Set(1.0f,lbl_806DBEC0,10);
   this->alpha.p->Set(255,255,1);
   this->size.p->Set(1.0f,lbl_806DBEC4,10);
   this->color.p->Set(255,255,1);
   if (!this->burst) this->burst = new clMrrItemEffect(this->context);
   this->state=2;
  }
 }
}


void clMrrItem::Update() {
 this->fade.p->Step(); this->alpha.p->Step(); this->size.p->Step();
 this->color.p->Step(); this->flash.p->Step(); this->offset.p->Step();
 if (this->fade.p->Done()) {
  float v = this->fade.p->Value();
  switch (this->state) {
  case 0: {
   float k = lbl_806DBEC0;
   if (k == v) {
    this->fade.p->Set(k,1.0f,8);
    this->size.p->Set(lbl_806DBEC0,1.0f,8);
   } else {
    this->fade.p->Set(1.0f,1.0f,1);
    this->size.p->Set(1.0f,1.0f,1);
    this->state=1;
   }
   break;
  }
  case 2: {
   float k = lbl_806DBEC0;
   if (k == v) {
    switch (this->category) {
    case 1:
     this->fade.p->Set(k,1.0f,10);
     this->size.p->Set(lbl_806DBEC4,1.0f,10);
     this->offset.p->Set(0.0f,lbl_806DBEC8,10);
     break;
    case 3:
     this->fade.p->Set(k,1.0f,10);
     this->size.p->Set(lbl_806DBEC4,1.0f,10);
     break;
    default:
     this->fade.p->Set(1.5f,1.0f,10);
     this->size.p->Set(lbl_806DBEC4,1.0f,10);
     this->alpha.p->Set(255,255,17);
     this->offset.p->Set(0.0f,lbl_806DBECC,10);
     break;
    }
   } else {
    switch (this->category) {
    case 1:
     this->fade.p->Set(1.0f,lbl_806DBED0,10);
     this->size.p->Set(1.0f,lbl_806DBED0,10);
     this->flash.p->Set(0,255,10);
     this->offset.p->Set(lbl_806DBEC8,lbl_806DBEC8,1);
     this->state=3;
     break;
    case 3:
     this->fade.p->Set(1.0f,lbl_806DBED0,10);
     this->size.p->Set(1.0f,lbl_806DBED0,10);
     this->flash.p->Set(0,255,10);
     this->state=3;
     break;
    default:
     this->fade.p->Set(1.0f,1.0f,1);
     this->size.p->Set(1.0f,1.0f,1);
     this->alpha.p->Set(0,0,1);
     this->offset.p->Set(lbl_806DBECC,lbl_806DBECC,1);
     this->state=5;
     break;
    }
   }
   break;
  }
  case 4:
  case 5:
   break;
  case 3:
   if (lbl_806DBED0 == v) {
    this->fade.p->Set(lbl_806DBED0,1.0f,10);
    this->size.p->Set(lbl_806DBED0,1.0f,10);
    this->flash.p->Set(255,0,10);
   } else {
    this->fade.p->Set(1.0f,lbl_806DBED0,10);
    this->size.p->Set(1.0f,lbl_806DBED0,10);
    this->flash.p->Set(0,255,10);
   }
   break;
  }
 }
 if (this->alpha.p->Done()) {
  int v = this->alpha.p->Value();
  if (this->state==2 && this->category==2 && v==255)
   this->alpha.p->Set(255,0,3);
 }
}


void clMrrItem::Draw(unsigned char visible) {
    Trigger();
    if (this->state == 2 || this->state == 3) {
        unsigned char changed=0;
        ItemUseStats *stats=this->owner->stats;
        int count=ItemUseStats_GetCountCat5_6_8(stats);
        int banana=ItemUseStats_GetCountBanana(stats);
        int shell=ItemUseStats_GetCountShell(stats);
        switch(this->category) {
        case 1:
            if (count < this->cat568) { this->cat568=count; changed=1; }
            break;
        case 2:
        default:
            goto draw;
        case 3:
            if (banana < this->bananas) { changed=1; this->bananas=banana; }
            if (shell < this->shells) { changed=1; this->shells=shell; }
            break;
        }
        if (changed) {
            this->category=4;
            this->fade.p->Set(0.0f,0.0f,1);
            this->size.p->Set(0.0f,0.0f,1);
            this->flash.p->Set(0,0,1);
            this->state=5;
        }
    }
draw:
    ResCtrl r;
    int layer=(int)this->context;
    float scale=this->scale;
    float offset=this->offset.p->Value();
    if (this->burst) {
        this->burst->SetPosition(this->x,offset*scale+this->y);
        this->burst->scale=scale;
        if (!this->burst->Draw(visible)) { delete this->burst; this->burst=0; }
    }
    {
        float size=scale*this->fade.p->Value();
        fn_80121E10(&r);
        r.resId=0xc2d;
        offset=offset*scale;
        r.Show(this->x,this->y+offset,1.0f);
        r.SetScale(size);
        r.SetColor(MaskColor(this->alpha.p->Value()));
        if (visible) fn_8011FAFC(&r,layer);
    }
    {
        float size=scale*this->size.p->Value();
        fn_80121E10(&r);
        r.resId=this->item;
        r.Show(this->x,this->y+offset,1.0f);
        r.SetScale(size);
        r.SetColor(MaskColor(this->color.p->Value()));
        if (visible) fn_8011FAFC(&r,layer);
        r.mode=3;
        r.SetColor(MaskColor(this->flash.p->Value()));
        if (visible) fn_8011FAFC(&r,layer);
    }
    Update();
}

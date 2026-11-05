#include "game/ItemUseEffectPrivate.h"
extern "C" void fn_80244840(ItemUseEffect *self) {
 self->fade.p->Step(); self->alpha.p->Step(); self->size.p->Step();
 self->color.p->Step(); self->flash.p->Step(); self->offset.p->Step();
 if (self->fade.p->Done()) {
  float v = self->fade.p->Value();
  switch (self->state) {
  case 0: {
   float k = lbl_806DBEC0;
   if (k == v) {
    self->fade.p->Set(k,1.0f,8);
    self->size.p->Set(lbl_806DBEC0,1.0f,8);
   } else {
    self->fade.p->Set(1.0f,1.0f,1);
    self->size.p->Set(1.0f,1.0f,1);
    self->state=1;
   }
   break;
  }
  case 2: {
   float k = lbl_806DBEC0;
   if (k == v) {
    switch (self->category) {
    case 1:
     self->fade.p->Set(k,1.0f,10);
     self->size.p->Set(lbl_806DBEC4,1.0f,10);
     self->offset.p->Set(0.0f,lbl_806DBEC8,10);
     break;
    case 3:
     self->fade.p->Set(k,1.0f,10);
     self->size.p->Set(lbl_806DBEC4,1.0f,10);
     break;
    default:
     self->fade.p->Set(1.5f,1.0f,10);
     self->size.p->Set(lbl_806DBEC4,1.0f,10);
     self->alpha.p->Set(255,255,17);
     self->offset.p->Set(0.0f,lbl_806DBECC,10);
     break;
    }
   } else {
    switch (self->category) {
    case 1:
     self->fade.p->Set(1.0f,lbl_806DBED0,10);
     self->size.p->Set(1.0f,lbl_806DBED0,10);
     self->flash.p->Set(0,255,10);
     self->offset.p->Set(lbl_806DBEC8,lbl_806DBEC8,1);
     self->state=3;
     break;
    case 3:
     self->fade.p->Set(1.0f,lbl_806DBED0,10);
     self->size.p->Set(1.0f,lbl_806DBED0,10);
     self->flash.p->Set(0,255,10);
     self->state=3;
     break;
    default:
     self->fade.p->Set(1.0f,1.0f,1);
     self->size.p->Set(1.0f,1.0f,1);
     self->alpha.p->Set(0,0,1);
     self->offset.p->Set(lbl_806DBECC,lbl_806DBECC,1);
     self->state=5;
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
    self->fade.p->Set(lbl_806DBED0,1.0f,10);
    self->size.p->Set(lbl_806DBED0,1.0f,10);
    self->flash.p->Set(255,0,10);
   } else {
    self->fade.p->Set(1.0f,lbl_806DBED0,10);
    self->size.p->Set(1.0f,lbl_806DBED0,10);
    self->flash.p->Set(0,255,10);
   }
   break;
  }
 }
 if (self->alpha.p->Done()) {
  int v = self->alpha.p->Value();
  if (self->state==2 && self->category==2 && v==255)
   self->alpha.p->Set(255,0,3);
 }
}

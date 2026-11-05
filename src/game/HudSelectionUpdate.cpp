#include "game/HudSelectionPrivate.h"
extern "C" void fn_80245850(HudSelection *self) {
 switch(self->state) {
 case -1:
  if(g_countdownPhase<=3) self->state=0;
  return;
 case 0:
  self->position.p->Step();
  if(self->position.p->Done()) { self->state=1; self->position.p->Set(lbl_806DBF18,lbl_806DBF18,1); }
  break;
 case 1:
  if(g_countdownPhase<=2) { self->alpha.p->Set(lbl_806DBF1C,lbl_806DBF20,4); self->state=2; }
  break;
 case 2:
  if(self->alpha.p->Done() && self->alpha.p->Value()==lbl_806DBF1C) self->state=3;
  break;
 case 4:
  self->position.p->Step();
  if(self->position.p->Done()) { self->state=5; return; }
  break;
 case 5:return;
 default:return;
 case 3:break;
 }
 if(self->countdown>0) {
  if(--self->countdown<=0) {
   self->countdown=0; self->state=4;
   self->position.p->Set(lbl_806DBF18,lbl_806DBF24,7);
  }
 }
 float value=self->position.p->Value();
 fn_801F93EC(self->text,lbl_803EF75C[self->selection].x-value,lbl_803EF75C[self->selection].y);
 float alpha=self->alpha.p->Value();
 fn_801F93D0(self->text,alpha,alpha);
 fn_801F8A34(self->context,self->text,self->field08);
 self->alpha.p->Step();
 if(self->alpha.p->Done()) {
  float v=self->alpha.p->Value();
  if(lbl_806DBF20==v) self->alpha.p->Set(lbl_806DBF20,lbl_806DBF1C,4);
  else if(lbl_806DBF1C==v) self->alpha.p->Set(lbl_806DBF1C,lbl_806DBF1C,1);
 }
}


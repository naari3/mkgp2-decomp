#include "game/ItemUseEffectPrivate.h"
extern "C" void fn_80244CE0(ItemUseEffect *self) {
 if (self->state < 5) {
  ItemUseStats *s = self->owner->stats;
  if (ItemUseStats_GetItemIdIfFlag14(s) > 0) {
   int a = ItemUseStats_GetCountCat5_6_8(s);
   int b = ItemUseStats_GetCountCat7_9(s);
   int c = ItemUseStats_GetCountBanana(s);
   int d = ItemUseStats_GetCountShell(s);
   if (a > self->cat568) { self->category=1; self->cat568=a; }
   if (b > self->cat79) { self->category=2; self->cat79=b; }
   if (c > self->bananas) { self->category=3; self->bananas=c; }
   if (d > self->shells) { self->category=3; self->shells=d; }
   self->fade.p->Set(1.0f,lbl_806DBEC0,10);
   self->alpha.p->Set(255,255,1);
   self->size.p->Set(1.0f,lbl_806DBEC4,10);
   self->color.p->Set(255,255,1);
   if (!self->burst) self->burst = new ItemUseBurst(self->context);
   self->state=2;
  }
 }
}

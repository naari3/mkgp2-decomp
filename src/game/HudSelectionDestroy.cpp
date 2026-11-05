#include "game/HudSelectionPrivate.h"
extern "C" HudSelection *fn_80245B10(HudSelection *self, short flag) {
 if (self) {
  self->vptr=lbl_804EE83C;
  if(self->text) MemoryManager_TimedFree(self->text);
  fn_801F8E54(); self->context=0;
  self->alpha.~VHolder<FlowFaderF>();
  self->position.~VHolder<FlowFaderF>();
  self->HudSelectionBase::~HudSelectionBase();
  if(flag>0) MemoryManager_TimedFree(self);
 }
 return self;
}

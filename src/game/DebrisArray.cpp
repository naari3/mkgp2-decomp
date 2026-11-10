/* Narrow layout from target access and existing DrawForward ABI. */
#include "game/types/size_t.h"
#include "game/types/DebrisVec.h"
#include "game/types/DebrisResponder.h"
#include "game/types/DebrisArray.h"
void *operator new(size_t);
void operator delete(void *);
extern "C" {
extern void *lbl_806D10AC;
extern const float lbl_806D5034;
void DebrisArray_DrawForward(DebrisArray*);
void clDrawMan_AddSorted_DepthRange(void*,void (*)(DebrisArray*),DebrisArray*,float,float,float,float);
unsigned char clItemBoxResponder_TickDebris(DebrisResponder*);
void clItemBoxResponder_DebrisArray_Dtor(DebrisResponder*,int);
void DrawEffect_Free(DebrisArray*);
void DebrisArray_DrawCb(DebrisArray*);
void DebrisArray_Update(DebrisArray *self) {
 switch(self->state) {
 case 0:
  self->responder=new DebrisResponder(self->position,self->velocity);
  self->draw=DebrisArray_DrawCb;
  self->drawSelf=self;
  ++self->state;
 case 1:
  if(clItemBoxResponder_TickDebris(self->responder)==1) {
   clItemBoxResponder_DebrisArray_Dtor(self->responder,1);
   DrawEffect_Free(self);
   return;
  }
 }
 if(self->cleanup) {
  clItemBoxResponder_DebrisArray_Dtor(self->responder,1);
  DrawEffect_Free(self);
 }
}
}

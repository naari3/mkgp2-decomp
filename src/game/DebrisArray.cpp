/* Narrow layout from target access and existing DrawForward ABI. */
struct DebrisVec { float x,y,z; };
struct DebrisResponder { void *particles; DebrisResponder(DebrisVec, DebrisVec); };
struct DebrisArray {
 char pad00[0x78]; void (*draw)(DebrisArray*); DebrisArray *drawSelf;
 char pad80[0xC]; DebrisVec position; char pad98[0xC]; DebrisVec velocity;
 float scale; signed char state; char padB5[0x14]; signed char cleanup;
 char padCA[2]; DebrisResponder *responder;
};
void *operator new(unsigned long);
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

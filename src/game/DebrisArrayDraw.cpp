/* Narrow layout from target access and existing DrawForward ABI. */
#include "game/types/DebrisVec.h"
#include "game/types/DebrisResponder.h"
#include "game/types/DebrisArray.h"
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
static inline void *GetDrawManager() {
 void *p;
 if ((p = lbl_806D10AC) == 0) p = 0;
 return p;
}
void DebrisArray_DrawCb(DebrisArray *self) {
 clDrawMan_AddSorted_DepthRange(GetDrawManager(),DebrisArray_DrawForward,self,self->position.x,self->position.y,self->position.z,lbl_806D5034);
}
}

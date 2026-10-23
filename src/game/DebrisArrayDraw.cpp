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
static inline void *GetDrawManager() {
 if(!lbl_806D10AC) return 0;
 return lbl_806D10AC;
}
void DebrisArray_DrawCb(DebrisArray *self) {
 clDrawMan_AddSorted_DepthRange(GetDrawManager(),DebrisArray_DrawForward,self,self->position.x,self->position.y,self->position.z,lbl_806D5034);
}
}

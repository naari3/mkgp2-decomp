/* Target-observed narrow layout; live Ghidra type service unavailable. */
struct TrailVec { float x,y,z; };
struct TrailMatrix { float m[16]; };
struct TrailEffect {
 char pad00[0x14]; char slot[0x14]; unsigned char visible; char pad29[3]; float alpha;
 char pad30[0x18]; float matrix[12]; char pad78[0x14]; TrailVec position;
 float pitch; float yaw; float roll; char padA4[12]; float scale; signed char state;
 char padB5[0x67]; void *kart; TrailVec localPosition; char pad12C[0x24]; float phase;
 char pad154[0x2C]; unsigned timer0,timer1,timer2,timer3;
};
extern "C" {
extern const float lbl_806D5790,lbl_806D5770,lbl_806D578C,lbl_806D580C,lbl_806D5810,lbl_806D57B8,lbl_806D5814,lbl_806D5818;
void *KartDriver_GetKartRootMtx(void *);
void Mtx_TransposeToMtx44(TrailMatrix *,const void *);
void VfxSlot_BindResource(void *,int);
void VfxSlot_SetMatrixSourceEnabled(void *,int);
void Mtx44_Inverse_GaussJordan(TrailMatrix *,const TrailMatrix *);
#ifdef __MWERKS__
void Mtx44_TransformVec3(TrailVec *,const TrailMatrix *,TrailVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_TransformVec3(TrailVec *, const TrailMatrix *, TrailVec *);
static inline void Mtx44_TransformVec3_ByValue(TrailVec *a0, const TrailMatrix *a1, TrailVec a2) { Mtx44_TransformVec3(a0, a1, &a2); }
#define Mtx44_TransformVec3 Mtx44_TransformVec3_ByValue
#endif
void DrawEffect_Free(void *);
#ifdef __MWERKS__
signed char ItemObject_GetGroundTypeAt(TrailVec,float *,int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(TrailVec *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(TrailVec a0, float *a1, int a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
#ifdef __MWERKS__
float Item_ProbeForwardGroundPitch(TrailVec,float,float,float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeForwardGroundPitch(TrailVec *, float, float, float);
static inline float Item_ProbeForwardGroundPitch_ByValue(TrailVec a0, float a1, float a2, float a3) { return Item_ProbeForwardGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeForwardGroundPitch Item_ProbeForwardGroundPitch_ByValue
#endif
#ifdef __MWERKS__
float Item_ProbeLateralGroundPitch(TrailVec,float,float,float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeLateralGroundPitch(TrailVec *, float, float, float);
static inline float Item_ProbeLateralGroundPitch_ByValue(TrailVec a0, float a1, float a2, float a3) { return Item_ProbeLateralGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeLateralGroundPitch Item_ProbeLateralGroundPitch_ByValue
#endif
void Matrix4_Identity(TrailMatrix *);
void Matrix4_PreMultiplyRotX(TrailMatrix *,const TrailMatrix *,float);
void Matrix4_PreMultiplyRotZ(TrailMatrix *,const TrailMatrix *,float);
void Mtx44_Scale_Uniform(TrailMatrix *,const TrailMatrix *,float);
#ifdef __MWERKS__
void Mtx44_Translate(TrailMatrix *,const TrailMatrix *,TrailVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Mtx44_Translate(TrailMatrix *, const TrailMatrix *, TrailVec *);
static inline void Mtx44_Translate_ByValue(TrailMatrix *a0, const TrailMatrix *a1, TrailVec a2) { Mtx44_Translate(a0, a1, &a2); }
#define Mtx44_Translate Mtx44_Translate_ByValue
#endif
void DbgScene_CopyMatrix3x4Transpose(float *,const TrailMatrix *);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void Effect_KartTrailRes3A_Update(TrailEffect *effect) {
 TrailMatrix root;
 Mtx_TransposeToMtx44(&root,KartDriver_GetKartRootMtx(effect->kart));
 switch(effect->state) {
 case 0: {
  TrailMatrix inverse;
  VfxSlot_BindResource(effect->slot,0x3A);
  VfxSlot_SetMatrixSourceEnabled(effect->slot,1);
  Mtx44_Inverse_GaussJordan(&inverse,&root);
  Mtx44_TransformVec3(&effect->localPosition,&inverse,effect->position);
  effect->alpha=lbl_806D5790;
  effect->phase=lbl_806D5770;
  effect->timer0=10;
  ++effect->state;
  break;
 }
 case 1: break;
 }
 if(effect->timer0==0) {
  effect->alpha-=lbl_806D578C;
  if(effect->alpha<lbl_806D5770) {DrawEffect_Free(effect);return;}
 }
 Mtx44_TransformVec3(&effect->position,&root,effect->localPosition);
 if(ItemObject_GetGroundTypeAt(effect->position,&effect->position.y,0)) {
  effect->pitch=Item_ProbeForwardGroundPitch(effect->position,lbl_806D5770,lbl_806D580C,lbl_806D5770);
  effect->roll=Item_ProbeLateralGroundPitch(effect->position,lbl_806D5770,lbl_806D580C,lbl_806D5770);
  effect->position.y+=lbl_806D5810;
 }
 effect->phase+=lbl_806D57B8;
 effect->scale=lbl_806D5814*effect->phase;
 TrailMatrix matrix;
 Matrix4_Identity(&matrix);
 Matrix4_PreMultiplyRotX(&matrix,&matrix,lbl_806D5818);
 Mtx44_Scale_Uniform(&matrix,&matrix,effect->scale);
 Matrix4_PreMultiplyRotZ(&matrix,&matrix,effect->roll);
 Matrix4_PreMultiplyRotX(&matrix,&matrix,effect->pitch);
 Mtx44_Translate(&matrix,&matrix,effect->position);
 DbgScene_CopyMatrix3x4Transpose(effect->matrix,&matrix);
 if(FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible=0;
 else effect->visible=1;
 if(effect->timer0) --effect->timer0;
 if(effect->timer1) --effect->timer1;
 if(effect->timer2) --effect->timer2;
 if(effect->timer3) --effect->timer3;
}
}

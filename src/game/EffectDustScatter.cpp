/* Target-observed field views; live Ghidra types unavailable. */
struct DustScatterVec { float x,y,z; };
struct DustScatterCamera { float world[16], view[16]; DustScatterVec position; };
struct DustScatterEffect {
 char pad00[0x14]; char slot[0x14]; unsigned char visible; char pad29[0x63];
 DustScatterVec position, rotation, velocity;
 float scale; signed char state; char padB5[0x67];
 void *kart; DustScatterVec origin, displacement, previousKart;
 char pad144[0xC]; float initialScale, fade;
 char pad158[0x28]; unsigned int timers[4]; signed char side;
};
extern "C" {
extern DustScatterCamera lbl_805DF3D0;
extern const float lbl_806D5770,lbl_806D5774,lbl_806D5778,lbl_806D577C,lbl_806D5780,lbl_806D5784,lbl_806D5788,lbl_806D578C,lbl_806D5790,lbl_806D5794,lbl_806D5798,lbl_806D579C,lbl_806D57A0;
void Vec3_Add_DestFirst(DustScatterVec*,const DustScatterVec*,const DustScatterVec*);
void Vec3_Subtract_DestFirst(DustScatterVec*,const DustScatterVec*,const DustScatterVec*);
void Vec3_Copy(DustScatterVec*,const DustScatterVec*);
void Mtx44_TransformVec3(DustScatterVec*,const float*,DustScatterVec);
void GetSpawnPosition(DustScatterVec*,float,float,float);
float Rand_RangeFloat(float,float);
int Rand_RangeIntMax(int);
void Vec2_RotateZ(DustScatterVec*,const DustScatterVec*,float);
void VfxSlot_BindResourceEx(void*,int,int);
const float *KartDriver_GetKartRootMtx(void*);
void Mtx44_GetTranslation_RowMajor(DustScatterVec*,const float*);
void DrawEffect_Free(DustScatterEffect*);
double atan2(double,double);
float BuildOrientationFromYaw(float);
void VfxSlot_SetPositionFromVec(void*,DustScatterVec);
void VfxSlot_SetRotationZ(void*,float);
void VfxSlot_SetScaleUniform(void*,float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void*);
void Effect_DustScatter_Update(DustScatterEffect *effect) {
 switch(effect->state) {
 case 0: {
  DustScatterVec cameraPoint;
  Vec3_Add_DestFirst(&cameraPoint,&lbl_805DF3D0.position,&effect->velocity);
  Mtx44_TransformVec3(&cameraPoint,lbl_805DF3D0.view,cameraPoint);
  if(lbl_806D5770 < cameraPoint.x) effect->side=0; else effect->side=1;
  float speed=Rand_RangeFloat(lbl_806D5774,lbl_806D5778);
  GetSpawnPosition(&effect->velocity,speed,lbl_806D5770,lbl_806D5770);
  Vec2_RotateZ(&effect->velocity,&effect->velocity,lbl_806D577C*Rand_RangeFloat(lbl_806D5780,lbl_806D5784));
  if(effect->side) effect->velocity.x *= lbl_806D5788;
  Vec3_Copy(&effect->origin,&effect->position);
  GetSpawnPosition(&effect->displacement,lbl_806D5770,lbl_806D5770,lbl_806D5770);
  int even = ((Rand_RangeIntMax(15)%2) == 0) ? 1 : 0;
  if(even) {
   if(!effect->side) VfxSlot_BindResourceEx(effect->slot,0x50,0);
   else VfxSlot_BindResourceEx(effect->slot,0x51,0);
  } else {
   if(!effect->side) VfxSlot_BindResourceEx(effect->slot,0x52,0);
   else VfxSlot_BindResourceEx(effect->slot,0x53,0);
  }
  effect->initialScale=lbl_806D578C*Rand_RangeFloat(lbl_806D5774,lbl_806D5778);
  effect->fade=lbl_806D5790;
  effect->timers[0]=30;
  if(effect->kart) Mtx44_GetTranslation_RowMajor(&effect->previousKart,KartDriver_GetKartRootMtx(effect->kart));
  ++effect->state;
  break;
 }
 case 1: break;
 }
 if(!effect->timers[0]) {
  effect->fade -= lbl_806D5794;
  if(effect->fade < lbl_806D5770) { DrawEffect_Free(effect); return; }
 }
 effect->velocity.y += lbl_806D5798;
 effect->velocity.x *= lbl_806D579C;
 effect->rotation.z=atan2(effect->velocity.x,effect->velocity.y);
 if(effect->side) effect->rotation.z=BuildOrientationFromYaw(lbl_806D57A0+effect->rotation.z);
 else effect->rotation.z=BuildOrientationFromYaw(effect->rotation.z-lbl_806D57A0);
 Vec3_Add_DestFirst(&effect->displacement,&effect->displacement,&effect->velocity);
 if(effect->kart) {
  DustScatterVec kartPosition, delta;
  Mtx44_GetTranslation_RowMajor(&kartPosition,KartDriver_GetKartRootMtx(effect->kart));
  Vec3_Subtract_DestFirst(&delta,&kartPosition,&effect->previousKart);
  Vec3_Add_DestFirst(&effect->origin,&effect->origin,&delta);
  Vec3_Copy(&effect->previousKart,&kartPosition);
 }
 DustScatterVec worldDelta;
 Mtx44_TransformVec3(&worldDelta,lbl_805DF3D0.world,effect->displacement);
 Vec3_Subtract_DestFirst(&worldDelta,&worldDelta,&lbl_805DF3D0.position);
 Vec3_Add_DestFirst(&effect->position,&effect->origin,&worldDelta);
 effect->scale=effect->initialScale*effect->fade;
 VfxSlot_SetPositionFromVec(effect->slot,effect->position);
 VfxSlot_SetRotationZ(effect->slot,effect->rotation.z);
 VfxSlot_SetScaleUniform(effect->slot,effect->scale);
 if(effect->timers[0]) --effect->timers[0];
 if(effect->timers[1]) --effect->timers[1];
 if(effect->timers[2]) --effect->timers[2];
 if(effect->timers[3]) --effect->timers[3];
 if(FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible=0;
 else effect->visible=1;
}
}

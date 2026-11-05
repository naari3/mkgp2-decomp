/* Native reconstruction. Matrix-loop code generation and FP register homes
 * remain NonMatching; the function size and simple EH are exact. */
#include "game/PhysicsCollisionPrivate.h"

#include "game/SmoothingPrivate.h"
extern "C" {
extern float lbl_806DA448, lbl_806DA44C;
extern int g_roundIndex, g_cupId;
unsigned char IsRaceStarted();
void KartPhysics_GroundedMovement(void *);
void fn_801EE36C(void *);
float LUT_Cosine(float);
float LUT_Sine(float);
void KartPhysics_ApplyCollisionForce(void *);
void PhysicsState_WallCollisionCheck(void *);
unsigned char PhysicsState_KartCollisionCheck(void *);
void fn_801ED798(void *, void *, void *, float);
void *GetEnemyParam();
float *GetKartTuningEntry(void *,int,int,int);
void PathFollower_Update(void *);
}
static inline float smoothingSqrt(float v) {
    if(v>lbl_806DA42C) {
        double e=__frsqrte(v);
        e=lbl_806DA458*e*(lbl_806DA460-v*(e*e));
        e=lbl_806DA458*e*(lbl_806DA460-v*(e*e));
        e=lbl_806DA458*e*(lbl_806DA460-v*(e*e));
        volatile float result=v*e;
        return result;
    }
    return v;
}
extern "C" void KartPhysics_UpdateSmoothing(SmoothingState *self) {
    if(!self->path) return;
    if(!IsRaceStarted()) return;
    self->velocityX=self->positionX-self->previousX;
    self->velocityY=self->positionY-self->previousY;
    self->velocityZ=self->positionZ-self->previousZ;
    self->previousX=self->positionX;
    self->previousY=self->positionY;
    self->previousZ=self->positionZ;
    if(!self->airborne) {
        KartPhysics_GroundedMovement(self);
        fn_801EE36C(self);
    } else {
        float speed=self->speed;
        speed/=lbl_806DA44C;
        speed/=lbl_806DA44C;
        speed/=lbl_806DA44C;
        if(speed<lbl_806DA450) speed=lbl_806DA450;
        float length=smoothingSqrt(speed*speed+self->velocityY*self->velocityY);
        float delta=length-speed;
        if(lbl_806DA42C<speed) {
            speed-=delta;
            if(speed<lbl_806DA42C) speed=lbl_806DA42C;
        }
        self->positionX+=speed*LUT_Cosine(self->yaw);
        self->positionZ+=speed*LUT_Sine(self->yaw);
    }
    KartPhysics_ApplyCollisionForce(self);
    self->world.identity();
    PhysicsState_WallCollisionCheck(self);
    if(PhysicsState_KartCollisionCheck(self)==1) PhysicsState_WallCollisionCheck(self);
    fn_801ED798(self,&self->positionX,&self->world,self->matrixYaw);
    SmoothingMatrix scale;
    scale.identity();
    float factor=self->scale;
    scale.m[0]=factor;
    scale.m[5]=factor;
    scale.m[10]=factor;
    scale*=self->world;
    self->world=scale;
    float yaw;
    float pitch=self->targetPitch;
    yaw=self->targetYaw;
    int round=g_roundIndex;
    int cup=g_cupId;
    float *tuning=GetKartTuningEntry(GetEnemyParam(),cup,round,self->kartId);
    float step=lbl_806DA444*(lbl_806DA448*tuning[1]);
    float delta=yaw-self->smoothYaw;
    if(step<delta) self->smoothYaw+=step;
    else if(delta < -step) self->smoothYaw-=step;
    else self->smoothYaw=yaw;
    self->targetYaw=yaw;
    float pitchDelta=pitch-self->smoothPitch;
    if(step<pitchDelta) self->smoothPitch+=step;
    else if(pitchDelta < -step) self->smoothPitch-=step;
    else self->smoothPitch=pitch;
    self->targetPitch=pitch;
    PathFollower_Update(self->path);
}

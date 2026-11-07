/* Native reconstruction. The airborne division and scale initialization retain
 * FP register/scheduling differences; matrix multiply and simple EH are exact. */
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
static inline void smoothingIdentity(SmoothingMatrix &matrix) {
    for(int i=0;i<16;i++) matrix.m[i]=0.0f;
    matrix.m[0]=matrix.m[5]=matrix.m[10]=matrix.m[15]=1.0f;
}
static inline void smoothingMultiply(SmoothingMatrix &a, const SmoothingMatrix &b) {
    SmoothingMatrix out;
    float *result=out.m;
    int n=0;
    for(int i=0;i<4;i++) {
        for(int j=0;j<4;j++) {
            float sum;
            float left0, right0, left1, right1, left2, right2, left3, right3;
            left0=a.m[i*4]; right0=b.m[j]; sum=left0*right0;
            left1=a.m[i*4+1]; right1=b.m[4+j]; sum+=left1*right1;
            left2=a.m[i*4+2]; right2=b.m[8+j]; sum+=left2*right2;
            left3=a.m[i*4+3]; right3=b.m[12+j]; sum+=left3*right3;
            result[n+j]=sum;
        }
        n+=4;
    }
    for(int k=0;k<16;k++) a.m[k]=out.m[k];
}
static inline float smoothingSqrt(float v) {
    if(v>lbl_806DA42C) {
        double e=__frsqrte(v);
        e=0.5*e*(3.0-v*(e*e));
        e=0.5*e*(3.0-v*(e*e));
        e=0.5*e*(3.0-v*(e*e));
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
        float divided=self->speed;
        divided/=lbl_806DA44C;
        divided/=lbl_806DA44C;
        float speed=divided/lbl_806DA44C;
        if(speed<1.0f) speed=1.0f;
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
    float factor;
    SmoothingMatrix scale;
    smoothingIdentity(scale);
    factor=self->scale;
    scale.m[0]=factor;
    scale.m[5]=factor;
    scale.m[10]=factor;
    smoothingMultiply(scale,self->world);
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

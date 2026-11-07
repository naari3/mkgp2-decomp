/* NonMatching: projection reload and cross/quaternion FPR scheduling differ. */
#include "game/ItemEffectImpactArmPrivate.h"

// Scalar length arguments preserve the matrix-row evaluation boundary.
static inline float ArmLengthSquared(float x, float y, float z) {
    float yy=y*y;
    float xx=x*x;
    float zz=z*z;
    return zz+(xx+yy);
}
static inline void ArmNormalizeCopy(C7Vec* v, const C7Vec* src) {
    float squared=ArmLengthSquared(src->x,src->y,src->z);
    *v=*src;
    float length=Root(squared);
    if(length<=lbl_806D27F8) {v->z=lbl_806D27F8;v->y=lbl_806D27F8;v->x=lbl_806D27F8;}
    else {float inv=lbl_806D27FC/length;v->x*=inv;v->y*=inv;v->z*=inv;}
}

extern "C" void ItemEffectImpact_TryArmInit(ImpactArmState* __restrict self, C7Vec* __restrict velocity, ImpactArmMatrix* __restrict pose, int timer) {
    self->Reset();
    self->pos=*velocity;
    for(int i=0;i<16;i++) ((float*)&self->start)[i]=((float*)pose)[i];
    for(int i=0;i<16;i++) ((float*)&self->current)[i]=((float*)pose)[i];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) self->rotation.m[i][j]=lbl_806D27F8;
    self->rotation.m[3][3]=lbl_806D27FC; self->rotation.m[2][2]=lbl_806D27FC; self->rotation.m[1][1]=lbl_806D27FC; self->rotation.m[0][0]=lbl_806D27FC;
    self->timer=timer;
    C7Vec up;
    ArmNormalizeCopy(&up,(C7Vec*)&self->start.m[1][0]);
    #pragma fp_contract off
    float dx=up.x*self->pos.x, dy=up.y*self->pos.y, dz=up.z*self->pos.z;
    float dot=dz+(dx+dy);
    #pragma fp_contract reset
    up.x*=dot; up.y*=dot; up.z*=dot;
    self->pos.x-=up.x; self->pos.y-=up.y; self->pos.z-=up.z;
    C7Vec v;
    NormalizeCopy(&v,&self->pos);
    C7Vec axis=up;
    axis.x=v.y*up.z-v.z*up.y;
    axis.y=v.z*up.x-v.x*up.z;
    axis.z=v.x*up.y-v.y*up.x;
    float length2=axis.z*axis.z+(axis.x*axis.x+axis.y*axis.y);
    if(length2>lbl_806D27F8) { Normalize(&axis); self->axis=axis; }
    else { float z=self->start.m[0][2], y=self->start.m[0][1], x=self->start.m[0][0]; self->axis.x=x; self->axis.y=y; self->axis.z=z; }
    ImpactArmQuat q;
    q.w=lbl_806D27F8; q.z=lbl_806D27F8; q.y=lbl_806D27F8; q.x=lbl_806D27F8;
    float ax,ay,az;
    az=self->axis.z; ay=self->axis.y; ax=self->axis.x;
    float sine=(float)sin(lbl_806D2828);
    q.x=ax*sine; q.y=ay*sine; q.z=az*sine;
    q.w=(float)cos(lbl_806D2828);
    float x=q.x,y=q.y,z=q.z,w=q.w;
    float two=lbl_806D281C, one=lbl_806D27FC;
    self->rotation.m[0][0]=one-two*(y*y+z*z);
    self->rotation.m[1][0]=two*(x*y-w*z);
    self->rotation.m[2][0]=two*(x*z+w*y);
    self->rotation.m[0][1]=two*(x*y+w*z);
    self->rotation.m[1][1]=one-two*(x*x+z*z);
    self->rotation.m[2][1]=two*(y*z-w*x);
    self->rotation.m[0][2]=two*(x*z-w*y);
    self->rotation.m[1][2]=two*(y*z+w*x);
    self->rotation.m[2][2]=one-two*(x*x+y*y);
    self->elapsed=lbl_806D27F8;
    self->flags=0;
    self->pos.x*=lbl_806D2824;
    self->pos.y*=lbl_806D2824;
    self->pos.z*=lbl_806D2824;
}

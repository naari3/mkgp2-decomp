/* NonMatching (98.05): quaternion-to-matrix block colours 4 saved FPRs, target 5 (x/z/w + yy/xx saved). */
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

// Axis normalization uses zero consistently for the degenerate-vector checks.
static inline float ArmAxisRoot(float x) {
    volatile float y;
    if(x>0.0f) {
        double guess=__frsqrte(x);
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        y=(float)(x*guess); return y;
    }
    return x;
}
static inline void ArmAxisNormalize(C7Vec* v) {
    float length=ArmAxisRoot(v->z*v->z+(v->x*v->x+v->y*v->y));
    if(length<=0.0f) { v->z=0.0f; v->y=0.0f; v->x=0.0f; }
    else { float inv=lbl_806D27FC/length; v->x*=inv; v->y*=inv; v->z*=inv; }
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
    const C7Vec* p=&self->pos;
    float dx=up.x*p->x, dy=up.y*p->y, dz=up.z*p->z;
    float dot=dz+(dx+dy);
    #pragma fp_contract reset
    up.x*=dot; up.y*=dot; up.z*=dot;
    self->pos.x-=up.x; self->pos.y-=up.y; self->pos.z-=up.z;
    C7Vec v=self->pos;
    Normalize(&v);
    C7Vec axis=up;
    axis.y=v.z*up.x-v.x*up.z;
    axis.z=v.x*up.y-v.y*up.x;
    axis.x=v.y*up.z-v.z*up.y;
    float length2=axis.z*axis.z+(axis.x*axis.x+axis.y*axis.y);
    if(length2>0.0f) { ArmAxisNormalize(&axis); self->axis=axis; }
    else { float x=self->start.m[0][0], y=self->start.m[0][1], z=self->start.m[0][2]; self->axis.x=x; self->axis.y=y; self->axis.z=z; }
    ImpactArmQuat q;
    q.w=lbl_806D27F8; q.z=lbl_806D27F8; q.y=lbl_806D27F8; q.x=lbl_806D27F8;
    float ay,ax,az;
    az=self->axis.z; ay=self->axis.y; ax=self->axis.x;
    float sine=(float)sin(lbl_806D2828);
    q.x=ax*sine; q.y=ay*sine; q.z=az*sine;
    q.w=(float)cos(lbl_806D2828);
    float x=q.x,y=q.y,z=q.z,w=q.w;
    float yz=y*z, wx=w*x, wy=w*y, xz=x*z, xy=x*y, xx=x*x, wz=w*z, yy=y*y, zz=z*z;
    self->rotation.m[0][0]=lbl_806D27FC-lbl_806D281C*(yy+zz);
    self->rotation.m[1][0]=lbl_806D281C*(xy-wz);
    self->rotation.m[2][0]=lbl_806D281C*(xz+wy);
    self->rotation.m[0][1]=lbl_806D281C*(xy+wz);
    self->rotation.m[1][1]=lbl_806D27FC-lbl_806D281C*(xx+zz);
    self->rotation.m[2][1]=lbl_806D281C*(yz-wx);
    self->rotation.m[0][2]=lbl_806D281C*(xz-wy);
    self->rotation.m[1][2]=lbl_806D281C*(yz+wx);
    self->rotation.m[2][2]=lbl_806D27FC-lbl_806D281C*(xx+yy);
    self->elapsed=lbl_806D27F8;
    self->flags=0;
    self->pos.x*=lbl_806D2824;
    self->pos.y*=lbl_806D2824;
    self->pos.z*=lbl_806D2824;
}

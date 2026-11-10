/* NonMatching (99.8): instruction sequence and frame match. Left (24 diff lines): in the cross product up.y and v.z sit in f8/f6 (target f6/f8), and ay/ax of the axis-angle step sit in f28/f27 (target f31/f30). Attempts in docs/gave_up.md. */
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
        guess=0.5*guess*(3.0-x*(guess*guess));
        guess=0.5*guess*(3.0-x*(guess*guess));
        guess=0.5*guess*(3.0-x*(guess*guess));
        y=(float)(x*guess); return y;
    }
    return x;
}
static inline void ArmAxisNormalize(C7Vec* v) {
    float length=ArmAxisRoot(v->z*v->z+(v->x*v->x+v->y*v->y));
    if(length<=0.0f) { v->z=0.0f; v->y=0.0f; v->x=0.0f; }
    else { float inv=lbl_806D27FC/length; v->x*=inv; v->y*=inv; v->z*=inv; }
}

static inline void ArmCross(C7Vec* a, const C7Vec* o, const C7Vec* u) {
    float ty, tz, tx;
    ty=o->z*u->x-o->x*u->z; tz=o->x*u->y-o->y*u->x; tx=o->y*u->z-o->z*u->y;
    a->x=tx; a->y=ty; a->z=tz;
}
static inline void ArmSet(C7Vec* v,float x,float y,float z){v->x=x;v->y=y;v->z=z;}
static inline float ArmHalfCos() { return (float)cos(lbl_806D2828); }
static inline void ArmAxisAngle(ImpactArmQuat* q, float x, float y, float z) {
    float sine=(float)sin(lbl_806D2828);
    q->x=x*sine; q->y=y*sine; q->z=z*sine;
}
static inline void ArmQuatMatrix(ImpactArmMatrix* m, const ImpactArmQuat* q) {
    float xx=q->x*q->x;
    float yy=q->y*q->y;
    float zz=q->z*q->z;
    float xy=q->x*q->y;
    float xz=q->x*q->z;
    float yz=q->y*q->z;
    float wx=q->w*q->x;
    float wy=q->w*q->y;
    float wz=q->w*q->z;
    m->m[0][0]=lbl_806D27FC-lbl_806D281C*(yy+zz);
    m->m[1][0]=lbl_806D281C*(xy-wz);
    m->m[2][0]=lbl_806D281C*(xz+wy);
    m->m[0][1]=lbl_806D281C*(xy+wz);
    m->m[1][1]=lbl_806D27FC-lbl_806D281C*(xx+zz);
    m->m[2][1]=lbl_806D281C*(yz-wx);
    m->m[0][2]=lbl_806D281C*(xz-wy);
    m->m[1][2]=lbl_806D281C*(yz+wx);
    m->m[2][2]=lbl_806D27FC-lbl_806D281C*(xx+yy);
}
struct ArmVec : C7Vec { ArmVec(float ax, float ay, float az) { x=ax; z=az; y=ay; } };
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
    ArmVec axis(up.x, up.y, up.z);
    ArmCross(&axis,&v,&up);
    float length2=axis.z*axis.z+(axis.x*axis.x+axis.y*axis.y);
    if(length2>0.0f) { ArmAxisNormalize(&axis); self->axis=axis; }
    else ArmSet(&self->axis,self->start.m[0][0],self->start.m[0][1],self->start.m[0][2]);
    ImpactArmQuat q;
    q.w=lbl_806D27F8; q.z=lbl_806D27F8; q.y=lbl_806D27F8; q.x=lbl_806D27F8;
    float ax,ay,az;
    az=self->axis.z; ay=self->axis.y; ax=self->axis.x;
    float sine=(float)sin(lbl_806D2828);
    q.x=ax*sine; q.y=ay*sine; q.z=az*sine;
    q.w=ArmHalfCos();
    ArmQuatMatrix(&self->rotation,&q);
    self->elapsed=lbl_806D27F8;
    self->flags=0;
    self->pos.x*=lbl_806D2824;
    self->pos.y*=lbl_806D2824;
    self->pos.z*=lbl_806D2824;
}

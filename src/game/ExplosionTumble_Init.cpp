/* NonMatching: 89.013824% text. Retained after three structural approaches.
 * Scalar matrix copies and normalized-copy helpers recover the target shape;
 * scheduling, FPR allocation and primary size still differ. */
#include "game/C7ItemCtorPrivate.h"

extern "C" {
extern const float lbl_806D27F8, lbl_806D27FC, lbl_806D2818, lbl_806D281C;
extern const double lbl_806D2808, lbl_806D2810;
extern double sin(double);
extern double cos(double);
}
struct C7Matrix { float m[4][4]; };
struct C7Tumble {
    virtual void Reset();
    void* owner;
    C7Vec pos;
    C7Matrix start, current, rotation;
    C7Vec axis;
};
struct C7Quat { float x,y,z,w; ~C7Quat() {} };
static inline float Root(float x) {
    volatile float y;
    if(x>lbl_806D27F8) {
        double guess=__frsqrte(x);
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        y=(float)(x*guess); return y;
    }
    return x;
}
static inline void Normalize(C7Vec* v) {
    float length=Root(v->z*v->z+(v->x*v->x+v->y*v->y));
    if(length<=lbl_806D27F8) { v->z=lbl_806D27F8; v->y=lbl_806D27F8; v->x=lbl_806D27F8; }
    else { float inv=lbl_806D27FC/length; v->x*=inv; v->y*=inv; v->z*=inv; }
}
static inline void NormalizeCopy(C7Vec* v, const C7Vec* src) {
    float x=src->z*src->z+(src->x*src->x+src->y*src->y);
    *v=*src;
    float length=Root(x);
    if(length<=lbl_806D27F8) {v->z=lbl_806D27F8;v->y=lbl_806D27F8;v->x=lbl_806D27F8;}
    else {float inv=lbl_806D27FC/length;v->x*=inv;v->y*=inv;v->z*=inv;}
}
extern "C" void ExplosionTumble_Init(C7Tumble* __restrict self, C7Vec* __restrict position, C7Vec* __restrict velocity, C7Matrix* __restrict pose) {
    self->Reset();
    self->pos=*position;
    for(int i=0;i<16;i++) ((float*)&self->start)[i]=((float*)pose)[i];
    for(int i=0;i<16;i++) ((float*)&self->current)[i]=((float*)pose)[i];
    for(int i=0;i<4;i++) for(int j=0;j<4;j++) self->rotation.m[i][j]=lbl_806D27F8;
    self->rotation.m[3][3]=lbl_806D27FC; self->rotation.m[2][2]=lbl_806D27FC; self->rotation.m[1][1]=lbl_806D27FC; self->rotation.m[0][0]=lbl_806D27FC;
    C7Vec v;
    NormalizeCopy(&v,velocity);
    C7Vec up;
    NormalizeCopy(&up,(C7Vec*)&self->start.m[1][0]);
    float dot=up.z*v.z+(up.x*v.x+up.y*v.y);
    up.x*=dot; up.y*=dot; up.z*=dot;
    v.x-=up.x; v.y-=up.y; v.z-=up.z;
    Normalize(&v);
    C7Vec axis=v;
    axis.x=up.y*v.z-up.z*v.y;
    axis.y=up.z*v.x-up.x*v.z;
    axis.z=up.x*v.y-up.y*v.x;
    float length2=axis.z*axis.z+(axis.x*axis.x+axis.y*axis.y);
    if(length2>lbl_806D27F8) { Normalize(&axis); self->axis=axis; }
    else { self->axis.x=self->start.m[0][0]; self->axis.y=self->start.m[0][1]; self->axis.z=self->start.m[0][2]; }
    C7Quat q;
    q.w=lbl_806D27F8; q.z=lbl_806D27F8; q.y=lbl_806D27F8; q.x=lbl_806D27F8;
    float ax=self->axis.x, ay=self->axis.y, az=self->axis.z;
    float sine=(float)sin(lbl_806D2818);
    q.x=ax*sine; q.y=ay*sine; q.z=az*sine;
    q.w=(float)cos(lbl_806D2818);
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
}

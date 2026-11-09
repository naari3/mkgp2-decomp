static inline float mul__lv(float a, float b) { return a * b; }
/* NonMatching: 94.86% text, exact 1736-byte primary size.
 * In-place roots and rounded quaternion products preserve target arithmetic.
 * Vector loads, projection reloads and FPR allocation still differ. */
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
static inline void Root(float& x) {
    volatile float y;
    if(x>lbl_806D27F8) {
        double guess=__frsqrte(x);
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        guess=lbl_806D2808*guess*(lbl_806D2810-x*(guess*guess));
        y=(float)(x*guess); x=y;
    }
}
static inline void Normalize(C7Vec* v) {
    float length=v->z*v->z+(v->x*v->x+v->y*v->y);
    Root(length);
    if(length<=lbl_806D27F8) { v->z=lbl_806D27F8; v->y=lbl_806D27F8; v->x=lbl_806D27F8; }
    else { float inv=lbl_806D27FC/length; v->x*=inv; v->y*=inv; v->z*=inv; }
}
static inline float LengthSquared(float x, float y, float z) {
    // Preserve the rounded component products before summing X + Y, then Z.
    float yy=y*y;
    float xx=x*x;
    float zz=z*z;
    return zz+(xx+yy);
}
static inline void NormalizeCopy(C7Vec* v, const C7Vec* src) {
    float length=LengthSquared(src->x,src->y,src->z);
    *v=*src;
    Root(length);
    if(length<=lbl_806D27F8) {v->z=lbl_806D27F8;v->y=lbl_806D27F8;v->x=lbl_806D27F8;}
    else {float inv=lbl_806D27FC/length;v->x*=inv;v->y*=inv;v->z*=inv;}
}
static inline float Dot(const C7Vec* a, const C7Vec* b) {
    float x=a->x*b->x, y=a->y*b->y, z=a->z*b->z;
    return z+(x+y);
}
static inline void Scale(C7Vec* a, float scale) {
    a->x*=scale; a->y*=scale; a->z*=scale;
}
static inline void Subtract(C7Vec* a, const C7Vec* b) {
    a->x-=b->x; a->y-=b->y; a->z-=b->z;
}
static inline void AxisAngle(C7Quat* q, float x, float y, float z) {
    float sine=(float)sin(lbl_806D2818);
    q->x=x*sine; q->y=y*sine; q->z=z*sine;
    q->w=(float)cos(lbl_806D2818);
}
static inline void QuaternionMatrix(C7Matrix* m, const C7Quat* q) {
    // Round the component products before combining matrix entries.
    float yy=q->y*q->y, zz=q->z*q->z;
    float xy=q->x*q->y, wz=q->w*q->z;
    float xz=q->x*q->z, wy=q->w*q->y;
    float xx=q->x*q->x, yz=q->y*q->z, wx=q->w*q->x;
    float two=lbl_806D281C, one=lbl_806D27FC;
    m->m[0][0]=one-two*(yy+zz);
    m->m[1][0]=two*(xy-wz);
    m->m[2][0]=two*(xz+wy);
    m->m[0][1]=two*(xy+wz);
    m->m[1][1]=one-two*(xx+zz);
    m->m[2][1]=two*(yz-wx);
    m->m[0][2]=two*(xz-wy);
    m->m[1][2]=two*(yz+wx);
    m->m[2][2]=one-two*(xx+yy);
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
    {const C7Vec* p=&v; float x=up.x*p->x, y=up.y*p->y, z=up.z*p->z; float dot=z+(x+y); Scale(&up,dot);}
    Subtract(&v,&up);
    Normalize(&v);
    C7Vec axis=v;
    axis.x=up.y*v.z-up.z*v.y;
    axis.y=mul__lv(up.z, v.x)-up.x*v.z;
    axis.z=up.x*v.y-up.y*v.x;
    float length2=axis.z*axis.z+(axis.x*axis.x+axis.y*axis.y);
    if(length2>lbl_806D27F8) { Normalize(&axis); self->axis=axis; }
    else { float x=self->start.m[0][0], y=self->start.m[0][1], z=self->start.m[0][2]; self->axis.x=x; self->axis.y=y; self->axis.z=z; }
    C7Quat q;
    q.w=lbl_806D27F8; q.z=lbl_806D27F8; q.y=lbl_806D27F8; q.x=lbl_806D27F8;
    AxisAngle(&q,self->axis.x,self->axis.y,self->axis.z);
    QuaternionMatrix(&self->rotation,&q);
}

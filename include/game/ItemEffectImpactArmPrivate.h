#ifndef ITEM_EFFECT_IMPACT_ARM_PRIVATE_H
#define ITEM_EFFECT_IMPACT_ARM_PRIVATE_H
#include "game/C7ItemCtorPrivate.h"

extern "C" {
extern const float lbl_806D27F8, lbl_806D27FC, lbl_806D2828, lbl_806D281C, lbl_806D2824;
extern const double lbl_806D2808, lbl_806D2810;
extern double sin(double);
extern double cos(double);
}
struct ImpactArmMatrix { float m[4][4]; };
struct ImpactArmState {
    virtual void Reset();
    void* owner;
    C7Vec pos;
    ImpactArmMatrix start, current, rotation;
    int timer;
    C7Vec axis;
    float elapsed;
    int flags;
};
struct ImpactArmQuat { float x,y,z,w; ~ImpactArmQuat() {} };
static inline float Root(float x) {
    volatile float y;
    if(x>lbl_806D27F8) {
        double guess=__frsqrte(x);
        guess=0.5*guess*(3.0-x*(guess*guess));
        guess=0.5*guess*(3.0-x*(guess*guess));
        guess=0.5*guess*(3.0-x*(guess*guess));
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
#endif

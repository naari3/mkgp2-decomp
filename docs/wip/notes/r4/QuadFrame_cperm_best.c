#pragma cplusplus on
/* Pure numerical frame construction; no owning objects or EH actions. */
extern const float lbl_806D23B0, lbl_806D23B4, lbl_806D23B8, lbl_806D23D0;
extern const double lbl_806D23C0, lbl_806D23C8;
struct Vec {
 float x,y,z;
 Vec() {}
 ~Vec() {}
 Vec(float a,float b,float c):x(a),y(b),z(c) {}
 Vec operator+(const Vec& v) const { return Vec(x+v.x,y+v.y,z+v.z); }
 Vec operator-(const Vec& v) const { return Vec(x-v.x,y-v.y,z-v.z); }
 Vec operator*(float s) const { return Vec(s*x,s*y,s*z); }
};
static inline float root(float x) {
    volatile float result;
    if(x > lbl_806D23B0) {
        register double g=__frsqrte(x);
        { g=lbl_806D23C0 * g*(lbl_806D23C8-x*(g * g));
        g=lbl_806D23C0 * g*(lbl_806D23C8-x*(g * g)); }
        { g=lbl_806D23C0 * g*(lbl_806D23C8-x*(g * g)); }
        { result=(float)(g * x); return result; }
    } return x;
}
static inline void norm(volatile Vec *v,float len) {
    if(len <= lbl_806D23B0) { v->z=lbl_806D23B0;v->y=lbl_806D23B0;v->x=lbl_806D23B0; }
    else { float s=lbl_806D23B4/len; float x=v->x,y=v->y,z=v->z; v->x=x * s; v->y=y * s; v->z=z * s; }
}
extern "C" void QuadFrame_FromCornerPtrs(Vec *a,Vec *b,Vec *c,Vec *d,float *out,float *height) {
    Vec ab,cd,ac,bd;
    { cd.x=lbl_806D23B8*c->x+lbl_806D23B8*d->x;cd.y=lbl_806D23B8*c->y+lbl_806D23B8*d->y;cd.z=lbl_806D23B8*c->z+lbl_806D23B8*d->z;
    ab.x=lbl_806D23B8*lbl_806D23B8 + a->x*b->x;ab.y=lbl_806D23B8 * a->y+b->y * lbl_806D23B8;ab.z=a->z * lbl_806D23B8+b->z * lbl_806D23B8; }
    float _t660;
    _t660 = b->x;
    bd.x=_t660 * lbl_806D23B8+lbl_806D23B8*d->x;bd.y=lbl_806D23B8*b->y+lbl_806D23B8*d->y;bd.z=lbl_806D23B8*b->z+d->z * lbl_806D23B8;
    { ac.x=lbl_806D23B8*a->x+lbl_806D23B8*c->x;ac.y=a->y * lbl_806D23B8+lbl_806D23B8*c->y;ac.z=a->z * lbl_806D23B8+lbl_806D23B8*c->z; }
    float x,y,z,len;
    volatile Vec fwd,right;
    float _t56;
    _t56 = cd.y;
    x=ab.x-cd.x;y=ab.y-_t56;z=ab.z-cd.z;
    { fwd.x=x;fwd.y=y;fwd.z=z; }
    len=root(z*z+(x*x+y * y)); norm(&fwd,len);
    { x=bd.x-ac.x;y=bd.y-ac.y;z=bd.z-ac.z;
    out[6]=fwd.x;out[7]=fwd.y;out[8]=fwd.z; }
    right.x=x;right.y=y;right.z=z;
    len=root(z * z+(x * y + x*y)); norm(&right,len);
    { out[0]=right.x;out[1]=right.y;out[2]=right.z; }
    x=right.y*fwd.z-fwd.y * right.z;y=right.z*fwd.x-fwd.z * right.x;z=right.x*fwd.y-fwd.x * right.y;
    fwd.x=x;fwd.y=y;fwd.z=z;
    { len=root(z * z+(x * x+y*y)); norm(&fwd,len); }
    float _t957 = c->y;
    *height=(b->y+a->y+d->y+_t957)*lbl_806D23D0;
}

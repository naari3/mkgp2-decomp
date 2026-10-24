#pragma cplusplus on
/* Pure numerical frame construction; no owning objects or EH actions. */
extern const float lbl_806D23B0, lbl_806D23B4, lbl_806D23B8, lbl_806D23D0;
extern const double lbl_806D23C0, lbl_806D23C8;
struct Vec {
 float x,y,z;
 Vec() {}
 Vec(float a,float b,float c):x(a),y(b),z(c) {}
 Vec operator+(const Vec& v) const { return Vec(x+v.x,y+v.y,z+v.z); }
 Vec operator-(const Vec& v) const { return Vec(x-v.x,y-v.y,z-v.z); }
 Vec operator*(float s) const { return Vec(s*x,s*y,s*z); }
};
static inline float root(float x) {
    volatile float result;
    if(x > lbl_806D23B0) {
        double g=__frsqrte(x);
        g=lbl_806D23C0*g*(lbl_806D23C8-x*(g*g));
        g=lbl_806D23C0*g*(lbl_806D23C8-x*(g*g));
        g=lbl_806D23C0*g*(lbl_806D23C8-x*(g*g));
        result=(float)(x*g); return result;
    } return x;
}
static inline void norm(volatile Vec *v,float len) {
    if(len <= lbl_806D23B0) { v->z=lbl_806D23B0;v->y=lbl_806D23B0;v->x=lbl_806D23B0; }
    else { float s=lbl_806D23B4/len; v->x*=s; v->y*=s; v->z*=s; }
}
extern "C" void QuadFrame_FromCornerPtrs(Vec *a,Vec *b,Vec *c,Vec *d,float *out,float *height) {
    Vec ab=(*a)*lbl_806D23B8+(*b)*lbl_806D23B8;
    Vec cd=(*c)*lbl_806D23B8+(*d)*lbl_806D23B8;
    Vec ac=(*a)*lbl_806D23B8+(*c)*lbl_806D23B8;
    Vec bd=(*b)*lbl_806D23B8+(*d)*lbl_806D23B8;
    volatile Vec fwd,right;
    float x,y,z,len;
    x=ab.x-cd.x;y=ab.y-cd.y;z=ab.z-cd.z;
    fwd.x=x;fwd.y=y;fwd.z=z;
    len=root(z*z+(x*x+y*y)); norm(&fwd,len);
    x=bd.x-ac.x;y=bd.y-ac.y;z=bd.z-ac.z;
    out[6]=fwd.x;out[7]=fwd.y;out[8]=fwd.z;
    right.x=x;right.y=y;right.z=z;
    len=root(z*z+(x*x+y*y));norm(&right,len);
    out[0]=right.x;out[1]=right.y;out[2]=right.z;
    *height=(c->y+d->y+b->y+a->y)*lbl_806D23D0;
}


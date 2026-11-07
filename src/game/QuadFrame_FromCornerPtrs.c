#pragma cplusplus on
/* QuadFrame_FromCornerPtrs (0x80036A10): build a frame from four corner
 * points. fwd = mid(a,b) - mid(c,d), right = mid(b,d) - mid(a,c), both
 * normalised into out[6..8] / out[0..2]; then right x fwd is normalised
 * into fwd's storage but never written out; height = mean corner y.
 *
 * NonMatching (94.0%): the instruction stream is identical, only the FPR
 * colouring differs (two extra saved FPRs -> 0x20 bigger frame).
 * The midpoints/normalised vectors must be reference-bound temporaries so
 * they live on the stack in creation order and get reloaded after the
 * volatile sqrt result; the products in mid() fuse because each inline
 * instance has its own local half constant. */
extern const float lbl_806D23B0, lbl_806D23B4, lbl_806D23B8, lbl_806D23D0;
extern const double lbl_806D23C0, lbl_806D23C8;
struct Vec {
 float x,y,z;
 Vec() {}
 Vec(float a,float b,float c):x(a),y(b),z(c) {}
 Vec operator-(const Vec& v) const { return Vec(x-v.x,y-v.y,z-v.z); }
 Vec cross(const Vec& v) const { return Vec(y*v.z-z*v.y,z*v.x-x*v.z,x*v.y-y*v.x); }
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
static inline Vec mid(const Vec *p,const Vec *q) {
    float h=lbl_806D23B8;
    return Vec(h*p->x+h*q->x,h*p->y+h*q->y,h*p->z+h*q->z);
}
static inline float mag(const Vec &v) { float xx=v.x*v.x; float yy=v.y*v.y; float zz=v.z*v.z; float s=xx+yy; return root(zz+s); }
static inline Vec &norm(const Vec &r) {
    Vec *v=(Vec *)&r;
    float len=mag(*v);
    if(len <= lbl_806D23B0) { v->z=lbl_806D23B0;v->y=lbl_806D23B0;v->x=lbl_806D23B0; }
    else { float s=lbl_806D23B4/len; v->x*=s; v->y*=s; v->z*=s; }
    return *v;
}
extern "C" void QuadFrame_FromCornerPtrs(Vec *a,Vec *b,Vec *c,Vec *d,float *out,float *height) {
    const Vec &ac=mid(a,c);
    const Vec &ab=mid(a,b);
    const Vec &cd=mid(c,d);
    const Vec &bd=mid(b,d);
    Vec &fwd=norm(ab-cd);
    const Vec &right=bd-ac;
    out[6]=fwd.x;out[7]=fwd.y;out[8]=fwd.z;
    norm(right);
    out[0]=right.x;out[1]=right.y;out[2]=right.z;
    fwd=right.cross(fwd);
    norm(fwd);
    *height=(b->y+a->y+d->y+c->y)*lbl_806D23D0;
}

#include "game/RivalMarkerPrivate.h"
extern "C" {
double sin(double);
double cos(double);
double atan2(double, double);
void DebugPrintf(const char *, ...);
extern const char lbl_803EF600[];
extern const double lbl_806DBE68, lbl_806DBE70, lbl_806DBE78;
}
static inline float Root(float x) {
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        volatile float result = (float)(x * guess);
        x = result;
    }
    return x;
}
struct RivalVector {
    float x,y,z;
    RivalVector(float a, float b, float c) : x(a), y(b), z(c) {}
    RivalVector(const RivalVector &v) : x(v.x), y(v.y), z(v.z) {}
    ~RivalVector() {}
    void Sub(const RivalVector &v) { x -= v.x; y -= v.y; z -= v.z; }
    void Scale(float v) { x *= v; y *= v; z *= v; }
    float Length() const { float xx=x*x; float yy=y*y; float zz=z*z; float xy=xx+yy; return Root(zz+xy); }
    float Dot(const RivalVector &v) const { float xx=x*v.x; float yy=y*v.y; float zz=z*v.z; float xy=xx+yy; return zz+xy; }
};
static inline float AngleSin(double angle) { return (float)sin(angle); }
static inline float AngleCos(double angle) { return (float)cos(angle); }
static inline float RotatedAngle(float ax, float az, float bx, float bz, double angle) {
    float x = ax - bx;
    float z = az - bz;
    float s = AngleSin(angle);
    float c = AngleCos(angle);
    return (float)atan2(x*c-z*s, x*s+z*c);
}
static inline RivalPath *PathOf(RivalMarkerHud *self) { return self->path; }
extern "C" float fn_80243074(RivalMarkerHud *self, int index, const RivalPosition *position) {
    RivalPath *path = PathOf(self);
    int total = Path_GetTotalCount(path);
    /* `long`: the advanced index becomes its own temp numbered above `position`
       (regalloc_patterns 95); with `int` it stays the parameter and r28/r29 swap. */
    long i = index;
    long old = i;
    i = (i + 1) % total;
    RivalWaypoint *a = Path_GetWaypointPtr(path, old);
    RivalWaypoint *b = Path_GetWaypointPtr(path, i);
    if (!a || !b) {
        DebugPrintf(lbl_803EF600);
        return 0.0f;
    }
    float angle = RotatedAngle(a->x, a->z, b->x, b->z, lbl_806DBE68);
    float side = RotatedAngle(a->x, a->z, position->x, position->z, angle);
    RivalVector end(b->x, b->y, b->z);
    RivalVector start(a->x, a->y, a->z);
    RivalVector point(position->x, position->y, position->z);
    end.Sub(start);
    point.Sub(start);
    RivalVector offset(point);
    float amount = point.Dot(end) / (end.Length() * end.Length());
    RivalVector projection(end);
    projection.Scale(amount);
    offset.Sub(projection);
    float distance = offset.Length();
    if (side < 0.0f) distance = -distance;
    return distance;
}

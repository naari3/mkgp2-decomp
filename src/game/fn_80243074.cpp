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
    if (x > lbl_806DBE64) {
        double guess = __frsqrte(x);
        guess = lbl_806DBE70 * guess * (lbl_806DBE78 - guess * guess * x);
        guess = lbl_806DBE70 * guess * (lbl_806DBE78 - guess * guess * x);
        guess = lbl_806DBE70 * guess * (lbl_806DBE78 - guess * guess * x);
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
static inline float RotatedAngle(float x, float z, double angle) {
    float s = (float)sin(angle);
    float c = (float)cos(angle);
    return (float)atan2(x*c-z*s, x*s+z*c);
}
extern "C" float fn_80243074(RivalMarkerHud *self, int index, const RivalPosition *position) {
    RivalPath *path = self->path;
    int total = Path_GetTotalCount(path);
    int old = index;
    index = (index + 1) % total;
    RivalWaypoint *a = Path_GetWaypointPtr(path, old);
    RivalWaypoint *b = Path_GetWaypointPtr(path, index);
    if (!a || !b) {
        DebugPrintf(lbl_803EF600);
        return lbl_806DBE64;
    }
    float x = a->x - b->x;
    float z = a->z - b->z;
    float angle = RotatedAngle(x, z, lbl_806DBE68);
    x = a->x - position->x;
    z = a->z - position->z;
    float side = RotatedAngle(x, z, angle);
    RivalVector end(b->x, b->y, b->z);
    RivalVector start(a->x, a->y, a->z);
    RivalVector point(position->x, position->y, position->z);
    end.Sub(start);
    point.Sub(start);
    RivalVector offset(point);
    float dot = point.Dot(end);
    float length = end.Length();
    float length2 = end.Length();
    float amount = dot / (length * length2);
    RivalVector projection(end);
    projection.Scale(amount);
    offset.Sub(projection);
    float distance = offset.Length();
    if (side < lbl_806DBE64) distance = -distance;
    return distance;
}

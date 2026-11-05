#include "game/SpecialFacePrivate.h"
static inline void Normalize(Vec3f *v) {
    float yy = v->y * v->y;
    float xx = v->x * v->x;
    float zz = v->z * v->z;
    float xy = xx + yy;
    float len = MathInline_sqrtf(zz + xy);
    if (len <= 0.0f) { v->z = v->y = v->x = 0.0f; }
    else {
        float inv = 1.0f / len;
        v->x *= inv; v->y *= inv; v->z *= inv;
    }
}
extern "C" void SpecialFace_BuildPlaneAndEdges(SpecialFaceNative *self, const SpecialFaceSource *src) {
    Vec3f a, b;
    a.x = src->vertices[1].x - src->vertices[0].x;
    a.y = src->vertices[1].y - src->vertices[0].y;
    a.z = src->vertices[1].z - src->vertices[0].z;
    Normalize(&a);
    b.x = src->vertices[2].x - src->vertices[0].x;
    b.y = src->vertices[2].y - src->vertices[0].y;
    b.z = src->vertices[2].z - src->vertices[0].z;
    Normalize(&b);
    float nx = a.y * b.z - a.z * b.y;
    float ny = a.z * b.x - a.x * b.z;
    float nz = a.x * b.y - a.y * b.x;
    b.x = nx; b.y = ny; b.z = nz;
    self->normal.x = b.x; self->normal.y = b.y; self->normal.z = b.z;
    self->distance = b.x * src->vertices[0].x + b.y * src->vertices[0].y + b.z * src->vertices[0].z;
    for (int i = 0; i < src->count; i++) {
        int next = (i + 1) % src->count;
        self->edges[i].x = src->vertices[next].x - src->vertices[i].x;
        self->edges[i].y = src->vertices[next].y - src->vertices[i].y;
        self->edges[i].z = src->vertices[next].z - src->vertices[i].z;
    }
}

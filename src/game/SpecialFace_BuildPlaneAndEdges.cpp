#include "game/SpecialFacePrivate.h"

static inline void SetVector(SpecialFaceVec *v, float x, float y, float z) {
    v->x = x; v->y = y; v->z = z;
}
static inline void CrossVector(SpecialFaceVec *out, const SpecialFaceVec *a, const SpecialFaceVec *b) {
    float x = a->y * b->z - a->z * b->y;
    float y = a->z * b->x - a->x * b->z;
    float z = a->x * b->y - a->y * b->x;
    out->x = x; out->y = y; out->z = z;
}
static inline void Normalize(SpecialFaceVec *v) {
    float yy = v->y * v->y;
    float xx = v->x * v->x;
    float zz = v->z * v->z;
    float xy = xx + yy;
    float len = MathInline_sqrtf(zz + xy);
    if (len <= 0.0f) { v->x = v->y = v->z = 0.0f; }
    else {
        float inv = 1.0f / len;
        v->x *= inv; v->y *= inv; v->z *= inv;
    }
}
extern "C" void SpecialFace_BuildPlaneAndEdges(SpecialFaceNative *self, const SpecialFaceSource *src) {
    SpecialFaceVec a, b;
    SetVector(&a,
        src->vertices[1].x - src->vertices[0].x,
        src->vertices[1].y - src->vertices[0].y,
        src->vertices[1].z - src->vertices[0].z);
    Normalize(&a);
    SetVector(&b,
        src->vertices[2].x - src->vertices[0].x,
        src->vertices[2].y - src->vertices[0].y,
        src->vertices[2].z - src->vertices[0].z);
    Normalize(&b);
    CrossVector(&b, &a, &b);
    self->normal.x = b.x; self->normal.y = b.y; self->normal.z = b.z;
    self->distance = b.x * src->vertices[0].x + b.y * src->vertices[0].y + b.z * src->vertices[0].z;
    for (int i = 0; i < src->count; i++) {
        int next = (i + 1) % src->count;
        SetVector(&self->edges[i],
            src->vertices[next].x - src->vertices[i].x,
            src->vertices[next].y - src->vertices[i].y,
            src->vertices[next].z - src->vertices[i].z);
    }
}

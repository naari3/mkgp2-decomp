/* Whole reversed EH group: retain NonMatching until every owned range matches. */
#include "game/SpecialFaceRaycastPrivate.h"
#include "game/singleton.h"

extern "C" unsigned char SpecialFaceMesh_Raycast(SpecialFaceMeshNative *self,
        const Vec3f *from, const Vec3f *to, Vec3f *out, Vec3f *normal) {
    FaceRaySegment ray;
    ray.endpoints[0].x = from->x; ray.endpoints[0].y = from->y; ray.endpoints[0].z = from->z;
    ray.endpoints[1].x = to->x; ray.endpoints[1].y = to->y; ray.endpoints[1].z = to->z;
    ray.delta.x = to->x; ray.delta.y = to->y; ray.delta.z = to->z;
    ray.delta.x -= from->x; ray.delta.y -= from->y; ray.delta.z -= from->z;
    float minZ, maxZ = ray.endpoints[1].z;
    if (ray.endpoints[0].z < maxZ) minZ = ray.endpoints[0].z;
    else { minZ = maxZ; maxZ = ray.endpoints[0].z; }
    float minX, maxX = ray.endpoints[1].x;
    if (ray.endpoints[0].x < maxX) minX = ray.endpoints[0].x;
    else { minX = maxX; maxX = ray.endpoints[0].x; }
    FaceRayBounds bounds;
    bounds.minZ = minZ; bounds.maxZ = maxZ; bounds.minX = minX; bounds.maxX = maxX;
    SpecialFaceNative **p = self->faces.data;
    int count = self->faces.count;
    while (count-- > 0) {
        if (*p && SpecialFace_RaycastSegment(*p, &bounds, &ray, out, normal) == 1) return 1;
        ++p;
    }
    return 0;
}

extern "C" {
extern const double lbl_806D2F68, lbl_806D2F70;
extern const float lbl_806D2F78;
}
static inline float FaceRaySqrt(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = lbl_806D2F68 * guess * (lbl_806D2F70 - x * (guess * guess));
        guess = lbl_806D2F68 * guess * (lbl_806D2F70 - x * (guess * guess));
        guess = lbl_806D2F68 * guess * (lbl_806D2F70 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

extern "C" unsigned char SpecialFace_RaycastSegment(SpecialFaceNative *self,
        const FaceRayBounds *bounds, const FaceRaySegment *ray, Vec3f *out, Vec3f *normal) {
    if (bounds->minZ > self->maxZ) return 0;
    if (bounds->maxZ < self->minZ) return 0;
    if (bounds->maxX < self->minX) return 0;
    if (bounds->minX > self->maxX) return 0;
    float normalX = self->normal.x, normalY = self->normal.y, normalZ = self->normal.z;
    if (normalX*ray->delta.x + normalY*ray->delta.y + normalZ*ray->delta.z > 0.0f) return 0;
    SpecialFaceVec a; a.x = ray->endpoints[0].x; a.y = ray->endpoints[0].y; a.z = ray->endpoints[0].z;
    SpecialFaceVec b; b.x = ray->endpoints[1].x; b.y = ray->endpoints[1].y; b.z = ray->endpoints[1].z;
    a.x -= self->source.vertices[0].x; a.y -= self->source.vertices[0].y; a.z -= self->source.vertices[0].z;
    b.x -= self->source.vertices[0].x; b.y -= self->source.vertices[0].y; b.z -= self->source.vertices[0].z;
    float ax = a.x*normalX, ay = a.y*normalY, az = a.z*normalZ;
    float bx = b.x*normalX, by = b.y*normalY, bz = b.z*normalZ;
    float da = (az + ay) + ax, db = bz + (bx + by);
    if (da > 0.0f && db > 0.0f) return 0;
    if (da < 0.0f && db < 0.0f) return 0;
    const Vec3f *vertex;
    int count = self->source.count;
    vertex = self->source.vertices + count;
    while (--vertex, count-- > 0) {
        const SpecialFaceVec *edge = (const SpecialFaceVec *)((const char *)vertex + sizeof(SpecialFaceSource) + sizeof(SpecialFaceVec) + sizeof(float));
        SpecialFaceVec cross; cross.x = edge->x; cross.y = edge->y; cross.z = edge->z;
        float cx = ray->delta.y*cross.z - ray->delta.z*cross.y;
        float cy = ray->delta.z*cross.x - ray->delta.x*cross.z;
        float cz = ray->delta.x*cross.y - ray->delta.y*cross.x;
        cross.x = cx; cross.y = cy; cross.z = cz;
        SpecialFaceVec relative;
        relative.x = ray->endpoints[0].x; relative.y = ray->endpoints[0].y; relative.z = ray->endpoints[0].z;
        relative.x -= vertex->x; relative.y -= vertex->y; relative.z -= vertex->z;
        float x = cross.x*relative.x, y = cross.y*relative.y, z = cross.z*relative.z;
        if (z + (x+y) > 0.0f) return 0;
    }
    float denom = self->normal.x*ray->delta.x;
    float dy = self->normal.y*ray->delta.y;
    float dz = self->normal.z*ray->delta.z;
    denom = dz + (denom + dy);
    float reciprocal = denom;
    if (denom != 0.0f) reciprocal = lbl_806D2F78 / denom;
    Vec3f origin; origin.x = ray->endpoints[0].x; origin.y = ray->endpoints[0].y; origin.z = ray->endpoints[0].z;
    float planeX = self->normal.x * origin.x;
    float planeY = self->normal.y * origin.y;
    float planeZ = self->normal.z * origin.z;
    reciprocal *= -(planeZ + (planeX + planeY) - self->distance);
    SpecialFaceVec offset; offset.x = ray->delta.x; offset.y = ray->delta.y; offset.z = ray->delta.z;
    offset.x *= reciprocal; offset.y *= reciprocal; offset.z *= reciprocal;
    out->x = origin.x + offset.x; out->y = origin.y + offset.y; out->z = origin.z + offset.z;
    {
        float yy = offset.y*offset.y;
        float xx = offset.x*offset.x;
        float zz = offset.z*offset.z;
        float xy = xx + yy;
        float length = FaceRaySqrt(zz + xy);
        if (length <= 0.0f) offset.x = offset.y = offset.z = 0.0f;
        else { float inv = lbl_806D2F78 / length; offset.x *= inv; offset.y *= inv; offset.z *= inv; }
    }
    offset.x *= lbl_806D2F7C; offset.y *= lbl_806D2F7C; offset.z *= lbl_806D2F7C;
    out->x += offset.x; out->y += offset.y; out->z += offset.z;
    normal->x = -self->normal.x; normal->y = -self->normal.y; normal->z = -self->normal.z;
    return 1;
}



#pragma dont_inline on
extern "C" unsigned char SpecialFaceMesh_RaycastThunk(SpecialFaceMeshNative *self,
        const Vec3f *from, const Vec3f *to, Vec3f *out, Vec3f *normal) {
    return SpecialFaceMesh_Raycast(self, from, to, out, normal);
}
#pragma dont_inline reset

extern "C" unsigned char SpecialFaceMesh_AddFace(SpecialFaceMeshNative *self, const SpecialFaceSource *src) {
    SpecialFaceNative *face = new SpecialFaceNative(src);
    PtrVec_InsertFill(&self->faces, self->faces.data + self->faces.count, 1, &face);
    return 1;
}

extern "C" void FUN_8007c56c(FaceSourceGroup *src, int extra) {
    SpecialFaceMeshNative *mesh = SINGLETON_INSTANCE(lbl_806D1138);
    if (!mesh) new SpecialFaceMeshNative(src, extra);
}

extern "C" void fn_8007C5DC(void *) {}

extern "C" FacePtrVec *dtor_8007C5E0(FacePtrVec *self, short release) {
    if (self) {
        if (self) { if (self) { if (self->data) operator delete(self->data); } }
        if (release > 0) operator delete(self);
    }
    return self;
}

static inline void FaceCopyBackward(SpecialFaceNative **first,
        SpecialFaceNative **last, SpecialFaceNative **result) {
    while (last > first) *--result = *--last;
}

template <class T> static inline T *FaceCopyForward(T *first, T *last, T *result) {
    while (first < last) *result++ = *first++;
    return result;
}

extern "C" void PtrVec_InsertFill(void *storage, SpecialFaceNative **position,
        unsigned int n, SpecialFaceNative **value) {
    FacePtrStorage *s = (FacePtrStorage *)storage;
    if (n != 0) {
        if (n > 0x3fffffff || s->count > 0x3fffffff - n) throw std::length_error(lbl_80311BDC);
        SpecialFaceNative **old;
        unsigned int size = s->count + n;
        if (size <= s->capacity) {
            SpecialFaceNative **source = value;
            unsigned int tail = (s->data + s->count) - position;
            SpecialFaceNative **end = s->data + s->count;
            if (end - (tail - n) <= value && value < end) source += n;
            if (tail != 0) {
                FaceCopyBackward(position, end, end + n);
            }
            SpecialFaceNative **out = position;
            for (unsigned int i = n; i; --i) *out++ = *source;
            s->count += n;
        } else {
            old = s->data;
            int offset = position - old;
            unsigned int capacity = s->capacity ? s->capacity : 1;
            while (size > capacity) {
                if (capacity < 0x1fffffff) capacity *= 2;
                else capacity = 0x3fffffff;
            }
            s->data = (SpecialFaceNative **)Alloc(capacity * 4);
            SpecialFaceNative **out = s->data + offset;
            for (unsigned int i = n; i; --i) *out++ = *value;
            if (old) {
                FaceCopyForward(old, old + offset, s->data);
                SpecialFaceNative **end = old + s->count;
                SpecialFaceNative **result = s->data + offset + n;
                FaceCopyForward(old + offset, end, result);
                operator delete(old);
            }
            s->count = size;
            s->capacity = capacity;
        }
    }
}

extern "C" void PtrVec_Reserve(void *storage, unsigned int capacity) {
    FacePtrStorage *s = (FacePtrStorage *)storage;
    if (capacity > s->capacity) {
        if (capacity > 0x3fffffff) throw std::length_error(lbl_80311C30);
        SpecialFaceNative **old = s->data;
        s->data = (SpecialFaceNative **)Alloc(capacity * 4);
        if (old) {
            SpecialFaceNative **end = old + s->count, **p = old, **out = s->data;
            while (p < end) *out++ = *p++;
            operator delete(old);
        }
        s->capacity = capacity;
    }
}

extern "C" FaceMeshBase *dtor_8007CC54(FaceMeshBase *self, short release) {
    if (self) { self->vptr = SpecialFaceMesh_vtable_803FE0B8; if (release > 0) operator delete(self); }
    return self;
}

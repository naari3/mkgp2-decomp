#ifndef GAME_SPECIAL_FACE_RAYCAST_PRIVATE_H
#define GAME_SPECIAL_FACE_RAYCAST_PRIVATE_H
#include "game/SpecialFaceMeshPrivate.h"
#include "game/WarpZoneInsertPrivate.h"

struct FaceRaySegment {
    SpecialFaceVec endpoints[2];
    Vec3f delta;
    FaceRaySegment() {}
    ~FaceRaySegment() {}
};
struct FaceRayBounds { float minZ, maxZ, minX, maxX; };
extern "C" {
extern const char lbl_80311BDC[], lbl_80311C30[];
extern const float lbl_806D2F7C;
unsigned char SpecialFace_RaycastSegment(SpecialFaceNative *, const FaceRayBounds *,
                                       const FaceRaySegment *, Vec3f *, Vec3f *);
unsigned char SpecialFaceMesh_Raycast(SpecialFaceMeshNative *, const Vec3f *,
                                    const Vec3f *, Vec3f *, Vec3f *);
}
template <class A> static inline float FaceDot(const A &a, const SpecialFaceVec &b) {
    float x = a.x*b.x, y = a.y*b.y, z = a.z*b.z;
    return z + (x + y);
}
#endif

#ifndef SPECIAL_FACE_PRIVATE_H
#define SPECIAL_FACE_PRIVATE_H
#include "game/MathInline.h"
struct SpecialFaceSource {
    Vec3f vertices[4];
    int count;
};
struct SpecialFaceVec {
    float x, y, z;
    SpecialFaceVec() {}
    ~SpecialFaceVec() {}
};
struct SpecialFaceNative {
    SpecialFaceSource source;
    SpecialFaceVec normal;
    float distance;
    SpecialFaceVec edges[4];
    float minX, maxX, minZ, maxZ;
    SpecialFaceNative(const SpecialFaceSource *);
};
extern "C" void SpecialFace_BuildPlaneAndEdges(SpecialFaceNative *, const SpecialFaceSource *);
#endif

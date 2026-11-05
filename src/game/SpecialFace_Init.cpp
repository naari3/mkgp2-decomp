#include "game/SpecialFacePrivate.h"
SpecialFaceNative::SpecialFaceNative(const SpecialFaceSource *src) {
    source = *src;
    SpecialFace_BuildPlaneAndEdges(this, &source);
    minX = source.vertices[0].x;
    for (int i = 1; i < source.count; i++)
        if (minX > source.vertices[i].x) minX = source.vertices[i].x;
    maxX = source.vertices[0].x;
    for (int i = 1; i < source.count; i++)
        if (maxX < source.vertices[i].x) maxX = source.vertices[i].x;
    minZ = source.vertices[0].z;
    for (int i = 1; i < source.count; i++)
        if (minZ > source.vertices[i].z) minZ = source.vertices[i].z;
    maxZ = source.vertices[0].z;
    for (int i = 1; i < source.count; i++)
        if (maxZ < source.vertices[i].z) maxZ = source.vertices[i].z;
}

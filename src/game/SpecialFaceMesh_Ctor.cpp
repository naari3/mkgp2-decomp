#include "game/SpecialFaceMeshPrivate.h"
SpecialFaceMeshNative::SpecialFaceMeshNative(FaceSourceGroup *src, int extra) {
    PtrVec_Reserve(&faces, src->count + extra);
    const unsigned char *data = (const unsigned char *)src->data;
    int i = 0;
    int count = src->count;
    int offset = 0;
    for (; i < count; offset += sizeof(SpecialFaceSource), i++) {
        SpecialFaceNative *face = new SpecialFaceNative((const SpecialFaceSource *)(data + offset));
        PtrVec_InsertFill(&faces, faces.data + faces.count, 1, &face);
    }
}

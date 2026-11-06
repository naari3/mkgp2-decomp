#include "game/SpecialFaceMeshPrivate.h"
SpecialFaceMeshNative::SpecialFaceMeshNative(FaceSourceGroup *__restrict src, int extra) {
    PtrVec_Reserve(&faces, src->count + extra);
    int count;
    const unsigned char *data;
    int offset;
    int i;
    data = (const unsigned char *)src->data;
    i = 0;
    count = src->count;
    offset = 0;
    for (; i < count; offset += sizeof(SpecialFaceSource), i++) {
        SpecialFaceNative *face = new SpecialFaceNative((const SpecialFaceSource *)(data + offset));
        PtrVec_InsertFill(&faces, faces.data + faces.count, 1, &face);
    }
}

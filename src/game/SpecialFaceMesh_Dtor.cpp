#include "game/SpecialFaceMeshPrivate.h"

SpecialFaceMeshNative::~SpecialFaceMeshNative() {
    vptr = lbl_803FE0AC;
    unsigned int offset;
    SpecialFaceNative *face;
    unsigned int i;
    i = 0;
    offset = 0;
    for (; i < faces.count; i++, offset += sizeof(*faces.data)) {
        face = *(SpecialFaceNative **)((unsigned char *)faces.data + offset);
        delete face;
    }
}

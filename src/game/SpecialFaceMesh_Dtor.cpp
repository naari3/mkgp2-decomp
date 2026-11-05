#include "game/SpecialFaceMeshPrivate.h"
SpecialFaceMeshNative::~SpecialFaceMeshNative() {
    vptr = lbl_803FE0AC;
    SpecialFaceNative *face;
    for (unsigned int i = 0; i < faces.count; i++) { face = faces.data[i]; delete face; }
}

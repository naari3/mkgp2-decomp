#include "game/SpecialFaceMeshPrivate.h"

/* opt_strength_reduction off: the target's byte offset into faces.data is
 * the frontend index temp, coloured above the hoisted dtor address. */
#pragma opt_strength_reduction off
SpecialFaceMeshNative::~SpecialFaceMeshNative() {
    vptr = SpecialFaceMesh_data_803FE0AC;
    for (unsigned int i = 0; i < faces.count; i++) {
        delete faces.data[i];
    }
}
#pragma opt_strength_reduction reset

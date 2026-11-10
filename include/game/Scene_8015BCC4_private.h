#ifndef SCENE_8015BCC4_PRIVATE_H
#define SCENE_8015BCC4_PRIVATE_H
/* Debug viewer resource replacement. Scene3D's base allocation is 0x3084. */
struct ViewerScene3D {
    virtual ~ViewerScene3D();
    void *camera;
    char opaque[0x3084 - 8];
    ViewerScene3D(unsigned int);
};
struct ViewerNormal3D {
    char opaque[0x5c];
    ViewerNormal3D(unsigned int, int);
};
#include "game/types/ViewerVec.h"
#endif

#ifndef OBJVIEW_A70C_PRIVATE_H
#define OBJVIEW_A70C_PRIVATE_H
#include "game/types/Vec.h"
struct clNormal3D {
    char _opaque[0x5C];
    clNormal3D(void *res, int flags);
};
#include "game/types/CourseMarkerBase.h"
struct ObjViewFrame { int active; float time; };
struct SoundProp : CourseMarkerBase {
    clNormal3D *model;
    float radius, yoff;
    Vec *pos;
    float *rot;
    ObjViewFrame *frames;
    int count;
    virtual void vKeyFunction3();
    SoundProp();
};
#endif

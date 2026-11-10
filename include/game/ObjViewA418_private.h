#ifndef OBJVIEW_A418_PRIVATE_H
#define OBJVIEW_A418_PRIVATE_H
#include "game/types/Vec.h"
typedef struct Frame { int active; float time; } Frame;
typedef struct ObjView {
    void *vt, *jobj;
    float radius, yoff;
    Vec *pos;
    float *rot;
    Frame *frames;
    int count;
} ObjView;
#endif

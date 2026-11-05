#ifndef OBJVIEW_A418_PRIVATE_H
#define OBJVIEW_A418_PRIVATE_H
typedef struct Vec { float x, y, z; } Vec;
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

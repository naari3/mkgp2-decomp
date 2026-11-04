#ifndef OBJVIEW_PATH186_PRIVATE_H
#define OBJVIEW_PATH186_PRIVATE_H
#ifdef __cplusplus
#include "game/mapobject/mapobject.h"
#else
#include "game/MathInline.h"
#endif
typedef struct Path186 {
#ifdef __cplusplus
    HSD_JObj *joint[4];
#else
    void *joint[4];
#endif
    Vec3f *points;
    int count, index;
    Vec3f a, b, c;
    float time;
    Vec3f position;
    float yaw;
} Path186;
typedef struct View186 {
    void *vt;
    void *object;
    Path186 *paths;
    float rotation, phase, phase2;
} View186;
static inline Vec3f *Path186_Point(Path186 *p, int i) {
    if (i >= p->count) i -= p->count;
    return &p->points[i];
}
#endif

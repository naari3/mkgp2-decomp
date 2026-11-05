#ifndef SCENE_80170B5C_PRIVATE_H
#define SCENE_80170B5C_PRIVATE_H

#include "game/Scene_80170544_private.h"

struct Vec3Grow { float x,y,z; };
struct GrowJoint {
    char pad00[0x38]; Vec3Grow pos;
};
struct GrowDObj { char pad00[0xC]; void *pobj; };
struct GrowFace { char data[0x48]; };
struct GrowAnim {
    void *data;
    GrowAnim(GrowFace *, int);
};
struct GrowSub {
    Vec3Grow pos;
    float scale;
    char rest[0xAC];
    GrowSub();
};
struct GrowEntry {
    GrowJoint *jobj;
    void *faces;
    int faceCount;
    GrowAnim *anim;
    int state;
    float t, scale;
    GrowSub *sub;
};
struct GrowSet : CourseMarkerBase {
    clNormal3D *model;
    GrowEntry *entries;
    int count;
    GrowSet();
    virtual void keyDerived();
};
#endif

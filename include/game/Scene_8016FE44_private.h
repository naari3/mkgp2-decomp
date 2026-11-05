#ifndef SCENE_8016FE44_PRIVATE_H
#define SCENE_8016FE44_PRIVATE_H

#include "game/Scene_80170544_private.h"

struct RenderJoint {
    char pad00[8]; RenderJoint *next;
    char pad0C[4]; RenderJoint *child;
    unsigned int flags; char pad18[4];
    float rx, ry, rz;
    char pad28[0x10]; float x, y, z;
};
struct SparkRender {
    void *vtable; RenderJoint *root; int count;
    clNormal3D *modelA, *modelB;
    RenderJoint *joints[4];
    CourseSpark sparks[5];
    int cooldown, randomIndex;
    void Draw();
};
#endif

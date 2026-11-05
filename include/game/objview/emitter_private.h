#ifndef OBJVIEW_E538_PRIVATE_H
#define OBJVIEW_E538_PRIVATE_H
#include "game/objview/part_render_private.h"
struct ViewJoint {
    char pad0[8]; ViewJoint *next; ViewJoint *parent; ViewJoint *child;
    unsigned int flags; char pad18[0x2c]; Mtx matrix;
};
struct ViewMatrixParticle { float age; ViewJoint *joint; Mtx matrix; };
struct ViewBillboardParticle {
    float age, scale, alpha; Vec3f pos; float speed, maxAlpha;
};
struct ViewEmitter {
    void *vt; clNormal3D *model; clNormal3D *billboard; int count;
    ViewMatrixParticle *matrices; ViewBillboardParticle *particles;
    int delay, randomIndex, variationIndex;
};
extern "C" {
extern const float lbl_806D9440, lbl_806D9444, lbl_806D9448, lbl_806D944C;
extern const float lbl_806D9460;
void Object_SetField8_AndDirty(clNormal3D *, float);
void Object_SetAnimBinding(clNormal3D *, Mtx, int);
void Object_DriveAnimMatrix(clNormal3D *);
}
#endif

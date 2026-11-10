#ifndef SCENE_8015B790_PRIVATE_H
#define SCENE_8015B790_PRIVATE_H
/* Debug model viewer: select a resource and adjust rotation/camera. */
struct ViewerInput {
    virtual void v0(); virtual void v1(); virtual float axis(); virtual void v3();
    virtual float right(); virtual float left();
    virtual unsigned char pressed(int); virtual unsigned char held(int);
};
struct ModelEntry { const char *res; float scale; int icon; float iconScale; float field10, field14, field18, field1C; float iconY; };
struct CameraOwner { void *vtable; void *camera; };
#include "game/types/ViewerVec.h"
#endif

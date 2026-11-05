#ifndef SCENE_8015B790_PRIVATE_H
#define SCENE_8015B790_PRIVATE_H
/* Debug model viewer: select a resource and adjust rotation/camera. */
struct ViewerInput {
    virtual void v0(); virtual void v1(); virtual float axis(); virtual void v3();
    virtual float right(); virtual float left();
    virtual unsigned char pressed(int); virtual unsigned char held(int);
};
struct ModelEntry { unsigned int res; float scale; int icon; float iconScale; char pad[16]; float iconY; };
struct ViewerPool { char strings[0x10c]; ModelEntry models[14]; float steps[3]; char rest[256]; };
struct CameraOwner { void *vtable; void *camera; };
struct ViewerVec { float x,y,z; };
#endif

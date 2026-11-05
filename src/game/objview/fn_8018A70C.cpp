#include "game/ObjViewA70C_private.h"
extern "C" {
extern char lbl_803776C8[];
extern float lbl_806D9368[2];
extern int g_cupId;
extern void *lbl_806CFBE0, *lbl_806CFBE4;
void DebugPrintf(const char *, ...);
void clNormal3D_SetScale(clNormal3D *, int, float, float, float, float);
void *FUN_8003b120(unsigned long);
}
SoundProp::SoundProp() {
    char *base = lbl_803776C8;
    void *resource;
    DebugPrintf(base + 0x4d0);
    model = 0;
    radius = 0.0f;
    yoff = 0.0f;
    frames = 0;
    count = 0;
    pos = 0;
    rot = 0;
    resource = 0;
    switch (g_cupId) {
    case 0: break;
    case 1:
        resource = lbl_806CFBE0;
        pos = (Vec *)(base + 0x410);
        rot = lbl_806D9368;
        count = 2;
        radius = 90.0f;
        yoff = 45.0f;
        break;
    case 2:
        resource = lbl_806CFBE4;
        pos = (Vec *)(base + 0x438);
        rot = (float *)(base + 0x474);
        count = 5;
        radius = 90.0f;
        yoff = 45.0f;
        break;
    default: break;
    }
    if (!resource || !pos || !rot || count == 0) return;
    model = new clNormal3D(resource,0);
    clNormal3D_SetScale(model,0,0.0f,1.0f,0.0f,0.0f);
    frames = (ObjViewFrame *)FUN_8003b120(count * sizeof(ObjViewFrame));
    for (int i=0; i<count; i++) {
        frames[i].active = 0;
        frames[i].time = 0.0f;
    }
}

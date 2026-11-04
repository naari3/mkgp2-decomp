#ifndef OBJVIEW_PART_RENDER_PRIVATE_H
#define OBJVIEW_PART_RENDER_PRIVATE_H
#include "game/mapobject/mapobject.h"
struct HSD_DObj;
struct GXChannel {
    GXChannel(HSD_JObj *, HSD_DObj *, unsigned int, int);
    ~GXChannel();
    unsigned char storage[0x14];
};
extern "C" {
void *GetCourseScene3D(void);
Mtx *CObj_GetProjMatrix_Cached(void *);
void Scene3D_GetCameraPos(void *, float *, float *);
HSD_DObj *HSD_JObjGetDObj(HSD_JObj *);
void PSMTXMultVec(const Mtx, const Vec3f *, Vec3f *);
void PSMTXScale(Mtx, float, float, float);
void Object_SetColorAlphaOnly(clNormal3D *, int, float);
void GXChannel_PushTransform(GXChannel *, Mtx);
void Object_GetJObjPositionVec(clNormal3D *, Vec3f *);
void clNormal3D_Exec(clNormal3D *);
void Object_RenderJObjTree(clNormal3D *, int);
unsigned char fn_801379F0(Vec3f *, float);
double tan(double);
}
#endif

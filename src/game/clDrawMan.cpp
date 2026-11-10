#include "game/clDrawMan_private.h"

/* 0x80079CDC..0x8007ADC0. Real new[] and scoped timers own all EH records.
 * The two no-bias variants test clipping before applying the depth bias. */

static inline DrawManager *CurrentDrawManager()
{
    DrawManager *manager = lbl_806D10AC;
    if (!manager) manager = 0;
    return manager;
}

#pragma use_lmw_stmw on
extern "C" DrawManager *DrawManager_GetOrCreate()
{
    if (!CurrentDrawManager()) new DrawManager;
    return CurrentDrawManager();
}

extern "C" void clDrawMan_EndFrame_NoOp(DrawManager *) {}

extern "C" void clDrawMan_Buckets_Reset(DrawManager *self)
{
    self->Reset();
}

extern "C" void clDrawMan_Buckets_Dispatch(DrawManager *self)
{
    int i = self->bucketCount;
    while (i-- > 0) {
        DrawBucket *bucket = &self->buckets[i];
        bucket->Dispatch();
    }
}
#pragma use_lmw_stmw off

extern "C" void clDrawMan_SetMaxClipZ(DrawManager *self, float z)
{
    self->maxClipZ = z;
}

extern "C" int clDrawMan_AddSorted(DrawManager *self, DrawCallback callback, void *object,
                                  float x, float y, float z, float bias)
{
    ScopedTimer total(20);
    ScopedTimer sort(41);
    if (!GetCourseScene3D()) return 0;
    float xx, yy, zz;
    CObj_UnprojectPoint(GetCourseScene3D(), x, y, z, &xx, &yy, &zz);
    zz = -zz;
    zz += bias;
    if (zz < self->minClipZ) return 0;
    return self->Insert(callback, object, zz);
}

extern "C" int clDrawMan_AddSorted_NoDepthBias(DrawManager *self, DrawCallback callback, void *object,
                                              float x, float y, float z, float bias)
{
    ScopedTimer total(20);
    ScopedTimer sort(41);
    if (!GetCourseScene3D()) return 0;
    float xx, yy, zz;
    CObj_UnprojectPoint(GetCourseScene3D(), x, y, z, &xx, &yy, &zz);
    zz = -zz;
    if (zz < self->minClipZ) return 0;
    return self->Insert(callback, object, zz + bias);
}

extern "C" int clDrawMan_AddSorted_DepthRange(DrawManager *self, DrawCallback callback, void *object,
                                             float x, float y, float z, float bias)
{
    ScopedTimer total(20);
    ScopedTimer sort(41);
    if (!GetCourseScene3D()) return 0;
    float xx, yy, zz;
    CObj_UnprojectPoint(GetCourseScene3D(), x, y, z, &xx, &yy, &zz);
    zz = -zz;
    if (zz < self->minClipZ || zz > self->maxClipZ) return 0;
    return self->Insert(callback, object, zz + bias);
}

DrawManagerBase::~DrawManagerBase()
{
    vtable = clDrawMan_vtable_803FE068;
}

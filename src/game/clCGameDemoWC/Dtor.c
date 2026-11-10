#pragma cplusplus on
#include "game/clCGameDemoWC_Dtor_private.h"
extern "C" {
extern void SetActiveCamera(void *, int);
extern void TransparentDraw_RemoveByOwner(int);
extern void SetPlayerCarObject(void *);
extern void SetCourseScene3D(void *);
extern void Object_DtorWithGXSync(void *, int);
extern void VisualEffectHolder_Dtor(void *, int);
extern void KartDriver_Dtor(void *, int);
extern void ItemObjectManager_Reset(void);
extern void VfxSlotMgr_Shutdown(void);
extern void ClRomTable_PurgeAll(void);
extern void SceneDrawList_Reset(void);
extern void SetResourceLoadingFlag(int);
extern void clRom_PurgeAll(void);
extern void dtor_8002CDF4(void *, int);
extern void MemoryManager_TimedFree(void *);
extern DemoWCVirtual *lbl_806D10AC;
extern unsigned int DemoWCOwner_vtable_80419ED8[], lbl_80419F0C[];
}
/* Base teardown also accepts a null object when called independently. */
static inline void DemoWCBaseDestroy(DemoWCDtorView *self)
{
    if (self) {
        self->vptr = lbl_80419F0C;
        dtor_8002CDF4(self, 0);
    }
}
#pragma exceptions on
extern "C" DemoWCDtorView *clCGameDemoWC_Dtor(DemoWCDtorView *self, short destroy)
{
    if (self) {
        self->vptr = DemoWCOwner_vtable_80419ED8;
        SetActiveCamera(0, 0);
        if (self->owner >= 0) TransparentDraw_RemoveByOwner(self->owner);
        SetPlayerCarObject(0);
        SetCourseScene3D(0);
        if (self->camera) self->camera->Destroy(1);
        Object_DtorWithGXSync(self->object, 1);
        if (self->other) self->other->Destroy(1);
        VisualEffectHolder_Dtor(self->effects, 1);
        KartDriver_Dtor(self->driver, 1);
        ItemObjectManager_Reset();
        VfxSlotMgr_Shutdown();
        ClRomTable_PurgeAll();
        SceneDrawList_Reset();
        if (lbl_806D10AC) lbl_806D10AC->Destroy(1);
        lbl_806D10AC = 0;
        SetResourceLoadingFlag(0);
        clRom_PurgeAll();
        DemoWCBaseDestroy(self);
        if (destroy > 0) MemoryManager_TimedFree(self);
    }
    return self;
}
#pragma exceptions reset
#pragma cplusplus reset

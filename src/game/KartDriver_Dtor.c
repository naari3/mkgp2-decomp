#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * KartDriver destructor (0x80045950, 0x200). Releases the kart's scene
 * objects, effect slots and polymorphic helpers, unbinds the race slot and
 * frees the driver when called as a deleting destructor (flags > 0).
 * Compiled as C++ (the helpers are deleted through their virtual dtor).
 */
C_REGION_END
#pragma cplusplus on

class KartHelper {
public:
    virtual ~KartHelper();
};

#include "game/types/KartDriver.h"

extern "C" {
void *Archive_GetRootJObj(void *obj);
void ISESlot_Dtor(void *slot, int flags);
void KartTireFX_Dtor(void *fx, int flags);
void MemoryManager_TimedFree(void *p);
void Object_DtorWithGXSync(void *obj, int flags);
void RaceSlot_SetDriverPtr(void *slot, KartDriver *driver);
void SceneRender_CmdA_8a9e8(void *camera, void *jobj);
void dtor_80091284(void *obj, int flags);
void fn_80173CC4(void *obj, int flags);

extern void *g_raceCamera;
}

static inline void KartDriver_DetachModel(KartDriver *self)
{
    void *camera = g_raceCamera;
    if (camera != 0 && self->obj18 != 0) {
        SceneRender_CmdA_8a9e8(camera, Archive_GetRootJObj(self->obj18));
    }
}

#pragma exceptions on

extern "C" KartDriver *KartDriver_Dtor(KartDriver *self, short flags)
{
    int i;

    if (self != 0) {
        KartDriver_DetachModel(self);
        Object_DtorWithGXSync(self->lodFar, 1);
        Object_DtorWithGXSync(self->lodMid, 1);
        Object_DtorWithGXSync(self->model, 1);
        Object_DtorWithGXSync(self->driver, 1);
        Object_DtorWithGXSync(self->animation, 1);
        Object_DtorWithGXSync(self->other, 1);
        fn_80173CC4(self->driver_29C, 1);
        dtor_80091284(self->itemBus, 1);
        Object_DtorWithGXSync(self->obj18, 1);
        KartTireFX_Dtor(self->tireFX, 1);
        MemoryManager_TimedFree(self->a32C);
        Object_DtorWithGXSync(self->extra, 1);
        MemoryManager_TimedFree(self->tail);
        delete self->helper35C;
        delete self->helper360;
        delete self->helper378;
        delete self->helper380;
        for (i = 0; i < 10; i++) {
            ISESlot_Dtor(self->seSlots[i], 1);
        }
        for (i = 0; i < 49; i++) {
            Object_DtorWithGXSync(self->parts[i], 1);
        }
        Object_DtorWithGXSync(self->accessory, 1);
        self->accessory = 0;
        RaceSlot_SetDriverPtr(self->raceSlot, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset

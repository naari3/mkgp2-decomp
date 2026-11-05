/*
 * KartDriver destructor (0x80045950, 0x200). Releases the kart's scene
 * objects, effect slots and polymorphic helpers, unbinds the race slot and
 * frees the driver when called as a deleting destructor (flags > 0).
 * Compiled as C++ (the helpers are deleted through their virtual dtor).
 */
#pragma cplusplus on

class KartHelper {
public:
    virtual ~KartHelper();
};

typedef struct KartDriver {
    void *body;              /* 0x000 */
    void *shadow;            /* 0x004 */
    void *wheels;            /* 0x008 */
    void *obj0C;             /* 0x00C */
    void *obj10;             /* 0x010 */
    void *obj14;             /* 0x014 */
    void *model;             /* 0x018 */
    void *obj1C;             /* 0x01C */
    void *obj20;             /* 0x020 */
    void *parts[49];         /* 0x024 */
    char pad0E8[0x248 - 0x0E8];
    void *raceSlot;          /* 0x248 */
    char pad24C[0x29C - 0x24C];
    void *obj29C;            /* 0x29C */
    char pad2A0[0x2DC - 0x2A0];
    void *seSlots[10];       /* 0x2DC */
    void *obj304;            /* 0x304 */
    char pad308[0x30C - 0x308];
    void *tireFx;            /* 0x30C */
    char pad310[0x32C - 0x310];
    void *buf32C;            /* 0x32C */
    char pad330[0x344 - 0x330];
    void *buf344;            /* 0x344 */
    char pad348[0x35C - 0x348];
    KartHelper *helper35C;   /* 0x35C */
    KartHelper *helper360;   /* 0x360 */
    char pad364[0x378 - 0x364];
    KartHelper *helper378;   /* 0x378 */
    char pad37C[0x380 - 0x37C];
    KartHelper *helper380;   /* 0x380 */
} KartDriver;

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
    if (camera != 0 && self->model != 0) {
        SceneRender_CmdA_8a9e8(camera, Archive_GetRootJObj(self->model));
    }
}

#pragma exceptions on

extern "C" KartDriver *KartDriver_Dtor(KartDriver *self, short flags)
{
    int i;

    if (self != 0) {
        KartDriver_DetachModel(self);
        Object_DtorWithGXSync(self->wheels, 1);
        Object_DtorWithGXSync(self->shadow, 1);
        Object_DtorWithGXSync(self->body, 1);
        Object_DtorWithGXSync(self->obj0C, 1);
        Object_DtorWithGXSync(self->obj10, 1);
        Object_DtorWithGXSync(self->obj14, 1);
        fn_80173CC4(self->obj29C, 1);
        dtor_80091284(self->obj304, 1);
        Object_DtorWithGXSync(self->model, 1);
        KartTireFX_Dtor(self->tireFx, 1);
        MemoryManager_TimedFree(self->buf32C);
        Object_DtorWithGXSync(self->obj20, 1);
        MemoryManager_TimedFree(self->buf344);
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
        Object_DtorWithGXSync(self->obj1C, 1);
        self->obj1C = 0;
        RaceSlot_SetDriverPtr(self->raceSlot, 0);
        if (flags > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

#pragma exceptions reset

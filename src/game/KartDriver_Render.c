/* KartDriver_Render @ 0x80042350: draws a kart driver.
 *
 * Skips hidden karts, culls by squared camera distance and view frustum,
 * then picks the body LOD (full model, mid LOD at >= 200 units, far LOD at
 * >= 280 units once the race has started) and renders the driver/accessory
 * joint trees requested by the render pass mode.
 */
#include "game/types/Vec.h"

#include "game/ItemEffectBusPrivate.h"

#include "game/types/KartDriver.h"

extern void *GetCourseScene3D(void);
extern void CObj_LoadProjMatrix(void *scene, Vec *out);
extern void Object_GetJObjPositionVec(void *obj, Vec *out);
extern float PSVECSquareDistance(const Vec *a, const Vec *b);
extern unsigned char fn_801375D8(Vec *pos, float radius);
extern unsigned char IsRaceStarted(void);
extern void Object_RenderJObjTree(void *obj, int flags);
extern void KartTireFX_ApplyAndRender(void *fx);
extern void Object_BindMatrixSource(void *obj, void *source, int mode);
extern void Object_DriveAnimMatrix(void *obj);
extern void fn_80231D4C(void *obj);
extern void fn_80245700(void *obj);

static inline unsigned char KartDriver_IsHidden(KartDriver *self)
{
    return (self->itemBus->mask & 0x8000000000ULL) == 0 ? 0 : 1;
}

#pragma exceptions on
int KartDriver_Render(KartDriver *self, int mode)
{
    Vec pos;
    Vec camPos;
    float dist;

    if (self->forceDraw == 0 && KartDriver_IsHidden(self) == 1) {
        return 1;
    }
    if (self->visible == 0) {
        return 0;
    }
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }

    CObj_LoadProjMatrix(GetCourseScene3D(), &camPos);
    Object_GetJObjPositionVec(self->model, &pos);
    dist = PSVECSquareDistance(&pos, &camPos);
    if (dist >= 2560000.0f) {
        return 1;
    }
    if (!fn_801375D8(&pos, 11.0f)) {
        return 1;
    }

    if (!IsRaceStarted()) {
        if (mode == 0 || mode == 1 || mode == 4) {
            Object_RenderJObjTree(self->model, 7);
            if (self->tireFX != 0) {
                KartTireFX_ApplyAndRender(self->tireFX);
            }
        }
    } else if (self->lodFar != 0 && dist >= 78400.0f) {
        if (mode == 0 || mode == 1 || mode == 4) {
            Object_BindMatrixSource(self->lodFar, self->matrixSource, 0);
            Object_DriveAnimMatrix(self->lodFar);
            Object_RenderJObjTree(self->lodFar, 7);
        }
    } else if (self->lodMid != 0 && dist >= 40000.0f) {
        if (mode == 0 || mode == 1 || mode == 4) {
            Object_BindMatrixSource(self->lodMid, self->matrixSource, 0);
            Object_DriveAnimMatrix(self->lodMid);
            Object_RenderJObjTree(self->lodMid, 7);
        }
    } else {
        if (mode == 0 || mode == 1 || mode == 4) {
            Object_RenderJObjTree(self->model, 7);
        }
        if (mode == 0 || mode == 2) {
            if (self->tireFX != 0) {
                KartTireFX_ApplyAndRender(self->tireFX);
            }
        }
    }

    if (mode == 0 || mode == 1 || mode == 3) {
        Object_RenderJObjTree(self->driver, 7);
        if (self->accessory != 0 && self->showAccessory != 0) {
            Object_RenderJObjTree(self->accessory, 7);
        }
        if (self->extraEnabled != 0 && self->extra != 0) {
            Object_RenderJObjTree(self->extra, 7);
        }
        if (self->helper35C != 0) {
            fn_80231D4C(self->helper35C);
        }
        if (self->helper360 != 0) {
            fn_80245700(self->helper360);
        }
    }
    return 1;
}
#pragma exceptions reset

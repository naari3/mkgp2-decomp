/* Set the Y rotation of the four wheel/steering joints (0xe8, 0xec, 0x164,
 * 0x16c); the last one is mirrored (negated angle). */
#include "game/types/HSD_JObj.h"

#include "game/types/KartDriver.h"

extern char lbl_806D2548[7]; /* "jobj.h" */
extern char lbl_806D2550[5]; /* "jobj" */
extern char KartDriver_InitFull_rodata_802EADBC[];  /* "!(jobj->flags & JOBJ_USE_QUATERNION)" */
extern void __assert(const char *file, int line, const char *cond);
extern void HSD_JObjSetMtxDirtySub(HSD_JObj *jobj);

static inline int HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;
    if (!jobj) {
        __assert(lbl_806D2548, 0x25d, lbl_806D2550);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetRotationY(HSD_JObj *jobj, float y)
{
    if (!jobj) {
        __assert(lbl_806D2548, 0x2b8, lbl_806D2550);
    }
    if (jobj->flags & 0x20000) {
        __assert(lbl_806D2548, 0x2b9, KartDriver_InitFull_rodata_802EADBC);
    }
    jobj->rotate.y = y;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

#pragma exceptions on
int KartDriver_SetEulerY_4Joints_LastMirrored(KartDriver *self, float y)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->wheel[0] != 0) {
        HSD_JObjSetRotationY(self->wheel[0], y);
    }
    if (self->wheel[1] != 0) {
        HSD_JObjSetRotationY(self->wheel[1], y);
    }
    if (self->joint164 != 0) {
        HSD_JObjSetRotationY(self->joint164, y);
    }
    if (self->joint16C != 0) {
        HSD_JObjSetRotationY(self->joint16C, -y);
    }
    return 1;
}
#pragma exceptions reset

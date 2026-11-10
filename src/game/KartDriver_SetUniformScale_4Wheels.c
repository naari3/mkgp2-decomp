/* Set the same uniform scale on the four wheel joints (0xe8..0xf4). */
#include "game/types/HSD_JObj.h"

#include "game/types/KartDriver.h"

extern char lbl_806D2548[7]; /* "jobj.h" */
extern char lbl_806D2550[5]; /* "jobj" */
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

static inline void HSD_JObjSetScaleUniform(HSD_JObj *jobj, float s)
{
    if (!jobj) {
        __assert(lbl_806D2548, 0x316, lbl_806D2550);
    }
    jobj->scale.x = s;
    jobj->scale.y = s;
    jobj->scale.z = s;
    if (!(jobj->flags & 0x02000000)) {
        if (jobj != 0 && !HSD_JObjMtxIsDirty(jobj)) {
            HSD_JObjSetMtxDirtySub(jobj);
        }
    }
}

int KartDriver_SetUniformScale_4Wheels(KartDriver *self, float s)
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    if (self->wheel[0] != 0) {
        HSD_JObjSetScaleUniform(self->wheel[0], s);
    }
    if (self->wheel[1] != 0) {
        HSD_JObjSetScaleUniform(self->wheel[1], s);
    }
    if (self->wheel[2] != 0) {
        HSD_JObjSetScaleUniform(self->wheel[2], s);
    }
    if (self->wheel[3] != 0) {
        HSD_JObjSetScaleUniform(self->wheel[3], s);
    }
    return 1;
}

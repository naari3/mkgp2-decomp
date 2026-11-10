/* World position of a kart joint (-1 = the kart root). */
#include "game/types/KartDriver.h"

typedef float Mtx[3][4];

extern float (*Object_GetJObjLocalMatrix(void *model))[4];
extern float (*KartDriver_GetJointByIdx(KartDriver *self, int idx))[4];

static inline float (*KartDriver_GetRootMtx(KartDriver *self))[4]
{
    if (self->model == 0 || self->driver == 0) {
        return 0;
    }
    return Object_GetJObjLocalMatrix(self->model);
}

void KartDriver_GetJointPosition(KartDriver *self, int idx, float *out)
{
    float (*mtx)[4];

    if (idx == -1) {
        mtx = KartDriver_GetRootMtx(self);
    } else {
        mtx = KartDriver_GetJointByIdx(self, idx);
    }
    out[0] = mtx[0][3];
    out[1] = mtx[1][3];
    out[2] = mtx[2][3];
}

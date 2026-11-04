#include "../src/game/mapeffect/mapfx16a_private.h"
extern "C" void fn_8016A654(Jungle16A *self) {
    Vec3f view;
    for (int i=0; i<2; ++i) {
        if (self->motions[i].state != 2 && fn_80137718(&self->motions[i].pos, &view, lbl_806D8A40)) {
            HSD_JObjReqAnimAll(self->motions[i].joint, self->motions[i].frame);
            HSD_JObjAnimAll(self->motions[i].joint);
            Translate16A(self->motions[i].joint, &self->motions[i].pos);
            Rotate16A(self->motions[i].joint, self->motions[i].rot);
            Object_RenderJObjEx(self->model, self->motions[i].joint, 7);
        }
    }
}

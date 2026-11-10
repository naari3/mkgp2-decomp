#pragma cplusplus on
#include "game/JyugemuReverseFlagTickPrivate.h"
#pragma exceptions on
/* Add the animated vertical displacement to the kart-relative height. */
static inline float FlagHeight(float y, float bob) { return y + bob; }
extern "C" int Jyugemu_ReverseFlag_Tick(ReverseFlag *self) {
    float bob;
    float (*matrix)[4];
    void *camera;
    Vec3 target, eye, direction;
    if (!self->object) return 0;
    if (!self->driver) return 0;
    if (!Jyugemu_ReverseFlag_data_806CEFC0[0]) return 0;
    if (self->state == 1) {
        if (self->phase > lbl_806D307C) {
            float phase = self->phase - lbl_806D3080;
            self->phase = phase;
            if (phase < lbl_806D307C) self->phase = lbl_806D307C;
        }
    } else {
        if (self->phase < lbl_806D3078) {
            float phase = self->phase + lbl_806D3084;
            self->phase = phase;
            if (phase > lbl_806D3078) self->phase = lbl_806D3078;
        }
    }
    bob = lbl_806D3088 * (float)sin(self->phase);
    matrix = KartDriver_GetKartRootMtx(self->driver);
    SetX(Archive_GetRootJObj(self->object), matrix[0][3]);
    SetY(Archive_GetRootJObj(self->object), FlagHeight(lbl_806D309C + matrix[1][3], bob));
    SetZ(Archive_GetRootJObj(self->object), matrix[2][3]);
    camera = GetCourseScene3D();
    if (camera) {
        CObj_LoadProjMatrix(camera, &eye);
        CObj_ApplyScissor(camera, &target);
        Vec3_Subtract(&target, &eye, &direction);
        direction.y = lbl_806D307C;
        Vec3_Normalize(&direction, &direction);
        RotateY(Archive_GetRootJObj(self->object), lbl_806D30A0 + (float)atan2(direction.x, direction.z));
    }
    clNormal3D_Exec(self->object);
    Object_DriveAnimMatrix(self->object);
    return 1;
}
#pragma exceptions reset
#pragma cplusplus reset

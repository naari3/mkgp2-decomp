#include "game/KartItemRearTargetPrivate.h"

extern "C" const float lbl_806D2F4C, lbl_806D2F50, lbl_806D2F54;

static inline unsigned char HasRearTargetFlag(RearTargetFlags *flags, unsigned long long mask) {
    if ((flags->bits & mask) == 0) return 0;
    return 1;
}

extern "C" int KartItem_FindRearTarget_v2(RearTargetOwner *self, RearTargetKart *target, RearTargetResult *result) {
    Vec3 right, forward, delta;
    float *matrix;
    float dot;
    if (!target) return 0;
    if (target == self->kart) return 0;
    unsigned char hidden = HasRearTargetFlag(target->flags, 0x80ULL);
    if (hidden) return 0;
    if ((target->flags->bits & 0x8000000000ULL) != 0) return 0;
    result->kart = target;
    matrix = KartDriver_GetKartRootMtx(self->kart);
    KartDriver_GetJointPosition(target, -1, &delta);
    if ((float)__fabs(delta.y - matrix[7]) > lbl_806D2F4C) return 0;
    delta.x -= matrix[3];
    delta.y = lbl_806D2F40;
    delta.z -= matrix[11];
    result->distance = Vec3_Magnitude(&delta);
    if (result->distance > lbl_806D2F50) return 0;
    right.x = matrix[0]; right.y = lbl_806D2F40; right.z = matrix[8];
    forward.x = matrix[2]; forward.y = lbl_806D2F40; forward.z = matrix[10];
    Vec3_Normalize(&delta, &delta);
    Vec3_Normalize(&right, &right);
    Vec3_Normalize(&forward, &forward);
    dot = Vec3_Dot(&right, &delta);
    if (Vec3_Dot(&forward, &delta) < lbl_806D2F40 && (float)__fabs(dot) < lbl_806D2F54) return 1;
    if ((float)__fabs(dot) < lbl_806D2F48) result->side = 0;
    else if (dot < lbl_806D2F40) result->side = 2;
    else result->side = 1;
    return 1;
}

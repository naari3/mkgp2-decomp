#include "game/clsound_spatial_private.h"
int fn_80192F04(unsigned int id, const ClSoundVec* position, unsigned char* volume, unsigned char* pan, unsigned char* surround) {
    ClSoundListener* listener = &lbl_80495F20;
    ClSoundVec delta;
    float near_distance, far_distance, distance;
    if (!ClSound_Initialized) return 0;
    if (!position) return 0;
    id &= ~0x78000000;
    if (id >= 490) return 0;
    near_distance = lbl_80379554[id].near_distance;
    far_distance = lbl_80379554[id].far_distance;
    Vec3_Subtract(position, &listener->position, &delta);
    distance = Vec3_Magnitude(&delta);
    if (distance >= far_distance) {
        if (volume) *volume = 0;
        if (pan) *pan = 64;
        if (surround) *surround = 64;
    } else {
        if (volume) {
            if (distance <= near_distance) *volume = 127;
            else *volume = (int)(lbl_806D9514 - lbl_806D9514 * ((distance-near_distance)/(far_distance-near_distance)));
        }
        if (pan) {
            distance = Vec3_Dot(&delta, &listener->right);
            if (distance >= near_distance) *pan = 0;
            else if (distance <= -near_distance) *pan = 127;
            else *pan = (int)(lbl_806D9518 - lbl_806D951C*(distance/near_distance));
        }
        if (surround) {
            distance = Vec3_Dot(&delta, &listener->forward);
            if (distance >= near_distance) *surround = 127;
            else if (distance <= -near_distance) *surround = 0;
            else *surround = (int)(lbl_806D9518 + lbl_806D951C*(distance/near_distance));
        }
    }
    return 1;
}

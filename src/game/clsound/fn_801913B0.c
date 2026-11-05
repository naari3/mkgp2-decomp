#include "game/clsound_spatial_private.h"
int fn_801913B0(int index, const ClSoundVec* position) {
    ClSoundListener* listener = &lbl_80495F20;
    ClSoundVec delta;
    float near_distance, far_distance, distance;
    int volume, pan, surround;
    near_distance = lbl_80379554[lbl_80678378[index].id & ~0x78000000].near_distance;
    far_distance = lbl_80379554[lbl_80678378[index].id & ~0x78000000].far_distance;
    Vec3_Subtract(position, &listener->position, &delta);
    distance = Vec3_Magnitude(&delta);
    if (distance >= far_distance) { volume=0; pan=64; surround=64; }
    else {
        if (distance <= near_distance) volume=127;
        else volume=(int)(lbl_806D9514-lbl_806D9514*((distance-near_distance)/(far_distance-near_distance)));
        distance=Vec3_Dot(&delta, &listener->right);
        if (distance >= near_distance) pan=0;
        else if (distance <= -near_distance) pan=127;
        else pan=(int)(lbl_806D9518-lbl_806D951C*(distance/near_distance));
        distance=Vec3_Dot(&delta, &listener->forward);
        if (distance >= near_distance) surround=127;
        else if (distance <= -near_distance) surround=0;
        else surround=(int)(lbl_806D9518+lbl_806D951C*(distance/near_distance));
    }
    if ((unsigned char)volume != lbl_80678378[index].volume) { lbl_80678378[index].volume=volume; lbl_80678378[index].flags |= 0x10; }
    if ((unsigned char)pan != lbl_80678378[index].pan) { lbl_80678378[index].pan=pan; lbl_80678378[index].flags |= 0x20; }
    if ((unsigned char)surround != lbl_80678378[index].surround) { lbl_80678378[index].surround=surround; lbl_80678378[index].flags |= 0x40; }
    return 1;
}

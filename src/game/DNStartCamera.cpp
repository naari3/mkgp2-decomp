#include "game/DNStartCameraPrivate.h"

void clDNStartCamera::Draw() {
    Mtx m;

    if (hidden == 1) {
        return;
    }
    Object_RenderJObjTree(cam, 7);
    GXChannel ch(Archive_GetRootJObj(flash), HSD_JObjGetDObj(Archive_GetRootJObj(flash)), 0x40000000, 1);
    for (int i = 0; i < 6; i++) {
        if (flashes[i].fp.active) {
            PSMTXScale(m, flashes[i].fp.scale, flashes[i].fp.scale, flashes[i].fp.scale);
            m[0][3] = flashes[i].fp.owner->pos.x;
            m[1][3] = flashes[i].fp.owner->pos.y;
            m[2][3] = flashes[i].fp.owner->pos.z;
            Object_SetColorAlphaOnly(flash, 0, flashes[i].fp.alpha);
            ch.PushTransform(m);
        }
    }
}

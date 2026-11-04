#include "game/DNFlash_private.h"

void clDNFlash::Draw() {
    Mtx m;

    if (fx == 0) {
        return;
    }
    GXChannel ch(Archive_GetRootJObj(fx), HSD_JObjGetDObj(Archive_GetRootJObj(fx)), 0x40000000, 1);
    for (int i = 0; i < 20; i++) {
        if (parts[i].active && parts[i].owner) {
            PSMTXScale(m, parts[i].scale, parts[i].scale, parts[i].scale);
            m[0][3] = parts[i].owner->pos.x;
            m[1][3] = parts[i].owner->pos.y;
            m[2][3] = parts[i].owner->pos.z;
            Object_SetColorAlphaOnly(fx, 0, parts[i].alpha);
            ch.PushTransform(m);
        }
    }
}

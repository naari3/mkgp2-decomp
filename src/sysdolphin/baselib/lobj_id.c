#include "lobj_private.h"

extern char lbl_806D0D20[7];
extern char lbl_806D0D28[2];
u32 HSD_LightID2Index(GXLightID id)
{
    u32 index;
    switch (id) {
    case GX_LIGHT0:
        index = 0;
        break;
    case GX_LIGHT1:
        index = 1;
        break;
    case GX_LIGHT2:
        index = 2;
        break;
    case GX_LIGHT3:
        index = 3;
        break;
    case GX_LIGHT4:
        index = 4;
        break;
    case GX_LIGHT5:
        index = 5;
        break;
    case GX_LIGHT6:
        index = 6;
        break;
    case GX_LIGHT7:
        index = 7;
        break;
    case GX_MAX_LIGHT:
        index = 8;
        break;
    default:
        __assert(lbl_806D0D20, 1192, lbl_806D0D28);
        break;
    }
    return index;
}

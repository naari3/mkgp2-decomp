#include "../src/game/mapeffect/mapfx16a_private.h"
Jungle16A::Jungle16A() {
    const Desc16A *d = (const Desc16A *)lbl_8036CA00;
    DebugPrintf((const char *)d + 0x544);
    model = new clNormal3D(lbl_806CFA00, 0);
    clNormal3D_SetScale(model, 0, lbl_806D8A68, lbl_806D8A54, lbl_806D8A68, lbl_806D8A68);
    zone = new Zone16A((const char *)d + 0x40c, 1);
    motions = (Motion16A *)FUN_8003b120(0x40);
    d = (const Desc16A *)((const char *)d + 0x488);
    for (int i=0; i<2; ++i, ++d) {
        motions[i].joint = ResolveJointByName(model, d->name);
        motions[i].pos = d->start;
        motions[i].rot = d->rot;
        motions[i].state = 0;
        motions[i].unused = lbl_806D8A68;
        motions[i].frame = lbl_806D8A68;
    }
}

#include "game/mapobject/mapobject.h"

void clModelM::Draw() {
    Vec3f p;
    Vec3f view;
    if (jobj == 0) {
        return;
    }
    if (def->flags & 2) {
        if (def->flags & 1) {
            HSD_JObjReqAnimAll(jobj, frame);
            fn_802CF244(jobj);
        }
        HSD_JObjSetTranslate(jobj, &pos);
        HSD_JObjSetRotationY(jobj, heading);
        fn_802CF3B0(jobj, 0, 7, 0);
        return;
    }
    p = pos;
    PSVECAdd(&p, &offset, &p);
    if (fn_80137718(&p, &view, def->height)) {
        if ((def->flags & 1) && view.z > def->height * lbl_806D15F0) {
            HSD_JObjReqAnimAll(jobj, frame);
            fn_802CF244(jobj);
        }
        HSD_JObjSetTranslate(jobj, &pos);
        HSD_JObjSetRotationY(jobj, heading);
        fn_802CF3B0(jobj, 0, 7, 0);
    }
}

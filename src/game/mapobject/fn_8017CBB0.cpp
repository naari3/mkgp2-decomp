#include "game/mapobject/mapobject.h"

void clModelP::Draw() {
    Vec3f pos;
    Vec3f view;
    if (jobj == 0) {
        return;
    }
    if (def->flags & 2) {
        if (def->flags & 1) {
            HSD_JObjReqAnimAll(jobj, frame);
            HSD_JObjAnimAll(jobj);
        }
        HSD_JObjSetTranslate(jobj, param);
        HSD_JObjDispAll(jobj, 0, 7, 0);
        return;
    }
    pos = *param;
    PSVECAdd(&pos, &offset, &pos);
    if (fn_80137718(&pos, &view, def->height)) {
        if ((def->flags & 1) && view.z > def->height * lbl_806D15F0) {
            HSD_JObjReqAnimAll(jobj, frame);
            HSD_JObjAnimAll(jobj);
        }
        HSD_JObjSetTranslate(jobj, param);
        HSD_JObjDispAll(jobj, 0, 7, 0);
    }
}

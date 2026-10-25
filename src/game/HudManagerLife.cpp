/*
 * HUD manager: speed gauge feed and destructor @ 0x80253FD8..0x8025421C.
 */

#include "game/HudManager.h"

extern "C" {
extern const float lbl_806DC1C8;
extern const float lbl_806DC1CC;
extern const float lbl_806DC1D0;
extern const float lbl_806DC1D4;
extern const float lbl_806DC1D8;
extern char lbl_806D0A38[8];
extern char s_clCDispInterface[8];
void *fn_80271340(void *p, int offset, void *from, void *to, int rethrow);
void fn_802524A0(void *gauge, float v);
void fn_8020ED30(FlowSceneList *list);
void fn_80121210(void);
}

void HudManager::SetSpeed(float v) {
    if (parts[6]) {
        fn_802524A0(fn_80271340(parts[6], 0, lbl_806D0A38, s_clCDispInterface, 0), v);
    }
    field70 = v;
    if (field70 <= lbl_806DC1C8 && field70 > lbl_806DC1CC && field08 < 0) {
        field08 = 1;
    }
    if (field70 <= lbl_806DC1D0 && field70 > lbl_806DC1C8 && field08 < 1) {
        field08 = 2;
    }
    if (field70 <= lbl_806DC1D4 && field70 > lbl_806DC1D0 && field08 < 2) {
        field08 = 3;
    }
    if (field70 <= lbl_806DC1D8 && field70 > lbl_806DC1D4 && field08 < 3) {
        field08 = 4;
    }
    if (field70 > lbl_806DC1D8 && field08 < 4) {
        field08 = 5;
    }
}

HudManager::~HudManager() {
    if (list.p->entries.count > 0) {
        fn_8020ED30(list.p);
    }
    for (int i = 22; i >= 0; i--) {
        if (parts[i]) {
            delete parts[i];
            parts[i] = 0;
        }
    }
    fn_80121210();
}

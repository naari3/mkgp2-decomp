/*
 * HUD manager: forward the lap scale to the slot 5 part @ 0x80253EC4..0x80253F2C.
 */

#include "game/HudManager.h"

extern "C" {
extern char lbl_806D0A48[8];
extern char s_clCDispInterface[8];
void *fn_80271340(void *p, int offset, void *from, void *to, int rethrow);
void fn_80246988(void *part, int lap, float v);
}

void HudManager::SetLapScale(float v) {
    field78 = v;
    if (parts[5]) {
        fn_80246988(fn_80271340(parts[5], 0, lbl_806D0A48, s_clCDispInterface, 0), field6C - 1, v);
    }
}

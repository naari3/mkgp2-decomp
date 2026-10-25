/*
 * HUD manager: forward a value to the clCDispInterface part (slot 8)
 * @ 0x80253E18..0x80253E68.
 */

#include "game/HudManager.h"

extern "C" {
extern char lbl_806D0A58[8];
extern char s_clCDispInterface[8];
void *fn_80271340(void *p, int offset, void *from, void *to, int rethrow);
void fn_80215D8C(void *disp, int value);
}

extern "C" void fn_80253E18(HudManager *self, int value) {
    if (self->parts[8]) {
        fn_80215D8C(fn_80271340(self->parts[8], 0, lbl_806D0A58, s_clCDispInterface, 0), value);
    }
}

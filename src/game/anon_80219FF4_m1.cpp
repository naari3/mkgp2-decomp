#include "game/FlashFx_rescue.h"

extern "C" FlashFx *fn_8021A354(void) {
    if (lbl_806D1A60 == 0) {
        lbl_806D1A60 = new FlashFx;
    }
    return lbl_806D1A60;
}

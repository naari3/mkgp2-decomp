/* acLib reset handling. */
#include "game/acLib_private.h"

extern "C" int fn_80255000(void) {
    ResetState *rs = fn_8028D6B0();
    int reset = 0;
    unsigned int error;
    switch (rs->kind) {
    case 2:
    case 3:
        reset = 1;
        error = 0;
        break;
    default:
        if (rs->error != 0) {
            reset = 1;
            error = rs->error;
        }
        break;
    }
    if (reset) {
        char info[0x30];
        char msg[0x50];
        if (acLib_tail_bss_80679E28.onReset != 0 && acLib_tail_bss_80679E28.onReset(error) == 0) {
            return 0;
        }
        sprintf(msg, lbl_803F13E4, rs->error);
        OSReport(msg);
        memset(info, 0, sizeof(info));
        if (rs->kind == 3) {
            fn_80286A74(info, 1);
        } else {
            fn_80286A74(info, 0);
        }
        fn_802947CC();
        fn_80286774();
        GXAbortFrame();
        VISetBlack(1);
        VIFlush();
        VIWaitForRetrace();
        if (rs->kind == 3) {
            OSResetSystem(0, 0, 0);
        } else {
            OSResetSystem(0, 0, 0);
        }
    }
    return 0;
}

#include <triforce/amnet_priv.h>

u32 fn_8028D870(void) {
    u32 ret = 8;
    if (lbl_80699140.numDev != 0 && FindDev(0x29) != NULL) {
        ret = (u8)(lbl_80699140.hwFlags & 7);
    }
    return ret;
}

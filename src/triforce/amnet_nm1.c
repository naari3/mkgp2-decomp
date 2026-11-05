#include <triforce/amnet_priv.h>

s32 fn_8028D750(s32 mask, u8 kind, u8* out) {
    u32 want = (mask | 1) & 0x7FFFFFFF;
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < lbl_80699140.numDev; i++) {
        if (rev) {
            dev = &lbl_80699140.dev[lbl_80699140.numDev - 1 - i];
        } else {
            dev = &lbl_80699140.dev[i];
        }
        if (dev->kind == kind && want == (want & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

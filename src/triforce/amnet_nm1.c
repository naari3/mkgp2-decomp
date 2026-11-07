#include <triforce/amnet_priv.h>

/* Wanted flag bits: bit 0 always, the sign bit selects reverse search. */
#define NET_WANT(m) (((m) | 1) & 0x7FFFFFFF)

s32 fn_8028D750(s32 mask, u8 kind, u8* out) {
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < lbl_80699140.numDev; i++) {
        if (rev) {
            dev = &lbl_80699140.dev[lbl_80699140.numDev - 1 - i];
        } else {
            dev = &lbl_80699140.dev[i];
        }
        if (dev->kind == kind && NET_WANT(mask) == (NET_WANT(mask) & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

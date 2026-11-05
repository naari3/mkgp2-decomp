#include "triforce/acsocket_private.h"

s32 fn_80292AD8(u8* src, u32 off, s32 len, s32 tx, s32 rx) {
    s32 mis;
    u32 dev;
    u32 size;
    u8* p;
    u32 al;

    if (tx) {
        mis = 0;
        if ((u32)src & 0x1F || off & 0x1F) {
            mis = 1;
        }
        p = src;
        if (mis) {
            p = TxBounce;
        }
        al = off & ~0x1F;
        dev = State.txOff + al;
        size = ((off + (len + 0x1F)) & ~0x1F) - al;
        if ((mis && size > 0x4000) || CheckRange(off, len, State.txSize)) {
            return -1;
        }
        if (mis) {
            memcpy(p + (off & 0x1F), src, len);
        }
        fn_8028D530(p, dev, size);
    } else {
        return -1;
    }
    return len;
}

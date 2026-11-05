#include "triforce/acsocket_private.h"

s32 fn_80292BFC(u32 off, u8* dst, s32 len) {
    s32 tx;
    s32 rx;
    s32 total = 0;
    s32 n;
    s32 r;

    GetAlign(&tx, &rx);
    while (len > 0) {
        n = len;
        if (tx) {
            if (((u32)dst & 0x1F || off & 0x1F) && ((off + len + 0x1F) & ~0x1F) - (off & ~0x1F) > 0x4000) {
                n = 0x4000 - (off & 0x1F);
            }
        } else if (((u32)dst & 0x1F || off & 0x1F) && ((off + len + 1) & ~1) - (off & ~1) > 0x4000) {
            n = 0x4000 - (off & 1);
        }
        r = fn_80292D18(off, dst, n, tx, rx);
        if (r == -1) {
            break;
        }
        total += r;
        off += r;
        dst += r;
        len -= r;
    }
    return total;
}

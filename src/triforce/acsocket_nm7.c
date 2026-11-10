#include "triforce/acsocket_private.h"

static inline u8* ReceiveBuffer(u8* dst, u32 off, s32 mis, u32* al) {
    u8* p = dst;
    *al = off & ~0x1F;
    if (mis) {
        p = RxBounce;
    }
    return p;
}

s32 fn_80292D18(u32 off, u8* dst, s32 len, s32 tx, s32 rx) {
    s32 mis;
    u8* p;
    u32 al;
    u32 dev;
    u32 size;
    u32 end;

    if (tx) {
        mis = 0;
        if ((u32)dst & 0x1F || off & 0x1F) {
            mis = 1;
        }
        p = (u8*)(void*)ReceiveBuffer(dst, off, mis, &al);
        dev = State.rxOff + al;
        end = (u32)len + 0x1F;
        end = off + end;
        size = (end & ~0x1F) - al;
        if ((mis && size > 0x4000) || CheckRange(off, len, State.rxSize)) {
            return -1;
        }
        fn_8028D5E8(dev, p, size);
        if (mis) {
            memcpy(dst, p + (off & 0x1F), len);
        }
    } else {
        return -1;
    }
    return len;
}

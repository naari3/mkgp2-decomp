#include "triforce/acsocket_private.h"

void fn_80291C7C(AcSock* k, void* rd, u32* rdOff, void* wr, u32* wrOff, void* ex, u32* exOff,
                 void* tv, u32* tvOff) {
    s32 n = 0;

    if (rd != NULL) {
        *rdOff = k->bufAddr + State.bufOff;
        memcpy(Buf, rd, 0x20);
        n = 0x20;
    } else {
        *rdOff = 0;
    }
    if (wr != NULL) {
        *wrOff = k->bufAddr + (State.bufOff + n);
        memcpy(Buf + n, wr, 0x20);
        n += 0x20;
    } else {
        *wrOff = 0;
    }
    if (ex != NULL) {
        *exOff = k->bufAddr + (State.bufOff + n);
        memcpy(Buf + n, ex, 0x20);
        n += 0x20;
    } else {
        *exOff = 0;
    }
    if (tv != NULL) {
        *tvOff = k->bufAddr + (State.bufOff + n);
        memcpy(Buf + n, tv, 8);
        n += 8;
    } else {
        *tvOff = 0;
    }
    if (n > 0) {
        fn_8028D530(Buf, k->bufAddr + State.bufOff, (n + 0x1F) & ~0x1F);
    }
}

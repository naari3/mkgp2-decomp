#include "triforce/acsocket_private.h"

static inline u8* ClearConnectBuffer(AcSock* k, u32* off) {
    u32 base = k->bufAddr;
    u8* buf = BufPtr(0);
    *off = base + State.bufOff;
    memset(buf, 0, 0x40);
    return buf;
}

s32 acConnect(s32 s, const void* addr, s32 len) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);
    u32 off;
    u8* buf;

    if (addr == NULL || len > 0x40) {
        return -4;
    }
    if (k->ready == 0) {
        return -2;
    }
    sem = &State.sem;
    OSWaitSemaphore(sem);
    k->ready = 0;
    k->id = 0;
    k->result = 0;
    memset(&k->addrOff, 0, 0x10);
    OSSignalSemaphore(sem);
    buf = ClearConnectBuffer(k, &off);
    memcpy(buf, addr, len);
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 4;
    k->id = fn_80290400(8, s, State.devBase + off, len);
    if (k->id == 0) {
        k->result = -2;
        OSWaitSemaphore(sem);
        k->ready = 1;
        OSSignalSemaphore(sem);
        return k->result;
    }
    return 0;
}

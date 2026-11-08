#include "triforce/acsocket_private.h"

static inline u8* GetSocketBuffer(s32 n, u32* off) {
    *off = State.bufOff + n;
    return BufPtr(n);
}

static inline u8* ClearBindBuffer(AcSock* k, u32* off) {
    u8* buf = GetSocketBuffer(0, off);
    *off += k->bufAddr;
    memset(buf, 0, 0x40);
    return buf;
}

s32 acBind(s32 s, const void* addr, s32 len) {
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
    buf = ClearBindBuffer(k, &off);
    memcpy(buf, addr, len);
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 2;
    k->result = fn_80290644(s, State.devBase + off, len);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

static inline s32 Accept(s32 s, void* addr, u32* len) {
    u32 lenOff;
    u32 addrOff;
    AcSock* k = SOCK(s);
    OSSemaphore* sem;
    u32 v;
    u8* b;

    if ((addr == NULL || len == NULL) && (addr != NULL || len != NULL)) {
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
    if (addr == NULL) {
        addrOff = 0;
        lenOff = 0;
    } else {
        v = *len;
        b = (u8*)k->bufAddr;
        lenOff = (u32)(b + State.bufOff);
        *(u32*)Buf = BSWAP32(v);
        addrOff = (u32)((b + 4) + State.bufOff);
        memset(Buf + 4, 0, 0x40);
        fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x60);
    }
    k->addrOff = addrOff;
    k->addr = addr;
    k->lenOff = lenOff;
    k->len = len;
    k->cmd = 1;
    k->id = fn_80290810(8, s, State.devBase + addrOff, State.devBase + lenOff);
    if (k->id == 0) {
        k->result = -2;
        OSWaitSemaphore(sem);
        k->ready = 1;
        OSSignalSemaphore(sem);
        return k->result;
    }
    return 0;
}

s32 acAccept(s32 s, void* addr, u32* len) {
    return Accept(s, addr, len);
}

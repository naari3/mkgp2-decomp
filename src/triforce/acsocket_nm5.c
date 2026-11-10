#include "triforce/acsocket_private.h"

static inline u8* GetSocketBuffer(s32 n, u8** off) {
    *off = (u8*)State.bufOff + n;
    return BufPtr(n);
}

/* Clear CPU staging storage and return its board-side byte address. */
static inline u8* ClearBindBuffer(AcSock* k, u8** buf) {
    u32 base = k->bufAddr;
    u8* off;
    *buf = GetSocketBuffer(0, &off);
    off += base;
    memset(*buf, 0, 0x40);
    return off;
}

s32 acBind(s32 s, const void* addr, s32 len) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);
    u8* off;
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
    off = ClearBindBuffer(k, &buf);
    memcpy(buf, addr, len);
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 2;
    k->result = fn_80290644(s, State.devBase + (u32)off, len);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

static inline s32 Accept(s32 s, void* addr, u32* len, u32* lenOut, u32* addrOut) {
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
        (*addrOut) = 0;
        (*lenOut) = 0;
    } else {
        v = *len;
        b = (u8*)k->bufAddr;
        (*lenOut) = (u32)(b + State.bufOff);
        *(u32*)Buf = BSWAP32(v);
        (*addrOut) = (u32)((b + 4) + State.bufOff);
        memset(Buf + 4, 0, 0x40);
        fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x60);
    }
    k->addrOff = (*addrOut);
    k->addr = addr;
    k->lenOff = (*lenOut);
    k->len = len;
    k->cmd = 1;
    k->id = fn_80290810(8, s, State.devBase + (*addrOut), State.devBase + (*lenOut));
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
    u32 addrOff;
    u32 lenOff;
    return Accept(s, addr, len, &lenOff, &addrOff);
}

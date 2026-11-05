#include "triforce/acsocket_private.h"

static inline u8* GetIPBuffer(s32 n, u32* off) {
    *off = State.bufOff + n;
    return Buf + n;
}

s32 acModifyMyIPaddr(const char* ip, s32 mask) {
    OSSemaphore* sem;
    AcSock* k = &State.sock[0];
    u32 off;
    u8* buf;

    if (ip == NULL) {
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
    buf = GetIPBuffer(0, &off);
    off = k->bufAddr + off;
    memset(buf, 0, 0x40);
    memcpy(buf, ip, strlen(ip));
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 21;
    k->result = fn_8028FCF0(State.devBase + off, strlen(ip), mask);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

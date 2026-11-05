#include "triforce/acsocket_private.h"

static inline u8* ClearInetBuf(void) {
    u8* buf = BufPtr(0);
    memset(buf, 0, 0x40);
    return buf;
}

s32 acInetAddr(const char* str) {
    OSSemaphore* sem;
    AcSock* k = &State.sock[0];
    u32 off;
    u8* buf;

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
    off = BufDev(k, 0);
    buf = ClearInetBuf();
    memcpy(buf, str, strlen(str));
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 6;
    k->result = fn_80290060(State.devBase + off, strlen(str));
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

#include "triforce/acsocket_private.h"

s32 acInetAddr(const char* str) {
    OSSemaphore* sem;
    AcSock* k = &State.sock[0];
    u32 off;

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
    memset(Buf, 0, 0x40);
    memcpy(Buf, str, strlen(str));
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 6;
    k->result = fn_80290060(State.devBase + off, strlen(str));
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

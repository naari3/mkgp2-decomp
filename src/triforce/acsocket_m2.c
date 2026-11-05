#include "triforce/acsocket_private.h"

s32 acRecv(s32 s, u32 off, s32 len, s32 flags) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);

    if (CheckRange(off, len, State.rxSize)) {
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
    off = State.rxOff + off;
    k->cmd = 9;
    k->id = fn_8028FC3C(8, s, State.devBase + off, len, flags);
    if (k->id == 0) {
        k->result = -2;
        OSWaitSemaphore(sem);
        k->ready = 1;
        OSSignalSemaphore(sem);
        return k->result;
    }
    return 0;
}

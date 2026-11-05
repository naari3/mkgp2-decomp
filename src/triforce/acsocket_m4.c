#include "triforce/acsocket_private.h"

s32 acGetLastError(s32 s) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);

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
    k->cmd = 17;
    k->result = fn_8029027C(s);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

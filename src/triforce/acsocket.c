#include "triforce/acsocket_private.h"

s32 acSocket(s32 domain, s32 type, s32 proto) {
    OSSemaphore* sem;
    AcSock* k = &State.sock[0];

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
    k->cmd = 11;
    k->result = fn_8028F590(domain, type, proto);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

s32 acSetTimeOuts(s32 s, s32 a0, s32 a1, s32 a2) {
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
    k->cmd = 16;
    k->result = fn_8028F7EC(s, a0, a1, a2);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

s32 acSend(s32 s, u32 off, s32 len, s32 flags) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);

    if (CheckRange(off, len, State.txSize)) {
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
    off = State.txOff + off;
    k->cmd = 10;
    k->id = fn_8028F9BC(8, s, State.devBase + off, len, flags);
    if (k->id == 0) {
        k->result = -2;
        OSWaitSemaphore(sem);
        k->ready = 1;
        OSSignalSemaphore(sem);
        return k->result;
    }
    return 0;
}

s32 acSelect(s32 nfds, void* rd, void* wr, void* ex, void* tv) {
    u32 wrResult;
    u32 exResult;
    OSSemaphore* sem;
    AcSock* k = &State.sock[0];
    u32 rdOff;
    u32 wrOff;
    u32 exOff;
    u32 tvOff;
    u32 base;
    u32 rdResult;

    if (rd == NULL && wr == NULL && ex == NULL) {
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
    fn_80291C7C(k, rd, &rdOff, wr, &wrOff, ex, &exOff, tv, &tvOff);
    k->cmd = 12;
    k->result = fn_8028FA70(nfds, State.devBase + rdOff, State.devBase + wrOff, State.devBase + exOff,
                            State.devBase + tvOff);
    if (!(k->result & 0x80000000)) {
        exResult = exOff;
        wrResult = wrOff;
        rdResult = rdOff;
        if (rd != NULL || wr != NULL || ex != NULL) {
            base = k->bufAddr + State.bufOff;
            fn_8028D5E8(base, Buf, State.bufSize);
            if (rd != NULL) {
                memcpy(rd, Buf + rdResult - base, 0x20);
            }
            if (wr != NULL) {
                memcpy(wr, Buf + wrResult - base, 0x20);
            }
            if (ex != NULL) {
                memcpy(ex, Buf + exResult - base, 0x20);
            }
        }
    }
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

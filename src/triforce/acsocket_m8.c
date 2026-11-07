#include "triforce/acsocket_private.h"

s32 acPollResponse(s32 s) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);
    s32 r;

    if (k->id != 0) {
        if (k->cmd == 5) {
            r = fn_802901F8(k->id);
        } else {
            r = fn_8028F69C(k->id);
        }
        if (r != -5) {
            sem = &State.sem;
            OSWaitSemaphore(sem);
            k->ready = 1;
            k->id = 0;
            k->result = r;
            OSSignalSemaphore(sem);
        }
    }
    /* fakematch (volatile read): the target reloads k->ready after the
     * saved-register restores. Natural code: return k->ready; */
    return *(volatile s32*)&k->ready;
}

static inline s32 ReadResponse(s32 s) {
    AcSock* k = SOCK(s);
    u32 addrOff;

    if (k->ready != 1 || k->cmd == 0) {
        return -2;
    }
    addrOff = k->addrOff;
    if (addrOff != 0) {
        switch (k->cmd) {
        case 1: {
            void* addr;
            u32* len;
            u32 base;
            u32 lenOff;
            u32 n;
            addr = k->addr;
            len = k->len;
            lenOff = k->lenOff;
            if (addr != NULL) {
                base = k->bufAddr + State.bufOff;
                fn_8028D5E8(base, Buf, State.bufSize);
                n = 0x10;
                *len = BSWAP32(*(u32*)(Buf + lenOff - base));
                if (*len >= 0x10) {
                    n = *len;
                }
                memcpy(addr, Buf + addrOff - base, n);
            }
            break;
        }
        case 22: {
            void* addr;
            u32* len;
            u32 base;
            u32 lenOff;
            u32 n;
            addr = k->addr;
            len = k->len;
            lenOff = k->lenOff;
            if (addr != NULL) {
                base = k->bufAddr + State.bufOff;
                fn_8028D5E8(base, Buf, State.bufSize);
                n = 0x10;
                *len = BSWAP32(*(u32*)(Buf + lenOff - base));
                if (*len >= 0x10) {
                    n = *len;
                }
                memcpy(addr, Buf + addrOff - base, n);
            }
            break;
        }
        }
    }
    return k->result;
}

s32 acReadResponse(s32 s) {
    return ReadResponse(s);
}


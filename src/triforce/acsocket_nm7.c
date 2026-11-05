#include "triforce/acsocket_private.h"

/* Shared storage stays on the target fallback until its layout is matched. */
u8 lbl_806992A0[0x4000] ATTRIBUTE_ALIGN(32);
u8 lbl_8069D2A0[0x4000] ATTRIBUTE_ALIGN(32);
u8 lbl_806A12A0[0x200] ATTRIBUTE_ALIGN(32);
AcState lbl_806A14A0;

s32 fn_80292D18(u32 off, u8* dst, s32 len, s32 tx, s32 rx) {
    s32 mis;
    u8* p;
    u32 al;
    u32 dev;
    u32 size;

    if (tx) {
        mis = 0;
        if ((u32)dst & 0x1F || off & 0x1F) {
            mis = 1;
        }
        p = dst;
        al = off & ~0x1F;
        if (mis) {
            p = RxBounce;
        }
        dev = State.rxOff + al;
        size = ((off + (len + 0x1F)) & ~0x1F) - al;
        if ((mis && size > 0x4000) || CheckRange(off, len, State.rxSize)) {
            return -1;
        }
        fn_8028D5E8(dev, p, size);
        if (mis) {
            memcpy(dst, p + (off & 0x1F), len);
        }
    } else {
        return -1;
    }
    return len;
}

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
    return k->ready;
}

s32 acReadResponse(s32 s) {
    AcSock* k = SOCK(s);
    u32 addrOff;
    void* addr;
    u32* len;
    u32 lenOff;
    u32 base;
    u32 n;

    if (k->ready != 1 || k->cmd == 0) {
        return -2;
    }
    addrOff = k->addrOff;
    if (addrOff != 0) {
        switch (k->cmd) {
        case 1:
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
        case 22:
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
    return k->result;
}

s32 fn_80293070(u32* cfg) {
    s32 i;
    AcSock* k;

    memset(&State, 0, sizeof(AcState));
    OSInitSemaphore(&State.sem, 1);
    State.sockBase = cfg[0];
    State.sockStride = cfg[1];
    State.unk08 = cfg[2];
    State.devBase = cfg[3];
    State.bufOff = cfg[4];
    State.bufSize = cfg[5];
    State.txOff = cfg[6];
    State.txSize = cfg[7];
    State.rxOff = cfg[8];
    State.rxSize = cfg[9];
    State.alignTx = 1;
    State.alignRx = 1;
    i = 0;
    do {
        k = SOCK(i);
        k->ready = 1;
        k->bufAddr = State.sockBase + i * State.sockStride;
        i++;
        k = SOCK(i);
        k->ready = 1;
        k->bufAddr = State.sockBase + i * State.sockStride;
        i++;
        k = SOCK(i);
        k->ready = 1;
        k->bufAddr = State.sockBase + i * State.sockStride;
        i++;
        k = SOCK(i);
        k->ready = 1;
        k->bufAddr = State.sockBase + i * State.sockStride;
        i++;
    } while (i < 64);
    return 0;
}

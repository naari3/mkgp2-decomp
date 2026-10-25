/* Triforce media board BSD-style socket API (ac*). Each socket slot tracks
 * one outstanding board request; buffers are staged through board memory. */
#include <dolphin.h>
#include <string.h>

extern char* strtok(char* str, const char* delim);
extern long strtol(const char* str, char** end, int base);

typedef struct AcSock {
    /* 0x00 */ s32 ready;
    /* 0x04 */ u8 id;
    /* 0x05 */ u8 cmd;
    /* 0x08 */ s32 result;
    /* 0x0C */ u32 bufAddr;
    /* 0x10 */ u32 addrOff;
    /* 0x14 */ void* addr;
    /* 0x18 */ u32 lenOff;
    /* 0x1C */ u32* len;
} AcSock;

typedef struct AcState {
    /* 0x00 */ u32 sockBase;
    /* 0x04 */ u32 sockStride;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 devBase;
    /* 0x10 */ u32 bufOff;
    /* 0x14 */ u32 bufSize;
    /* 0x18 */ u32 txOff;
    /* 0x1C */ u32 txSize;
    /* 0x20 */ u32 rxOff;
    /* 0x24 */ u32 rxSize;
    /* 0x28 */ s32 alignTx;
    /* 0x2C */ s32 alignRx;
    /* 0x30 */ OSSemaphore sem;
    /* 0x3C */ AcSock sock[64];
} AcState;

extern void fn_8028D530(void* buf, u32 addr, u32 len);
extern void fn_8028D5E8(u32 addr, void* buf, u32 len);
extern s32 fn_8028F590(s32 a0, s32 a1, s32 a2);
extern s32 fn_8028F69C(u8 id);
extern s32 fn_8028F7EC(s32 a0, s32 a1, s32 a2, s32 a3);
extern u8 fn_8028F9BC(s32 mask, s32 a0, u32 a1, s32 a2, s32 a3);
extern s32 fn_8028FA70(s32 a0, u32 a1, u32 a2, u32 a3, u32 a4);
extern u8 fn_8028FC3C(s32 mask, s32 a0, u32 a1, s32 a2, s32 a3);
extern s32 fn_8028FCF0(u32 a0, u32 a1, s32 a2);
extern s32 fn_8028FEB8(s32 a0, s32 a1);
extern s32 fn_80290060(u32 a0, u32 a1);
extern s32 fn_802901F8(u8 id);
extern s32 fn_8029027C(s32 a0);
extern u8 fn_80290400(s32 mask, s32 a0, u32 a1, u32 a2);
extern s32 fn_802904C0(s32 a0);
extern s32 fn_80290644(s32 a0, u32 a1, u32 a2);
extern u8 fn_80290810(s32 mask, s32 a0, u32 a1, u32 a2);

#define BSWAP32(v) (((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24))

static u8 RxBounce[0x4000] ATTRIBUTE_ALIGN(32);
static u8 TxBounce[0x4000] ATTRIBUTE_ALIGN(32);
static u8 Buf[0x200] ATTRIBUTE_ALIGN(32);
static AcState State;

static inline u32 SockAddr(AcSock* k, u32 off) {
    return k->bufAddr + off;
}

static inline u32 BufDev(AcSock* k, s32 n) {
    return SockAddr(k, State.bufOff + n);
}

static inline u8* BufPtr(s32 n) {
    return Buf + n;
}

/* Out-of-range descriptors fall back to slot 0. */
#define SOCK(s) (&State.sock[(s) & -((u32)(s) <= 63)])

static inline s32 CheckRange(u32 off, u32 len, u32 size) {
    if (off >= size || off + len > size) {
        return -1;
    }
    return 0;
}

static inline void GetAlign(s32* tx, s32* rx) {
    if (tx != NULL) {
        *tx = State.alignTx;
    }
    if (rx != NULL) {
        *rx = State.alignRx;
    }
}

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

void fn_80291C7C(AcSock* k, void* rd, u32* rdOff, void* wr, u32* wrOff, void* ex, u32* exOff,
                 void* tv, u32* tvOff);

s32 acSelect(s32 nfds, void* rd, void* wr, void* ex, void* tv) {
    AcSock* k = &State.sock[0];
    OSSemaphore* sem;
    u32 rdOff;
    u32 wrOff;
    u32 exOff;
    u32 tvOff;
    u32 base;

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
    if (k->result >= 0 && (rd != NULL || wr != NULL || ex != NULL)) {
        base = k->bufAddr + State.bufOff;
        fn_8028D5E8(base, Buf, State.bufSize);
        if (rd != NULL) {
            memcpy(rd, Buf + rdOff - base, 0x20);
        }
        if (wr != NULL) {
            memcpy(wr, Buf + wrOff - base, 0x20);
        }
        if (ex != NULL) {
            memcpy(ex, Buf + exOff - base, 0x20);
        }
    }
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

void fn_80291C7C(AcSock* k, void* rd, u32* rdOff, void* wr, u32* wrOff, void* ex, u32* exOff,
                 void* tv, u32* tvOff) {
    s32 n = 0;

    if (rd != NULL) {
        *rdOff = k->bufAddr + State.bufOff;
        memcpy(Buf, rd, 0x20);
        n = 0x20;
    } else {
        *rdOff = 0;
    }
    if (wr != NULL) {
        *wrOff = k->bufAddr + (State.bufOff + n);
        memcpy(Buf + n, wr, 0x20);
        n += 0x20;
    } else {
        *wrOff = 0;
    }
    if (ex != NULL) {
        *exOff = k->bufAddr + (State.bufOff + n);
        memcpy(Buf + n, ex, 0x20);
        n += 0x20;
    } else {
        *exOff = 0;
    }
    if (tv != NULL) {
        *tvOff = k->bufAddr + (State.bufOff + n);
        memcpy(Buf + n, tv, 8);
        n += 8;
    } else {
        *tvOff = 0;
    }
    if (n > 0) {
        fn_8028D530(Buf, k->bufAddr + State.bufOff, (n + 0x1F) & ~0x1F);
    }
}

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

s32 acModifyMyIPaddr(const char* ip, s32 mask) {
    OSSemaphore* sem;
    AcSock* k = &State.sock[0];
    u32 off;

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
    off = k->bufAddr + State.bufOff;
    memset(Buf, 0, 0x40);
    memcpy(Buf, ip, strlen(ip));
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 21;
    k->result = fn_8028FCF0(State.devBase + off, strlen(ip), mask);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

s32 acListen(s32 s, s32 backlog) {
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
    k->cmd = 8;
    k->result = fn_8028FEB8(s, backlog);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

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

s32 acConnect(s32 s, const void* addr, u32 len) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);
    u32 off;

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
    off = k->bufAddr + State.bufOff;
    memset(Buf, 0, 0x40);
    memcpy(Buf, addr, len);
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 4;
    k->id = fn_80290400(8, s, State.devBase + off, len);
    if (k->id == 0) {
        k->result = -2;
        OSWaitSemaphore(sem);
        k->ready = 1;
        OSSignalSemaphore(sem);
        return k->result;
    }
    return 0;
}

s32 acClosesocket(s32 s) {
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
    k->cmd = 3;
    k->result = fn_802904C0(s);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

s32 acBind(s32 s, const void* addr, u32 len) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);
    u32 off;

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
    off = k->bufAddr + State.bufOff;
    memset(Buf, 0, 0x40);
    memcpy(Buf, addr, len);
    fn_8028D530(Buf, k->bufAddr + State.bufOff, 0x40);
    k->cmd = 2;
    k->result = fn_80290644(s, State.devBase + off, len);
    OSWaitSemaphore(sem);
    k->ready = 1;
    OSSignalSemaphore(sem);
    return k->result;
}

s32 acAccept(s32 s, void* addr, u32* len) {
    OSSemaphore* sem;
    AcSock* k = SOCK(s);
    u32 addrOff;
    u32 lenOff;
    u32 v;
    u32 b;

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
        b = k->bufAddr;
        lenOff = b + State.bufOff;
        *(u32*)Buf = BSWAP32(v);
        addrOff = b + (State.bufOff + 4);
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

s32 fn_802928DC(void) {
    s32 i;
    s32 n = 0;

    for (i = 0; i < 64; i++) {
        if (!(acClosesocket(i) & 0x80000000)) {
            n++;
        }
    }
    return n;
}

u32 fn_80292934(const char* str) {
    u8 ip[4];
    char buf[0x20];
    char* tok;
    u8* p;
    s32 i;

    strncpy(buf, str, 0x1F);
    tok = strtok(buf, " \t\n.");
    p = ip;
    for (i = 0; i < 4; i++, p++) {
        if (tok == NULL) {
            break;
        }
        *p = strtol(tok, NULL, 10);
        tok = strtok(NULL, " \t\n.");
    }
    return *(u32*)ip;
}

s32 fn_80292AD8(u8* src, u32 off, s32 len, s32 tx, s32 rx);

s32 fn_802929BC(u8* src, u32 off, s32 len) {
    s32 tx;
    s32 rx;
    s32 total = 0;
    s32 n;
    s32 r;

    GetAlign(&tx, &rx);
    while (len > 0) {
        n = len;
        if (tx) {
            if (((u32)src & 0x1F || off & 0x1F) && ((off + len + 0x1F) & ~0x1F) - (off & ~0x1F) > 0x4000) {
                n = 0x4000 - (off & 0x1F);
            }
        } else if (((u32)src & 0x1F || off & 0x1F) && ((off + len + 1) & ~1) - (off & ~1) > 0x4000) {
            n = 0x4000 - (off & 1);
        }
        r = fn_80292AD8(src, off, n, tx, rx);
        if (r == -1) {
            break;
        }
        total += r;
        off += r;
        src += r;
        len -= r;
    }
    return total;
}

s32 fn_80292AD8(u8* src, u32 off, s32 len, s32 tx, s32 rx) {
    s32 mis;
    u8* p;
    u32 al;
    u32 dev;
    u32 size;

    if (tx) {
        mis = 0;
        if ((u32)src & 0x1F || off & 0x1F) {
            mis = 1;
        }
        p = src;
        if (mis) {
            p = TxBounce;
        }
        al = off & ~0x1F;
        dev = State.txOff + al;
        size = ((off + (len + 0x1F)) & ~0x1F) - al;
        if (!mis || size <= 0x4000) {
            if (CheckRange(off, len, State.txSize)) {
                return -1;
            }
            if (mis) {
                memcpy(p + (off & 0x1F), src, len);
            }
            fn_8028D530(p, dev, size);
            return len;
        }
        return -1;
    }
    return -1;
}

s32 fn_80292D18(u32 off, u8* dst, s32 len, s32 tx, s32 rx);

s32 fn_80292BFC(u32 off, u8* dst, s32 len) {
    s32 tx;
    s32 rx;
    s32 total = 0;
    s32 n;
    s32 r;

    GetAlign(&tx, &rx);
    while (len > 0) {
        n = len;
        if (tx) {
            if (((u32)dst & 0x1F || off & 0x1F) && ((off + len + 0x1F) & ~0x1F) - (off & ~0x1F) > 0x4000) {
                n = 0x4000 - (off & 0x1F);
            }
        } else if (((u32)dst & 0x1F || off & 0x1F) && ((off + len + 1) & ~1) - (off & ~1) > 0x4000) {
            n = 0x4000 - (off & 1);
        }
        r = fn_80292D18(off, dst, n, tx, rx);
        if (r == -1) {
            break;
        }
        total += r;
        off += r;
        dst += r;
        len -= r;
    }
    return total;
}

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
        if (!mis || size <= 0x4000) {
            if (CheckRange(off, len, State.rxSize)) {
                return -1;
            }
            fn_8028D5E8(dev, p, size);
            if (mis) {
                memcpy(dst, p + (off & 0x1F), len);
            }
            return len;
        }
        return -1;
    }
    return -1;
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
    for (i = 0; i < 64; i++) {
        k = SOCK(i);
        k->ready = 1;
        k->bufAddr = State.sockBase + i * State.sockStride;
    }
    return 0;
}

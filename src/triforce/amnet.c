/* Triforce baseboard network transport: packet channels exchanged with the
 * media board through DVD-mapped command/status registers. */
#include <dolphin.h>
#include <string.h>

typedef struct NetTrace {
    /* 0x00 */ u8 flags;
    /* 0x01 */ u8 seq;
    /* 0x02 */ u8 op;
    /* 0x03 */ u8 dir;
    /* 0x04 */ void* buf;
    /* 0x08 */ u32 addr;
    /* 0x0C */ u32 size;
    /* 0x10 */ u8 data[0x20];
} NetTrace;

typedef struct NetPacket {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 sub;
    /* 0x02 */ u16 flags;
    /* 0x04 */ u8 body[0x1C];
} NetPacket;

typedef struct NetChan {
    /* 0x00 */ NetPacket rx;
    /* 0x20 */ NetPacket tx;
    /* 0x40 */ u8 dev;
    /* 0x41 */ u8 pad41[0x1F];
} NetChan;

typedef struct NetDev {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 kind;
    /* 0x02 */ u8 pad2[2];
    /* 0x04 */ u32 flags;
    /* 0x08 */ u32 cmdAddr;
    /* 0x0C */ u32 statAddr;
} NetDev;

typedef s32 (*NetSendHook)(u8 ch);

typedef struct NetState {
    /* 0x00 */ u32 numDev;
    /* 0x04 */ NetDev dev[2];
    /* 0x24 */ u32 param;
    /* 0x28 */ u32 unk28;
    /* 0x2C */ void* cb[4];
    /* 0x3C */ u8 pad3C[0x14];
    /* 0x50 */ u32 base[2];
    /* 0x58 */ u32 cfgA[10];
    /* 0x80 */ u32 cfgB[6];
    /* 0x98 */ u32 cfgC[4];
    /* 0xA8 */ u16 hwFlags;
    /* 0xAA */ u8 prio;
    /* 0xAB */ u8 lastId;
    /* 0xAC */ u32 rxCount;
    /* 0xB0 */ void* hookB0;
    /* 0xB4 */ u32 txCount;
    /* 0xB8 */ NetSendHook sendHook;
    /* 0xBC */ OSSemaphore sem;
    /* 0xC8 */ u32 unkC8;
    /* 0xCC */ OSSemaphore irqSem;
} NetState;

typedef struct NetBlob {
    u32 len;
    void* data;
} NetBlob;

typedef void (*NetHandler)(u8 ch);

typedef struct NetDispatch {
    u16 key;
    u16 count;
    const NetHandler* fns;
} NetDispatch;

extern BOOL fn_80286934(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback,
                        s32 prio);
extern s32 fn_802869A0(DVDCommandBlock* block);
extern s32 fn_80286A74(DVDCommandBlock* block, u32 arg);
extern BOOL fn_8028772C(s32 chan, u32 dev, u16* data);
extern BOOL fn_802878B4(s32 chan, u32 dev, u16 data);
extern BOOL fn_802879FC(s32 chan, u32 dev, u16 data);
extern BOOL fn_80287B44(s32 chan, u32 dev, u16* data);
extern BOOL fn_80287CCC(s32 chan, u32 dev, u16 data);
extern void fn_80287E14(s32 chan, EXICallback callback);
extern void fn_80290F70(u32* cfg);
extern void fn_80291010(u32* cfg);
extern void fn_80291098(u8 ch);
extern void fn_80291134(u8 ch);
extern void fn_8029121C(u8 ch);
extern void fn_80291314(u8 ch);
extern void fn_802913CC(u8 ch);
extern void fn_8029145C(u8 ch);
extern void fn_80291524(u8 ch);
extern void fn_802915F4(u8 ch);
extern void fn_80291690(u8 ch);
extern void fn_802916E4(u8 ch);
extern void fn_80291738(u8 ch);
extern void fn_80293070(u32* cfg);
extern BOOL fn_80294DF8(s32);
extern BOOL fn_80294E30(s32, s32);

void fn_8028CC80(void);
void fn_8028F25C(void);
void fn_8028F298(void);
void fn_8028F31C(void);
void fn_8028F348(void);
void fn_8028F3D8(void);
void fn_8028F404(void);
void fn_8028F430(void);

static NetTrace Trace[8];
static u32 LogBuf[0x1000];
static NetChan Chan[64];
static NetState State;

/* Debug helper stripped from the final link; fixes the order of the statics. */
void NetResetTrace(void) {
    Trace[0].flags = 0;
    LogBuf[0] = 0;
    Chan[0].dev = 0;
    State.numDev = 0;
}

static u32 TraceIdx;
static u32 LogIdx;

static void (*IrqCallbacks[5])(void) = {NULL, fn_8028F430, fn_8028F3D8, fn_8028F31C, fn_8028F25C};
static void (*SendCallbacks[5])(void) = {NULL, fn_8028F404, fn_8028F348, fn_8028F298, NULL};

static const u32 NetCfg[36] = {
    0x00800000, 0x00001000, 0x00000020, 0x00000000, 0x00000200, 0x00000200, 0x00A00000, 0x00100000, 0x00B00000,
    0x00100000, 0x00D00000, 0x00100000, 0x000FF000, 0x00000000, 0x00D00000, 0x00100000, 0x00C00000, 0x00001000,
    0x00000020, 0x00000000, 0x00040000, 0x00001000, 0x00000020, 0x00000000, 0x00000200, 0x00000200, 0x00100000,
    0x00080000, 0x00180000, 0x00080000, 0x00080000, 0x00080000, 0x0007F000, 0x00000000, 0x00080000, 0x00080000,
};

static const NetHandler Handlers0[12] = {
    fn_80291738, fn_80291738, fn_802916E4, fn_80291690, fn_802915F4, fn_80291524,
    fn_8029145C, fn_802913CC, fn_80291314, fn_80291738, fn_8029121C, fn_80291134,
};

static const NetHandler Handlers3[4] = {fn_80291738, fn_80291738, fn_80291098, fn_80291738};

static const NetDispatch Dispatch[3] = {
    {0x0000, 12, Handlers0},
    {0x0300, 4, Handlers3},
    {0, 0, NULL},
};

static const u8 DevIds[] = {0x21, 0x29, 0};
static const char Magic[] = "GCAM";

#define LOG(v) (LogBuf[LogIdx++ & 0xFFF] = (v))
#define ALIGN32(p) ((void*)(((u32)(p) + 0x1F) & ~0x1F))
#define BSWAP16(v) ((((v) << 8) & 0xFF00) | (((v) >> 8) & 0xFF))
#define BSWAP32(v) (((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24))

static inline void TraceAdd(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    u32 n = TraceIdx++;
    NetTrace* t = &Trace[n & 7];
    t->seq = n;
    t->op = op;
    t->dir = dir;
    t->buf = buf;
    t->addr = addr;
    t->size = size;
    memcpy(t->data, buf, 0x20);
}

static inline void DevWrite(void* buf, u32 addr, u32 len) {
    DVDCommandBlock block;
    if (addr < 0x80000000) {
        memset(&block, 0, sizeof(block));
        fn_80286A74(&block, State.prio);
    }
    DCFlushRange(buf, len);
    memset(&block, 0, sizeof(block));
    fn_80286934(&block, buf, len, addr, NULL, 2);
    while (DVDGetCommandBlockStatus(&block) != 0) {
    }
}

static inline void DevRead(u32 addr, void* buf, u32 len) {
    DVDCommandBlock block;
    if (addr < 0x80000000) {
        memset(&block, 0, sizeof(block));
        fn_80286A74(&block, State.prio);
    }
    DCInvalidateRange(buf, len);
    memset(&block, 0, sizeof(block));
    DVDReadAbsAsyncPrio(&block, buf, len, addr, NULL, 2);
    while (DVDGetCommandBlockStatus(&block) != 0) {
    }
}

static inline void DevReadPkt(u32 addr, void* buf) {
    DevRead(addr, buf, 0x20);
}

static inline void DevWaitIdle(u32 addr, NetPacket* stat) {
    do {
        DevReadPkt(addr, stat);
    } while (stat->flags != 0);
}

static inline void DevSend(void* buf, u32 addr, u8 id) {
    if ((Trace[0].flags & 1) && id == 0xA9) {
        TraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((Trace[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        TraceAdd('W', '2', buf, -1, -1);
    }
}

static inline void DevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u8 id = dev->id;
    memset(buf, 0, 0x20);
    if ((Trace[0].flags & 2) && id == 0xA9) {
        TraceAdd('C', 'L', buf, addr, 0x20);
    }
    DevSend(buf, addr, id);
}

static inline void DevPoke(u32 addr, u32 val) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    memset(buf, 0, 0x20);
    *(u32*)buf = val;
    DevWrite(buf, addr, 0x20);
}

static inline NetDev* FindDev(u8 id) {
    NetDev* dev = State.dev;
    u32 i;
    for (i = 0; i < State.numDev; i++, dev++) {
        if (id == dev->id) {
            return dev;
        }
    }
    return NULL;
}

static inline NetChan* FindChan(u8 id) {
    NetChan* c = Chan;
    s32 i;
    for (i = 0; i < 64; c++, i++) {
        if (!(c->tx.flags & 0x80) && c->tx.id == id) {
            return c;
        }
    }
    return NULL;
}

static inline NetPacket* FindRx(u8 id) {
    NetChan* c = FindChan(id);
    if (c != NULL) {
        return &c->rx;
    }
    return NULL;
}

static inline NetPacket* TxPacket(u8 ch) {
    if (ch <= 0x3F) {
        return &Chan[ch].tx;
    }
    return NULL;
}

static inline NetPacket* RxPacket(u8 ch) {
    if (ch <= 0x3F) {
        return &Chan[ch].rx;
    }
    return NULL;
}

static inline void FreeChan(NetChan* c) {
    LOG((c - Chan) | 0xC1000000);
    memset(c, 0, sizeof(NetChan));
}

static inline NetHandler GetHandler(u16 cmd) {
    const NetDispatch* d;
    for (d = Dispatch; d->fns != NULL; d++) {
        if ((cmd & 0x7F00) == d->key) {
            u8 idx = cmd;
            if (idx < d->count) {
                return d->fns[idx];
            }
            break;
        }
    }
    return fn_80291738;
}

s32 fn_8028C1B8(u8 ch);
s32 fn_8028C644(u8 kind);
u8 fn_8028D15C(NetPacket* pkt);
s32 fn_8028D750(s32 mask, u8 kind, u8* out);

static inline s32 LockedSend(u8 ch) {
    OSSemaphore* sem = &State.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C1B8(ch);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028C158(u8 ch) {
    OSSemaphore* sem = &State.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C1B8(ch);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028C1B8(u8 ch) {
    u8 devId;
    NetDev* dev;
    u32 addr;
    NetPacket* stat;
    NetPacket* pkt;
    u8 raw[0x40];
    OSSemaphore* sem;

    LOG((ch << 16) | 0x20000000 | (u16)State.txCount);
    if (ch == 0xFF) {
        return 3;
    }
    if (ch <= 0x3F) {
        devId = Chan[ch].dev;
    } else {
        devId = 0;
    }
    dev = FindDev(devId);
    addr = dev->statAddr;
    stat = ALIGN32(raw);
    DevWaitIdle(addr, stat);
    pkt = TxPacket(ch);
    if ((Trace[0].flags & 2) && devId == 0xA9) {
        TraceAdd('T', 'R', pkt, dev->statAddr, 0x20);
    }
    DevSend(pkt, dev->statAddr, dev->id);
    if (dev->kind <= 3 && SendCallbacks[dev->kind] != NULL) {
        SendCallbacks[dev->kind]();
    }
    State.txCount++;
    LOG((pkt->id << 16) | 0x30000000 | BSWAP16(pkt->flags));
    if (pkt->flags & 0x80) {
        sem = &State.sem;
        OSSignalSemaphore(sem);
        if (ch <= 0x3F) {
            OSWaitSemaphore(sem);
            FreeChan(&Chan[ch]);
            OSSignalSemaphore(sem);
        }
        OSWaitSemaphore(sem);
    }
    return 0;
}

s32 fn_8028C5E4(u8 kind) {
    OSSemaphore* sem = &State.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C644(kind);
    OSSignalSemaphore(sem);
    return ret;
}

static inline u8 OpenChan(NetPacket* pkt, u8 dev) {
    u8 ch = fn_8028D15C(pkt);
    if (ch == 0xFF) {
        return 0xFF;
    }
    if (ch <= 0x3F) {
        Chan[ch].dev = dev;
    }
    GetHandler(BSWAP16(pkt->flags))(ch);
    return ch;
}

s32 fn_8028C644(u8 kind) {
    u8 devId;
    NetDev* dev;
    NetPacket* pkt;
    NetPacket* rx;
    u8 ch;
    s32 ret;
    u8 raw[0x40];
    void* buf;
    OSSemaphore* sem;

    buf = ALIGN32(raw);
    ret = 0;
    LOG((u16)State.rxCount | 0x21000000);
    if (!fn_8028D750(0, kind, &devId)) {
        return 4;
    }
    dev = FindDev(devId);
    DevReadPkt(dev->cmdAddr, buf);
    pkt = buf;
    if (pkt->flags == 0) {
        ret = 3;
    } else {
        if (!(dev->flags & 2)) {
            if (pkt->flags != 0x180) {
                ret = 4;
            } else {
                dev->flags |= 2;
            }
        }
        if (dev->flags & 2) {
            LOG((pkt->id << 16) | 0x31000000 | BSWAP16(pkt->flags));
            if (pkt->flags & 0x80) {
                rx = FindRx(pkt->id);
                if (rx != NULL) {
                    memcpy(rx, pkt, 0x20);
                }
            } else {
                sem = &State.sem;
                OSSignalSemaphore(sem);
                ch = OpenChan(pkt, devId);
                OSWaitSemaphore(sem);
                if (ch == 0xFF) {
                    ret = 2;
                }
            }
        }
    }
    DevClear(dev->cmdAddr, dev);
    return ret;
}

s32 fn_8028CB64(u8* out) {
    u16 status;
    u8 kind;
    OSSemaphore* sem = &State.irqSem;

    do {
        OSWaitSemaphore(sem);
        kind = 0;
        fn_8028772C(0, 2, &status);
        if (status & 0x10) {
            kind = 3;
        } else if (status & 4) {
            kind = 2;
        } else if (status & 2) {
            kind = 1;
        }
        if (kind == 0) {
            State.rxCount++;
        }
    } while (kind == 0);
    OSSignalSemaphore(sem);
    if (kind <= 4 && IrqCallbacks[kind] != NULL) {
        IrqCallbacks[kind]();
    }
    *out = kind;
    State.rxCount++;
    LOG(0x11000000);
    return 1;
}

void fn_8028CC80(void) {
    OSSignalSemaphore(&State.irqSem);
}

BOOL fn_8028CCAC(u8 id) {
    NetChan* c = FindChan(id);
    if (c != NULL) {
        return c->rx.flags != 0;
    }
    return FALSE;
}

s32 fn_8028CD74(u8 id, u8 dev) {
    NetChan* c = FindChan(id);
    if (c == NULL) {
        return 1;
    }
    c->dev = dev;
    return 0;
}

NetPacket* fn_8028CE34(u8 ch) {
    return TxPacket(ch);
}

NetPacket* fn_8028CE60(u8 id) {
    NetChan* c = FindChan(id);
    if (c != NULL) {
        return &c->tx;
    }
    return NULL;
}

NetPacket* fn_8028CF1C(u8 ch) {
    return RxPacket(ch);
}

NetPacket* fn_8028CF44(u8 id) {
    return FindRx(id);
}

s32 fn_8028D000(u8 id) {
    OSSemaphore* sem = &State.sem;
    s32 ret = 1;
    NetChan* c;

    OSWaitSemaphore(sem);
    c = FindChan(id);
    if (c != NULL) {
        LOG((c - Chan) | 0xC0000000);
        memset(c, 0, sizeof(NetChan));
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

u8 fn_8028D15C(NetPacket* pkt) {
    OSSemaphore* sem = &State.sem;
    NetChan* c;
    u8 ret = 0xFF;
    s32 i;

    OSWaitSemaphore(sem);
    for (i = 0, c = Chan; i < 64; i++, c++) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            memcpy(&c->rx, pkt, 0x20);
            LOG((c - Chan) | 0xA1000000);
            ret = i;
            break;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

u8 fn_8028D234(void) {
    OSSemaphore* sem = &State.sem;
    u8 ret = 0;
    NetChan* c;
    s32 n;
    u8 id;

    OSWaitSemaphore(sem);
    c = Chan;
    for (n = 64; n != 0; n--) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            id = State.lastId;
            do {
                id++;
                if (id == 0) {
                    id++;
                }
            } while (FindChan(id) != NULL);
            c->tx.id = id;
            c->tx.sub = 0;
            ret = id;
            State.lastId = id;
            c->tx.flags = 0xFF00;
            LOG((c - Chan) | 0xA0000000);
            break;
        }
        c++;
    }
    OSSignalSemaphore(sem);
    return ret;
}

static inline s32 SendChan(u8 ch) {
    s32 ret = 0;
    if (State.sendHook != NULL) {
        State.sendHook(ch);
    } else {
        ret = LockedSend(ch);
    }
    return ret;
}

s32 fn_8028D3E4(u8 ch) {
    s32 ret = 0;
    if (State.sendHook != NULL) {
        State.sendHook(ch);
    } else {
        ret = LockedSend(ch);
    }
    return ret;
}

s32 fn_8028D460(u8 id) {
    NetChan* c;
    s32 i;
    s32 n;

    if (id == 0) {
        return 1;
    }
    c = Chan;
    i = 0;
    for (n = 64; n != 0; n--) {
        if (!(c->tx.flags & 0x80) && c->tx.id == id) {
            return SendChan(i);
        }
        c++;
        i++;
    }
    return 1;
}

void fn_8028D530(void* buf, u32 addr, u32 len) {
    DevWrite(buf, addr, len);
}

void fn_8028D5E8(u32 addr, void* buf, u32 len) {
    DevRead(addr, buf, len);
}

u32 fn_8028D6A0(void) {
    return State.unkC8;
}

u32* fn_8028D6B0(void) {
    return &State.param;
}

s32 fn_8028D6C0(u32 idx, void* cb) {
    if (idx > 3) {
        return 1;
    }
    State.cb[idx] = cb;
    return 0;
}

NetSendHook fn_8028D6EC(NetSendHook hook) {
    NetSendHook old = State.sendHook;
    State.sendHook = hook;
    return old;
}

void* fn_8028D704(void* hook) {
    void* old = State.hookB0;
    State.hookB0 = hook;
    return old;
}

s32 fn_8028D71C(s32 idx, u32 base) {
    if (idx < 0 || idx > 1) {
        return 1;
    }
    State.base[idx] = base;
    return 0;
}

s32 fn_8028D750(s32 mask, u8 kind, u8* out) {
    u32 want = (mask | 1) & 0x7FFFFFFF;
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < State.numDev; i++) {
        if (rev) {
            dev = &State.dev[State.numDev - 1 - i];
        } else {
            dev = &State.dev[i];
        }
        if (dev->kind == kind && want == (want & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

s32 fn_8028D7E8(s32 mask, u8* out) {
    u32 want = (mask | 1) & 0x7FFFFFFF;
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < State.numDev; i++) {
        if (rev) {
            dev = &State.dev[State.numDev - 1 - i];
        } else {
            dev = &State.dev[i];
        }
        if (want == (want & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

u32 fn_8028D870(void) {
    u32 ret = 8;
    if (State.numDev != 0 && FindDev(0x29) != NULL) {
        ret = State.hwFlags & 7;
    }
    return ret;
}

s32 fn_8028D8CC(u8 id, NetBlob* blob) {
    NetDev* dev;
    u32 base;
    u32 off;
    u32 v;
    void* buf;
    u8 raw0[0x40];
    u8 raw1[0x40];
    u8 raw2[0x40];
    u16 cmd[16];
    u8 info[0x20];
    u16 hdr[4];

    dev = FindDev(id);
    if (dev == NULL) {
        return 1;
    }
    switch (id) {
    case 0x21:
        buf = ALIGN32(raw0);
        DevRead(0x80000040, buf, 0x20);
        memcpy(info, buf, 0x20);
        memcpy(hdr, info, 8);
        if (memcmp(&hdr[2], Magic, 4) != 0) {
            cmd[1] = 0;
            buf = ALIGN32(raw1);
            cmd[0] = 0x100;
            cmd[2] = 0;
            cmd[3] = 0;
            memcpy(buf, cmd, 0x20);
            DevWrite(buf, 0x80000040, 0x20);
            return 5;
        }
        buf = ALIGN32(raw2);
        base = (BSWAP16(hdr[1]) << 16) | BSWAP16(hdr[0]);
        DevRead(0x80000000, buf, 0x20);
        v = *(u16*)buf;
        State.hwFlags = BSWAP16(v);
        if (State.hwFlags & 0x100) {
            State.prio = 0;
        } else {
            State.prio = 1;
        }
        State.base[0] = base;
        State.base[1] = 0;
        dev->kind = 1;
        if (base != 0) {
            off = base - 0x01000000;
            dev->flags |= 0xD;
            dev->cmdAddr = off + 0x900000;
            dev->statAddr = off + 0x900020;
            DevClear(dev->cmdAddr, dev);
            DevClear(dev->statAddr, dev);
            memcpy(State.cfgA, &NetCfg[0], sizeof(State.cfgA));
            State.cfgA[0] += off;
            State.cfgA[6] += off;
            State.cfgA[8] += off;
            fn_80293070(State.cfgA);
            memcpy(State.cfgB, &NetCfg[10], sizeof(State.cfgB));
            State.cfgB[0] += off;
            State.cfgB[4] += off;
            fn_80290F70(State.cfgB);
            memcpy(State.cfgC, &NetCfg[16], sizeof(State.cfgC));
            State.cfgC[0] += off;
            fn_80291010(State.cfgC);
        }
        return 0;
    case 0x29:
        buf = ALIGN32(raw0);
        DevRead(0x80000140, buf, 0x20);
        v = *(u32*)buf;
        if (!(BSWAP32(v) & 1)) {
            if (blob != NULL && blob->len != 0 && blob->data != NULL) {
                DevWrite(blob->data, 0x84800000, blob->len);
                DevPoke(0x80000140, 0x01000000);
            }
            return 5;
        }
        buf = ALIGN32(raw1);
        State.prio = 1;
        DevRead(0x80000120, buf, 0x20);
        v = *(u32*)buf;
        State.hwFlags = BSWAP32(v);
        dev->kind = 2;
        dev->flags |= 1;
        dev->cmdAddr = 0x84000000;
        dev->statAddr = 0x84000020;
        DevClear(dev->cmdAddr, dev);
        DevClear(dev->statAddr, dev);
        return 0;
    case 0xA9:
        buf = ALIGN32(raw0);
        DevRead(0x80000160, buf, 0x20);
        v = *(u32*)buf;
        if (BSWAP32(v) & 1) {
            return 5;
        }
        State.base[1] = 0x89000000;
        dev->kind = 3;
        dev->flags |= 9;
        dev->cmdAddr = 0x89000000;
        dev->statAddr = 0x89000200;
        DevClear(dev->cmdAddr, dev);
        DevClear(dev->statAddr, dev);
        memcpy(State.cfgA, &NetCfg[20], sizeof(State.cfgA));
        State.cfgA[0] += 0x89000000;
        State.cfgA[6] += 0x89000000;
        State.cfgA[8] += 0x89000000;
        fn_80293070(State.cfgA);
        memcpy(State.cfgB, &NetCfg[30], sizeof(State.cfgB));
        State.cfgB[0] += 0x89000000;
        State.cfgB[4] += 0x89000000;
        fn_80290F70(State.cfgB);
        return 0;
    default:
        return 1;
    }
}

s32 fn_8028EAA8(u8 id) {
    NetDev* dev = FindDev(id);

    if (dev == NULL) {
        return 1;
    }
    DevClear(dev->cmdAddr, dev);
    DevClear(dev->statAddr, dev);
    switch (dev->kind) {
    case 1:
        break;
    case 2:
        DevPoke(0x84000040, 0);
        break;
    }
    return 0;
}

u8 fn_8028EF74(u8 id) {
    switch (id) {
    case 0x21:
        break;
    case 0x29:
        if (FindDev(0xA9) == NULL && State.numDev < 2) {
            State.dev[State.numDev++].id = 0xA9;
            return 0xA9;
        }
        return 0;
    }
    return 0;
}

u8 fn_8028F008(void) {
    DVDCommandBlock block;
    const u8* p;
    u32 v;
    u8 id;

    memset(&block, 0, sizeof(block));
    v = fn_802869A0(&block);
    id = BSWAP32(v);
    for (p = DevIds; *p != 0;) {
        if (*p++ == id) {
            if (FindDev(id) == NULL && State.numDev < 2) {
                State.dev[State.numDev++].id = id;
                return id;
            }
            return 0;
        }
    }
    return 0;
}

s32 fn_8028F0E8(void) {
    u16 v;

    fn_80287B44(0, 2, &v);
    v |= 0x37F;
    fn_802879FC(0, 2, v);
    if (!fn_80294DF8(0)) {
        return 1;
    }
    memset(&State, 0, sizeof(NetState));
    return 0;
}

s32 fn_8028F160(u32 param) {
    u16 v;

    memset(&State, 0, sizeof(NetState));
    State.param = param;
    State.unkC8 = 0x01000000;
    OSInitSemaphore(&State.sem, 1);
    memset(Chan, 0, sizeof(Chan));
    if (!fn_80294E30(0, 2)) {
        return 1;
    }
    OSInitSemaphore(&State.irqSem, 0);
    if (IrqCallbacks[4] != NULL) {
        IrqCallbacks[4]();
    }
    fn_80287E14(2, (EXICallback)fn_8028CC80);
    fn_80287B44(0, 2, &v);
    v &= ~0x7E;
    fn_802879FC(0, 2, v);
    return 0;
}

void fn_8028F25C(void) {
    fn_80287CCC(0, 2, 0x201);
    fn_802878B4(0, 2, 0x14);
}

void fn_8028F298(void) {
    u8 info[0x20];
    u8 raw[0x40];
    void* buf = ALIGN32(raw);

    DevRead(0x88000000, buf, 0x20);
    memcpy(info, buf, 0x20);
}

void fn_8028F31C(void) {
    fn_802878B4(0, 2, 0x10);
}

void fn_8028F348(void) {
    DevPoke(0x84000040, 0x01000000);
}

void fn_8028F3D8(void) {
    fn_802878B4(0, 2, 4);
}

void fn_8028F404(void) {
    fn_80287CCC(0, 2, 0);
}

void fn_8028F430(void) {
    fn_80287CCC(0, 2, 0x201);
}

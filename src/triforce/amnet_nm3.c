#include <triforce/amnet_priv.h>

NetTrace lbl_806937C0[8];
u32 lbl_80693940[0x1000];
NetChan lbl_80697940[64];
NetState lbl_80699140;

/* Debug helper stripped from the final link; fixes the order of the statics. */
void NetResetTrace(void) {
    lbl_806937C0[0].flags = 0;
    lbl_80693940[0] = 0;
    lbl_80697940[0].dev = 0;
    lbl_80699140.numDev = 0;
}

u32 lbl_806D1E44;
u32 lbl_806D1E40;

void (*lbl_804F5800[5])(void) = {NULL, fn_8028F430, fn_8028F3D8, fn_8028F31C, fn_8028F25C};
void (*lbl_804F5814[5])(void) = {NULL, fn_8028F404, fn_8028F348, fn_8028F298, NULL};

const u32 lbl_803F2798[36] = {
    0x00800000, 0x00001000, 0x00000020, 0x00000000, 0x00000200, 0x00000200, 0x00A00000, 0x00100000, 0x00B00000,
    0x00100000, 0x00D00000, 0x00100000, 0x000FF000, 0x00000000, 0x00D00000, 0x00100000, 0x00C00000, 0x00001000,
    0x00000020, 0x00000000, 0x00040000, 0x00001000, 0x00000020, 0x00000000, 0x00000200, 0x00000200, 0x00100000,
    0x00080000, 0x00180000, 0x00080000, 0x00080000, 0x00080000, 0x0007F000, 0x00000000, 0x00080000, 0x00080000,
};

const NetHandler lbl_803F2828[12] = {
    fn_80291738, fn_80291738, fn_802916E4, fn_80291690, fn_802915F4, fn_80291524,
    fn_8029145C, fn_802913CC, fn_80291314, fn_80291738, fn_8029121C, fn_80291134,
};

const NetHandler lbl_803F2858[4] = {fn_80291738, fn_80291738, fn_80291098, fn_80291738};

const NetDispatch lbl_803F2868[3] = {
    {0x0000, 12, lbl_803F2828},
    {0x0300, 4, lbl_803F2858},
    {0, 0, NULL},
};

const u8 lbl_806DC930[] = {0x21, 0x29, 0};
const char lbl_806DC934[] = "GCAM";

static inline void TracePacket(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    NetTrace* t = lbl_806937C0;
    u32 n = lbl_806D1E44++;
    t += n & 7;
    t->seq = n;
    t->op = op;
    t->dir = dir;
    t->buf = buf;
    t->addr = addr;
    t->size = size;
    memcpy(t->data, buf, 0x20);
}

static inline void SendPacket(void* buf, NetDev* dev) {
    u32 addr = dev->statAddr;
    u8 id = dev->id;
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) TracePacket('W', 'R', buf, addr, 0x20);
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        TracePacket('W', '2', buf, -1, -1);
    }
}

static inline void ClearPacket(NetDev* dev) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u32 addr = dev->cmdAddr;
    u8 id = dev->id;
    memset(buf, 0, 0x20);
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) TracePacket('C', 'L', buf, addr, 0x20);
    DevSend(buf, addr, id);
}

s32 fn_8028C1B8(u8 channel) {
    u32 ch = channel;
    u8 devId;
    NetDev* dev;
    u32 addr;
    NetPacket* pkt;
    u8 raw[0x40];
    OSSemaphore* sem;

    LOG((ch << 16) | 0x20000000 | (u16)lbl_80699140.txCount);
    if (ch == 0xFF) {
        return 3;
    }
    if (ch <= 0x3F) {
        devId = lbl_80697940[ch].dev;
    } else {
        devId = 0;
    }
    dev = FindDev(devId);
    addr = dev->statAddr;
    pkt = ALIGN32(raw);
    DevWaitIdle(addr, pkt);
    pkt = TxPacket(ch);
    if ((lbl_806937C0[0].flags & 2) && devId == 0xA9) {
        TracePacket('T', 'R', pkt, dev->statAddr, 0x20);
    }
    SendPacket(pkt, dev);
    {
        u32 kind = dev->kind;
        if (kind <= 3 && lbl_804F5814[kind] != NULL) {
            lbl_804F5814[kind]();
        }
    }
    lbl_80699140.txCount++;
    LOG((pkt->id << 16) | 0x30000000 | BSWAP16(pkt->flags));
    if (pkt->flags & 0x80) {
        sem = &lbl_80699140.sem;
        OSSignalSemaphore(sem);
        if (ch <= 0x3F) {
            OSWaitSemaphore(sem);
            FreeChan(&lbl_80697940[ch]);
            OSSignalSemaphore(sem);
        }
        OSWaitSemaphore(sem);
    }
    return 0;
}

s32 fn_8028C5E4(u8 kind) {
    OSSemaphore* sem = &lbl_80699140.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C644(kind);
    OSSignalSemaphore(sem);
    return ret;
}

static inline NetHandler HandlerFor(NetPacket* pkt);

static inline u8 OpenChan(NetPacket* pkt, u8 dev) {
    u8 ch = fn_8028D15C(pkt);
    if (ch == 0xFF) {
        return 0xFF;
    }
    if (ch <= 0x3F) {
        lbl_80697940[ch].dev = dev;
    }
    HandlerFor(pkt)(ch);
    return ch;
}

static inline NetHandler HandlerFor(NetPacket* pkt) {
    const NetHandler* fns;
    const NetDispatch* d;
    u16 cmd;
    cmd = BSWAP16(pkt->flags);
    d = lbl_803F2868;
    while ((fns = d->fns) != NULL) {
        if ((cmd & 0x7F00) == d->key) {
            s32 idx = (u8)cmd;
            if (idx < d->count) return fns[idx];
            break;
        }
        d++;
    }
    return fn_80291738;
}

s32 fn_8028C644(u8 kind) {
    u8 devId;
    NetDev* dev;
    OSSemaphore* sem;
    NetPacket* pkt;
    NetPacket* rx;
    u8 ch;
    s32 ret;
    u8 raw[0x40];
    void* buf;

    buf = ALIGN32(raw);
    ret = 0;
    LOG((u16)lbl_80699140.rxCount | 0x21000000);
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
                sem = &lbl_80699140.sem;
                OSSignalSemaphore(sem);
                ch = OpenChan(pkt, devId);
                OSWaitSemaphore(sem);
                if (ch == 0xFF) {
                    ret = 2;
                }
            }
        }
    }
    ClearPacket(dev);
    return ret;
}

s32 fn_8028CB64(u8* out) {
    u16 status;
    u8 kind;
    OSSemaphore* sem = &lbl_80699140.irqSem;

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
            lbl_80699140.rxCount++;
        }
    } while (kind == 0);
    OSSignalSemaphore(sem);
    {
        u32 index = kind;
        if (index <= 4 && lbl_804F5800[index] != NULL) {
            lbl_804F5800[index]();
        }
    }
    *out = kind;
    lbl_80699140.rxCount++;
    LOG(0x11000000);
    return 1;
}

void fn_8028CC80(void) {
    OSSignalSemaphore(&lbl_80699140.irqSem);
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
    OSSemaphore* sem = &lbl_80699140.sem;
    s32 ret = 1;
    NetChan* c;

    OSWaitSemaphore(sem);
    c = FindChan(id);
    if (c != NULL) {
        LOG((c - lbl_80697940) | 0xC0000000);
        memset(c, 0, sizeof(NetChan));
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

u8 fn_8028D15C(NetPacket* pkt) {
    NetChan* c;
    OSSemaphore* sem = &lbl_80699140.sem;
    u8 ret = 0xFF;
    s32 i;

    OSWaitSemaphore(sem);
    for (i = 0, c = lbl_80697940; i < 64; c++, i++) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            memcpy(&c->rx, pkt, 0x20);
            LOG((c - lbl_80697940) | 0xA1000000);
            ret = i;
            break;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

static inline NetChan* FindChanFrom(NetChan* c, u8 id) {
    s32 i;
    for (i = 0; i < 64; c++, i++) {
        if (!(c->tx.flags & 0x80) && c->tx.id == id) return c;
    }
    return NULL;
}

static inline u8 NextChannelId(NetState* state, NetChan* channels) {
    u8 id = state->lastId;
    do {
        id++;
        if (id == 0) id++;
    } while (FindChanFrom(channels, id) != NULL);
    return id;
}

u8 fn_8028D234(void) {
    OSSemaphore* sem = &lbl_80699140.sem;
    u8 ret = 0;
    NetChan* c;
    NetState* state;
    NetChan* channels;
    s32 n;
    u8 id;

    OSWaitSemaphore(sem);
    channels = lbl_80697940;
    c = channels;
    for (n = 64; n != 0; n--) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            state = &lbl_80699140;
            id = NextChannelId(state, channels);
            c->tx.id = id;
            c->tx.sub = 0;
            ret = id;
            state->lastId = id;
            c->tx.flags = 0xFF00;
            LOG((c - lbl_80697940) | 0xA0000000);
            break;
        }
        c++;
    }
    OSSignalSemaphore(sem);
    return ret;
}

/* ---- amnet_io.c ---- */

s32 fn_8028D3E4(u8 ch) {
    s32 ret = 0;
    if (lbl_80699140.sendHook != NULL) {
        lbl_80699140.sendHook(ch);
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
    c = lbl_80697940;
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
    return lbl_80699140.unkC8;
}

u32* fn_8028D6B0(void) {
    return &lbl_80699140.param;
}

s32 fn_8028D6C0(u32 idx, void* cb) {
    if (idx > 3) {
        return 1;
    }
    lbl_80699140.cb[idx] = cb;
    return 0;
}

NetSendHook fn_8028D6EC(NetSendHook hook) {
    NetSendHook old = lbl_80699140.sendHook;
    lbl_80699140.sendHook = hook;
    return old;
}

void* fn_8028D704(void* hook) {
    void* old = lbl_80699140.hookB0;
    lbl_80699140.hookB0 = hook;
    return old;
}

s32 fn_8028D71C(s32 idx, u32 base) {
    if (idx < 0 || idx > 1) {
        return 1;
    }
    lbl_80699140.base[idx] = base;
    return 0;
}

/* ---- amnet_nm1.c ---- */

/* Wanted flag bits: bit 0 always, the sign bit selects reverse search. */
#define NET_WANT(m) (((m) | 1) & 0x7FFFFFFF)

s32 fn_8028D750(s32 mask, u8 kind, u8* out) {
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < lbl_80699140.numDev; i++) {
        if (rev) {
            dev = &lbl_80699140.dev[lbl_80699140.numDev - 1 - i];
        } else {
            dev = &lbl_80699140.dev[i];
        }
        if (dev->kind == kind && NET_WANT(mask) == (NET_WANT(mask) & dev->flags)) {
            if (out != NULL) {
                *out = dev->id;
            }
            return 1;
        }
    }
    return 0;
}

/* ---- amnet_probe.c ---- */

s32 fn_8028D7E8(s32 mask, u8* out) {
    u32 want = (mask | 1) & 0x7FFFFFFF;
    s32 rev = mask & 0x80000000;
    NetDev* dev;
    u32 i;

    for (i = 0; i < lbl_80699140.numDev; i++) {
        if (rev) {
            dev = &lbl_80699140.dev[lbl_80699140.numDev - 1 - i];
        } else {
            dev = &lbl_80699140.dev[i];
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

/* ---- amnet_nm2.c ---- */

u32 fn_8028D870(void) {
    u32 ret = 8;
    if (lbl_80699140.numDev != 0 && FindDev(0x29) != NULL) {
        ret = (u8)(lbl_80699140.hwFlags & 7);
    }
    return ret;
}

/* ---- amnet_nm2_rest.c ---- */

static inline void ProbeTraceAdd(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    u32 n = lbl_806D1E44++;
    u32 i = n & 7;
    lbl_806937C0[i].seq = n;
    lbl_806937C0[i].op = op;
    lbl_806937C0[i].dir = dir;
    lbl_806937C0[i].buf = buf;
    lbl_806937C0[i].addr = addr;
    lbl_806937C0[i].size = size;
    memcpy(lbl_806937C0[i].data, buf, 0x20);
}

static inline void ProbeDevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    u8 id;
    void* buf;
    buf = ALIGN32(raw);
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

/* Keep aligned transfer storage inside the transport helpers. */
static inline void ReadDeviceInfoImpl(u32 addr, void* info) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    DevRead(addr, buf, 0x20);
    memcpy(info, buf, 0x20);
}

static inline void WriteDeviceCommandImpl(u32 addr, void* cmd) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    memcpy(buf, cmd, 0x20);
    DevWrite(buf, addr, 0x20);
}

static inline u16 ReadDeviceHalfImpl(u32 addr) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u32 v;
    DevRead(addr, buf, 0x20);
    v = *(u16*)buf;
    return BSWAP16(v);
}

static inline u32 ReadDeviceWordImpl(u32 addr) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u32 v;
    DevRead(addr, buf, 0x20);
    return BSWAP32(*(u32*)buf);
}

static inline void ReadDeviceInfo(u32 addr, void* info) {
    ReadDeviceInfoImpl(addr, info);
}

static inline void WriteDeviceCommand(u32 addr, void* cmd) {
    WriteDeviceCommandImpl(addr, cmd);
}

static inline u16 ReadDeviceHalf(u32 addr) {
    return ReadDeviceHalfImpl(addr);
}

static inline u32 ReadDeviceWord(u32 addr) {
    return ReadDeviceWordImpl(addr);
}

static inline void WriteDeviceWord(u32 addr, u32 val) {
    DevPoke(addr, val);
}

static inline void InitializeDevSend(void* buf, u32 addr, u8 id) {
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

static inline void InitializeDevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    u8 id;
    void* buf;
    buf = ALIGN32(raw);
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    InitializeDevSend(buf, addr, id);
}

#pragma push
#pragma opt_propagation off
#pragma opt_loop_invariants off
s32 fn_8028D8CC(u8 id, NetBlob* blob) {
    NetDev* dev;
    const u32* configs = lbl_803F2798;
    u32 base;
    u32 off;
    u32 v;

    dev = FindDev(id);
    if (dev == NULL) {
        return 1;
    }
    switch (id) {
    case 0x21: {
        /* The device header workspace is a complete 32-byte packet. */
        u16 hdr[16];
        u8 info[0x20];
        u16 cmd[16];
        ReadDeviceInfo(0x80000040, info);
        memcpy(hdr, info, 8);
        if (memcmp(&hdr[2], lbl_806DC934, 4) != 0) {
            cmd[1] = 0;
            cmd[0] = 0x100;
            cmd[2] = 0;
            cmd[3] = 0;
            WriteDeviceCommand(0x80000040, cmd);
            return 5;
        }
        base = BSWAP16(hdr[1]);
        base <<= 16;
        base |= BSWAP16(hdr[0]);
        lbl_80699140.hwFlags = ReadDeviceHalf(0x80000000);
        if (lbl_80699140.hwFlags & 0x100) {
            lbl_80699140.prio = 0;
        } else {
            lbl_80699140.prio = 1;
        }
        lbl_80699140.base[0] = base;
        lbl_80699140.base[1] = 0;
        dev->kind = 1;
        if (base != 0) {
            off = base - 0x01000000;
            dev->flags |= 0xD;
            dev->cmdAddr = off + 0x900000;
            dev->statAddr = off + 0x900020;
            InitializeDevClear(dev->cmdAddr, dev);
            InitializeDevClear(dev->statAddr, dev);
            memcpy(lbl_80699140.cfgA, &configs[0], sizeof(lbl_80699140.cfgA));
            lbl_80699140.cfgA[0] += off;
            lbl_80699140.cfgA[6] += off;
            lbl_80699140.cfgA[8] += off;
            fn_80293070(lbl_80699140.cfgA);
            memcpy(lbl_80699140.cfgB, &configs[10], sizeof(lbl_80699140.cfgB));
            lbl_80699140.cfgB[0] += off;
            lbl_80699140.cfgB[4] += off;
            fn_80290F70(lbl_80699140.cfgB);
            memcpy(lbl_80699140.cfgC, &configs[16], sizeof(lbl_80699140.cfgC));
            lbl_80699140.cfgC[0] += off;
            fn_80291010(lbl_80699140.cfgC);
        }
        return 0;
    }
    case 0x29: {
        v = ReadDeviceWord(0x80000140);
        if (!(v & 1)) {
            if (blob != NULL && blob->len != 0 && blob->data != NULL) {
                DevWrite(blob->data, 0x84800000, blob->len);
                WriteDeviceWord(0x80000140, 0x01000000);
            }
            return 5;
        }
        lbl_80699140.prio = 1;
        lbl_80699140.hwFlags = ReadDeviceWord(0x80000120);
        dev->kind = 2;
        dev->flags |= 1;
        dev->cmdAddr = 0x84000000;
        dev->statAddr = 0x84000020;
        InitializeDevClear(dev->cmdAddr, dev);
        InitializeDevClear(dev->statAddr, dev);
        return 0;
    }
    case 0xA9: {
        v = ReadDeviceWord(0x80000160);
        if (v & 1) {
            return 5;
        }
        lbl_80699140.base[1] = 0x89000000;
        dev->kind = 3;
        dev->flags |= 9;
        dev->cmdAddr = 0x89000000;
        dev->statAddr = 0x89000200;
        InitializeDevClear(dev->cmdAddr, dev);
        InitializeDevClear(dev->statAddr, dev);
        memcpy(lbl_80699140.cfgA, &configs[20], sizeof(lbl_80699140.cfgA));
        lbl_80699140.cfgA[0] += 0x89000000;
        lbl_80699140.cfgA[6] += 0x89000000;
        lbl_80699140.cfgA[8] += 0x89000000;
        fn_80293070(lbl_80699140.cfgA);
        memcpy(lbl_80699140.cfgB, &configs[30], sizeof(lbl_80699140.cfgB));
        lbl_80699140.cfgB[0] += 0x89000000;
        lbl_80699140.cfgB[4] += 0x89000000;
        fn_80290F70(lbl_80699140.cfgB);
        return 0;
    }
    default:
        return 1;
    }
}
#pragma pop


static inline void ResetDevAddress(u32* address, NetDev* dev) {
    u8 raw[0x40];
    void* buf;
    u32 addr;
    u8 id;
    buf = ALIGN32(raw);
    addr = *address;
    id = dev->id;
    memset(buf, 0, 0x20);
    if ((lbl_806937C0[0].flags & 2) && id == 0xA9) {
        ProbeTraceAdd('C', 'L', buf, addr, 0x20);
    }
    if ((lbl_806937C0[0].flags & 1) && id == 0xA9) {
        ProbeTraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((lbl_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        ProbeTraceAdd('W', '2', buf, -1, -1);
    }
}

#pragma push
#pragma opt_dead_assignments off
s32 fn_8028EAA8(u8 id) {
    NetDev* dev = FindDev(id);

    if (dev == NULL) {
        return 1;
    }
    ResetDevAddress(&dev->cmdAddr, dev);
    ProbeDevClear(dev->statAddr, dev);
    switch (dev->kind) {
    case 1:
        break;
    case 2:
        DevPoke(0x84000040, 0);
        break;
    case 3:
        break;
    }
    return 0;
}
#pragma pop


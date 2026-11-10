#include <triforce/amnet_priv.h>

NetTrace amnet_nm3_bss_806937C0[8];
u32 amnet_nm3_bss_80693940[0x1000];
NetChan amnet_nm3_bss_80697940[64];
NetState amnet_nm3_bss_80699140;

/* Debug helper stripped from the final link; fixes the order of the statics. */
void NetResetTrace(void) {
    amnet_nm3_bss_806937C0[0].flags = 0;
    amnet_nm3_bss_80693940[0] = 0;
    amnet_nm3_bss_80697940[0].dev = 0;
    amnet_nm3_bss_80699140.numDev = 0;
}

u32 amnet_nm3_bss_806D1E44;
u32 amnet_nm3_bss_806D1E40;

void (*amnet_nm3_data_804F5800[5])(void) = {NULL, fn_8028F430, fn_8028F3D8, fn_8028F31C, fn_8028F25C};
void (*amnet_nm3_data_804F5814[5])(void) = {NULL, fn_8028F404, fn_8028F348, fn_8028F298, NULL};

static inline void TracePacket(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    NetTrace* t = amnet_nm3_bss_806937C0;
    u32 n = amnet_nm3_bss_806D1E44++;
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
    u8 id = (int)dev->id;
    if ((amnet_nm3_bss_806937C0[0].flags & 1) && id == 0xA9) TracePacket('W', 'R', buf, addr, 0x20);
    DevWrite(buf, addr, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 4) && id == 0xA9) {
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
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && id == 0xA9) TracePacket('C', 'L', buf, addr, 0x20);
    DevSend(buf, addr, id);
}

static inline NetChan* ChannelFor(u32 index) {
    NetChan* c = amnet_nm3_bss_80697940;
    c += index;
    return c;
}

static inline u8 ChannelDeviceId(u32 ch) {
    if (ch <= 0x3F) return amnet_nm3_bss_80697940[ch].dev;
    return 0;
}

static inline NetDev* ChannelDevice(u32 ch, u8* devId) {
    *devId = ChannelDeviceId(ch);
    return FindDev(*devId);
}

s32 fn_8028C1B8(u8 channel) {
    u32 ch = channel;
    u8 devId;
    NetDev* dev;
    u32 addr;
    NetPacket* pkt;
    u8 raw[0x40];
    OSSemaphore* sem;

    LOG((ch << 16) | 0x20000000 | (u16)amnet_nm3_bss_80699140.txCount);
    if (ch == 0xFF) {
        return 3;
    }
    dev = ChannelDevice(ch, &devId);
    addr = dev->statAddr;
    pkt = ALIGN32(raw);
    DevWaitIdle(addr, pkt);
    pkt = TxPacket(ch);
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && devId == 0xA9) {
        TracePacket('T', 'R', pkt, dev->statAddr, 0x20);
    }
    SendPacket(pkt, dev);
    {
        u32 kind = dev->kind;
        if (kind <= 3 && amnet_nm3_data_804F5814[kind] != NULL) {
            amnet_nm3_data_804F5814[kind]();
        }
    }
    amnet_nm3_bss_80699140.txCount++;
    LOG((pkt->id << 16) | 0x30000000 | BSWAP16(pkt->flags));
    if (pkt->flags & 0x80) {
        sem = &amnet_nm3_bss_80699140.sem;
        OSSignalSemaphore(sem);
        if (ch <= 0x3F) {
            OSWaitSemaphore(sem);
            FreeChan(ChannelFor(ch));
            OSSignalSemaphore(sem);
        }
        OSWaitSemaphore(sem);
    }
    return 0;
}


s32 fn_8028C5E4(u8 kind) {
    OSSemaphore* sem = &amnet_nm3_bss_80699140.sem;
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
        amnet_nm3_bss_80697940[ch].dev = dev;
    }
    HandlerFor(pkt)(ch);
    return ch;
}

static inline NetHandler HandlerFor(NetPacket* pkt) {
    const NetHandler* fns;
    const NetDispatch* d;
    u16 cmd;
    cmd = BSWAP16(pkt->flags);
    d = amnet_nm3_rodata_803F2868;
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
    LOG((u16)amnet_nm3_bss_80699140.rxCount | 0x21000000);
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
                sem = &amnet_nm3_bss_80699140.sem;
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
    OSSemaphore* sem = &amnet_nm3_bss_80699140.irqSem;

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
            amnet_nm3_bss_80699140.rxCount++;
        }
    } while (kind == 0);
    OSSignalSemaphore(sem);
    {
        u32 index = kind;
        if (index <= 4 && amnet_nm3_data_804F5800[index] != NULL) {
            amnet_nm3_data_804F5800[index]();
        }
    }
    *out = kind;
    amnet_nm3_bss_80699140.rxCount++;
    LOG(0x11000000);
    return 1;
}

void fn_8028CC80(void) {
    OSSignalSemaphore(&amnet_nm3_bss_80699140.irqSem);
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
    OSSemaphore* sem = &amnet_nm3_bss_80699140.sem;
    s32 ret = 1;
    NetChan* c;

    OSWaitSemaphore(sem);
    c = FindChan(id);
    if (c != NULL) {
        LOG((c - amnet_nm3_bss_80697940) | 0xC0000000);
        memset(c, 0, sizeof(NetChan));
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

u8 fn_8028D15C(NetPacket* pkt) {
    NetChan* c;
    OSSemaphore* sem = &amnet_nm3_bss_80699140.sem;
    u8 ret = 0xFF;
    s32 i;

    OSWaitSemaphore(sem);
    for (i = 0, c = amnet_nm3_bss_80697940; i < 64; c++, i++) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            memcpy(&c->rx, pkt, 0x20);
            LOG((c - amnet_nm3_bss_80697940) | 0xA1000000);
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
    OSSemaphore* sem = &amnet_nm3_bss_80699140.sem;
    u8 ret = 0;
    NetChan* c;
    NetState* state;
    NetChan* channels;
    s32 n;
    u8 id;

    OSWaitSemaphore(sem);
    channels = amnet_nm3_bss_80697940;
    c = channels;
    for (n = 64; n != 0; n--) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            state = &amnet_nm3_bss_80699140;
            id = NextChannelId(state, channels);
            c->tx.id = id;
            c->tx.sub = 0;
            ret = id;
            state->lastId = id;
            c->tx.flags = 0xFF00;
            LOG((c - amnet_nm3_bss_80697940) | 0xA0000000);
            break;
        }
        c++;
    }
    OSSignalSemaphore(sem);
    return ret;
}


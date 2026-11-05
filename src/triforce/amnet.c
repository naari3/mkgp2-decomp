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

s32 fn_8028C158(u8 ch) {
    OSSemaphore* sem = &lbl_80699140.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C1B8(ch);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028C1B8(u8 channel) {
    u32 ch = channel;
    u8 devId;
    NetDev* dev;
    u32 addr;
    NetPacket* stat;
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
    stat = ALIGN32(raw);
    DevWaitIdle(addr, stat);
    pkt = TxPacket(ch);
    if ((lbl_806937C0[0].flags & 2) && devId == 0xA9) {
        TraceAdd('T', 'R', pkt, dev->statAddr, 0x20);
    }
    DevSend(pkt, dev->statAddr, dev->id);
    if (dev->kind <= 3 && lbl_804F5814[dev->kind] != NULL) {
        lbl_804F5814[dev->kind]();
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

static inline u8 OpenChan(NetPacket* pkt, u8 dev) {
    u8 ch = fn_8028D15C(pkt);
    if (ch == 0xFF) {
        return 0xFF;
    }
    if (ch <= 0x3F) {
        lbl_80697940[ch].dev = dev;
    }
    GetHandler(BSWAP16(pkt->flags))(ch);
    return ch;
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
    DevClear(dev->cmdAddr, dev);
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
    if (kind <= 4 && lbl_804F5800[kind] != NULL) {
        lbl_804F5800[kind]();
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

u8 fn_8028D234(void) {
    OSSemaphore* sem = &lbl_80699140.sem;
    u8 ret = 0;
    NetChan* c;
    s32 n;
    u8 id;

    OSWaitSemaphore(sem);
    c = lbl_80697940;
    for (n = 64; n != 0; n--) {
        if (c->rx.flags == 0 && c->tx.flags == 0) {
            id = lbl_80699140.lastId;
            do {
                id++;
                if (id == 0) {
                    id++;
                }
            } while (FindChan(id) != NULL);
            c->tx.id = id;
            c->tx.sub = 0;
            ret = id;
            lbl_80699140.lastId = id;
            c->tx.flags = 0xFF00;
            LOG((c - lbl_80697940) | 0xA0000000);
            break;
        }
        c++;
    }
    OSSignalSemaphore(sem);
    return ret;
}

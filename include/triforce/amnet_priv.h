#include "game/types/le.h"
#ifndef AMNET_PRIV_H
#define AMNET_PRIV_H
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

extern NetTrace amnet_nm3_bss_806937C0[8];
extern u32 amnet_nm3_bss_80693940[0x1000];
extern NetChan amnet_nm3_bss_80697940[64];
extern NetState amnet_nm3_bss_80699140;
extern u32 amnet_nm3_bss_806D1E40;
extern u32 amnet_nm3_bss_806D1E44;
extern void (*amnet_nm3_data_804F5800[5])(void);
extern void (*amnet_nm3_data_804F5814[5])(void);
extern const u32 amnet_setup_nm_rodata_803F2798[10];
extern const NetHandler amnet_setup_nm_rodata_803F2828[12];
extern const NetHandler amnet_setup_nm_rodata_803F2858[4];
extern const NetDispatch amnet_nm3_rodata_803F2868[3];
extern const u8 lbl_806DC930[3];
extern const char lbl_806DC934[5];

#define LOG(v) (amnet_nm3_bss_80693940[amnet_nm3_bss_806D1E40++ & 0xFFF] = (v))
#define ALIGN32(p) ((void*)(((u32)(p) + 0x1F) & ~0x1F))
#define BSWAP16(v) LE_AS_WRITTEN(((((v) << 8) & 0xFF00) | (((v) >> 8) & 0xFF)), (v))
#define BSWAP32(v) LE_AS_WRITTEN((((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24)), (v))

static inline void TraceAdd(u8 op, u8 dir, void* buf, u32 addr, u32 size) {
    NetTrace* t;
    u32 n = amnet_nm3_bss_806D1E44++;
    /* fakematch (hand): natural code is `t = &amnet_nm3_bss_806937C0[n & 7];`. The integer
     * accumulate form computes the scaled index into t's register and the table
     * address into a scratch (`add r8, r3, r8` instead of `add r8, r8, r3`). */
    u32 i = (n & 7) * sizeof(NetTrace);
    i += (u32)amnet_nm3_bss_806937C0;
    t = (NetTrace*)i;
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
        fn_80286A74(&block, amnet_nm3_bss_80699140.prio);
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
        fn_80286A74(&block, amnet_nm3_bss_80699140.prio);
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
    if ((amnet_nm3_bss_806937C0[0].flags & 1) && id == 0xA9) {
        TraceAdd('W', 'R', buf, addr, 0x20);
    }
    DevWrite(buf, addr, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 4) && id == 0xA9) {
        DCInvalidateRange(buf, 0x20);
        TraceAdd('W', '2', buf, -1, -1);
    }
}

static inline void DevClear(u32 addr, NetDev* dev) {
    u8 raw[0x40];
    void* buf = ALIGN32(raw);
    u8 id = dev->id;
    memset(buf, 0, 0x20);
    if ((amnet_nm3_bss_806937C0[0].flags & 2) && id == 0xA9) {
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
    NetDev* dev = amnet_nm3_bss_80699140.dev;
    u32 i;
    for (i = 0; i < amnet_nm3_bss_80699140.numDev; i++, dev++) {
        if (id == dev->id) {
            return dev;
        }
    }
    return NULL;
}

static inline NetChan* FindChan(u8 id) {
    NetChan* c = amnet_nm3_bss_80697940;
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
        return &amnet_nm3_bss_80697940[ch].tx;
    }
    return NULL;
}

static inline NetPacket* RxPacket(u8 ch) {
    if (ch <= 0x3F) {
        return &amnet_nm3_bss_80697940[ch].rx;
    }
    return NULL;
}

static inline void FreeChan(NetChan* c) {
    LOG((c - amnet_nm3_bss_80697940) | 0xC1000000);
    memset(c, 0, sizeof(NetChan));
}

static inline NetHandler GetHandler(u16 cmd) {
    const NetDispatch* d;
    for (d = amnet_nm3_rodata_803F2868; d->fns != NULL; d++) {
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
    OSSemaphore* sem = &amnet_nm3_bss_80699140.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C1B8(ch);
    OSSignalSemaphore(sem);
    return ret;
}

static inline s32 SendChan(u8 ch) {
    s32 ret = 0;
    if (amnet_nm3_bss_80699140.sendHook != NULL) {
        amnet_nm3_bss_80699140.sendHook(ch);
    } else {
        ret = LockedSend(ch);
    }
    return ret;
}


#endif

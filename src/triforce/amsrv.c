/* Triforce media board service: board-side requests that read and write
 * game memory, plus the two link status blocks. */
#include <dolphin.h>
#include <string.h>

typedef struct NetPacket {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 sub;
    /* 0x02 */ u16 flags;
    /* 0x04 */ u32 result;
    /* 0x08 */ u32 arg[6];
} NetPacket;

typedef struct NetLinkA {
    /* 0x00 */ u32 cfg[6];
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ OSSemaphore sem;
    /* 0x2C */ s32 ready;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 busy;
    /* 0x34 */ s32 result;
    /* 0x38 */ u32 cfg0;
    /* 0x3C */ u8 pad3C[4];
} NetLinkA;

typedef struct NetLinkB {
    /* 0x00 */ u32 cfg0;
    /* 0x04 */ u32 cfg1;
    /* 0x08 */ u32 unk08;
    /* 0x0C */ u32 cfg2;
    /* 0x10 */ u32 cfg3;
    /* 0x14 */ OSSemaphore sem;
    /* 0x20 */ s32 ready;
    /* 0x24 */ u32 unk24[2];
    /* 0x2C */ u32 cfg0b;
    /* 0x30 */ u8 pad30[0x10];
} NetLinkB;

extern NetPacket* fn_8028CE34(u8 ch);
extern NetPacket* fn_8028CF1C(u8 ch);
extern s32 fn_8028D3E4(u8 ch);
extern u32* fn_8028D6B0(void);
extern s32 fn_8028F45C(void);

#define BSWAP16(v) ((((v) << 8) & 0xFF00) | (((v) >> 8) & 0xFF))
#define BSWAP32(v) (((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24))

static NetLinkA LinkA;
static NetLinkB LinkB;

s32 fn_80290ED8(void) {
    NetLinkA* l = &LinkA;
    OSSemaphore* sem;

    if (l->ready == 0) {
        return -2;
    }
    sem = &l->sem;
    OSWaitSemaphore(sem);
    l->ready = 0;
    l->unk30 = 0;
    l->result = 0;
    OSSignalSemaphore(sem);
    l->busy = 1;
    l->result = fn_8028F45C();
    OSWaitSemaphore(sem);
    l->ready = 1;
    OSSignalSemaphore(sem);
    return l->result;
}

s32 fn_80290F70(u32* cfg) {
    memset(&LinkA, 0, 0x3C);
    OSInitSemaphore(&LinkA.sem, 1);
    LinkA.cfg[0] = cfg[0];
    LinkA.cfg[1] = cfg[1];
    LinkA.cfg[2] = cfg[2];
    LinkA.cfg[3] = cfg[3];
    LinkA.cfg[4] = cfg[4];
    LinkA.cfg[5] = cfg[5];
    LinkA.unk18 = 1;
    LinkA.unk1C = 1;
    LinkA.ready = 1;
    LinkA.cfg0 = cfg[0];
    return 0;
}

s32 fn_80291010(u32* cfg) {
    memset(&LinkB, 0, 0x30);
    OSInitSemaphore(&LinkB.sem, 1);
    LinkB.cfg0 = cfg[0];
    LinkB.cfg1 = cfg[1];
    LinkB.cfg2 = cfg[2];
    LinkB.cfg3 = cfg[3];
    LinkB.ready = 1;
    LinkB.cfg0b = cfg[0];
    return 0;
}

#define REPLY(rsp, req)                                     \
    do {                                                    \
        (rsp)->id = (req)->id;                              \
        (rsp)->sub = (req)->sub;                            \
        (rsp)->flags = BSWAP16(BSWAP16((req)->flags) | 0x8000); \
    } while (0)

s32 fn_80291098(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    base[9] = BSWAP32(req->result);
    base[10] = BSWAP32(req->arg[0]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_80291134(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* p = (u32*)((fn_8028D6B0()[1] + BSWAP32(req->result)) & ~3);

    p[0] = BSWAP32(req->arg[0]);
    p[1] = BSWAP32(req->arg[1]);
    p[2] = BSWAP32(req->arg[2]);
    p[3] = BSWAP32(req->arg[3]);
    p[4] = BSWAP32(req->arg[4]);
    p[5] = BSWAP32(req->arg[5]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_8029121C(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* p = (u32*)((fn_8028D6B0()[1] + BSWAP32(req->result)) & ~3);

    rsp->result = BSWAP32(p[0]);
    rsp->arg[0] = BSWAP32(p[1]);
    rsp->arg[1] = BSWAP32(p[2]);
    rsp->arg[2] = BSWAP32(p[3]);
    rsp->arg[3] = BSWAP32(p[4]);
    rsp->arg[4] = BSWAP32(p[5]);
    rsp->arg[5] = BSWAP32(p[6]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_80291314(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    u32 idx = BSWAP32(req->result);

    rsp->result = BSWAP32(base[0]);
    rsp->arg[0] = BSWAP32(base[idx + 2]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_802913CC(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    base[7] = BSWAP32(req->result);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_8029145C(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();
    u32 addr = base[1] + BSWAP32(req->result);

    if (addr & 3) {
        rsp->result = 0;
    } else {
        *(u32*)addr = BSWAP32(req->arg[0]);
        rsp->result = BSWAP32(base[0]);
    }
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_80291524(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();
    u32 addr = base[1] + BSWAP32(req->result);

    if (addr & 3) {
        rsp->result = 0;
        rsp->arg[0] = 0;
    } else {
        rsp->result = BSWAP32(base[0]);
        rsp->arg[0] = BSWAP32(*(u32*)addr);
    }
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_802915F4(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    base[1] = BSWAP32(req->result);
    rsp->result = BSWAP32(base[0]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_80291690(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    *(u16*)((u8*)base + 0x18) = BSWAP16(req->flags);
    return 1;
}

s32 fn_802916E4(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    *(u16*)((u8*)base + 0x18) = BSWAP16(req->flags);
    return 1;
}

s32 fn_80291738(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);

    rsp->id = req->id;
    rsp->sub = req->sub;
    rsp->flags = 0x80;
    fn_8028D3E4(ch);
    return 1;
}

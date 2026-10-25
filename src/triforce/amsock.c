/* Triforce media board socket commands: each call sends a request packet on
 * a fresh channel and waits for the board's reply. */
#include <dolphin.h>
#include <string.h>

typedef struct NetPacket {
    /* 0x00 */ u8 id;
    /* 0x01 */ u8 sub;
    /* 0x02 */ u16 flags;
    /* 0x04 */ u32 result;
    /* 0x08 */ u32 arg[6];
} NetPacket;

extern BOOL fn_8028CCAC(u8 id);
extern s32 fn_8028CD74(u8 id, u8 dev);
extern NetPacket* fn_8028CE60(u8 id);
extern NetPacket* fn_8028CF44(u8 id);
extern s32 fn_8028D000(u8 id);
extern u8 fn_8028D234(void);
extern s32 fn_8028D460(u8 id);
extern s32 fn_8028D6A0(void);
extern s32 fn_8028D7E8(s32 mask, u8* out);

#define BSWAP16(v) ((((v) << 8) & 0xFF00) | (((v) >> 8) & 0xFF))
#define BSWAP32(v) (((v) << 24) | (((v) << 8) & 0xFF0000) | (((v) >> 8) & 0xFF00) | ((v) >> 24))

static inline s32 NetReply(u8 id) {
    NetPacket* p;
    s32 ret;

    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    ret = BSWAP32(p->result);
    fn_8028D000(id);
    return ret;
}

static inline s32 NetReplyRaw(u8 id) {
    NetPacket* p;
    s32 ret;

    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    ret = p->result;
    fn_8028D000(id);
    return ret;
}

static inline u8 NetRequest0(s32 mask, u16 cmd) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->id = id;
    p->sub = 0;
    p->flags = cmd;
    fn_8028D460(id);
    return id;
}

s32 fn_8028F45C(void) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = NetRequest0(8, 0x106);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_8028F72C(s32 mask, u32 a0, u32 a1, u32 a2);

s32 fn_8028F590(u32 a0, u32 a1, u32 a2) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_8028F72C(8, a0, a1, a2);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

s32 fn_8028F69C(u8 id) {
    NetPacket* p;
    s32 ret;

    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    ret = BSWAP32(p->result);
    fn_8028D000(id);
    return ret;
}

u8 fn_8028F72C(s32 mask, u32 a0, u32 a1, u32 a2) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->id = id;
    p->sub = 0;
    p->flags = 0xB04;
    fn_8028D460(id);
    return id;
}

u8 fn_8028F908(s32 mask, u32 a0, u32 a1, u32 a2, u32 a3);

s32 fn_8028F7EC(u32 a0, u32 a1, u32 a2, u32 a3) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_8028F908(8, a0, a1, a2, a3);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_8028F908(s32 mask, u32 a0, u32 a1, u32 a2, u32 a3) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->arg[3] = BSWAP32(a3);
    p->id = id;
    p->sub = a0;
    p->flags = 0x1004;
    fn_8028D460(id);
    return id;
}

u8 fn_8028F9BC(s32 mask, u32 a0, u32 a1, u32 a2, u32 a3) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->arg[3] = BSWAP32(a3);
    p->id = id;
    p->sub = a0;
    p->flags = 0xA04;
    fn_8028D460(id);
    return id;
}

u8 fn_8028FB7C(s32 mask, u32 a0, u32 a1, u32 a2, u32 a3, u32 a4);

s32 fn_8028FA70(u32 a0, u32 a1, u32 a2, u32 a3, u32 a4) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_8028FB7C(8, a0, a1, a2, a3, a4);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_8028FB7C(s32 mask, u32 a0, u32 a1, u32 a2, u32 a3, u32 a4) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->arg[3] = BSWAP32(a3);
    p->arg[4] = BSWAP32(a4);
    p->id = id;
    p->sub = 0;
    p->flags = 0xC04;
    fn_8028D460(id);
    return id;
}

u8 fn_8028FC3C(s32 mask, u32 a0, u32 a1, u32 a2, u32 a3) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->arg[3] = BSWAP32(a3);
    p->id = id;
    p->sub = a0;
    p->flags = 0x904;
    fn_8028D460(id);
    return id;
}

u8 fn_8028FDFC(s32 mask, u32 a0, u32 a1, u32 a2);

s32 fn_8028FCF0(u32 a0, u32 a1, u32 a2) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_8028FDFC(8, a0, a1, a2);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_8028FDFC(s32 mask, u32 a0, u32 a1, u32 a2) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = a2;
    p->id = id;
    p->sub = 0;
    p->flags = 0x1504;
    fn_8028D460(id);
    return id;
}

u8 fn_8028FFB4(s32 mask, u32 a0, u32 a1);

s32 fn_8028FEB8(u32 a0, u32 a1) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_8028FFB4(8, a0, a1);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_8028FFB4(s32 mask, u32 a0, u32 a1) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->id = id;
    p->sub = a0;
    p->flags = 0x804;
    fn_8028D460(id);
    return id;
}

u8 fn_8029014C(s32 mask, u32 a0, u32 a1);

s32 fn_80290060(u32 a0, u32 a1) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_8029014C(8, a0, a1);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReplyRaw(id);
}

u8 fn_8029014C(s32 mask, u32 a0, u32 a1) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->id = id;
    p->sub = 0;
    p->flags = 0x604;
    fn_8028D460(id);
    return id;
}

s32 fn_802901F8(u8 id) {
    NetPacket* p;
    s32 ret;

    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    ret = p->result;
    fn_8028D000(id);
    return ret;
}

u8 fn_80290368(s32 mask, u32 a0);

s32 fn_8029027C(u32 a0) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_80290368(8, a0);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_80290368(s32 mask, u32 a0) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->id = id;
    p->sub = a0;
    p->flags = 0x1104;
    fn_8028D460(id);
    return id;
}

u8 fn_80290400(s32 mask, u32 a0, u32 a1, u32 a2) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->id = id;
    p->sub = a0;
    p->flags = 0x404;
    fn_8028D460(id);
    return id;
}

u8 fn_802905AC(s32 mask, u32 a0);

s32 fn_802904C0(u32 a0) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_802905AC(8, a0);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_802905AC(s32 mask, u32 a0) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->id = id;
    p->sub = a0;
    p->flags = 0x304;
    fn_8028D460(id);
    return id;
}

u8 fn_80290750(s32 mask, u32 a0, u32 a1, u32 a2);

s32 fn_80290644(u32 a0, u32 a1, u32 a2) {
    volatile s32 timeout = fn_8028D6A0();
    u8 id = fn_80290750(8, a0, a1, a2);

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
        if (timeout-- <= 0) {
            fn_8028D000(id);
            return -6;
        }
    }
    return NetReply(id);
}

u8 fn_80290750(s32 mask, u32 a0, u32 a1, u32 a2) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->id = id;
    p->sub = a0;
    p->flags = 0x204;
    fn_8028D460(id);
    return id;
}

u8 fn_80290810(s32 mask, u32 a0, u32 a1, u32 a2) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = 0;
    p->arg[0] = BSWAP32(a0);
    p->arg[1] = BSWAP32(a1);
    p->arg[2] = BSWAP32(a2);
    p->id = id;
    p->sub = a0;
    p->flags = 0x104;
    fn_8028D460(id);
    return id;
}

s32 fn_802908D0(char* out) {
    u8 id = NetRequest0(0x80000000, 0x301);
    NetPacket* p;

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
    }
    if (out == NULL) {
        return -4;
    }
    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    memcpy(out, &p->result, 0x10);
    out[0x10] = 0;
    fn_8028D000(id);
    return 0;
}

s32 fn_802909FC(char* out) {
    u8 id = NetRequest0(0, 0x301);
    NetPacket* p;

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
    }
    if (out == NULL) {
        return -4;
    }
    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    memcpy(out, &p->result, 0x10);
    out[0x10] = 0;
    fn_8028D000(id);
    return 0;
}

s32 fn_80290B28(u16* a, u16* b) {
    u8 id = NetRequest0(0x80000000, 0x101);
    NetPacket* p;

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
    }
    if (a == NULL && b == NULL) {
        return -4;
    }
    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    if (a != NULL) {
        *a = BSWAP16(((u16*)&p->result)[0]);
    }
    if (b != NULL) {
        *b = BSWAP16(((u16*)&p->result)[1]);
    }
    fn_8028D000(id);
    return 0;
}

s32 fn_80290C6C(u16* a, u16* b) {
    u8 id = NetRequest0(0, 0x101);
    NetPacket* p;

    if (id == 0) {
        return -2;
    }
    while (!fn_8028CCAC(id)) {
    }
    if (a == NULL && b == NULL) {
        return -4;
    }
    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    if (a != NULL) {
        *a = BSWAP16(((u16*)&p->result)[0]);
    }
    if (b != NULL) {
        *b = BSWAP16(((u16*)&p->result)[1]);
    }
    fn_8028D000(id);
    return 0;
}

s32 fn_80290DB0(u8 id, u32* out) {
    NetPacket* p;

    if (!fn_8028CCAC(id)) {
        return -5;
    }
    p = fn_8028CF44(id);
    if (BSWAP16(p->flags) == 0x8000) {
        fn_8028D000(id);
        return -3;
    }
    if (out != NULL) {
        *out = BSWAP32(p->result);
    }
    fn_8028D000(id);
    return 0;
}

u8 fn_80290E44(s32 mask, u32 a0) {
    u8 dev;
    u8 id;
    NetPacket* p;

    if (!fn_8028D7E8(mask, &dev)) {
        return 0;
    }
    id = fn_8028D234();
    if (id == 0) {
        return id;
    }
    fn_8028CD74(id, dev);
    p = fn_8028CE60(id);
    p->result = BSWAP32(a0);
    p->id = id;
    p->sub = 0;
    p->flags = 0x100;
    fn_8028D460(id);
    return id;
}

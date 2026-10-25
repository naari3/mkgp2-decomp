/* Triforce JVS I/O manager: queues per-node output requests and polls inputs. */
#include <dolphin.h>
#include <string.h>

typedef struct JvsNode {
    /* 0x00 */ u8 pad0[0xAC];
    /* 0xAC */ u8* sw;
    /* 0xB0 */ u8* analog;
    /* 0xB4 */ u8* coin;
    /* 0xB8 */ u8 padB8[0xCC - 0xB8];
    /* 0xCC */ u8 players;
    /* 0xCD */ u8 swBits;
    /* 0xCE */ u8 analogCh;
    /* 0xCF */ u8 coinSlots;
    /* 0xD0 */ u8 analogBits;
    /* 0xD1 */ u8 rotary;
    /* 0xD2 */ u8 keycode;
    /* 0xD3 */ u8 unkD3;
    /* 0xD4 */ u8 unkD4;
    /* 0xD5 */ u8 screenPos;
    /* 0xD6 */ u16 miscSw;
    /* 0xD8 */ u8 extAnalog;
    /* 0xD9 */ u8 unkD9;
    /* 0xDA */ u8 gpOut;
    /* 0xDB */ u8 padDB[5];
} JvsNode;

typedef struct JvsEvent {
    u8 node;
    u8 cmd;
    u8 err;
    u8 pad;
} JvsEvent;

typedef struct JvsReq {
    /* 0x00 */ u8 n;
    /* 0x01 */ u8 pad1[0x80];
    /* 0x81 */ u8 cmd[0x20];
    /* 0xA1 */ u8 rlen[0x20];
    /* 0xC4 */ u32 resp[0x20];
} JvsReq;

typedef struct JvsCmd {
    /* 0x0000 */ u8 pad0[0x84];
    /* 0x0084 */ s32 cur[16];
    /* 0x00C4 */ u8 padC4[0x130C - 0xC4];
    /* 0x130C */ JvsReq req[2][16];
} JvsCmd;

typedef s32 (*JvsHandler)(u8 node, u8 cmd, u32 resp);

typedef struct JvsHandlerEntry {
    JvsHandler fn;
    u8 rlen;
} JvsHandlerEntry;

typedef struct JvsStats {
    s32 total;
    s32 count;
    s32 runs;
    s32 streak;
} JvsStats;

typedef struct JvsOutCfg {
    u8 data[0x10];
} JvsOutCfg;

typedef struct JvsMgrNode {
    /* 0x000 */ u32 flags;
    /* 0x004 */ u32 rawMask;
    /* 0x008 */ JvsStats err;
    /* 0x018 */ u8 arg[0x40];
    /* 0x058 */ void* data[0x40];
    /* 0x158 */ u32 used;
    /* 0x15C */ u8 buf[0x100];
} JvsMgrNode;

typedef struct JvsMgr {
    /* 0x0000 */ BOOL ready;
    /* 0x0004 */ u32 state;
    /* 0x0008 */ JvsMgrNode node[16];
    /* 0x25C8 */ BOOL outPending;
    /* 0x25CC */ JvsOutCfg out;
    /* 0x25DC */ BOOL resetPending;
    /* 0x25E0 */ OSSemaphore sem;
    /* 0x25EC */ JvsHandlerEntry handler[0x20];
    /* 0x26EC */ u8 pad26EC[0x1C];
} JvsMgr;

extern void fn_8028250C(void);
extern BOOL fn_80282AC8(u8 a, u8 b);
extern BOOL fn_80282B54(void);
extern BOOL fn_80282BB0(void);
extern BOOL fn_80282C0C(void);
extern BOOL fn_80282C68(u8 v);
extern BOOL fn_80282CDC(u32 v);
extern BOOL fn_80282DA8(void);
extern BOOL fn_80282E04(void);
extern void fn_80282E60(void);
extern BOOL fn_80282EB8(void);
extern void fn_80282F3C(void);
extern u8 fn_80283E3C(void);
extern JvsEvent fn_80283E54(void);
extern BOOL fn_80283E9C(void);
extern BOOL fn_80284480(u8 len, void* data, u8 rlen);
extern BOOL fn_80284518(u8 a, u16 v);
extern BOOL fn_802845D4(u8 a, u16 v);
extern BOOL fn_80284690(u8 len, void* data);
extern BOOL fn_80284754(u8 len, void* data);
extern BOOL fn_80284834(u8 a, u8 b);
extern BOOL fn_802848D8(u8 a, u8 b);
extern BOOL fn_8028497C(u8 len, void* data);
extern BOOL fn_80284A40(u8 a, u16 v);
extern BOOL fn_80284AFC(u8 a, u16 v);
extern BOOL fn_80284BB8(u8 a);
extern BOOL fn_80284C48(u8 a);
extern BOOL fn_80284CD8(u8 a);
extern BOOL fn_80284D68(void);
extern BOOL fn_80284DE4(u8 a);
extern BOOL fn_80284E78(u8 a);
extern BOOL fn_80284F0C(u8 a);
extern BOOL fn_80284FA0(u8 a, u8 b);
extern BOOL fn_80285048(const char* str);
extern BOOL fn_80285118(void);
extern BOOL fn_80285194(void);
extern BOOL fn_80285210(void);
extern BOOL fn_8028528C(void);
extern BOOL fn_80285308(void);
extern BOOL fn_80285384(u8 a);
extern BOOL fn_80285418(void);
extern BOOL fn_802854B0(void);
extern void fn_80285638(u8 node);
extern void fn_802856A4(void* cb);
extern u8* fn_80285778(void);
extern u8* fn_80285788(void);
extern u8* fn_802857A8(void);
extern JvsNode* fn_802857B8(void);
extern JvsCmd* fn_802857C8(void);
extern void* fn_802857D4(void);
extern s32 fn_80293580(void);
extern void fn_80293AF0(void);
extern void fn_80293B74(void);

static JvsMgr Mgr;

static s16 AnalogBuf[4];
static u32 InitNode;
static u32 InitTimer;

s32 fn_8028A618(s32 node, u8 n, u8* data);
s32 fn_8028A934(s32 node, u8 idx, s16 v);
s32 fn_8028AAC0(s32 node, s16** out, u8* count);

s32 fn_8028A598(s32 node, u8 n, u8* data) {
    OSSemaphore* sem = &Mgr.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028A618(node, n, data);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028A618(s32 node, u8 n, u8* data) {
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    JvsMgrNode* m;
    u32 used;
    u8* p;

    if (node < 1 || node > *count || data == NULL) {
        return 1;
    }
    if (nodes[node].gpOut == 0 || n < 1 || n > (u32)(((nodes[node].gpOut + 7) & ~7) / 8)) {
        return 1;
    }
    m = &Mgr.node[node];
    if ((m->flags & 0x40000) || m->used + n > 0x100) {
        return 4;
    }
    m->flags |= 0x40000;
    used = m->used;
    m->used = used + ((n + 1) & ~1);
    p = &m->buf[used];
    m->arg[18] = n;
    m->data[18] = p;
    memcpy(p, data, n);
    return 0;
}

s32 fn_8028A740(s32 node, u8 ch) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;
    u8* p;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count) {
        ret = 0x80000000;
    } else {
        p = nodes[node].coin;
        if (ch > (u32)(nodes[node].coinSlots - 1)) {
            ret = 0x80000000;
        } else {
            ret = (p[ch * 2] << 8) | p[ch * 2 + 1];
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028A808(s32 node, u8* slots, u8* bits) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count) {
        ret = 1;
    } else {
        if (slots != NULL) {
            *slots = nodes[node].coinSlots;
        }
        if (bits != NULL) {
            *bits = nodes[node].analogBits;
        }
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028A8B4(s32 node, u8 idx, s16 v) {
    OSSemaphore* sem = &Mgr.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028A934(node, idx, v);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028A934(s32 node, u8 idx, s16 v) {
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    JvsMgrNode* m;
    u32 used;
    s16* p;

    if (node < 1 || node > *count) {
        return 1;
    }
    if (nodes[node].analogCh == 0 || idx < 1 || idx > (u32)(nodes[node].analogCh + nodes[node].extAnalog)) {
        return 1;
    }
    m = &Mgr.node[node];
    if ((m->flags & 0x10000) || m->used + 2 > 0x100) {
        return 4;
    }
    m->flags |= 0x10000;
    used = m->used;
    m->used = used + 2;
    p = (s16*)&m->buf[used];
    m->arg[16] = idx;
    m->data[16] = p;
    *p = v;
    return 0;
}

s32 fn_8028AA40(s32 node, s16** out, u8* count) {
    OSSemaphore* sem = &Mgr.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028AAC0(node, out, count);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028AAC0(s32 node, s16** out, u8* chans) {
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    u32 n;
    u8* p;
    s16* dst;

    if (node < 1 || node > *count || out == NULL) {
        return 1;
    }
    if (chans != NULL) {
        *chans = nodes[node].analogCh;
    }
    n = 4;
    if (nodes[node].analogCh <= 4) {
        n = nodes[node].analogCh;
    }
    p = nodes[node].analog;
    if (p == (u8*)nodes) {
        return 5;
    }
    dst = AnalogBuf;
    for (; n > 0; n--) {
        *dst++ = (p[0] << 8) | p[1];
        p += 2;
    }
    *out = AnalogBuf;
    return 0;
}

s32 fn_8028AC1C(s32 node, u8 ch) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;
    u8* p;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count) {
        ret = 0x80000000;
    } else {
        p = nodes[node].analog;
        if (ch > (u32)(nodes[node].analogCh + (nodes[node].extAnalog - 1))) {
            ret = 0x80000000;
        } else {
            ret = (p[ch * 2] << 8) | p[ch * 2 + 1];
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028ACEC(s32 node, u8* chans) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count) {
        ret = 1;
    } else {
        if (chans != NULL) {
            *chans = nodes[node].analogCh;
        }
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028AD94(s32 node, u8** sw, u8* players, u8* bits) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count || sw == NULL) {
        ret = 1;
    } else {
        *sw = nodes[node].sw;
        if (*sw == (u8*)nodes) {
            ret = 5;
        } else {
            if (players != NULL) {
                *players = nodes[node].players;
            }
            if (bits != NULL) {
                *bits = nodes[node].swBits;
            }
            ret = 0;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028AE64(s32 node, u8 player, u8 byte) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;
    u8* p;
    u8 bytes;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count) {
        ret = 0x80000000;
    } else {
        p = nodes[node].sw;
        bytes = (nodes[node].swBits + 7) / 8;
        if (player == 0xFF) {
            ret = p[0];
        } else if (player > (u32)(nodes[node].players - 1) || byte > (u32)(bytes - 1)) {
            ret = 0x80000000;
        } else {
            ret = p[1 + byte + player * bytes];
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028AF48(s32 node, u8* players, u8* bits) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count) {
        ret = 1;
    } else {
        if (players != NULL) {
            *players = nodes[node].players;
        }
        if (bits != NULL) {
            *bits = nodes[node].swBits;
        }
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028AFF4(JvsOutCfg* out) {
    s32 ret;
    OSSemaphore* sem = &Mgr.sem;

    OSWaitSemaphore(sem);
    if (out == NULL) {
        ret = 1;
    } else {
        ret = 0;
        Mgr.outPending = TRUE;
        Mgr.out = *out;
    }
    OSSignalSemaphore(sem);
    return ret;
}

u8 fn_8028B090(void) {
    return *fn_80285788();
}

u8 fn_8028B0B4(void) {
    return *fn_80285778();
}

s32 fn_8028B0D8(s32 node, JvsStats* out) {
    OSSemaphore* sem;

    if (node < 0 || node > 16 || out == NULL) {
        return 1;
    }
    sem = &Mgr.sem;
    OSWaitSemaphore(sem);
    *out = Mgr.node[node].err;
    OSSignalSemaphore(sem);
    return 0;
}

void fn_8028B180(BOOL filter) {
    OSSemaphore* sem = &Mgr.sem;
    JvsMgr* m;
    JvsStats* st;
    JvsEvent ev;
    s32 i;
    s32 n;

    OSWaitSemaphore(sem);
    m = &Mgr;
    for (i = 0; i < 16; i++) {
        m->node[i].err.count = 0;
    }
    if (fn_80283E3C() != 0) {
        for (n = fn_80283E3C(); n > 0; n--) {
            ev = fn_80283E54();
            if (!filter || !((ev.node == 0 && ev.cmd == 0xF0 && (ev.err & 8)) ||
                             (ev.node == 0 && ev.cmd == 0xF1 && (ev.err & 8)) || (ev.cmd == 0x15 && (ev.err & 0x40))))
            {
                st = &Mgr.node[ev.node].err;
                st->total++;
                st->count++;
            }
        }
    }
    for (i = 0; i < 16; i++) {
        st = &m->node[i].err;
        if (m->node[i].err.count > 0) {
            st->runs++;
            st->streak++;
        } else {
            st->streak = 0;
        }
    }
    OSSignalSemaphore(sem);
}

s32 fn_8028B3D0(u8 node, u8 idx) {
    JvsCmd* c = fn_802857C8();
    s32 cur = c->cur[node];
    u32 resp;
    JvsHandler fn;

    resp = c->req[cur][node].resp[idx];
    idx = c->req[cur][node].cmd[idx];
    if ((s32)idx < 0x60 || (s32)idx > 0x7F) {
        return 0;
    }
    fn = Mgr.handler[(u8)idx - 0x60].fn;
    if (fn == NULL) {
        return 0;
    }
    return fn(node, idx, resp);
}

static inline u8 HandlerRlen(s32 cmd) {
    if (cmd < 0x20 || cmd > 0x3F || Mgr.handler[cmd - 0x20].fn == NULL) {
        return 0;
    }
    return Mgr.handler[cmd - 0x20].rlen;
}

s32 fn_8028B48C(s32 node) {
    JvsNode* nodes = fn_802857B8();
    s32 i;
    OSSemaphore* sem;
    JvsMgrNode* m;
    BOOL ok = TRUE;
    BOOL r;

    if (!Mgr.ready) {
        return 5;
    }
    sem = &Mgr.sem;
    OSWaitSemaphore(sem);
    fn_80285638(node);
    m = &Mgr.node[node];
    if (m->flags & 1) {
        ok = ok && fn_80284FA0(nodes[node].players, (nodes[node].swBits + 7) >> 3);
    }
    if (m->flags & 2) {
        ok = ok && fn_80284F0C(nodes[node].analogCh + nodes[node].extAnalog);
    }
    if (m->flags & 4) {
        ok = ok && fn_80284E78(nodes[node].coinSlots);
    }
    if (m->flags & 8) {
        ok = ok && fn_80284DE4(nodes[node].rotary);
    }
    if (m->flags & 0x10) {
        ok = ok && fn_80284D68();
    }
    if (m->flags & 0x20) {
        ok = ok && fn_80284CD8(nodes[node].screenPos);
    }
    if (m->flags & 0x40) {
        ok = ok && fn_80284C48(((nodes[node].miscSw + 7) & ~7) / 8);
    }
    if (m->flags & 0x4000) {
        ok = ok && fn_80284BB8(nodes[node].unkD9);
    }
    if (m->flags & 0x10000) {
        r = FALSE;
        if (ok && fn_80284AFC(m->arg[16], *(u16*)m->data[16])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x20000) {
        r = FALSE;
        if (ok && fn_80284A40(m->arg[17], *(u16*)m->data[17])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x40000) {
        r = FALSE;
        if (ok && fn_8028497C(m->arg[18], m->data[18])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x80000) {
        r = FALSE;
        if (ok && fn_80284754(m->arg[19], m->data[19])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x100000) {
        r = FALSE;
        if (ok && fn_80284690(m->arg[20], m->data[20])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x200000) {
        r = FALSE;
        if (ok && fn_802845D4(m->arg[21], *(u16*)m->data[21])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x400000) {
        r = FALSE;
        if (ok && fn_80284518(m->arg[22], *(u16*)m->data[22])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x800000) {
        r = FALSE;
        if (ok && fn_802848D8(m->arg[23], *(u8*)m->data[23])) {
            r = TRUE;
        }
        ok = r;
    }
    if (m->flags & 0x1000000) {
        r = FALSE;
        if (ok && fn_80284834(m->arg[24], *(u8*)m->data[24])) {
            r = TRUE;
        }
        ok = r;
    }
    for (i = 0x20; i <= 0x3F; i++) {
        if (m->rawMask & (1 << (i - 0x20))) {
            ok = (ok != 0) && (fn_80284480(m->arg[i], m->data[i], HandlerRlen(i)) != 0);
        }
    }
    fn_802854B0();
    m->flags &= 0xFFFF;
    m->rawMask = 0;
    memset(m->arg, 0, sizeof(m->arg));
    memset(m->data, 0, sizeof(m->data));
    m->used = 0;
    memset(m->buf, 0, sizeof(m->buf));
    OSSignalSemaphore(sem);
    return !ok;
}

s32 fn_8028B9A4(void) {
    u8* count = fn_80285778();
    OSSemaphore* sem;
    JvsMgr* mgr;
    s32 i;
    s32 ret;

    fn_80282F3C();
    fn_80282E04();
    for (i = 1; i <= *count; i++) {
        fn_8028B48C(i);
    }
    sem = &Mgr.sem;
    OSWaitSemaphore(sem);
    mgr = &Mgr;
    if (mgr->outPending) {
        mgr->outPending = FALSE;
        if (mgr->out.data[0] == 0x20) {
            fn_80282AC8(1, mgr->out.data[1] & 0x3F);
            fn_80282AC8(0, mgr->out.data[2]);
            fn_80282AC8(7, mgr->out.data[3]);
            fn_80282AC8(8, mgr->out.data[4]);
            fn_80282AC8(9, mgr->out.data[5]);
        }
    }
    if (Mgr.resetPending) {
        Mgr.resetPending = FALSE;
        fn_80282C0C();
    }
    OSSignalSemaphore(sem);
    ret = fn_80293580();
    fn_80282EB8();
    fn_802857D4();
    fn_80282E60();
    fn_8028B180(FALSE);
    return ret == 0 ? 0 : ret;
}

#define NEXT_STATE()  \
    InitTimer = 0;    \
    Mgr.state++;      \
    InitNode = 0

s32 fn_8028BAD0(void) {
    u8* res = fn_802857A8();
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    OSSemaphore* sem;
    JvsNode* n;
    u32 bits;

    if (Mgr.ready) {
        return 0;
    }
    sem = &Mgr.sem;
    OSWaitSemaphore(sem);
    switch (Mgr.state) {
    case 0:
        fn_802856A4(fn_8028B3D0);
        NEXT_STATE();
        break;
    case 1:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80285638(0);
        fn_80285418();
        fn_802854B0();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 2) {
            NEXT_STATE();
        }
        break;
    case 2:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 60) {
            NEXT_STATE();
        }
        break;
    case 3:
        InitTimer++;
        if (!(res[0x17] & 1)) {
            fn_80282F3C();
            fn_80282E04();
            fn_80282EB8();
            fn_80282E60();
            break;
        }
        Mgr.state++;
        InitTimer = 0;
        InitNode = 0;
    case 4:
        if (InitTimer++ == 0 && InitNode == 0) {
            InitNode = 1;
        }
        if (InitNode < 16 && (res[0x17] & 1) && *count == InitNode - 1) {
            fn_80282F3C();
            fn_80285638(0);
            fn_80285384(InitNode);
            fn_802854B0();
            fn_80282EB8();
            fn_80282E60();
            InitTimer = 0;
            Mgr.state++;
            break;
        }
        Mgr.state = 6;
        InitTimer = 0;
        InitNode = 0;
        break;
    case 5:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 3) {
            Mgr.state = 4;
            InitTimer = 0;
            InitNode++;
        }
        break;
    case 6:
        if (InitTimer++ == 0 && InitNode == 0) {
            InitNode = 1;
        }
        if (InitNode <= *count && InitNode < 16) {
            fn_80282F3C();
            fn_80285638(InitNode);
            fn_80285308();
            fn_802854B0();
            fn_80282EB8();
            fn_80282E60();
            InitTimer = 0;
            Mgr.state++;
            break;
        }
        Mgr.state = 10;
        InitTimer = 0;
        InitNode = 0;
        break;
    case 7:
        fn_80282F3C();
        fn_80285638(InitNode);
        fn_8028528C();
        fn_80285210();
        fn_80285194();
        fn_80285118();
        fn_802854B0();
        fn_80282EB8();
        fn_80282E60();
        InitTimer = 0;
        Mgr.state++;
        break;
    case 8:
        fn_80282F3C();
        fn_80285638(InitNode);
        fn_80285048("namco ltd.;GC-AM BASE PCB;Ver1.00;JPN,TRIFORCE");
        fn_802854B0();
        fn_80282EB8();
        fn_80282E60();
        InitTimer = 0;
        Mgr.state++;
        break;
    case 9:
        bits = 0;
        n = &nodes[InitNode];
        if (n->players != 0) {
            bits |= 1;
        }
        if (n->analogCh != 0) {
            bits |= 2;
        }
        if (n->coinSlots != 0) {
            bits |= 4;
        }
        if (n->rotary != 0) {
            bits |= 8;
        }
        if (n->keycode != 0) {
            bits |= 0x10;
        }
        if (n->screenPos != 0) {
            bits |= 0x20;
        }
        if (n->miscSw != 0) {
            bits |= 0x40;
        }
        if (n->unkD9 != 0) {
            bits |= 0x4000;
        }
        InitTimer = 0;
        Mgr.node[InitNode].flags = bits;
        Mgr.state = 6;
        InitNode++;
        break;
    case 10:
        InitTimer++;
        fn_80282F3C();
        fn_80282E04();
        fn_80282EB8();
        fn_80282E60();
        if (InitTimer >= 2) {
            NEXT_STATE();
            OSSignalSemaphore(sem);
            fn_8028B180(TRUE);
            OSWaitSemaphore(sem);
            Mgr.ready = TRUE;
        }
        break;
    }
    OSSignalSemaphore(sem);
    return Mgr.ready ? 0 : 5;
}

s32 fn_8028BFB0(void) {
    fn_80293AF0();
    return 0;
}

static inline void Delay(void) {
    volatile s32 n = 0x196E28;

    while (n-- != 0) {
    }
}

s32 fn_8028BFD4(void) {
    u8* res;

    memset(&Mgr, 0, 0x26EC);
    OSInitSemaphore(&Mgr.sem, 1);
    fn_8028250C();
    res = fn_802857A8();
    if (res[0] != 0) {
        return 2;
    }
    if (res[3] != 0x10) {
        return 3;
    }
    switch (res[4] >> 4) {
    case 2:
        return 3;
    default:
        return 3;
    case 1:
        do {
            fn_80282F3C();
            fn_80282E04();
            fn_80282BB0();
            fn_80282B54();
            fn_80282DA8();
            fn_80282CDC(0x3000);
            fn_80282EB8();
            fn_80282E60();
            Delay();
        } while (res[0] != 0);
        fn_80282F3C();
        fn_80283E9C();
        fn_80282C68(1);
        fn_80282EB8();
        fn_80282E60();
        Delay();
        do {
            fn_80282F3C();
            fn_80282E04();
            fn_80282EB8();
            fn_80282E60();
            Delay();
        } while (!(res[0x17] & 0x10));
        fn_80293B74();
        return 0;
    }
}

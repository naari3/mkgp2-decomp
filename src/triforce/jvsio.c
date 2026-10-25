/* Triforce JVS I/O over SI channel 0. */
#include <dolphin.h>

typedef struct JvsRing {
    /* 0x0 */ u16 size;
    /* 0x2 */ u16 rd;
    /* 0x4 */ u16 wr;
    /* 0x8 */ u8* buf;
    /* 0xC */ u8 state;
    /* 0xD */ u8 unkD;
    /* 0xE */ u8 unkE;
    /* 0xF */ u8 unkF;
} JvsRing;

typedef struct JvsReq {
    /* 0x00 */ u8 n;
    /* 0x01 */ u8 pad1[0x80];
    /* 0x81 */ u8 cmd[0x20];
    /* 0xA1 */ u8 rlen[0x20];
    /* 0xC1 */ u8 padC1[0x144 - 0xC1];
} JvsReq;

typedef struct JvsNode {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[0x65 - 0x1];
    /* 0x65 */ u8 unk65[0x41];
    /* 0xA6 */ u8 unkA6;
    /* 0xA7 */ u8 unkA7;
    /* 0xA8 */ u8 unkA8;
    /* 0xAC */ void* unkAC;
    /* 0xB0 */ void* unkB0;
    /* 0xB4 */ void* unkB4;
    /* 0xB8 */ u8 padB8[0xCC - 0xB8];
    /* 0xCC */ u8 unkCC;
    /* 0xCD */ u8 unkCD;
    /* 0xCE */ u8 unkCE;
    /* 0xCF */ u8 unkCF;
    /* 0xD0 */ u8 unkD0;
    /* 0xD1 */ u8 unkD1;
    /* 0xD2 */ u8 unkD2;
    /* 0xD3 */ u8 unkD3;
    /* 0xD4 */ u8 unkD4;
    /* 0xD5 */ u8 unkD5;
    /* 0xD6 */ u16 unkD6;
    /* 0xD8 */ u8 unkD8;
    /* 0xD9 */ u8 unkD9;
    /* 0xDA */ u8 unkDA;
    /* 0xDB */ u8 unkDB;
    /* 0xDC */ u8 unkDC;
    /* 0xDD */ u8 unkDD;
    /* 0xDE */ u8 unkDE;
    /* 0xDF */ u8 unkDF;
} JvsNode;

typedef struct JvsEvent {
    u8 node;
    u8 cmd;
    u8 err;
    u8 pad;
} JvsEvent;

static struct {
    /* 0x0000 */ u8 buf[0x80];
    /* 0x0080 */ u16 len;
    /* 0x0084 */ s32 cur[16];
    /* 0x00C4 */ s32 next[16];
    /* 0x0104 */ u32 unk104;
    /* 0x0108 */ u8 unk108;
    /* 0x0109 */ u8 nodeCount;
    /* 0x010A */ u8 qrd;
    /* 0x010B */ u8 qwr;
    /* 0x010C */ JvsEvent queue[256];
    /* 0x050C */ JvsNode node[16];
    /* 0x130C */ JvsReq req[2][16];
    /* 0x3B8C */ u8 pad3B8C[0x4FCC - 0x3B8C];
    /* 0x4FCC */ JvsReq* curReq;
    /* 0x4FD0 */ u8 pad4FD0[0x10];
} cmd;

static struct {
    /* 0x000 */ u8 buf[0x80];
    /* 0x080 */ u8 rx[0x80];
    /* 0x100 */ u32 err[4];
    /* 0x110 */ u16 len;
    /* 0x112 */ u8 pad112[2];
    /* 0x114 */ u8 result;
    /* 0x115 */ u8 unk115;
    /* 0x116 */ u8 unk116;
    /* 0x117 */ u8 unk117[3];
    /* 0x11A */ u8 unk11A[0x10];
    /* 0x12A */ u8 unk12A;
    /* 0x12B */ u8 unk12B;
    /* 0x12C */ u8 pad12C[0x134 - 0x12C];
    /* 0x134 */ u8 unk134;
    /* 0x135 */ u8 unk135;
    /* 0x136 */ u8 unk136;
    /* 0x137 */ u8 unk137;
    /* 0x138 */ u32 unk138;
    /* 0x13C */ u8 unk13C[0x10];
    /* 0x14C */ u8 pad14C[0x250 - 0x14C];
    /* 0x250 */ JvsRing ring[2];
} tx;

#define R tx.ring
#define PUT(b) (tx.buf[tx.len++] = (b))
#define CPUT(b) (cmd.buf[cmd.len++] = (b))
#define REQ(c, r) (cmd.curReq->rlen[cmd.curReq->n] = (r), CPUT(c), cmd.curReq->cmd[cmd.curReq->n++] = (c))

static void fn_80282F54(s32 chan, u32 err, OSContext* ctx);
static void fn_80283154(void);

void fn_8028250C(void) {
    int i;
    BOOL ok;
    u8 tries;

    tries = 0;
    tx.result = 0x80;
    tx.unk115 = 0x80;
    tx.unk116 = 0x80;
    tx.unk117[2] = 0;
    tx.unk117[1] = 0;
    tx.unk117[0] = 0;
    tx.unk11A[15] = 0;
    tx.unk11A[14] = 0;
    tx.unk11A[13] = 0;
    tx.unk11A[12] = 0;
    tx.unk11A[11] = 0;
    tx.unk11A[10] = 0;
    tx.unk11A[9] = 0;
    tx.unk11A[8] = 0;
    tx.unk11A[7] = 0;
    tx.unk11A[6] = 0;
    tx.unk11A[5] = 0;
    tx.unk11A[4] = 0;
    tx.unk11A[3] = 0;
    tx.unk11A[2] = 0;
    tx.unk11A[1] = 0;
    tx.unk11A[0] = 0;
    tx.unk12A = 0xFF;
    tx.unk12B = 1;
    tx.unk135 = 0;
    tx.unk134 = 0;
    tx.unk137 = 0;
    tx.unk136 = 0;
    tx.unk138 = 0;
    tx.unk13C[15] = 0;
    tx.unk13C[14] = 0;
    tx.unk13C[13] = 0;
    tx.unk13C[12] = 0;
    tx.unk13C[11] = 0;
    tx.unk13C[10] = 0;
    tx.unk13C[9] = 0;
    tx.unk13C[8] = 0;
    tx.unk13C[7] = 0;
    tx.unk13C[6] = 0;
    tx.unk13C[5] = 0;
    tx.unk13C[4] = 0;
    tx.unk13C[3] = 0;
    tx.unk13C[2] = 0;
    tx.unk13C[1] = 0;
    tx.unk13C[0] = 0;
    R[1].state = 0x80;
    R[0].state = 0x80;
    for (i = 0; i < 16; i++) {
        cmd.cur[i] = 0;
        cmd.next[i] = 1;
    }
    cmd.nodeCount = 0;
    tx.buf[0] = 0;
    do {
        tries++;
        ok = SITransfer(0, tx.buf, 1, tx.unk117, 3, fn_80282F54, 0x13880);
        while (SIIsChanBusy(0)) {
        }
    } while ((!ok || tx.result != 0) && tries != 0);
    do {
        tries++;
        ok = SITransfer(0, tx.buf, 1, tx.unk117, 3, fn_80282F54, 0x13880);
        while (SIIsChanBusy(0)) {
        }
    } while ((!ok || tx.result != 0) && tries != 0);
}

u8 fn_80282708(int ch) {
    u8 c;
    if (R[ch & 0xFF].rd != R[ch & 0xFF].wr) {
        c = R[ch & 0xFF].buf[R[ch & 0xFF].rd++];
        if (R[ch & 0xFF].rd >= R[ch & 0xFF].size) {
            R[ch & 0xFF].rd = 0;
        }
        return c;
    }
    return 0;
}

u16 fn_80282768(u8 ch) {
    if (R[ch].state == 0) {
        if (R[ch].rd <= R[ch].wr) {
            return R[ch].wr - R[ch].rd;
        }
        return R[ch].size + R[ch].wr - R[ch].rd;
    }
    if (R[ch].state == 1) {
        R[ch].wr = 0;
        R[ch].rd = 0;
        R[ch].state = 0;
    }
    return 0xFFFF;
}

void fn_802827E0(u8 ch, u8* buf, u16 size) {
    R[ch].wr = 0;
    R[ch].rd = 0;
    R[ch].size = size;
    R[ch].buf = buf;
    R[ch].unkD = 0;
    R[ch].unkE = 0;
    R[ch].unkF = 0;
    R[ch].state = 0;
}

BOOL fn_80282818(u8 ch, u8* data, u8 len) {
    if (tx.len < 0x7E - len) {
        PUT(((ch & 1) + 1) | 0x30);
        PUT(len);
        while (len != 0) {
            len--;
            PUT(*data++);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL fn_802828B0(u8 ch, u8 v) {
    if (tx.len < 0x7E) {
        PUT((ch & 1) + 0x23);
        PUT(1);
        PUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282928(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f) {
    if (tx.len < 0x78) {
        PUT(0x22);
        PUT(6);
        PUT(a);
        PUT(b);
        PUT(c);
        PUT(d);
        PUT(e);
        PUT(f);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282A24(u8 a, u8 b, u8 c) {
    if (tx.len < 0x7B) {
        PUT(0x21);
        PUT(2);
        PUT(a);
        PUT(b);
        PUT(c);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282AC8(u8 a, u8 b) {
    if (tx.len < 0x7C) {
        PUT(0x60);
        PUT(2);
        PUT(a);
        PUT(b);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282B54(void) {
    if (tx.len < 0x7E) {
        PUT(0x16);
        PUT(0);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282BB0(void) {
    if (tx.len < 0x7E) {
        PUT(0x15);
        PUT(0);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282C0C(void) {
    if (tx.len < 0x7E) {
        PUT(0x14);
        PUT(0);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282C68(u8 v) {
    if (tx.len < 0x7D) {
        PUT(0x12);
        PUT(1);
        PUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282CDC(u32 v) {
    if (tx.len < 0x7A) {
        PUT(0x1F);
        PUT(0);
        PUT(v >> 24);
        PUT(v >> 16);
        PUT(v >> 8);
        PUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282DA8(void) {
    if (tx.len < 0x7E) {
        PUT(0x11);
        PUT(0);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80282E04(void) {
    if (tx.len < 0x7E) {
        PUT(0x10);
        PUT(0);
        return TRUE;
    }
    return FALSE;
}

void fn_80282E60(void) {
    while (SIIsChanBusy(0)) {
    }
    SITransfer(0, tx.buf, 0x80, tx.rx, 0x80, fn_80282F54, 0x1388);
}

BOOL fn_80282EB8(void) {
    int i;
    if (tx.len < 0x80) {
        for (i = 0x7F; i >= tx.len; i--) {
            tx.buf[i] = 0;
        }
        tx.buf[1] = tx.len - 2;
        for (; i >= 0; i--) {
            tx.buf[0x7F] += tx.buf[i];
        }
        tx.buf[0x7F] = ~(tx.buf[0x7F] | tx.buf[0x7F]);
        return TRUE;
    }
    return FALSE;
}

void fn_80282F3C(void) {
    tx.buf[0] = 0x70;
    tx.len = 2;
}

static void fn_80282F54(s32 chan, u32 err, OSContext* ctx) {
    int i;
    int j;
    u8 sum;
    u8 res;

    tx.err[chan] = err;
    if (err != 0) {
        tx.result = 1;
    } else if (chan == 0) {
        if (tx.buf[0] == 0x70) {
            if (tx.rx[0] != 1) {
                tx.result = 2;
            } else {
                sum = 0;
                for (i = 0; i < 0x80; i++) {
                    sum += tx.rx[i];
                }
                if (sum != 0xFF) {
                    tx.result = 4;
                } else if (tx.rx[1] != 0) {
                    tx.result = 0;
                    fn_80283154();
                } else {
                    tx.result = 0x40;
                }
            }
        } else {
            tx.result = 0;
        }
    }
    res = tx.result;
    if (res != 0) {
        for (i = 0; i <= cmd.nodeCount && i < 16; i++) {
            if (cmd.req[cmd.cur[i]][i].n != 0) {
                for (j = 0; j < cmd.req[cmd.cur[i]][i].n; j++) {
                    u8 c = cmd.req[cmd.cur[i]][i].cmd[j];
                    if (cmd.qwr + 1 != cmd.qrd) {
                        cmd.queue[cmd.qwr].node = i;
                        cmd.queue[cmd.qwr].cmd = c;
                        cmd.queue[cmd.qwr].err = res;
                        cmd.queue[cmd.qwr++].pad = 0;
                    }
                }
                cmd.req[cmd.cur[i]][i].n = 0;
            }
            if (cmd.req[cmd.next[i]][i].n != 0) {
                cmd.cur[i] = cmd.next[i];
            }
        }
    }
}

u8 fn_80283E3C(void) {
    return cmd.qwr - cmd.qrd;
}

JvsEvent fn_80283E54(void) {
    if (cmd.qwr == cmd.qrd) {
        return cmd.queue[cmd.qrd];
    }
    return cmd.queue[cmd.qrd++];
}

static inline BOOL jvsPut60(u8 a, u8 b) {
    if (tx.len < 0x7C) {
        PUT(0x60);
        PUT(2);
        PUT(a);
        PUT(b);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80283E9C(void) {
    BOOL ok = TRUE;
    ok &= jvsPut60(0, 0x1a);
    ok &= jvsPut60(1, 0xe);
    ok &= jvsPut60(2, 0x0);
    ok &= jvsPut60(3, 0x0);
    ok &= jvsPut60(4, 0x0);
    ok &= jvsPut60(5, 0x0);
    ok &= jvsPut60(6, 0x0);
    ok &= jvsPut60(7, 0xff);
    ok &= jvsPut60(8, 0xff);
    ok &= jvsPut60(9, 0xff);
    ok &= jvsPut60(10, 0xc0);
    return ok;
}

BOOL fn_80284480(u8 len, u8* data, u8 rlen) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7B - len) {
        cmd.curReq->rlen[cmd.curReq->n] = rlen;
        cmd.curReq->cmd[cmd.curReq->n++] = *data;
        while (len != 0) {
            len--;
            CPUT(*data++);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284518(u8 a, u16 v) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x77) {
        REQ(0x36, 1);
        CPUT(a);
        CPUT(v >> 8);
        CPUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_802845D4(u8 a, u16 v) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x77) {
        REQ(0x35, 1);
        CPUT(a);
        CPUT(v >> 8);
        CPUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284690(u8 len, u8* data) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79 - len) {
        REQ(0x34, 1);
        CPUT(len);
        while (len != 0) {
            len--;
            CPUT(*data++);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284754(u8 len, u16* data) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79 - len * 2) {
        REQ(0x33, 1);
        CPUT(len);
        while (len != 0) {
            len--;
            CPUT((*data >> 8) & 0xFF);
            CPUT(*data++);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284834(u8 a, u8 b) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x78) {
        REQ(0x38, 1);
        CPUT(a);
        CPUT(b);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_802848D8(u8 a, u8 b) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x78) {
        REQ(0x37, 1);
        CPUT(a);
        CPUT(b);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_8028497C(u8 len, u8* data) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79 - len) {
        REQ(0x32, 1);
        CPUT(len);
        while (len != 0) {
            len--;
            CPUT(*data++);
        }
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284A40(u8 a, u16 v) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x77) {
        REQ(0x31, 1);
        CPUT(a);
        CPUT(v >> 8);
        CPUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284AFC(u8 a, u16 v) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x77) {
        REQ(0x30, 1);
        CPUT(a);
        CPUT(v >> 8);
        CPUT(v);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284BB8(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0x2E, 5);
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284C48(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0x26, a + 1);
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284CD8(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0x25, 5);
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284D68(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7A) {
        REQ(0x24, 2);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284DE4(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0x23, a * 2 + 1);
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284E78(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0x22, a * 2 + 1);
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284F0C(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0x21, a * 2 + 1);
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80284FA0(u8 a, u8 b) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x78) {
        REQ(0x20, a * b + 2);
        CPUT(a);
        CPUT(b);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80285048(u8* str) {
    u16 saved;
    if (cmd.curReq->n < 0x1F) {
        saved = cmd.len;
        if (saved < 0x7A) {
            REQ(0x15, 1);
            do {
                CPUT(*str);
            } while (*str++ != 0);
            if (cmd.len >= 0x7B) {
                cmd.curReq->n--;
                cmd.len = saved;
                return FALSE;
            }
            return TRUE;
        }
    }
    return FALSE;
}

BOOL fn_80285118(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7A) {
        REQ(0x14, 0xFC);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80285194(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7A) {
        REQ(0x13, 2);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80285210(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7A) {
        REQ(0x12, 2);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_8028528C(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7A) {
        REQ(0x11, 2);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80285308(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x7A) {
        REQ(0x10, 0xFF);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80285384(u8 a) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0xF1, 1);
        cmd.unk108 = a;
        CPUT(a);
        return TRUE;
    }
    return FALSE;
}

BOOL fn_80285418(void) {
    if (cmd.curReq->n < 0x1F && cmd.len < 0x79) {
        REQ(0xF0, 0);
        CPUT(0xD9);
        cmd.nodeCount = 0;
        return TRUE;
    }
    return FALSE;
}

BOOL fn_802854B0(void) {
    int i;
    u16 start;
    u8 c;
    if (tx.len < 0x7F - cmd.len) {
        cmd.buf[1] = cmd.len - 1;
        PUT((cmd.buf[0] & 0x1F) | 0x40);
        if (cmd.buf[0] == 0) {
            cmd.buf[0] = 0xFF;
        }
        cmd.buf[cmd.len] = 0;
        for (i = 0; i < cmd.len; i++) {
            cmd.buf[cmd.len] += cmd.buf[i];
        }
        start = tx.len++;
        PUT(0xE0);
        for (i = 0; i <= cmd.len; i++) {
            c = cmd.buf[i];
            if (c == 0xD0 || c == 0xE0) {
                PUT(0xD0);
                PUT(c - 1);
            } else {
                PUT(c);
            }
        }
        tx.buf[start] = tx.len - start - 1;
        if (tx.len > 0x80) {
            tx.len = 0x80;
            return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}

void fn_80285638(u8 node) {
    if (cmd.next[node] == 2) {
        cmd.next[node] = 0;
    } else {
        cmd.next[node]++;
    }
    cmd.buf[0] = node;
    cmd.len = 2;
    cmd.curReq = &cmd.req[cmd.next[node]][node];
    cmd.curReq->n = 0;
}

void fn_802856A4(u32 v) {
    int i;
    int j;
    cmd.qwr = 0;
    cmd.qrd = 0;
    cmd.unk104 = v;
    for (i = 0; i < 16; i++) {
        cmd.node[i].unk0 = 0;
        cmd.node[i].unkA6 = 0;
        cmd.node[i].unkA7 = 0;
        cmd.node[i].unkA8 = 0;
        cmd.node[i].unk65[0] = 0;
        cmd.node[i].unkAC = cmd.node;
        cmd.node[i].unkB0 = cmd.node;
        cmd.node[i].unkB4 = cmd.node;
        for (j = 0; j < 0x41; j++) {
            cmd.node[i].unk65[j] = 0;
        }
        cmd.node[i].unkCC = 0;
        cmd.node[i].unkCD = 0;
        cmd.node[i].unkCE = 0;
        cmd.node[i].unkCF = 0;
        cmd.node[i].unkD0 = 0;
        cmd.node[i].unkD1 = 0;
        cmd.node[i].unkD2 = 0;
        cmd.node[i].unkD3 = 0;
        cmd.node[i].unkD4 = 0;
        cmd.node[i].unkD5 = 0;
        cmd.node[i].unkD6 = 0;
        cmd.node[i].unkD8 = 0;
        cmd.node[i].unkD9 = 0;
        cmd.node[i].unkDA = 0;
        cmd.node[i].unkDB = 0;
        cmd.node[i].unkDC = 0;
        cmd.node[i].unkDD = 0;
        cmd.node[i].unkDE = 0;
        cmd.node[i].unkDF = 0;
    }
}

u8* fn_80285778(void) {
    return &cmd.nodeCount;
}

u8* fn_80285788(void) {
    return &tx.unk12A;
}

JvsRing* fn_80285798(void) {
    return tx.ring;
}

u8* fn_802857A8(void) {
    return &tx.result;
}

JvsNode* fn_802857B8(void) {
    return cmd.node;
}

void* fn_802857C8(void) {
    return &cmd;
}

void* fn_802857D4(void) {
    return &tx;
}

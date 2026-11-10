#include "game/types/shared_data.h"
#ifndef __MWERKS__ /* the names other units use (tools/alias_census.py) */
/* In front of the headers on purpose: JvsReq has a member called `cmd`, and
 * the macro has to rename it in its declaration as well as in its uses. */
#define cmd jvsio_bss_8067E2A0
#define tx jvsio_bss_80683280
#endif
#include <triforce/jvsio_private.h>
#include <triforce/jvsio_packet_private.h>

SHARED_BSS JvsCmd cmd;
SHARED_BSS JvsTx tx;

#define R tx.ring
#define PUT(b) (tx.buf[tx.len++] = (b))
#define CPUT(b) (cmd.buf[cmd.len++] = (b))
#define REQ(c, r) (cmd.curReq->rlen[cmd.curReq->n] = (r), CPUT(c), cmd.curReq->cmd[cmd.curReq->n++] = (c))

static void fn_80282F54(s32 chan, u32 err, OSContext* ctx);
void fn_80283154(void);

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
        PUT((v >> 24) & 0xFF);
        PUT((v >> 16) & 0xFF);
        PUT((v >> 8) & 0xFF);
        PUT(v & 0xFF);
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

static inline void jvsFailReplies(u8 res, int *nodeIndex, int *commandIndex) {
    for ((*nodeIndex) = 0; (*nodeIndex) <= cmd.nodeCount && (*nodeIndex) < 16; (*nodeIndex)++) {
        if (cmd.req[cmd.cur[(*nodeIndex)]][(*nodeIndex)].n != 0) {
            for ((*commandIndex) = 0; (*commandIndex) < cmd.req[cmd.cur[(*nodeIndex)]][(*nodeIndex)].n; (*commandIndex)++) {
                u8 c = cmd.req[cmd.cur[(*nodeIndex)]][(*nodeIndex)].cmd[(*commandIndex)];
                if (cmd.qwr + 1 != cmd.qrd) {
                    cmd.queue[cmd.qwr].node = (*nodeIndex);
                    cmd.queue[cmd.qwr].cmd = c;
                    cmd.queue[cmd.qwr].err = res;
                    cmd.queue[cmd.qwr++].pad = 0;
                }
            }
            cmd.req[cmd.cur[(*nodeIndex)]][(*nodeIndex)].n = 0;
        }
        if (cmd.req[cmd.next[(*nodeIndex)]][(*nodeIndex)].n != 0) {
            cmd.cur[(*nodeIndex)] = cmd.next[(*nodeIndex)];
        }
    }
}


static void fn_80282F54(s32 chan, u32 err, OSContext* ctx) {
    int checksumIndex;
    int nodeIndex;
    int commandIndex;
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
                for (checksumIndex = 0; checksumIndex < 0x80; checksumIndex++) {
                    sum += tx.rx[checksumIndex];
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
        jvsFailReplies(res, &nodeIndex, &commandIndex);
    }
}


/* Decode the SI response and dispatch each JVS reply. */
void fn_80283154(void) {
    JvsPacket* packet;
    int command;
    u8 status[16];
    int i, j, k, pos, count;
    /* separate counters per loop: one shared j is a single web in the colouring (mwccdbg) */
    int nameLen, rx1, rx0, idByte, sumIdx;
    int bank;
    u8 node, commandIndex;
    u8 sum;
    u8* p;
    u8* out;
    for (i = 0; i < 16 && i <= cmd.nodeCount; i++) status[i] = 0;
    tx.packetCount = 0;
    for (i = 2; i < tx.rx[1]; i += tx.rx[i + 1] + 2) {
        tx.packet[tx.packetCount++] = &tx.rx[i];
    }
    for (i = 0; i < tx.packetCount; i++) {
        packet = (JvsPacket*)tx.packet[i];
        switch (command = packet->command) {
        case 0x10:
            tx.unk12A = tx.packet[i][2]; tx.unk12B = tx.packet[i][3]; break;
        case 0x11:
            for (idByte = 0; idByte < 16; idByte++) tx.unk11A[idByte] = tx.packet[i][idByte + 2];
            break;
        case 0x14:
            tx.analog[0] = (tx.packet[i][2] << 8) | tx.packet[i][3];
            tx.analog[1] = (tx.packet[i][4] << 8) | tx.packet[i][5];
            tx.analog[2] = (tx.packet[i][6] << 8) | tx.packet[i][7];
            tx.analog[3] = (tx.packet[i][8] << 8) | tx.packet[i][9]; break;
        case 0x15:
            tx.unk134 = tx.packet[i][2]; tx.unk135 = tx.packet[i][3]; break;
        case 0x16:
            tx.unk136 = tx.packet[i][2]; tx.unk137 = tx.packet[i][3]; break;
        case 0x1F:
            tx.unk138 = (tx.packet[i][2] << 24) | (tx.packet[i][3] << 16) |
                        (tx.packet[i][4] << 8) | tx.packet[i][5];
            for (j = 0; j < 16; j++) tx.unk13C[j] = tx.packet[i][j + 6];
            break;
        case 0x23:
            R[0].unkD = tx.packet[i][2]; R[0].unkE = tx.packet[i][3]; R[0].unkF = tx.packet[i][4]; break;
        case 0x24:
            R[1].unkD = tx.packet[i][2]; R[1].unkE = tx.packet[i][3]; R[1].unkF = tx.packet[i][4]; break;
        case 0x31:
            for (rx0 = 0; rx0 < tx.packet[i][1]; rx0++) {
                if (R[0].wr + 1 == R[0].rd + (R[0].rd == 0) * R[0].size) R[0].state = 1;
                else if (R[0].state == 0) {
                    R[0].buf[R[0].wr++] = tx.packet[i][rx0 + 2];
                    if (R[0].wr >= R[0].size) R[0].wr = 0;
                }
            }
            break;
        case 0x32:
            for (rx1 = 0; rx1 < tx.packet[i][1]; rx1++) {
                if (R[1].wr + 1 == R[1].rd + (R[1].rd == 0) * R[1].size) R[1].state = 1;
                else if (R[1].state == 0) {
                    R[1].buf[R[1].wr++] = tx.packet[i][rx1 + 2];
                    if (R[1].wr >= R[1].size) R[1].wr = 0;
                }
            }
            break;
        case 0xE0: tx.unk115 = tx.packet[i][2]; break;
        case 0xE1: tx.unk116 = tx.packet[i][2]; break;
        default:
            if ((command & 0xE0) != 0x40) break;
            if (packet->length != 0) { node = command & 0x1F; bank = cmd.cur[node]; }
            else status[node] = 1;
            if (packet->length == 0 || packet->payload[1] != 0) break;
            count = 0;
            for (j = 2; j < packet->length; j++) {
                if (packet->payload[j] == 0xD0) cmd.req[bank][node].response[count++] = packet->payload[++j] + 1;
                else cmd.req[bank][node].response[count++] = packet->payload[j];
            }
            sum = packet->payload[1];
            for (j = 0; j < count - 1; j++) sum += cmd.req[bank][node].response[j];
            if (sum != cmd.req[bank][node].response[j]) status[node] = 4;
            else status[node] = 5;
            if (status[node] != 5) break;
            pos = 2;
            if (cmd.req[bank][node].response[1] == 1 || cmd.req[bank][node].response[1] == 2) {
                for (sumIdx = 0; sumIdx < cmd.req[bank][node].n; sumIdx++) {
                    cmd.req[bank][node].reply[sumIdx] = &cmd.req[bank][node].response[pos];
                    if (cmd.req[bank][node].rlen[sumIdx] & 0x80) {
                        while (pos <= cmd.req[bank][node].response[0] && cmd.req[bank][node].response[pos] != 0) pos -= (s8)cmd.req[bank][node].rlen[sumIdx];
                        pos++;
                    } else if (cmd.req[bank][node].rlen[pos] != 0 && cmd.req[bank][node].response[pos] == 2) pos++;
                    else pos += cmd.req[bank][node].rlen[sumIdx];
                }
                if (node == 0) {
                    if (cmd.req[bank][node].cmd[0] == 0xF1 && cmd.req[bank][node].reply[0][0] == 1) cmd.nodeCount = cmd.unk108;
                    break;
                }
                for (commandIndex = 0; commandIndex < cmd.req[bank][node].n; commandIndex++) {
                    u32 replyStatus;
                    p = cmd.req[bank][node].reply[commandIndex];
                    replyStatus = p[0];
                    if (replyStatus == 1) {
                        switch (cmd.req[bank][node].cmd[commandIndex]) {
                        case 0x20: cmd.node[node].unkAC = p + 1; break;
                        case 0x21: cmd.node[node].unkB0 = p + 1; break;
                        case 0x22: cmd.node[node].unkB4 = p + 1; break;
                        case 0x23: cmd.node[node].unkB8 = p + 1; break;
                        case 0x24: cmd.node[node].unkC0 = p + 1; break;
                        case 0x25: cmd.node[node].unkBC = p[1]; break;
                        case 0x26: cmd.node[node].unkC4 = p + 1; break;
                        case 0x10:
                            out = &cmd.node[node].unk0;
                            for (j = 1; j < 0x65 && p[j] != 0; j++) *out++ = p[j];
                            *out = 0; break;
                        case 0x11: cmd.node[node].unkA6 = p[1]; break;
                        case 0x12: cmd.node[node].unkA7 = p[1]; break;
                        case 0x13: cmd.node[node].unkA8 = p[1]; break;
                        case 0x14:
                            out = cmd.node[node].unk65;
                            for (nameLen = 1; nameLen <= 0x40 && p[nameLen] != 0;) {
                                *out++ = p[nameLen++]; *out++ = p[nameLen++]; *out++ = p[nameLen++]; *out++ = p[nameLen++];
                            }
                            *out = 0;
                            for (k = 0; k < nameLen - 1; k += 4) {
                                out = cmd.node[node].unk65;
                                switch (out[k]) {
                                case 1: cmd.node[node].unkCC = out[k+1]; cmd.node[node].unkCD = out[k+2]; break;
                                case 2: cmd.node[node].unkCE = out[k+1]; break;
                                case 3: cmd.node[node].unkCF = out[k+1]; cmd.node[node].unkD0 = out[k+2]; break;
                                case 4: cmd.node[node].unkD1 = out[k+1]; break;
                                case 5: cmd.node[node].unkD2 = out[k+1]; break;
                                case 6: cmd.node[node].unkD3 = out[k+1]; cmd.node[node].unkD4 = out[k+2]; cmd.node[node].unkD5 = out[k+3]; break;
                                case 7: cmd.node[node].unkD6 = (out[k+1] << 8) | out[k+2]; break;
                                case 0x10: cmd.node[node].unkD8 = out[k+1]; break;
                                case 0x11: cmd.node[node].unkD9 = out[k+1]; break;
                                case 0x12: cmd.node[node].unkDA = out[k+1]; break;
                                case 0x13: cmd.node[node].unkDB = out[k+1]; break;
                                case 0x14: cmd.node[node].unkDC = out[k+1]; cmd.node[node].unkDD = out[k+2]; cmd.node[node].unkDE = out[k+3]; break;
                                case 0x15: cmd.node[node].unkDF = 1; break;
                                }
                            }
                            break;
                        default:
                            if (cmd.unk104 != 0 && ((u8 (*)(u8, u8))cmd.unk104)(node, commandIndex)) status[node] = 7;
                            break;
                        }
                    } else {
                        if (cmd.req[bank][node].response[1] == 1) {
                            u8 c = cmd.req[bank][node].cmd[commandIndex];
                            if (cmd.qwr + 1 != cmd.qrd) {
                                cmd.queue[cmd.qwr].node = node;
                                cmd.queue[cmd.qwr].cmd = c;
                                cmd.queue[cmd.qwr].err = 0x20;
                                cmd.queue[cmd.qwr++].pad = replyStatus;
                            }
                        } else {
                            u8 c = cmd.req[bank][node].cmd[commandIndex];
                            if (cmd.qwr + 1 != cmd.qrd) {
                                cmd.queue[cmd.qwr].node = node;
                                cmd.queue[cmd.qwr].cmd = c;
                                cmd.queue[cmd.qwr].err = 0x40;
                                cmd.queue[cmd.qwr++].pad = 0;
                            }
                        }
                    }
                }
            } else {
                status[node] = 3;
            }
            break;
        }
    }
    for (i = 0; i <= cmd.nodeCount && i < 16; i++) {
        if (cmd.req[cmd.cur[i]][i].n != 0) {
            if (status[i] == 0 || status[i] == 1) {
                status[i] = 6;
                for (j = 0; j < cmd.req[cmd.cur[i]][i].n; j++) {
                    u8 c = cmd.req[cmd.cur[i]][i].cmd[j];
                    if (cmd.qwr + 1 != cmd.qrd) {
                        cmd.queue[cmd.qwr].node = i; cmd.queue[cmd.qwr].cmd = c;
                        cmd.queue[cmd.qwr].err = 8; cmd.queue[cmd.qwr++].pad = 0;
                    }
                }
            } else if (status[i] == 4) {
                for (j = 0; j < cmd.req[cmd.cur[i]][i].n; j++) {
                    u8 c = cmd.req[cmd.cur[i]][i].cmd[j];
                    if (cmd.qwr + 1 != cmd.qrd) {
                        cmd.queue[cmd.qwr].node = i; cmd.queue[cmd.qwr].cmd = c;
                        cmd.queue[cmd.qwr].err = 0x10; cmd.queue[cmd.qwr++].pad = 0;
                    }
                }
            }
            cmd.req[cmd.cur[i]][i].n = 0;
        }
        if (cmd.req[cmd.next[i]][i].n != 0) cmd.cur[i] = cmd.next[i];
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

static inline BOOL jvsTxHasSpace(u16 length) {
    return tx.len < 0x7F - length;
}

BOOL fn_802854B0(void) {
    int i;
    int len;
    int start;
    u8 c;
    if (jvsTxHasSpace(cmd.len)) {
        cmd.buf[1] = cmd.len - 1;
        PUT((cmd.buf[0] & 0x1F) | 0x40);
        if (cmd.buf[0] == 0) {
            cmd.buf[0] = 0xFF;
        }
        cmd.buf[cmd.len] = 0;
        for (i = 0; i < (len = cmd.len); i++) {
            cmd.buf[cmd.len] += cmd.buf[i];
        }
        start = tx.len++;
        PUT(0xE0);
        for (i = 0; i <= len; i++) {
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

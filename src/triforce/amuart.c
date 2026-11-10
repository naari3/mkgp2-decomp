/* Triforce JVS-side serial channels: two receive rings filled by the JVS
 * I/O layer, drained into a scratch buffer and forwarded each frame. */
#include <dolphin.h>
#include <string.h>

#include <triforce/amuart_private.h>

extern u8 fn_80282708(u8 ch);
extern u16 fn_80282768(u8 ch);
extern void fn_802827E0(u8 ch, u8* buf, u16 size);
extern BOOL fn_80282818(u8 ch, u8* data, u8 len);
extern BOOL fn_802828B0(u8 ch, u8 v);
extern BOOL fn_80282928(u8 a, u8 b, u8 c, u8 d, u8 e, u8 f);
extern BOOL fn_80282A24(u8 a, u8 b, u8 c);
extern JvsPort* fn_80285798(void);
extern u8* fn_802857A8(void);

static inline s32 RingCount(s32 ch, s32* n) {
    UartChan* c;

    if (ch < 0 || ch > 1 || n == NULL) {
        return 1;
    }
    c = &amuart_bss_806A1D60.chan[ch];
    if (c->head >= c->tail) {
        *n = c->head - c->tail;
    } else {
        *n = c->size + c->head - c->tail;
    }
    return 0;
}

static inline s32 RingRead(s32 ch, u8* dst, s32 len) {
    UartChan* c = &amuart_bss_806A1D60.chan[ch];
    s32 n;

    if (ch < 0 || ch > 1) {
        return 1;
    }
    while (c->tail + len >= c->size) {
        memcpy(dst, c->buf + c->tail, c->size - c->tail);
        n = c->size - c->tail;
        c->tail = 0;
        len -= n;
        dst += n;
    }
    memcpy(dst, c->buf + c->tail, len);
    c->tail += len;
    return 0;
}

static inline s32 UartRead(s32 ch, u8* dst, s32* len) {
    s32 n;

    if (ch < 0 || ch > 1) {
        return 1;
    }
    if (RingCount(ch, &n)) {
        return 1;
    }
    if (n < *len) {
        *len = n;
    }
    if (RingRead(ch, dst, *len)) {
        return 1;
    }
    return 0;
}

u8 fn_8029321C(s32 ch) {
    u8 ret;
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;

    OSWaitSemaphore(sem);
    if (ch < 0 || ch > 1) {
        ret = 0;
    } else {
        ret = fn_80282708(ch);
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_80293290(s32 ch, s32* out) {
    s32 ret;
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;
    u16 n;

    OSWaitSemaphore(sem);
    if (ch < 0 || ch > 1 || out == NULL) {
        ret = 1;
    } else {
        n = fn_80282768(ch);
        if (n == 0xFFFF) {
            ret = 1;
            *out = 0;
        } else {
            *out = n;
            ret = 0;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_80293338(s32 ch, u8 b) {
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;
    s32 ret;
    s32 n;
    UartChan* c;

    OSWaitSemaphore(sem);
    if (RingCount(ch, &n)) {
        ret = 1;
    } else {
        c = &amuart_bss_806A1D60.chan[ch];
        if (n >= c->size - 1) {
            ret = 2;
        } else {
            c->buf[c->head++] = b;
            if (c->head >= c->size) {
                c->head = 0;
            }
            ret = 0;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8029345C(s32 ch, u8* data, u32 len) {
    OSSemaphore* sem;
    s32 ret = 0;
    UartChan* c;
    s32 n;
    JvsPort* port;

    if (ch < 0 || ch > 1) {
        return 1;
    }
    c = &amuart_bss_806A1D60.chan[ch];
    if (c->newFirm != 0) {
        port = fn_80285798();
        port += ch;
        if (port->flags & 3) {
            ret = 1;
            sem = &amuart_bss_806A1D60.sem;
            OSWaitSemaphore(sem);
            c->tail = c->head;
            n = fn_80282768(ch);
            if (n != 0xFFFF) {
                while (n-- > 0) {
                    fn_80282708(ch);
                }
            }
            OSSignalSemaphore(sem);
        }
        if (!fn_802828B0(ch, ret == 1)) {
            ret = 1;
        }
        if (ret != 0) {
            return ret;
        }
    }
    if (!fn_80282818(ch, data, len)) {
        ret = 1;
    }
    return ret;
}

s32 fn_80293580(void) {
    UartChan* c;
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;
    s32 err = 0;
    s32 ch = 0;
    s32 active;
    s32 len;

    do {
        c = &amuart_bss_806A1D60.chan[ch];
        OSWaitSemaphore(sem);
        if (c->cfgPending != 0) {
            c->cfgPending = 0;
            if (ch == 0) {
                if (!fn_80282A24(((u8*)&c->cfg)[0], ((u8*)&c->cfg)[1], ((u8*)&c->cfg)[2])) {
                    err |= 1;
                }
            } else if (!fn_80282928(((u8*)&c->cfg)[0], ((u8*)&c->cfg)[1], ((u8*)&c->cfg)[2],
                                    ((u8*)&c->cfg)[3], ((u8*)&c->cfg)[4], ((u8*)&c->cfg)[5])) {
                err |= 2;
            }
        }
        active = c->active;
        OSSignalSemaphore(sem);
        if (active != 0) {
            OSWaitSemaphore(sem);
            len = c->maxRead;
            if (UartRead(ch, amuart_bss_806A1CE0, &len)) {
                len = 0;
                err |= 4 << ch;
            }
            OSSignalSemaphore(sem);
            if (fn_8029345C(ch, amuart_bss_806A1CE0, len)) {
                err |= 4 << ch;
            }
        }
        ch++;
    } while (ch < 2);
    return err;
}

s32 fn_802937C8(s32 ch, u16 max) {
    UartChan* c;

    if (ch < 0 || ch > 1 || max > 0x7F) {
        return 1;
    }
    c = &amuart_bss_806A1D60.chan[ch];
    c->maxRead = max;
    return 0;
}

s32 fn_80293808(void) {
    UartChan* c = &amuart_bss_806A1D60.chan[1];
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;

    OSWaitSemaphore(sem);
    c->active = 0;
    c->cfgPending = 0;
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80293860(u8* txBuf, u16 txSize, u8* rxBuf, u16 rxSize, UartCfg* cfg) {
    OSSemaphore* sem;
    UartChan* c = &amuart_bss_806A1D60.chan[1];
    u8* info;
    u16 ver;

    if (rxBuf == NULL || rxSize == 0 || txBuf == NULL || txSize == 0 || cfg == NULL) {
        return 1;
    }
    sem = &amuart_bss_806A1D60.sem;
    OSWaitSemaphore(sem);
    c->active = 1;
    c->cfgPending = 1;
    c->maxRead = 0x20;
    c->buf = rxBuf;
    c->size = rxSize;
    c->head = 0;
    c->tail = 0;
    memcpy(&c->cfg, cfg, sizeof(UartCfg));
    info = fn_802857A8();
    ver = (info[0x20] << 8) | info[0x21];
    c->newFirm = FALSE;
    c->newFirm = (ver >= 0x37 && ver <= 0x999);
    c->cfg.enable = 1;
    c->cfg.mode = 1;
    c->cfg.parity = 0;
    c->cfg.baud = 15;
    c->cfg.stop = 0;
    fn_802827E0(1, txBuf, txSize);
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80293998(void) {
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;

    OSWaitSemaphore(sem);
    amuart_bss_806A1D60.chan[0].active = 0;
    amuart_bss_806A1D60.chan[0].cfgPending = 0;
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_802939F0(u8* txBuf, u16 txSize, u8* rxBuf, u16 rxSize, u8* cfg) {
    OSSemaphore* sem;
    UartChan* c = &amuart_bss_806A1D60.chan[0];
    u8* info;
    u16 ver;

    if (rxBuf == NULL || rxSize == 0 || txBuf == NULL || txSize == 0 || cfg == NULL) {
        return 1;
    }
    sem = &amuart_bss_806A1D60.sem;
    OSWaitSemaphore(sem);
    c->active = 1;
    c->cfgPending = 1;
    c->maxRead = 0x20;
    c->buf = rxBuf;
    c->size = rxSize;
    c->head = 0;
    c->tail = 0;
    memcpy(&c->cfg, cfg, 3);
    info = fn_802857A8();
    ver = (info[0x20] << 8) | info[0x21];
    c->newFirm = FALSE;
    c->newFirm = (ver >= 0x37 && ver <= 0x999);
    fn_802827E0(0, txBuf, txSize);
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80293AF0(void) {
    OSSemaphore* sem = &amuart_bss_806A1D60.sem;
    UartChan* c;

    OSWaitSemaphore(sem);
    amuart_bss_806A1D60.chan[0].active = 0;
    amuart_bss_806A1D60.chan[0].cfgPending = 0;
    OSSignalSemaphore(sem);
    c = &amuart_bss_806A1D60.chan[1];
    OSWaitSemaphore(sem);
    c->active = 0;
    c->cfgPending = 0;
    OSSignalSemaphore(sem);
    return 0;
}

s32 fn_80293B74(void) {
    memset(&amuart_bss_806A1D60, 0, sizeof(UartState));
    OSInitSemaphore(&amuart_bss_806A1D60.sem, 1);
    return 0;
}

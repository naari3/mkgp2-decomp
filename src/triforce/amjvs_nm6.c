#include <triforce/amjvs_internal.h>

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

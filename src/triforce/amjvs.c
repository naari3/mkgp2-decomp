#include <triforce/amjvs_internal.h>

JvsMgr amjvs_bss_806910B8;

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

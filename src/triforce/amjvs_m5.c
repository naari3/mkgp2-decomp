#include <triforce/amjvs_internal.h>

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

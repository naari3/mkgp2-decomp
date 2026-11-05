#include <triforce/amjvs_internal.h>

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

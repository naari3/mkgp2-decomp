#include <triforce/amjvs_internal.h>

s32 fn_8028A740(s32 node, u32 ch) {
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
        if ((u8)ch > (u32)(nodes[node].coinSlots - 1)) {
            ret = 0x80000000;
        } else {
            ret = p[((ch << 1) & 0x1FE) + 1] | (p[((ch << 1) & 0x1FE)] << 8);
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

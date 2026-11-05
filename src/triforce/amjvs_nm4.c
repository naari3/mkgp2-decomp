#include <triforce/amjvs_internal.h>

s32 fn_8028AE64(s32 node, u8 player, u8 byte) {
    s32 ret;
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    u8 bytes;
    u8* p;

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

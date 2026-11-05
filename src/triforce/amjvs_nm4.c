#include <triforce/amjvs_internal.h>

static inline s32 ReadSwitch(s32 node, u8 player, u8 byte) {
    s32 ret;
    u8* count;
    JvsNode* nodes;
    u8* p;
    u8 bytes;
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
    return ret;
}

s32 fn_8028AE64(s32 node, u8 player, u8 byte) {
    OSSemaphore* sem = &Mgr.sem;
    s32 ret;
    OSWaitSemaphore(sem);
    ret = ReadSwitch(node, player, byte);
    OSSignalSemaphore(sem);
    return ret;
}

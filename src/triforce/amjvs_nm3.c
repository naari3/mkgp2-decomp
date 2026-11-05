#include <triforce/amjvs_internal.h>

s16 lbl_806D1E30[4];

s32 fn_8028AAC0(s32 node, s16** out, u8* chans) {
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    u32 n;
    u8* p;
    s16* dst;

    if (node < 1 || node > *count || out == NULL) {
        return 1;
    }
    if (chans != NULL) {
        *chans = nodes[node].analogCh;
    }
    n = 4;
    if (nodes[node].analogCh <= 4) {
        n = nodes[node].analogCh;
    }
    p = nodes[node].analog;
    if (p == (u8*)nodes) {
        return 5;
    }
    dst = AnalogBuf;
    for (; n > 0; n--) {
        *dst++ = (p[0] << 8) | p[1];
        p += 2;
    }
    *out = AnalogBuf;
    return 0;
}

s32 fn_8028AC1C(s32 node, u8 ch) {
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
        p = nodes[node].analog;
        if (ch > (u32)(nodes[node].analogCh + (nodes[node].extAnalog - 1))) {
            ret = 0x80000000;
        } else {
            ret = (p[ch * 2] << 8) | p[ch * 2 + 1];
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

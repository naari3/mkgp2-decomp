#include <triforce/amjvs_internal.h>

s32 fn_8028ACEC(s32 node, u8* chans) {
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
        if (chans != NULL) {
            *chans = nodes[node].analogCh;
        }
        ret = 0;
    }
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_8028AD94(s32 node, u8** sw, u8* players, u8* bits) {
    OSSemaphore* sem = &Mgr.sem;
    u8* count;
    JvsNode* nodes;
    s32 ret;

    OSWaitSemaphore(sem);
    count = fn_80285778();
    nodes = fn_802857B8();
    if (node < 1 || node > *count || sw == NULL) {
        ret = 1;
    } else {
        *sw = nodes[node].sw;
        if (*sw == (u8*)nodes) {
            ret = 5;
        } else {
            if (players != NULL) {
                *players = nodes[node].players;
            }
            if (bits != NULL) {
                *bits = nodes[node].swBits;
            }
            ret = 0;
        }
    }
    OSSignalSemaphore(sem);
    return ret;
}

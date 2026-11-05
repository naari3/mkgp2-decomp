#include <triforce/amjvs_internal.h>

s32 fn_8028AA40(s32 node, s16** out, u8* count) {
    OSSemaphore* sem = &Mgr.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028AAC0(node, out, count);
    OSSignalSemaphore(sem);
    return ret;
}

#include <triforce/amnet_priv.h>

s32 fn_8028C158(u8 ch) {
    OSSemaphore* sem = &amnet_nm3_bss_80699140.sem;
    s32 ret;

    OSWaitSemaphore(sem);
    ret = fn_8028C1B8(ch);
    OSSignalSemaphore(sem);
    return ret;
}

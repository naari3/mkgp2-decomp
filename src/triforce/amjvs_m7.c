#include <triforce/amjvs_internal.h>

s32 fn_8028B9A4(void) {
    u8* count = fn_80285778();
    OSSemaphore* sem;
    JvsMgr* mgr;
    s32 i;
    s32 ret;

    fn_80282F3C();
    fn_80282E04();
    for (i = 1; i <= *count; i++) {
        fn_8028B48C(i);
    }
    sem = &Mgr.sem;
    OSWaitSemaphore(sem);
    mgr = &Mgr;
    if (mgr->outPending) {
        mgr->outPending = FALSE;
        if (mgr->out.data[0] == 0x20) {
            fn_80282AC8(1, mgr->out.data[1] & 0x3F);
            fn_80282AC8(0, mgr->out.data[2]);
            fn_80282AC8(7, mgr->out.data[3]);
            fn_80282AC8(8, mgr->out.data[4]);
            fn_80282AC8(9, mgr->out.data[5]);
        }
    }
    if (Mgr.resetPending) {
        Mgr.resetPending = FALSE;
        fn_80282C0C();
    }
    OSSignalSemaphore(sem);
    ret = fn_80293580();
    fn_80282EB8();
    fn_802857D4();
    fn_80282E60();
    fn_8028B180(FALSE);
    return ret == 0 ? 0 : ret;
}

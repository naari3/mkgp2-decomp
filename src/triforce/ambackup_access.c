#include <triforce/ambackup_private.h>

s32 fn_80288574(u32 chan, void* data, BackupConfig* cfg) {
    s32 ret;
    OSSemaphore* sem;
    BackupEntry* e;

    if (chan > 1 || data == NULL || cfg == NULL) {
        return 1;
    }
    sem = &ambackup_nm1_bss_80690DE0.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    e = &ambackup_nm1_bss_80690DE0.entry[chan][1];
    e->cfg = *cfg;
    ret = BackupReadRecord(chan, data, e);
    e->reset = (ret == 1);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_80288668(u32 chan, void* data) {
    s32 ret;
    OSSemaphore* sem;

    if (chan > 1 || data == NULL) {
        return 1;
    }
    sem = &ambackup_nm1_bss_80690DE0.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    ret = BackupReadRecord(chan, data, &ambackup_nm1_bss_80690DE0.entry[chan][0]);
    OSSignalSemaphore(sem);
    return ret;
}

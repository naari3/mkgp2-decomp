#include <triforce/ambackup_private.h>

s32 fn_80288048(s32 chan, u32 mode, u8* bufIn, u32 addrIn, u32 lenIn) {
    u8* buf = bufIn;
    u32 len = lenIn;
    u32 addr = addrIn;
    switch (chan) {
    case 0:
        switch (mode) {
        case 1:
            fn_802876F4(0);
            if (!fn_802870A4(0, 2, addr, buf, len, FALSE)) {
                return 1;
            }
            fn_802876F4(0);
            break;
        case 0:
        default:
            while (len-- != 0) {
                if (!fn_80286C54(0, 2, addr++, *buf++)) {
                    return 1;
                }
            }
            break;
        }
        break;
    default:
        return 1;
    }
    return 0;
}

s32 fn_8028812C(s32 chan, u32 mode, u32 addr, u8* bufIn, u32 lenIn) {
    u8* buf = bufIn;
    u32 len = lenIn;
    switch (chan) {
    case 0:
        switch (mode) {
        case 1:
            fn_802876F4(0);
            if (!fn_802873A0(0, 2, addr, buf, len, FALSE)) {
                return 1;
            }
            fn_802876F4(0);
            break;
        case 0:
        default:
            while (len-- != 0) {
                if (!fn_80286E78(0, 2, addr++, buf++)) {
                    return 1;
                }
            }
            break;
        }
        break;
    default:
        return 1;
    }
    return 0;
}


s32 fn_80288210(u32 chan, void* data) {
    s32 ret;
    OSSemaphore* sem;

    if (chan > 1 || data == NULL) {
        return 1;
    }
    sem = &ambackup_nm1_bss_80690DE0.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    ret = BackupWriteRecord(chan, data, &ambackup_nm1_bss_80690DE0.entry[chan][1]);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_802882BC(u32 chan, void* data) {
    s32 ret;
    OSSemaphore* sem;

    if (chan > 1 || data == NULL) {
        return 1;
    }
    sem = &ambackup_nm1_bss_80690DE0.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    ret = BackupWriteRecord(chan, data, &ambackup_nm1_bss_80690DE0.entry[chan][0]);
    OSSignalSemaphore(sem);
    return ret;
}

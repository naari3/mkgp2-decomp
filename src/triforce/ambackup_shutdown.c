#include <triforce/ambackup_private.h>

s32 fn_80288B80(void) {
    if (!fn_80294DF8(0)) {
        return 1;
    }
    memset(&ambackup_nm1_bss_80690DE0, 0, 0x3C);
    return 0;
}

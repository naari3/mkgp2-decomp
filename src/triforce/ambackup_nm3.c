#include <triforce/ambackup_private.h>

s32 fn_80288BCC(BackupConfig* cfg) {
    BackupEntry* e;
    const BackupInfo* info;
    u32 alignment;
    u32 chan;

    memset(&ambackup_nm1_bss_80690DE0, 0, 0x3C);
    OSInitSemaphore(&ambackup_nm1_bss_80690DE0.sem, 1);
    if (!fn_80294E30(0, 2)) {
        return 1;
    }
    if (cfg == NULL) {
        for (chan = 0; chan < 1; chan++) {
            if (fn_802889AC(chan)) {
                return 1;
            }
        }
    } else {
        for (chan = 0; chan < 1; chan++) {
            e = &ambackup_nm1_bss_80690DE0.entry[chan][0];
            info = &lbl_806DC918[chan];
            e->addr = 0;
            e->cfg = *cfg;
            alignment = info->align;
            e[1].addr = (e->cfg.size + 0xC + alignment - 1) & -alignment;
            if (e->cfg.flags & 2) {
                e[1].addr *= 2;
            }
        }
    }
    return 0;
}

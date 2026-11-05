#include <triforce/ambackup_private.h>

s32 fn_80288BCC(BackupConfig* cfg) {
    BackupEntry* e;
    const BackupInfo* info;

    memset(&lbl_80690DE0, 0, 0x3C);
    OSInitSemaphore(&lbl_80690DE0.sem, 1);
    if (!fn_80294E30(0, 2)) {
        return 1;
    }
    if (cfg == NULL) {
        if (fn_802889AC(0)) {
            return 1;
        }
    } else {
        e = &lbl_80690DE0.entry[0][0];
        info = &lbl_806DC918[0];
        e->addr = 0;
        e->cfg = *cfg;
        e[1].addr = (e->cfg.size + 0xC + info->align - 1) & -info->align;
        if (e->cfg.flags & 2) {
            e[1].addr *= 2;
        }
    }
    return 0;
}

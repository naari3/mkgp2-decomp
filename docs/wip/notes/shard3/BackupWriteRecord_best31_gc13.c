#include <triforce/ambackup_private.h>

u8 ambackup_nm1_bss_806835E0[0xD800];
BackupState ambackup_nm1_bss_80690DE0;
const BackupInfo lbl_806DC918[1] = {{0x2000, 0x20}};

s32 BackupWriteRecord(u32 chan, void* data, BackupEntry* e) {
    u32 size;
    BackupHeader* hdr;
    u32 recSize;
    const BackupInfo* info;
    u32 total;

    if (chan > 1 || NULL == data || e == NULL) {
        return 1;
    }
    if (e->cfg.id[0] == 0) {
        return 1;
    }
    hdr = (BackupHeader*)ambackup_nm1_bss_806835E0;
    { info = &lbl_806DC918[chan]; }
    { size = (3 + e->cfg.size) & ~3; }
    recSize = (size + 0xC + info->align - 1) & -info->align;
    { total = (e->cfg.flags & 2) ? 2 * recSize : recSize; }
    if (e->reset && 0 != e->addr) {
        { total = info->words * 4 - e->addr; }
        e->reset = FALSE;
    }
    { memset(ambackup_nm1_bss_806835E0, 0, recSize); }
    { memcpy(hdr->data, data, e->cfg.size); }
    memcpy(hdr->id, e->cfg.id, 8);
    { hdr->words = size >> 2; }
    if (e->cfg.flags & 1) {
        char _t375 = e->cfg.size;
        hdr->sum = Checksum(hdr->data, _t375);
    } else {
        hdr->sum = 0;
    }
    if (2 & e->cfg.flags) {
        memcpy(recSize + ambackup_nm1_bss_806835E0, ambackup_nm1_bss_806835E0, recSize);
    }
    if (fn_80288048(chan, (e->cfg.flags >> 4) & 1, ambackup_nm1_bss_806835E0, e->addr, total)) {
        return 1;
    }
    return 0;
}

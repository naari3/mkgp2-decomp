#include <triforce/ambackup_private.h>

u8 lbl_806835E0[0xD800];
BackupState lbl_80690DE0;
const BackupInfo lbl_806DC918[1] = {{0x2000, 0x20}};

/* Running-sum checksum: the sum is a parameter so it takes r4 between the
 * pointer (r3) and the count (r5), as in the target. */
static inline u16 ChecksumFrom(u8* p, u16 sum, u32 n) {
    while (n != 0) {
        sum += *p++;
        n--;
    }
    return sum;
}
s32 BackupWriteRecord(u32 chan, void* data, BackupEntry* e) {
    const BackupInfo* info;
    u32 size;
    BackupHeader* hdr;
    u32 recSize;
    u32 total;

    if (chan > 1 || data == NULL || e == NULL) {
        return 1;
    }
    if (e->cfg.id[0] == 0) {
        return 1;
    }
    info = &lbl_806DC918[chan];
    size = (e->cfg.size + 3) & ~3;
    hdr = (BackupHeader*)lbl_806835E0;
    recSize = (size + 0xC + info->align - 1) & -info->align;
    total = (e->cfg.flags & 2) ? recSize * 2 : recSize;
    if (e->reset && e->addr != 0) {
        total = info->words * 4 - e->addr;
        e->reset = FALSE;
    }
    memset(lbl_806835E0, 0, recSize);
    memcpy(hdr->data, data, e->cfg.size);
    memcpy(hdr->id, e->cfg.id, 8);
    hdr->words = size >> 2;
    if (e->cfg.flags & 1) {
        hdr->sum = ChecksumFrom(hdr->data, 0, e->cfg.size);
    } else {
        hdr->sum = 0;
    }
    if (e->cfg.flags & 2) {
        memcpy(lbl_806835E0 + recSize, lbl_806835E0, recSize);
    }
    if (fn_80288048(chan, (e->cfg.flags >> 4) & 1, lbl_806835E0, e->addr, total)) {
        return 1;
    }
    return 0;
}

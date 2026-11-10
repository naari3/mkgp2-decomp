#include <triforce/ambackup_private.h>

/* Accumulate from an initial checksum, as used by the record writer. */
static inline u16 ChecksumFrom(u8* p, u16 sum, u32 n) {
    while (n != 0) {
        sum += *p++;
        n--;
    }
    return sum;
}

s32 fn_802889AC(u32 chan) {
    const BackupInfo* info;
    BackupHeader* hdr;
    BackupEntry* e;
    BackupEntry* mirror;
    u32 recSize;
    u16 sum;

    if (chan > 1) {
        return 1;
    }
    info = &lbl_806DC918[chan];
    if (fn_8028812C(chan, 0, 0, ambackup_nm1_bss_806835E0, info->words * 4)) {
        return 1;
    }
    hdr = (BackupHeader*)ambackup_nm1_bss_806835E0;
    recSize = (hdr->words + 0xC + info->align - 1) & -info->align;
    sum = ChecksumFrom(hdr->data, 0, hdr->words - 0xC);
    if ((recSize > info->words >> 1 || hdr->sum != sum) &&
        hdr == NULL) {
        return 1;
    }
    e = &ambackup_nm1_bss_80690DE0.entry[chan][0];
    e->addr = 0;
    e->cfg.flags = 0x83;
    mirror = e + 1;
    memcpy(e->cfg.id, hdr->id, 8);
    e->cfg.size = hdr->words * 4;
    mirror->addr = (e->cfg.size + info->align - 1) & -info->align;
    if (e->cfg.flags & 2) {
        mirror->addr <<= 1;
    }
    return 0;
}

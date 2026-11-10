#include <triforce/ambackup_private.h>

static inline u16 ChecksumFrom(u8* p, u16 sum, u32 n) {
    while (n != 0) {
        sum += *p++;
        n--;
    }
    return sum;
}

#pragma opt_common_subs off
#pragma push
s32 BackupReadRecord(u32 chan, void* data, BackupEntry* e) {
    u8* buffer;
    BOOL* valid;
    u32 off;
    u32 words;
    BackupHeader* hdr;
    u32 i;
    u32 size;
    u32 recSize;
    const BackupInfo* info;
    BOOL ok[2];
    s32 k;
    s32 j;
    s32 result;

    if (chan > 1 || data == NULL || e == NULL) {
        return 1;
    }
    size = (e->cfg.size + 3) & ~3;
    info = &lbl_806DC918[chan];
    recSize = (size + 0xC + info->align - 1) & -info->align;
    if (fn_8028812C(chan, (e->cfg.flags >> 4) & 1, e->addr, ambackup_nm1_bss_806835E0,
                      (e->cfg.flags & 2) ? recSize * 2 : recSize)) {
        return 1;
    }
    ok[0] = TRUE;
    ok[1] = e->cfg.flags & 2;
    valid = ok;
    words = size >> 2;
    buffer = ambackup_nm1_bss_806835E0;
    for (i = 0, off = 0; i < 2; i++, off += recSize, valid++) {
        if (!*valid) {
            break;
        }
        hdr = (BackupHeader*)(buffer + off);
        if (e->cfg.id[0] != 0 && memcmp(hdr, e->cfg.id, 8) != 0) {
            *valid = FALSE;
        }
        if (hdr->words != words) {
            *valid = FALSE;
        }
        if (e->cfg.flags & 1) {
            u16 sum;
            sum = ChecksumFrom((u8*)hdr + 0xC, 0, e->cfg.size);
            if (sum != hdr->sum) {
                *valid = FALSE;
            }
        }
    }
    for (j = 0; j < 2; j++) {
        k = j;
        if (e->cfg.flags & 4) {
            k = 1 - j;
        }
        if (ok[k]) {
            memcpy(data, ambackup_nm1_bss_806835E0 + k * recSize + 0xC, e->cfg.size);
            break;
        }
    }
    if (e->cfg.flags & 2) {
        if (ok[0]) {
            result = 3;
            if (ok[1]) { result = 0; }
            return result;
        }
        result = 1;
        if (ok[1]) { result = 2; }
        return result;
    }
    return !ok[0];
}
#pragma pop

#pragma opt_common_subs reset

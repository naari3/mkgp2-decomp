#include <triforce/ambackup_private.h>

s32 BackupReadRecord(u32 chan, void* data, BackupEntry* e) {
    u8* buffer;
    BOOL* valid;
    u32 off;
    u32 words;
    BackupHeader* hdr;
    u32 size;
    u32 i;
    u32 recSize;
    const BackupInfo* info;
    u32 total;
    BOOL ok[2];
    s32 j;
    s32 k;

    if (chan > 1 || data == NULL || e == NULL) {
        return 1;
    }
    info = &lbl_806DC918[chan];
    size = (e->cfg.size + 3) & ~3;
    recSize = (size + 0xC + info->align - 1) & -info->align;
    total = recSize;
    if (e->cfg.flags & 2) {
        total = recSize * 2;
    }
    if (fn_8028812C(chan, (e->cfg.flags >> 4) & 1, e->addr, lbl_806835E0, total)) {
        return 1;
    }
    ok[0] = TRUE;
    ok[1] = e->cfg.flags & 2;
    buffer = lbl_806835E0;
    valid = ok;
    words = size >> 2;
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
        if ((e->cfg.flags & 1) && Checksum((u8*)hdr + 0xC, e->cfg.size) != hdr->sum) {
            *valid = FALSE;
        }
    }
    for (j = 0; j < 2; j++) {
        k = j;
        if (e->cfg.flags & 4) {
            k = 1 - j;
        }
        if (ok[k]) {
            memcpy(data, lbl_806835E0 + k * recSize + 0xC, e->cfg.size);
            break;
        }
    }
    if (e->cfg.flags & 2) {
        if (ok[0]) {
            if (ok[1]) { return 0; }
            return 3;
        }
        if (ok[1]) { return 2; }
        return 1;
    }
    return !ok[0];
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
    if (fn_8028812C(0, 0, 0, lbl_806835E0, info->words * 4)) {
        return 1;
    }
    hdr = (BackupHeader*)lbl_806835E0;
    recSize = (hdr->words + 0xC + info->align - 1) & -info->align;
    sum = Checksum((u8*)hdr + 0xC, hdr->words - 0xC);
    if ((recSize > info->words >> 1 || hdr->sum != sum) &&
        hdr == NULL) {
        return 1;
    }
    e = &lbl_80690DE0.entry[chan][0];
    e->addr = 0;
    e->cfg.flags = 0x83;
    mirror = e + 1;
    memcpy(e->cfg.id, hdr->id, 8);
    e->cfg.size = hdr->words * 4;
    mirror->addr = (e->cfg.size + info->align - 1) & -info->align;
    if (e->cfg.flags & 2) {
        mirror->addr *= 2;
    }
    return 0;
}

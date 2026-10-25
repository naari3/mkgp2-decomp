/* Triforce baseboard backup memory: mirrored records with a checksum. */
#include <dolphin.h>
#include <string.h>

typedef struct BackupConfig {
    /* 0x00 */ u8 id[8];
    /* 0x08 */ u32 size;
    /* 0x0C */ u32 flags;
} BackupConfig;

typedef struct BackupEntry {
    /* 0x00 */ BackupConfig cfg;
    /* 0x10 */ u32 addr;
    /* 0x14 */ BOOL reset;
} BackupEntry;

typedef struct BackupHeader {
    /* 0x00 */ u8 id[8];
    /* 0x08 */ u16 words;
    /* 0x0A */ u16 sum;
    /* 0x0C */ u8 data[1];
} BackupHeader;

typedef struct BackupInfo {
    u32 words;
    u32 align;
} BackupInfo;

typedef struct BackupState {
    BackupEntry entry[1][2];
    OSSemaphore sem;
} BackupState;

extern BOOL fn_80286C54(s32 chan, u32 dev, u16 addr, u8 data);
extern BOOL fn_80286E78(s32 chan, u32 dev, u16 addr, u8* data);
extern BOOL fn_802870A4(s32 chan, u32 dev, u16 addr, void* buf, u32 len, BOOL sync);
extern BOOL fn_802873A0(s32 chan, u32 dev, u16 addr, void* buf, u32 len, BOOL sync);
extern void fn_802876F4(s32 chan);
extern BOOL fn_80294DF8(s32);
extern BOOL fn_80294E30(s32, s32);

static u8 Buffer[0xD800];
static BackupState State;

static const BackupInfo Info[1] = {{0x2000, 0x20}};

static inline u16 Checksum(u8* p, u32 n) {
    u16 sum = 0;
    while (n != 0) {
        sum += *p++;
        n--;
    }
    return sum;
}

s32 fn_80288048(s32 chan, u32 mode, u8* buf, u32 addr, u32 len) {
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

s32 fn_8028812C(s32 chan, u32 mode, u32 addr, u8* buf, u32 len) {
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

static s32 BackupWriteRecord(u32 chan, void* data, BackupEntry* e);
static s32 BackupReadRecord(u32 chan, void* data, BackupEntry* e);

s32 fn_80288210(u32 chan, void* data) {
    s32 ret;
    OSSemaphore* sem;

    if (chan > 1 || data == NULL) {
        return 1;
    }
    sem = &State.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    ret = BackupWriteRecord(chan, data, &State.entry[chan][1]);
    OSSignalSemaphore(sem);
    return ret;
}

s32 fn_802882BC(u32 chan, void* data) {
    s32 ret;
    OSSemaphore* sem;

    if (chan > 1 || data == NULL) {
        return 1;
    }
    sem = &State.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    ret = BackupWriteRecord(chan, data, &State.entry[chan][0]);
    OSSignalSemaphore(sem);
    return ret;
}

static s32 BackupWriteRecord(u32 chan, void* data, BackupEntry* e) {
    const BackupInfo* info;
    u32 size;
    u32 recSize;
    BackupHeader* hdr;
    u32 total;

    if (chan > 1 || data == NULL || e == NULL) {
        return 1;
    }
    if (e->cfg.id[0] == 0) {
        return 1;
    }
    info = &Info[chan];
    size = (e->cfg.size + 3) & ~3;
    recSize = (size + 0xC + info->align - 1) & -info->align;
    hdr = (BackupHeader*)Buffer;
    total = recSize;
    if (e->cfg.flags & 2) {
        total = recSize * 2;
    }
    if (e->reset && e->addr != 0) {
        e->reset = FALSE;
        total = info->words * 4 - e->addr;
    }
    memset(Buffer, 0, recSize);
    memcpy(hdr->data, data, e->cfg.size);
    memcpy(hdr->id, e->cfg.id, 8);
    hdr->words = size >> 2;
    if (e->cfg.flags & 1) {
        hdr->sum = Checksum(hdr->data, e->cfg.size);
    } else {
        hdr->sum = 0;
    }
    if (e->cfg.flags & 2) {
        memcpy(Buffer + recSize, Buffer, recSize);
    }
    if (fn_80288048(chan, (e->cfg.flags >> 4) & 1, Buffer, e->addr, total)) {
        return 1;
    }
    return 0;
}

s32 fn_80288574(u32 chan, void* data, BackupConfig* cfg) {
    s32 ret;
    OSSemaphore* sem;
    BackupEntry* e;

    if (chan > 1 || data == NULL || cfg == NULL) {
        return 1;
    }
    sem = &State.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    e = &State.entry[chan][1];
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
    sem = &State.sem;
    if (OSTryWaitSemaphore(sem) <= 0) {
        return 5;
    }
    ret = BackupReadRecord(chan, data, &State.entry[chan][0]);
    OSSignalSemaphore(sem);
    return ret;
}

static s32 BackupReadRecord(u32 chan, void* data, BackupEntry* e) {
    const BackupInfo* info;
    u32 size;
    u32 recSize;
    u32 total;
    BOOL ok[2];
    u32 i;
    u32 off;
    u8* rec;
    BackupHeader* hdr;
    s32 j;
    s32 k;

    if (chan > 1 || data == NULL || e == NULL) {
        return 1;
    }
    info = &Info[chan];
    size = (e->cfg.size + 3) & ~3;
    recSize = (size + 0xC + info->align - 1) & -info->align;
    total = recSize;
    if (e->cfg.flags & 2) {
        total = recSize * 2;
    }
    if (fn_8028812C(chan, (e->cfg.flags >> 4) & 1, e->addr, Buffer, total)) {
        return 1;
    }
    ok[0] = TRUE;
    ok[1] = e->cfg.flags & 2;
    for (i = 0, off = 0; i < 2 && ok[i]; i++, off += recSize) {
        rec = Buffer + off;
        hdr = (BackupHeader*)rec;
        if (e->cfg.id[0] != 0 && memcmp(rec, e->cfg.id, 8) != 0) {
            ok[i] = FALSE;
        }
        if (hdr->words != size >> 2) {
            ok[i] = FALSE;
        }
        if ((e->cfg.flags & 1) && Checksum(rec + 0xC, e->cfg.size) != hdr->sum) {
            ok[i] = FALSE;
        }
    }
    for (j = 0; j < 2; j++) {
        k = j;
        if (e->cfg.flags & 4) {
            k = 1 - j;
        }
        if (ok[k]) {
            memcpy(data, Buffer + k * recSize + 0xC, e->cfg.size);
            break;
        }
    }
    if (e->cfg.flags & 2) {
        if (ok[0]) {
            return ok[1] ? 0 : 3;
        }
        return ok[1] ? 2 : 1;
    }
    return !ok[0];
}

s32 fn_802889AC(u32 chan) {
    const BackupInfo* info;
    BackupHeader* hdr;
    BackupEntry* e;
    u16 sum;

    if (chan > 1) {
        return 1;
    }
    info = &Info[chan];
    if (fn_8028812C(0, 0, 0, Buffer, info->words * 4)) {
        return 1;
    }
    hdr = (BackupHeader*)Buffer;
    sum = Checksum(Buffer + 0xC, hdr->words - 0xC);
    if ((((hdr->words + 0xC + info->align - 1) & -info->align) > info->words >> 1 || hdr->sum != sum) &&
        Buffer == NULL) {
        return 1;
    }
    e = &State.entry[chan][0];
    e->addr = 0;
    e->cfg.flags = 0x83;
    memcpy(e->cfg.id, hdr->id, 8);
    e->cfg.size = hdr->words * 4;
    e[1].addr = (e->cfg.size + info->align - 1) & -info->align;
    if (e->cfg.flags & 2) {
        e[1].addr *= 2;
    }
    return 0;
}

s32 fn_80288B80(void) {
    if (!fn_80294DF8(0)) {
        return 1;
    }
    memset(&State, 0, 0x3C);
    return 0;
}

static inline void SetMirrorAddr(BackupEntry* e, const BackupInfo* info) {
    e[1].addr = (e->cfg.size + 0xC + info->align - 1) & -info->align;
    if (e->cfg.flags & 2) {
        e[1].addr *= 2;
    }
}

s32 fn_80288BCC(BackupConfig* cfg) {
    memset(&State, 0, 0x3C);
    OSInitSemaphore(&State.sem, 1);
    if (!fn_80294E30(0, 2)) {
        return 1;
    }
    if (cfg == NULL) {
        if (fn_802889AC(0)) {
            return 1;
        }
    } else {
        State.entry[0][0].addr = 0;
        State.entry[0][0].cfg = *cfg;
        SetMirrorAddr(State.entry[0], &Info[0]);
    }
    return 0;
}

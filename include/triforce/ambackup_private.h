#ifndef AMBACKUP_PRIVATE_H
#define AMBACKUP_PRIVATE_H
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

extern u8 ambackup_nm1_bss_806835E0[0xD800];
extern BackupState ambackup_nm1_bss_80690DE0;

extern const BackupInfo lbl_806DC918[1];

static inline u16 Checksum(u8* p, u32 n) {
    u16 sum = 0;
    while (n != 0) {
        sum += *p++;
        n--;
    }
    return sum;
}

s32 fn_80288048(s32 chan, u32 mode, u8* buf, u32 addr, u32 len);
s32 fn_8028812C(s32 chan, u32 mode, u32 addr, u8* buf, u32 len);
s32 BackupWriteRecord(u32 chan, void* data, BackupEntry* e);
s32 BackupReadRecord(u32 chan, void* data, BackupEntry* e);
s32 fn_802889AC(u32 chan);
#endif

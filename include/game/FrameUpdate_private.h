#ifndef FRAME_UPDATE_PRIVATE_H
#define FRAME_UPDATE_PRIVATE_H
#pragma options align=packed
struct BackupPacked8 { unsigned char byte2A; unsigned int word2B; unsigned short half2F; unsigned char byte31; };
struct BackupPacked15 { unsigned char byte52; unsigned int word53, word57, word5B; unsigned short half5F; };
#pragma options align=reset
struct BackupWords210 { unsigned int words[0x84]; };
struct BackupWords26C { unsigned int words[0x9B]; };
struct BackupWords2D00 { unsigned int words[0xB40]; };
struct BackupWords3840 { unsigned int words[0xE10]; };
struct FrameBackup {
    unsigned char byte00;
    unsigned int word04, word08, word0C, word10, word14;
    unsigned long long qw18;
    unsigned int word20, word24;
    unsigned short half28;
    struct BackupPacked8 packed2A;
    unsigned int word34, word38, word3C, word40, word44, word48, word4C;
    unsigned short half50;
    struct BackupPacked15 packed52;
    struct BackupWords210 block64;
    struct BackupWords26C block274;
    struct BackupWords2D00 block4E0;
    struct BackupWords3840 block31E0;
};
typedef char CheckFrameBackupSize[sizeof(struct FrameBackup) == 0x6A20 ? 1 : -1];
extern struct FrameBackup lbl_80598A60, g_backupShadowCopy;
extern unsigned char g_jvsOperatorBits[];
extern unsigned char lbl_806D1120;
extern int lbl_806D1124, lbl_806D1128, lbl_806D1114, lbl_806D1110;
extern void fn_80288210(int, struct FrameBackup *);
#endif

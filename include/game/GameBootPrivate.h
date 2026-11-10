#ifndef GAME_BOOT_PRIVATE_H
#define GAME_BOOT_PRIVATE_H
/* TU-private backup layout inferred from GameBoot_Init aggregate copies. */
#pragma options align=packed
struct BootPair { virtual void key(); unsigned long long value; };
#pragma options align=reset
#pragma options align=packed
struct BootPackedSeven { unsigned int a; unsigned short b; unsigned char c; };
struct BootPackedFourteen { unsigned int a, b, c; unsigned short d; };
#pragma options align=reset
struct BootPayload { unsigned int words[0x84]; };
struct BootHead {
    unsigned char tag;
    int a04, a08, a0c, a10;
    BootPair pair;
    int a20, a24;
    unsigned short a28;
    unsigned char a2a;
    BootPackedSeven packed2b;
    int a34, a38, a3c, a40, a44, a48, a4c;
    unsigned short a50;
    unsigned char a52;
    BootPackedFourteen packed53;
    BootPayload payload;
};
struct BootStats { unsigned int words[0x9b]; };
struct BootLarge { unsigned int words[0xb40]; };
struct BootTail { unsigned int words[0xe10]; };
struct BootBackup { BootHead head; BootStats stats; BootLarge large; BootTail tail; };
typedef char BootBackupSizeCheck[sizeof(BootBackup) == 0x6a20 ? 1 : -1];
struct BootDescriptor { unsigned int words[2]; int size, type; };
struct BootClock { char bytes[16]; };
extern "C" {
extern BootBackup lbl_80598A60, lbl_8059F480;
extern BootClock lbl_805A5EA0;
extern BootDescriptor GameBoot_Init_bss_805A5EB0;
extern unsigned char lbl_806CEF68, lbl_806CEF69, lbl_806D1120;
extern int lbl_806D1124, lbl_806D1114, lbl_806D1110, lbl_806D1128;
extern const char lbl_80310DE0[];
extern const char *lbl_806D1118, *lbl_806D111C;
struct BootIP { unsigned int address, other; };
extern BootIP g_pcbIpTable[4];
void OperationClockState_Reset(BootClock *);
void OperationClockState_StartTick(BootClock *);
void OperationClockState_CommitDelta(BootClock *);
void Backup_LoadFromMemoryOrInit();
void Backup_ClearHiScores();
void PlayStats_Clear();
void CreditMgr_ResetState(int);
int fn_80288574(int, BootBackup *);
void fn_80288210(int, BootBackup *);
int acModifyMyIPaddr(unsigned int, unsigned int);
void DebugPrintf(const char *, ...);
void *memcpy(void *, const void *, unsigned long);
void *memset(void *, int, unsigned long);
}
#endif

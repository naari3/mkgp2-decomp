#include "game/GameBootPrivate.h"

static inline void ClearBootStats() {
    memset(&lbl_80598A60.stats, 0, 0x26c);
    PlayStats_Clear();
    OperationClockState_CommitDelta(&lbl_805A5EA0);
    OperationClockState_Reset(&lbl_805A5EA0);
    OperationClockState_StartTick(&lbl_805A5EA0);
}
static inline void SnapshotBootBackup() {
    lbl_8059F480.head = lbl_80598A60.head;
    lbl_8059F480.stats = lbl_80598A60.stats;
    lbl_8059F480.large = lbl_80598A60.large;
    lbl_8059F480.tail = lbl_80598A60.tail;
}
static inline void ConfigureBootIP(BootBackup *backup, const char *messages) {
    int cabinet = ((signed char *)backup)[0x21];
    BootIP *ip = g_pcbIpTable;
    ip += cabinet;
    DebugPrintf(messages + 0x4d0, (--ip)->address);
    int result = acModifyMyIPaddr(ip->address, 0xffffff00);
    DebugPrintf(messages + 0x500, cabinet, result, ip->address);
    if (result == 0) DebugPrintf(messages + 0x540);
    if (result == -1) DebugPrintf(messages + 0x560);
    if (result == -2) DebugPrintf(messages + 0x58c);
    if (result == -3) DebugPrintf(messages + 0x5e4);
    if (result == -4) DebugPrintf(messages + 0x620);
    if (result == -6) DebugPrintf(messages + 0x64c);
    DebugPrintf(messages + 0x688, result);
}
static inline void FinishBootBackup(char *backup) {
    backup[0x2a] = 0;
    if (lbl_806D1120 && lbl_806D1128 == 0) {
        fn_80288210(0, (BootBackup *)backup);
        SnapshotBootBackup();
    }
}
extern "C" void GameBoot_Init() {
    const char *messages = lbl_80310DE0;
    OperationClockState_Reset(&lbl_805A5EA0);
    OperationClockState_StartTick(&lbl_805A5EA0);
    lbl_806CEF68 = 1; lbl_806CEF69 = 0;
    lbl_806D1124 = 0; lbl_806D1120 = 1;
    lbl_806D1114 = 0x708; lbl_806D1110 = 0;
    Backup_LoadFromMemoryOrInit();
    if (lbl_806D1120 && lbl_806D1128 == 0) ClearBootStats();
    SnapshotBootBackup();
    memcpy(&GameBoot_Init_bss_805A5EB0, messages + 0x6bc, 8);
    GameBoot_Init_bss_805A5EB0.size = 0x6a20; GameBoot_Init_bss_805A5EB0.type = 0x11;
    if (fn_80288574(0, &lbl_80598A60) != 0 || lbl_80598A60.head.tag != 15 || lbl_80598A60.head.a08 != 0) {
        Backup_LoadFromMemoryOrInit();
        Backup_ClearHiScores();
        if (lbl_806D1120 && lbl_806D1128 == 0) ClearBootStats();
        if (lbl_806D1120 && lbl_806D1128 == 0) {
            fn_80288210(0, &lbl_80598A60);
            SnapshotBootBackup();
        }
        CreditMgr_ResetState(1);
        lbl_806D1124 = 4;
    } else CreditMgr_ResetState(0);
    SnapshotBootBackup();
    if (lbl_806D1120) ConfigureBootIP(&lbl_80598A60, messages);
    FinishBootBackup((char *)&lbl_80598A60);
    lbl_806D1118 = messages + 0x6c8;
    lbl_806D111C = messages + 0x6d4;
}

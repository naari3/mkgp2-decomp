/* Reset the backup to defaults; on a cold start also clear the play stats
 * and restart the operation clock. */
typedef struct BackupData {
    unsigned char pad000[0x274];
    unsigned char stats[0x26c]; /* 0x274 */
} BackupData;

typedef struct OperationClockState OperationClockState;

extern unsigned char lbl_806D1120;
extern int lbl_806D1128;
extern BackupData lbl_80598A60;
extern OperationClockState lbl_805A5EA0;
extern void *memset(void *dst, int c, unsigned long n);
extern void Backup_LoadFromMemoryOrInit(void);
extern void Backup_ClearHiScores(void);
extern void PlayStats_Clear(void);
extern void OperationClockState_CommitDelta(OperationClockState *state);
extern void OperationClockState_Reset(OperationClockState *state);
extern void OperationClockState_StartTick(OperationClockState *state);

void Backup_ClearAll(void)
{
    Backup_LoadFromMemoryOrInit();
    Backup_ClearHiScores();
    if (lbl_806D1120 != 0 && lbl_806D1128 == 0) {
        memset(lbl_80598A60.stats, 0, sizeof(lbl_80598A60.stats));
        PlayStats_Clear();
        OperationClockState_CommitDelta(&lbl_805A5EA0);
        OperationClockState_Reset(&lbl_805A5EA0);
        OperationClockState_StartTick(&lbl_805A5EA0);
    }
}

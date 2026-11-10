/* Clear the play stats and restart the operation clock. Only allowed on a
 * cold start; returns 1 when cleared. */
#include "game/types/BackupData.h"

typedef struct OperationClockState OperationClockState;

extern unsigned char lbl_806D1120;
extern int lbl_806D1128;
extern BackupData lbl_80598A60;
extern OperationClockState g_operationClock;
extern void *memset(void *dst, int c, unsigned long n);
extern void PlayStats_Clear(void);
extern void OperationClockState_CommitDelta(OperationClockState *state);
extern void OperationClockState_Reset(OperationClockState *state);
extern void OperationClockState_StartTick(OperationClockState *state);

int Backup_ClearBookkeeping(void)
{
    if (lbl_806D1120 == 0) {
        return 0;
    }
    if (lbl_806D1128 != 0) {
        return 0;
    }
    memset(lbl_80598A60.stats, 0, sizeof(lbl_80598A60.stats));
    PlayStats_Clear();
    OperationClockState_CommitDelta(&g_operationClock);
    OperationClockState_Reset(&g_operationClock);
    OperationClockState_StartTick(&g_operationClock);
    return 1;
}

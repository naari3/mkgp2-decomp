/* Commit the operation clock and play-time stats on shutdown. */
#include "game/types/OperationClockState.h"

extern unsigned char lbl_806D1120;
extern OperationClockState g_operationClock;
extern void OperationClockState_CommitDelta(OperationClockState *state);
extern void PlayStats_AddTotalPlaySeconds(int seconds);
extern void PlayStats_PublishStatsBlockShadow(void);

void Backup_Shutdown(void)
{
    if (lbl_806D1120 != 0) {
        OperationClockState_CommitDelta(&g_operationClock);
        PlayStats_AddTotalPlaySeconds(g_operationClock.deltaSeconds);
        PlayStats_PublishStatsBlockShadow();
        lbl_806D1120 = 0;
    }
}

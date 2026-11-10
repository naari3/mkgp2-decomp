/* Commit the operation clock and play-time stats on shutdown. */
#include "game/types/OperationClockState.h"

extern unsigned char lbl_806D1120;
extern OperationClockState lbl_805A5EA0;
extern void OperationClockState_CommitDelta(OperationClockState *state);
extern void PlayStats_AddTotalPlaySeconds(int seconds);
extern void PlayStats_PublishStatsBlockShadow(void);

void Backup_Shutdown(void)
{
    if (lbl_806D1120 != 0) {
        OperationClockState_CommitDelta(&lbl_805A5EA0);
        PlayStats_AddTotalPlaySeconds(lbl_805A5EA0.deltaSeconds);
        PlayStats_PublishStatsBlockShadow();
        lbl_806D1120 = 0;
    }
}

// Session-time commit and lifetime statistics facade.
#include "game/types/OperationClockState.h"
struct OperationClockStatsView {
    unsigned char prefix[0x274];
    unsigned int totalPlaySeconds;
};
extern "C" {
extern unsigned char lbl_806D1120;
extern OperationClockState g_operationClock;
extern OperationClockStatsView lbl_80598A60;
void OperationClockState_CommitDelta(OperationClockState*);
void OperationClockState_RefreshCurrent(OperationClockState*);
void OperationClockState_Reset(OperationClockState*);
void OperationClockState_StartTick(OperationClockState*);
void PlayStats_AddTotalPlaySeconds(unsigned int);
void PlayStats_PublishStatsBlockShadow(void);

void OperationClock_Commit(void) {
    if (lbl_806D1120) {
        OperationClockState_CommitDelta(&g_operationClock);
        PlayStats_AddTotalPlaySeconds(g_operationClock.deltaSeconds);
        PlayStats_PublishStatsBlockShadow();
        OperationClockState_Reset(&g_operationClock);
        OperationClockState_StartTick(&g_operationClock);
    }
}

unsigned int OperationClock_GetLifetimeSeconds(void) {
    unsigned int seconds = lbl_80598A60.totalPlaySeconds;
    OperationClockState_RefreshCurrent(&g_operationClock);
    seconds += g_operationClock.currentSeconds;
    if (seconds > 99999999U) seconds = 99999999U;
    return seconds;
}
}

// Session-time commit and lifetime statistics facade.
struct OperationClockState {
    unsigned char tick[8];
    unsigned int currentSeconds;
    unsigned int deltaSeconds;
};
struct OperationClockStatsView {
    unsigned char prefix[0x274];
    unsigned int totalPlaySeconds;
};
extern "C" {
extern unsigned char lbl_806D1120;
extern OperationClockState lbl_805A5EA0;
extern OperationClockStatsView lbl_80598A60;
void OperationClockState_CommitDelta(OperationClockState*);
void OperationClockState_RefreshCurrent(OperationClockState*);
void OperationClockState_Reset(OperationClockState*);
void OperationClockState_StartTick(OperationClockState*);
void PlayStats_AddTotalPlaySeconds(unsigned int);
void PlayStats_PublishStatsBlockShadow(void);

void OperationClock_Commit(void) {
    if (lbl_806D1120) {
        OperationClockState_CommitDelta(&lbl_805A5EA0);
        PlayStats_AddTotalPlaySeconds(lbl_805A5EA0.deltaSeconds);
        PlayStats_PublishStatsBlockShadow();
        OperationClockState_Reset(&lbl_805A5EA0);
        OperationClockState_StartTick(&lbl_805A5EA0);
    }
}

unsigned int OperationClock_GetLifetimeSeconds(void) {
    unsigned int seconds = lbl_80598A60.totalPlaySeconds;
    OperationClockState_RefreshCurrent(&lbl_805A5EA0);
    seconds += lbl_805A5EA0.currentSeconds;
    if (seconds > 99999999U) seconds = 99999999U;
    return seconds;
}
}

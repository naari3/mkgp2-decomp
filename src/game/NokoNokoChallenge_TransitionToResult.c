extern void SetSyncTarget(int);

#pragma exceptions on
int NokoNokoChallenge_TransitionToResult(void) {
    SetSyncTarget(0x34);
    return 0xD;
}
#pragma exceptions reset

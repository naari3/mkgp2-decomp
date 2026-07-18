extern unsigned char g_finalLapCoinJumpEnabled;

int FinalLapCoinJump_CheckActiveForObject(void *object)
{
    int active;

    if (object == 0) {
        return 0;
    }

    if (object == 0) {
        active = 0;
    } else if (*(int *)((char *)object + 0x238) != 0) {
        active = 1;
    } else {
        active = 0;
    }
    if (active) {
        return g_finalLapCoinJumpEnabled != 0;
    }
    return 0;
}

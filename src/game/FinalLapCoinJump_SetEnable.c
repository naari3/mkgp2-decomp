extern unsigned char g_finalLapCoinJumpEnabled;

void FinalLapCoinJump_SetEnable(void *coinSystem, int enabled)
{
    unsigned char *self = (unsigned char *)coinSystem;
    self[0x18] = enabled;
    self[0x19] = 1;
    g_finalLapCoinJumpEnabled = self[0x18];
}

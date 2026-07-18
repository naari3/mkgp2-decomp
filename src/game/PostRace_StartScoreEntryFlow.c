extern void Sci2Card_PrintReceipt_StartFlow(int, int, int);

void PostRace_StartScoreEntryFlow(void)
{
    Sci2Card_PrintReceipt_StartFlow(3, 1, 0);
}

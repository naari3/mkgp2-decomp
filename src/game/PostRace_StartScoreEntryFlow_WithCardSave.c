extern void Sci2Card_PrintReceipt_StartFlow(int, int, int);

void PostRace_StartScoreEntryFlow_WithCardSave(void)
{
    Sci2Card_PrintReceipt_StartFlow(3, 1, 1);
}

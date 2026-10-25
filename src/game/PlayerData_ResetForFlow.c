extern unsigned char g_playerData[];
extern void *memset(void *, int, unsigned long);
extern void fn_801D7610(void *playerData, int flag);

void PlayerData_ResetForFlow(void)
{
    memset(g_playerData, 0, 0x1DC);
    fn_801D7610(g_playerData, 1);
}

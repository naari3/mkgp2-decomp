extern unsigned char g_playerData[];
extern void fn_801D5F74(void *playerData, int id, int value);

void PlayerData_ApplyItemUnlockById(int id)
{
    fn_801D5F74(g_playerData, id, 1);
}

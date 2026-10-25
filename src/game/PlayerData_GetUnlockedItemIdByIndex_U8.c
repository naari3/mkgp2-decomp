extern unsigned char g_playerData[];
extern int PlayerData_ResolveUnlockedIdByIndex(void *playerData, int index);

unsigned char PlayerData_GetUnlockedItemIdByIndex_U8(int index)
{
    return PlayerData_ResolveUnlockedIdByIndex(g_playerData, index);
}

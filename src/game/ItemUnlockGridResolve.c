/* Find a table row by the player-resolved ID. The special ID 0x24 has no row. */
extern unsigned char g_playerData[];
extern int PlayerData_ResolveUnlockedIdByIndex(void *playerData, int index);
extern const int lbl_803E56B0[13][6];

int fn_8023D710(int id)
{
    void *playerData;
    int row, column;
    if (id == 0x24) return -1;
    playerData = g_playerData;
    for (row = 0; row < 13; ++row) {
        for (column = 0; column < 6; ++column) {
            if (id == PlayerData_ResolveUnlockedIdByIndex(playerData, lbl_803E56B0[row][column]))
                return row;
        }
    }
    return -1;
}

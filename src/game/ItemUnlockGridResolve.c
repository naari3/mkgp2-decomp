/* Find a table row by the player-resolved ID. The special ID 0x24 has no row.
 * NonMatching: outer and inner table cursors use exchanged registers.
 */
extern unsigned char g_playerData[];
extern int PlayerData_ResolveUnlockedIdByIndex(void *playerData, int index);
extern const int lbl_803E56B0[13][6];

int fn_8023D710(int id)
{
    const int *entry;
    void *playerData;
    int row, column;
    if (id == 0x24) return -1;
    playerData = g_playerData;
    for (row = 0; row < 13; ++row) {
        for (column = 0, entry = lbl_803E56B0[row]; column < 6; ++column, ++entry) {
            if (id == PlayerData_ResolveUnlockedIdByIndex(playerData, *entry))
                return row;
        }
    }
    return -1;
}

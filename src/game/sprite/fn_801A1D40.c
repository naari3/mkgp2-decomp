typedef struct RaceEntry {
    unsigned char pad[0x33];
    signed char player;
    unsigned char pad34[4];
    int id;
    unsigned char pad3c[0x68 - 0x3c];
} RaceEntry;
extern RaceEntry g_raceEntryArray[8];

RaceEntry *fn_801A1D40(int player) {
    int i;
    for (i = 0; i < 8; i++) {
        if (g_raceEntryArray[i].id != -1 && player == g_raceEntryArray[i].player) {
            return &g_raceEntryArray[i];
        }
    }
    return 0;
}

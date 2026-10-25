typedef struct RaceEntry {
    char pad0[0x28];
    int f28;
    char pad2C[0x34 - 0x2C];
    signed char f34;
    char pad35[0x68 - 0x35];
} RaceEntry;

extern unsigned char g_voiceSystemInitDone;
extern RaceEntry g_raceEntryArray[];

int fn_801B3CE0(int idx, int v) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (idx < 0 || idx >= 8) {
        return 0;
    }
    if (v < 0 || v >= 8) {
        return 0;
    }
    g_raceEntryArray[idx].f28 = v;
    return 1;
}

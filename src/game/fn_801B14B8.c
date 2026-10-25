typedef struct RaceEntry {
    char pad0[0xC];
    int voiceState;
    void *voiceTarget;
    char pad14[0x40 - 0x14];
    void *kartItem;
    char pad44[0x68 - 0x44];
} RaceEntry;

extern unsigned char g_voiceSystemInitDone;
extern unsigned char g_bgmStateId;
extern RaceEntry g_raceEntryArray[];
extern unsigned char KartItem_GetByte_f4(void *item);

int fn_801B14B8(char *kart, char *target) {
    void *item;

    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart == 0) {
        return 0;
    }
    if (target == 0) {
        return 0;
    }
    item = g_raceEntryArray[*(int *)(target + 0x248)].kartItem;
    if (item != 0 && KartItem_GetByte_f4(item)) {
        g_bgmStateId = 0;
        return 0;
    }
    g_raceEntryArray[*(int *)(kart + 0x248)].voiceState = 7;
    g_raceEntryArray[*(int *)(kart + 0x248)].voiceTarget = target;
    return 1;
}

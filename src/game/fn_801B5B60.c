typedef struct RaceEntry {
    char unk0;
    char voiceEnabled;
    char pad_2[0x2E];
    char isTaPlayer;
    char isHuman;
    char unk32;
    char pad_33[5];
    int playerType;
    int unk3C;
    int carObject;
    int unk44;
    char pad_48[0x20];
} RaceEntry;

extern RaceEntry g_raceEntryArray[8];
extern int g_taMinLapPlayerIndex;
extern unsigned char g_voiceSystemInitDone;

int fn_801B5B60(int kart) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart < 0 || kart >= 8) {
        return 0;
    }
    g_raceEntryArray[kart].voiceEnabled = 1;
    return 1;
}

int VoiceSystem_BindKartCarObject(int kart, int carObject) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart < 0 || kart >= 8) {
        return 0;
    }
    g_raceEntryArray[kart].carObject = carObject;
    return 1;
}

int fn_801B5BF4(int kart, int playerType, int arg2, int arg3) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart < 0 || kart >= 8) {
        return 0;
    }
    g_raceEntryArray[kart].unk32 = 0;
    g_raceEntryArray[kart].playerType = playerType;
    g_raceEntryArray[kart].unk3C = arg2;
    g_raceEntryArray[kart].unk44 = arg3;
    if (playerType >= 0 && playerType <= 3) {
        g_raceEntryArray[kart].isHuman = 1;
    }
    if (playerType >= 0 && playerType <= 3) {
        if (g_taMinLapPlayerIndex == -1) {
            g_taMinLapPlayerIndex = kart;
        }
        g_raceEntryArray[kart].isTaPlayer = 1;
    }
    return 1;
}

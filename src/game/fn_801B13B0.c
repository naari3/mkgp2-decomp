typedef struct Speaker {
    int priority;
    void *kart;
    unsigned char flag;
} Speaker;

typedef struct RaceEntry {
    char pad00[0x60];
    void *rival;
    unsigned char announced;
    char pad65[3];
} RaceEntry;

typedef struct KartObj {
    char pad000[0x248];
    int entryIndex;
} KartObj;

extern unsigned char g_voiceSystemInitDone;
extern Speaker g_raceCurrentSpeakerId;
extern RaceEntry g_raceEntryArray[];

int fn_801B13B0(void *kart, int priority, unsigned char flag) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart == 0) {
        return 0;
    }
    if (g_raceCurrentSpeakerId.priority != -1 && g_raceCurrentSpeakerId.priority < priority) {
        return 0;
    }
    g_raceCurrentSpeakerId.kart = kart;
    g_raceCurrentSpeakerId.priority = priority;
    g_raceCurrentSpeakerId.flag = flag;
    return 1;
}

int fn_801B1410(KartObj *kart) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (kart == 0) {
        return 0;
    }
    g_raceEntryArray[kart->entryIndex].announced = 1;
    return 1;
}

int fn_801B1458(KartObj *a, KartObj *b) {
    if (!g_voiceSystemInitDone) {
        return 0;
    }
    if (a == 0) {
        return 0;
    }
    if (b == 0) {
        return 0;
    }
    g_raceEntryArray[a->entryIndex].rival = b;
    g_raceEntryArray[b->entryIndex].rival = a;
    return 1;
}

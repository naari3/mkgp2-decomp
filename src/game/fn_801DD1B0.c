typedef struct KartCond {
    signed char mode;
    signed char cup;
    signed char ccClass;
    signed char round;
    signed char kart;
} KartCond;

extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;

typedef struct RangeEntry {
    KartCond cond;
    int minValue;
    int maxValue;
} RangeEntry;

typedef struct SyncSlot {
    char pad[0x1B];
    unsigned char random;
} SyncSlot;

extern int lbl_806CFF00;
extern RangeEntry lbl_804E27B0[];
extern float PseudoRandom_Next(void);
extern SyncSlot *SyncSlot_GetRecv(void);

static inline unsigned char KartCond_MatchesRace(KartCond c) {
    if (c.mode != -1 && c.mode != g_gameMode) {
        return 0;
    }
    if (c.cup != -1 && c.cup != g_cupId) {
        return 0;
    }
    if (c.ccClass != -1 && c.ccClass != g_ccClass) {
        return 0;
    }
    if (c.round != -1 && c.round != g_roundIndex) {
        return 0;
    }
    return 1;
}

int fn_801DD1B0(void) {
    int i;

    for (i = 0; i < lbl_806CFF00; i++) {
        if (KartCond_MatchesRace(lbl_804E27B0[i].cond)) {
            float t = PseudoRandom_Next();
            if (g_gameMode == 2) {
                t = SyncSlot_GetRecv()->random / 255.0f;
            }
            return lbl_804E27B0[i].minValue + t * (lbl_804E27B0[i].maxValue - lbl_804E27B0[i].minValue);
        }
    }
    return 0;
}

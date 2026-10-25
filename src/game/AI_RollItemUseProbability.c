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

typedef struct ItemUseProbEntry {
    KartCond cond;
    int kart;
    float probability;
} ItemUseProbEntry;

extern int lbl_806CFF04;
extern ItemUseProbEntry g_itemUseProbTable[];
extern float PseudoRandom_Next(void);

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

int AI_RollItemUseProbability(int kart) {
    int i;

    for (i = 0; i < lbl_806CFF04; i++) {
        if (KartCond_MatchesRace(g_itemUseProbTable[i].cond)) {
            if (g_itemUseProbTable[i].kart == -1 || kart == g_itemUseProbTable[i].kart) {
                if (PseudoRandom_Next() <= g_itemUseProbTable[i].probability) {
                    return 1;
                }
                return 0;
            }
        }
    }
    return 0;
}

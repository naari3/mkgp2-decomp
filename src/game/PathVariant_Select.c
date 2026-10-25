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

typedef struct PathVariantEntry {
    KartCond cond;
    int kart;
    int variantA;
    int variantB;
} PathVariantEntry;

extern int g_PathVariantTableCount;
extern PathVariantEntry g_PathVariantTable[];
extern const float lbl_806DA2A0;
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

int PathVariant_Select(int kart) {
    int i;

    for (i = 0; i < g_PathVariantTableCount; i++) {
        if (KartCond_MatchesRace(g_PathVariantTable[i].cond)) {
            if (g_PathVariantTable[i].kart == -1 || kart == g_PathVariantTable[i].kart) {
                if (PseudoRandom_Next() <= lbl_806DA2A0) {
                    return g_PathVariantTable[i].variantA;
                }
                return g_PathVariantTable[i].variantB;
            }
        }
    }
    return 0;
}

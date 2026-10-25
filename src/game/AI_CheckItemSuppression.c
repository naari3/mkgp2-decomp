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

typedef struct ItemSuppressionEntry {
    KartCond cond;
    int item;
    int minValue;
    int maxValue;
} ItemSuppressionEntry;

extern int g_itemSuppressionCount;
extern ItemSuppressionEntry g_itemSuppressionTable[];

static inline unsigned char KartCond_Matches(KartCond c, int kart) {
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
    if (c.kart != -1 && kart != -1 && c.kart != kart) {
        return 0;
    }
    return 1;
}

int AI_CheckItemSuppression(int kart, int item, int value) {
    int i;

    for (i = 0; i < g_itemSuppressionCount; i++) {
        if (KartCond_Matches(g_itemSuppressionTable[i].cond, kart)) {
            if (g_itemSuppressionTable[i].item == -1 || item == g_itemSuppressionTable[i].item - 1) {
                if (g_itemSuppressionTable[i].minValue <= value && value <= g_itemSuppressionTable[i].maxValue) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

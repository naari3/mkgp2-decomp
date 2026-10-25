typedef struct PathCond {
    signed char mode;
    signed char cup;
    signed char ccClass;
    signed char round;
    unsigned char extra;
} PathCond;

typedef struct LateralOffsetEntry {
    PathCond cond;
    int kart;
    float magnitude;
    int unk10;
} LateralOffsetEntry;

extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;
extern int lbl_806CFEF0;
extern LateralOffsetEntry g_lateralOffsetTable[];
extern const float FLOAT_defaultBonus;

static inline unsigned char PathCond_Matches(PathCond c) {
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

float LateralOffset_GetMagnitude(int kart) {
    int i;

    for (i = 0; i < lbl_806CFEF0; i++) {
        if (PathCond_Matches(g_lateralOffsetTable[i].cond)) {
            if (g_lateralOffsetTable[i].kart == -1 || kart == g_lateralOffsetTable[i].kart) {
                return g_lateralOffsetTable[i].magnitude;
            }
        }
    }
    return FLOAT_defaultBonus;
}

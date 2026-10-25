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

typedef struct DistanceBonusEntry {
    KartCond cond;
    float bonus[6][6];
} DistanceBonusEntry;

extern int lbl_806CFF08;
extern DistanceBonusEntry lbl_804E3184[];
extern const float FLOAT_defaultBonus;

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

float AI_CalcDistanceSpeedBonus(int kart, int row, int col) {
    int i;

    for (i = 0; i < lbl_806CFF08; i++) {
        if (KartCond_Matches(lbl_804E3184[i].cond, kart)) {
            return lbl_804E3184[i].bonus[row][col];
        }
    }
    return FLOAT_defaultBonus;
}

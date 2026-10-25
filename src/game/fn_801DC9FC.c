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
    int unkC;
    int unk10;
} PathVariantEntry;

extern int lbl_806CFF14;
extern PathVariantEntry lbl_804E3C5C[];

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

int fn_801DC9FC(int kart, int prev) {
    int i;

    if (lbl_806CFF14 <= prev + 1) {
        return -1;
    }
    for (i = prev + 1; i < lbl_806CFF14; i++) {
        if (KartCond_MatchesRace(lbl_804E3C5C[i].cond)) {
            if (lbl_804E3C5C[i].kart == -1 || kart == lbl_804E3C5C[i].kart) {
                return i;
            }
        }
    }
    return -1;
}

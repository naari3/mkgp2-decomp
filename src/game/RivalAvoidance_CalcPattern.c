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

typedef struct RivalPatternEntry {
    KartCond cond;
    int kart;
    float maxDistance;
    int group;
    int pattern[3];
} RivalPatternEntry;

extern int lbl_806CFEF4;
extern RivalPatternEntry lbl_804E21C4[];

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

int RivalAvoidance_CalcPattern(int kart, int rank, float distance) {
    int group;
    int i;

    switch (rank) {
    case 0:
    case 1:
    case 2:
    case 3:
        group = 0;
        break;
    case 6:
        group = 1;
        break;
    default:
        return -1;
    }
    for (i = 0; i < lbl_806CFEF4; i++) {
        if (KartCond_MatchesRace(lbl_804E21C4[i].cond)) {
            if ((lbl_804E21C4[i].kart == -1 || kart == lbl_804E21C4[i].kart) &&
                distance < lbl_804E21C4[i].maxDistance &&
                (lbl_804E21C4[i].group == -1 || group == lbl_804E21C4[i].group)) {
                return i;
            }
        }
    }
    return -1;
}

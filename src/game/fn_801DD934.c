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

typedef struct KartChanceEntry {
    KartCond cond;
    float chance;
    int unkC;
    int unk10;
} KartChanceEntry;

extern int lbl_806CFEF8;
extern KartChanceEntry lbl_804E2404[];
extern float PseudoRandom_Next(void);

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

int fn_801DD934(int kart) {
    int i;

    for (i = 0; i < lbl_806CFEF8; i++) {
        if (KartCond_Matches(lbl_804E2404[i].cond, kart)) {
            if (PseudoRandom_Next() <= lbl_804E2404[i].chance) {
                return i;
            }
            return -1;
        }
    }
    return -1;
}

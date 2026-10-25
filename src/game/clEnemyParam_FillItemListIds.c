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

typedef struct EnemyItemListEntry {
    KartCond cond;
    int itemIds[8];
} EnemyItemListEntry;

typedef struct clEnemyParam {
    int itemListIds[6];
} clEnemyParam;

extern int lbl_806CFF1C;
extern EnemyItemListEntry lbl_804E40A8[];
extern clEnemyParam *g_clEnemyParam;
extern int fn_801EB708(void);

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

static inline int EnemyItemList_Pick(int kart) {
    int i;

    for (i = 0; i < lbl_806CFF1C; i++) {
        if (KartCond_Matches(lbl_804E40A8[i].cond, kart)) {
            EnemyItemListEntry *e = &lbl_804E40A8[i];
            int count = 0;
            int j;
            for (j = 0; j < 8; j++) {
                if (e->itemIds[j] != -1) {
                    count++;
                }
            }
            return e->itemIds[fn_801EB708() % count];
        }
    }
    return 0;
}

void clEnemyParam_FillItemListIds(void) {
    int kart;

    for (kart = 0; kart < 6; kart++) {
        g_clEnemyParam->itemListIds[kart] = EnemyItemList_Pick(kart);
    }
}

typedef struct KartTuningEntry {
    float speedFactor;
    char pad04[0xC];
    char gpSpeed[0x4C];
} KartTuningEntry;

typedef struct BaseSpeed {
    float max;
    float min;
} BaseSpeed;

typedef struct ItemList {
    int ids[4];
} ItemList;

extern int g_gameMode;
extern int g_ccClass;
extern int *g_clEnemyParam;
extern ItemList lbl_804E3D88[];
extern KartTuningEntry g_kartTuningTable[];
extern KartTuningEntry g_kartTuningTableNonRace[];
extern const BaseSpeed kAIBaseSpeedTable_Race[];
extern const BaseSpeed kAIBaseSpeedTable_BattleTimeAttack[];

ItemList *AI_GetItemList(void *param, int mode, int cup, int round, int kart) {
    int idx = g_clEnemyParam[kart];
    if (idx < 0) {
        return lbl_804E3D88;
    }
    return &lbl_804E3D88[idx];
}

static inline KartTuningEntry *TuningEntry(int cup, int round, int kart) {
    int mode = g_gameMode;
    if (cup < 1 || cup >= 9) {
        cup = 0;
    } else if (mode == 0) {
        cup = (cup - 1) * 192 + g_ccClass * 64 + round * 8 + kart;
    } else {
        cup += g_ccClass * 8;
        cup -= 1;
    }
    if (mode == 0) {
        return &g_kartTuningTable[cup];
    }
    return &g_kartTuningTableNonRace[cup];
}

void *GetKartTuningGPSpeedParams(void *param, int cup, int round, int kart) {
    return TuningEntry(cup, round, kart)->gpSpeed;
}

float GetKartTuningSpeedFactor(void *param, int cup, int round, int kart) {
    return TuningEntry(cup, round, kart)->speedFactor;
}

KartTuningEntry *GetKartTuningEntry(void *param, int cup, int round, int kart) {
    return TuningEntry(cup, round, kart);
}

static inline const BaseSpeed *BaseSpeedEntry(int cup, int round) {
    int mode = g_gameMode;
    const BaseSpeed *p;
    if (cup < 1 || cup >= 9) {
        cup = 0;
    } else if (mode == 0) {
        cup = (cup - 1) * 24 + g_ccClass * 8 + round;
    } else {
        cup += g_ccClass * 8;
        cup -= 1;
    }
    p = &kAIBaseSpeedTable_BattleTimeAttack[cup];
    if (mode == 0) {
        p = &kAIBaseSpeedTable_Race[cup];
    }
    return p;
}

float GetBaseSpeedMin(void *param, int cup, int round) {
    return BaseSpeedEntry(cup, round)->min;
}

float GetBaseSpeedMax(void *param, int cup, int round) {
    return BaseSpeedEntry(cup, round)->max;
}

int fn_801DE6E0(void) {
    return 0;
}

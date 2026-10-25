typedef struct PlayerData {
    char pad000[0xA8];
    unsigned char unlockFlags[0x79];
    unsigned char extraFlags[3];
    char pad124[0x1AC - 0x124];
    int raceCount;
    char pad1B0[4];
    int coinMilage;
    unsigned char variant;
    unsigned char kartVariant;
    unsigned char cupRank[3][8];
    char pad1D2[0x1DA - 0x1D2];
    signed char streak;
} PlayerData;

extern int g_roundIndex;
extern int g_ccClass;
extern int g_cupId;

int fn_801D5970(PlayerData *p) {
    return p->streak;
}

void fn_801D597C(PlayerData *p) {
    if (++p->streak > 31) {
        p->streak = 31;
    }
}



int fn_801D59A0(PlayerData *p, int cc, int cup) {
    if (cc < 0 || cc > 2) {
        return 0;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    return p->cupRank[cc][cup];
}

static inline int RankReached(PlayerData *p, int cc, int cup, int round) {
    int need;
    if (cc < 0 || cc > 2) {
        return 0;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    need = (unsigned char)(round + 1);
    if (round >= 4) {
        need++;
    }
    if (p->cupRank[cc][cup] >= need) {
        return 1;
    }
    return 0;
}

int fn_801D59F8(PlayerData *p, int cup, int flag) {
    int round = 7;
    int need;
    if (flag == 0) {
        round = 3;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    need = (unsigned char)(round + 1);
    if (round >= 4) {
        need++;
    }
    if (p->cupRank[2][cup] >= need) {
        return 1;
    }
    return 0;
}

int fn_801D5A68(PlayerData *p) {
    int need;
    int cc;
    int cup;
    int round = 3;
    if (g_roundIndex >= 4) {
        round = 7;
    }
    cc = g_ccClass;
    cup = g_cupId;
    if (cc < 0 || cc > 2) {
        return 0;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    need = (unsigned char)(round + 1);
    if (round >= 4) {
        need++;
    }
    if (p->cupRank[cc][cup] >= need) {
        return 1;
    }
    return 0;
}

int RoundIsUnlocked(PlayerData *p, int round) {
    int need;
    int cc = g_ccClass;
    int cup = g_cupId;
    if (cc < 0 || cc > 2) {
        return 0;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    need = (unsigned char)(round + 1);
    if (round >= 4) {
        need++;
    }
    if (p->cupRank[cc][cup] >= need) {
        return 1;
    }
    return 0;
}

int fn_801D5B8C(PlayerData *p, int cc, int cup, int round) {
    return RankReached(p, cc, cup, round);
}

int RoundCupIsCompleted(PlayerData *p, int cc, int cup, int flag) {
    if (cc < 0 || cc > 2) {
        return 0;
    }
    if (cup < 1 || cup >= 17) {
        return 0;
    }
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    if (p->cupRank[cc][cup] >= (flag == 0 ? 5 : 10)) {
        return 1;
    }
    return 0;
}

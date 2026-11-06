/* Read-only view of the original AI rule pool. No data is emitted here. */
typedef struct AILapRule {
    signed char cc, round, kart, remainingLaps;
    int minDifference;
    int maxDifference;
    signed char excludedRank;
    char reserved[3];
    float bonus;
} AILapRule;
extern const unsigned char lbl_8039FD90[];
extern int lbl_806D12C0;
extern int g_roundIndex, g_tableVariant, g_cupId, g_gameMode, g_ccClass;
extern const float FLOAT_defaultBonus;
static inline unsigned char FindBonus(const AILapRule *table, signed char cc, signed char round,
                                     int kart, signed char laps, int difference, signed char rank, float *bonus) {
    int i = 0;
    const AILapRule *p = table;
    for (; p->cc != -100; ++p, ++i) {
        if ((p->cc == -1 || cc == p->cc) &&
            (p->round == -1 || round == p->round) &&
            (p->kart == -1 || kart == -1 || kart == p->kart) &&
            (p->remainingLaps == -1 || laps == p->remainingLaps - 1) &&
            p->minDifference <= difference && p->maxDifference >= difference &&
            (p->excludedRank == -1 || rank != p->excludedRank - 1)) {
            *bonus = table[i].bonus;
            return 1;
        }
    }
    return 0;
}
float AI_CalcLapSpeedBonus(int kart, int lapsArg, int difference, int rankArg) {
    const char *window = (const char *)&lbl_8039FD90 + 0x20000;
    signed char rank = rankArg;
    signed char laps = lapsArg;
    int variant;
    int cup;
    signed char round;
    float bonus;
    round = g_roundIndex;
    variant = g_tableVariant;
    cup = g_cupId;
    if (lbl_806D12C0 <= 0) variant = 0;
    if (cup > 9) cup -= 9;
    bonus = FLOAT_defaultBonus;
    /* Pointer-table row strides are 32, 256, and 128 bytes respectively. */
    if (g_gameMode == 0) {
        if (!FindBonus(*(const AILapRule *const *)((window - 0x31E4) + (variant * 32 + (cup - 1) * 4)), g_ccClass, round, kart, laps, difference, rank, &bonus)) {
            FindBonus(*(const AILapRule *const *)((window - 0x3184) + (variant * 256 + (cup - 1) * 32 + round * 4)), g_ccClass, round, kart, laps, difference, rank, &bonus);
        }
    } else {
        if (!FindBonus((const AILapRule *)(window - 0x3248), g_ccClass, round, kart, laps, difference, rank, &bonus)) {
            int section = round;
            if (section >= 4) section -= 4;
            FindBonus(*(const AILapRule *const *)((window - 0x2E84) + (g_ccClass * 128 + (cup - 1) * 16 + section * 4)), g_ccClass, round, kart, laps, difference, rank, &bonus);
        }
    }
    return bonus;
}

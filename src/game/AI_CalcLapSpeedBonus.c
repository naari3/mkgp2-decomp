/* Lap speed bonus rules and their shared AI parameter pool. */
typedef struct AILapRule {
    signed char cc, round, kart, remainingLaps;
    int minDifference;
    int maxDifference;
    signed char excludedRank;
    char reserved[3];
    float bonus;
} AILapRule;
#include "game/AI_CalcLapSpeedBonus_pool.h"
extern int lbl_806D12C0;
extern int g_roundIndex, g_tableVariant, g_cupId, g_gameMode, g_ccClass;
extern const float FLOAT_defaultBonus;
static inline unsigned char FindBonus(signed char cc, const AILapRule *table, signed char round,
                                     int kart, signed char laps, int difference, signed char rank, float *bonus) {
    int i = 0;
    for (; table[i].cc != -100; ++i) {
        const AILapRule *p = &table[i];
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
        if (!FindBonus(g_ccClass, *(const AILapRule *const *)((const char *)kAILapBonusRuleTable_RaceCourse + variant * 32 + (cup - 1) * 4), round, kart, laps, difference, rank, &bonus)) {
            FindBonus(g_ccClass, *(const AILapRule *const *)((const char *)kAILapBonusRuleTable_RaceFallback + variant * 256 + (cup - 1) * 32 + round * 4), round, kart, laps, difference, rank, &bonus);
        }
    } else {
        if (!FindBonus(g_ccClass, kAILapBonusRules_NonRaceCommon, round, kart, laps, difference, rank, &bonus)) {
            int courseOffset = (cup - 1) * 16;
            int ccOffset = g_ccClass * 128;
            const char *courseBase = (const char *)kAILapBonusRuleTable_NonRace;
            int section = round;
            courseOffset = ccOffset + courseOffset;
            if (section >= 4) section -= 4;
            {
                signed char cc = g_ccClass;
                FindBonus(cc, *(const AILapRule *const *)(courseBase + (courseOffset + section * 4)), round, kart, laps, difference, rank, &bonus);
            }
        }
    }
    return bonus;
}

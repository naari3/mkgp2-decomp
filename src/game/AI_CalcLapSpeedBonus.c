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
/* The non-race common table is searched by name, not through the table
 * parameter: the target folds the member offset into the index
 * (`addi rI, rI, 0x10; lfsx f1, rBase, rI`) only for this copy.
 * fakematch (hand): the float-array view of the table gives that form.
 * natural: *bonus = kAILapBonusRules_NonRaceCommon[i].bonus; */
static inline unsigned char FindBonusCommon(signed char cc, signed char round,
                                     int kart, signed char laps, int difference, signed char rank, float *bonus) {
    int i = 0;
    for (; kAILapBonusRules_NonRaceCommon[i].cc != -100; ++i) {
        const AILapRule *p = &kAILapBonusRules_NonRaceCommon[i];
        if ((p->cc == -1 || cc == p->cc) &&
            (p->round == -1 || round == p->round) &&
            (p->kart == -1 || kart == -1 || kart == p->kart) &&
            (p->remainingLaps == -1 || laps == p->remainingLaps - 1) &&
            p->minDifference <= difference && p->maxDifference >= difference &&
            (p->excludedRank == -1 || rank != p->excludedRank - 1)) {
            *bonus = ((const float *)kAILapBonusRules_NonRaceCommon)[i * 5 + 4];
            return 1;
        }
    }
    return 0;
}
/* fakematch (hand, regalloc_patterns 97): the non-race row lookup is written
 * as an outer inline with two nested helper inlines so that the register
 * allocator numbers section > cup offset > table base > cc offset (the wrapped
 * section is the outer inline's parameter, the other two are single-use locals
 * of nested inlines). cc is written through a pointer after the wrap so that
 * its sign extension is emitted after the branch join.
 * natural: int courseOffset = (cup - 1) * 16 + g_ccClass * 128;
 *          int section = round; if (section >= 4) section -= 4;
 *          FindBonus(g_ccClass, table[courseOffset / 4 + section], ...); */
static inline int NonRaceCupOffset(int cup) {
    int offset = (cup - 1) * 16;
    return offset;
}
static inline const char *NonRaceTable(void) {
    const char *table = (const char *)kAILapBonusRuleTable_NonRace;
    return table;
}
static inline const AILapRule *NonRaceRules(int section, int cup, signed char *cc) {
    int courseOffset;
    const char *courseBase;
    int ccOffset;
    courseOffset = NonRaceCupOffset(cup);
    ccOffset = g_ccClass * 128;
    courseBase = NonRaceTable();
    courseOffset = ccOffset + courseOffset;
    if (section >= 4) section -= 4;
    *cc = g_ccClass;
    return *(const AILapRule *const *)(courseBase + courseOffset + section * 4);
}
/* fakematch (leversweep dead-def-split): opt_dead_assignments off gives the
 * target address math in the non-race path.
 * natural: no pragma. */
#pragma push
#pragma opt_dead_assignments off
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
        if (!FindBonusCommon(g_ccClass, round, kart, laps, difference, rank, &bonus)) {
            signed char cc;
            FindBonus(cc, NonRaceRules(round, cup, &cc), round, kart, laps, difference, rank, &bonus);
        }
    }
    return bonus;
}
#pragma pop

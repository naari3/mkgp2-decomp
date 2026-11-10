#include "game/singleton.h"

/* RankLog / TitleTracker (0x800A5CEC..0x800A8D34): per-race stat counters
 * used to pick the player's title after a race, the title check
 * predicates and the name/title lookup. Each counter method takes the
 * tracker singleton (unused) and a display slot that must be the local
 * player's.
 *
 * InitStartRace matches with separately scoped, non-aliasing snapshot
 * regions and packed 0x1BA words at their target offsets. NonMatching:
 * residual scheduling and register allocation remain in the title-name
 * lookups, DetermineTitle and NewClearedRecord_Race. The score predicates
 * use their own pooled target tables and match exactly. Reversed EH ordering prevents
 * isolating the exact methods into independently linked TUs.
 */

#include "game/types/RoundInfo.h"

typedef struct KartResult {
    unsigned char pad0[0x1F8];
    int kind;
} KartResult;

extern int g_gameMode;
extern int GetDisplayBufferIndex(void);
extern RoundInfo *fn_8024F588(void);

extern int RankLog_bss_806D13EC;
extern int RankLog_bss_806D13F0;
extern int g_technicalTitleGrade;
extern int g_raceResult;
extern int g_totalScore;
extern unsigned int lbl_806D1428;
extern unsigned int lbl_806D1450;
extern int g_totalDistance;
extern int g_defeatCount;
extern int g_matchCount;
extern int g_undefeatedStreak;
extern int g_hitCount;
extern int g_perfectCount;
extern int RankLog_bss_806D1434;
extern int g_gpLossCount;
extern int g_specificDefeatCount;
extern int g_ghostDefeatCount;
extern int g_prevRaceScore;
extern int g_gpWinCount;
extern int g_currentRaceScore;
extern unsigned char lbl_806D1420;
extern unsigned char g_allCoursesCleared;
extern int g_totalRaces;
extern const float lbl_806D4DD0;
extern int g_roundCount;
extern int g_prevRaceResult;
extern int g_prevPrevRaceResult;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern int RankLog_data_806CF204;
extern float RankLog_data_806CF208;
extern int RankLog_bss_806D1404;
extern int RankLog_bss_806D1408;
extern int RankLog_bss_806D140C;
extern int g_consecutiveWins;
extern int g_scoreThreshold;
extern int g_playCount;
extern unsigned char RankLog_bss_806D13D0;
extern int g_stagingTitleId;
extern int g_titleParam;
extern int g_nameId;
extern int g_rankingPosition;
extern unsigned char RankLog_bss_806D1448;
extern unsigned char RankLog_bss_806D1449;
extern unsigned char RankLog_InitStartRace_bss_806D144A;
extern int RankLog_data_806CF1F4;
extern int lbl_806CF1F8;
extern int RankLog_bss_806D1424;
extern int RankLog_data_806CF21C;
extern int g_hazardPassCount;
extern int RankLog_data_806CF20C;
extern int g_maxCoins;
extern const float lbl_806D4DD4;
extern char lbl_80326B54[];
extern char lbl_80326B70[];
extern char RankLog_InitStartRace_rodata_80326B84[];

#pragma pack(push, 1)
typedef struct PackedWords {
    unsigned int w1BA, w1BE, w1C2, w1C6, w1CA, w1CE;
} PackedWords;
#pragma pack(pop)

typedef struct PlayerData {
    unsigned int word000, word004, word008;
    unsigned char byte00C, byte00D;
    unsigned short wins;
    unsigned short losses;
    unsigned int word014;
    unsigned char byte018, byte019, byte01A;
    unsigned int w01C, w020, w024, w028, w02C, w030, w034, w038, w03C, w040, w044, w048, w04C, w050, w054, w058, w05C, w060, w064, w068, w06C, w070, w074, w078, w07C, w080, w084, w088, w08C, w090, w094, w098, w09C, w0A0, w0A4;
    unsigned char bytes0A8[0x79];
    unsigned char bytes121[0x69];
    unsigned int word18C, word190, word194;
    unsigned char b198, b199, b19A, b19B, b19C, b19D, b19E, b19F, b1A0;
    unsigned int word1A4;
    unsigned char byte1A8;
    unsigned int word1AC;
    unsigned char byte1B0, byte1B1;
    unsigned int word1B4;
    unsigned char byte1B8, byte1B9;
    PackedWords words1BA;
    unsigned int word1D4;
    unsigned char byte1D8, byte1D9, byte1DA;
} PlayerData;

#include "game/types/RankEntry.h"

extern PlayerData g_playerData;
extern PlayerData RankLog_bss_805D2F40;
extern void fn_801D5DD0(PlayerData *p);
extern RankEntry *RaceResult_GetRankEntry(int i);
extern void DebugPrintf(const char *fmt, ...);
void DetermineTitle(unsigned char arg);
extern unsigned char RankLog_rodata_80324B98[];
extern char *RankLog_data_806CF1E8;
extern char lbl_806D4A44[4];
extern char lbl_806D4DD8[5];
extern char lbl_806D4DE0[7];
extern char RankLog_bss_805D311C[0x200];
extern int isJapanese(void);
extern int sprintf(char *buf, const char *fmt, ...);
extern void *memset(void *p, int c, unsigned long n);
extern void *Alloc(unsigned long size);
extern void *lbl_806D10A0;
extern void *TitleTracker_data_80411DC0[];
extern void *TitleTracker_data_80411DB4[];

typedef struct TitleEntry {
    int type;
    char *en;
    char *jp;
} TitleEntry;

#include "game/types/NameEntry.h"

extern NameEntry RankLog_data_80411B18[0x26];

typedef unsigned char (*TitleCheckFn)(void);

#include "game/types/DisplayState.h"

#include "game/types/OSCalendarTime.h"

extern DisplayState lbl_80598A60;
/* Per cup, CC class and round length: score and two floating limits. */
typedef struct TitleTarget {
    signed char score;
    float limitA;
    float limitB;
} TitleTarget;

typedef TitleTarget TargetCup[3][2];

TargetCup RankLog_data_80411458[8] = {
    {
        { { 6, 120.0f, 15.0f }, { 4, 120.0f, 20.0f } },
        { { 6, 120.0f, 15.0f }, { 4, 120.0f, 20.0f } },
        { { 9, 90.0f, 15.0f }, { 6, 90.0f, 20.0f } },
    },
    {
        { { 8, 120.0f, 10.0f }, { 4, 120.0f, 20.0f } },
        { { 8, 120.0f, 10.0f }, { 4, 120.0f, 20.0f } },
        { { 9, 90.0f, 10.0f }, { 6, 90.0f, 20.0f } },
    },
    {
        { { 4, 120.0f, 20.0f }, { 4, 120.0f, 30.0f } },
        { { 4, 120.0f, 20.0f }, { 4, 120.0f, 30.0f } },
        { { 6, 90.0f, 20.0f }, { 5, 90.0f, 30.0f } },
    },
    {
        { { 3, 120.0f, 40.0f }, { 3, 120.0f, 50.0f } },
        { { 3, 120.0f, 40.0f }, { 3, 120.0f, 50.0f } },
        { { 4, 100.0f, 40.0f }, { 4, 100.0f, 50.0f } },
    },
    {
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 35.0f } },
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 35.0f } },
        { { 5, 100.0f, 30.0f }, { 5, 100.0f, 35.0f } },
    },
    {
        { { 2, 120.0f, 90.0f }, { 2, 120.0f, 100.0f } },
        { { 2, 120.0f, 90.0f }, { 2, 120.0f, 100.0f } },
        { { 3, 100.0f, 90.0f }, { 3, 100.0f, 100.0f } },
    },
    {
        { { 3, 120.0f, 90.0f }, { 2, 150.0f, 100.0f } },
        { { 3, 120.0f, 90.0f }, { 2, 150.0f, 100.0f } },
        { { 4, 100.0f, 90.0f }, { 3, 150.0f, 100.0f } },
    },
    {
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 30.0f } },
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 30.0f } },
        { { 5, 100.0f, 30.0f }, { 5, 100.0f, 30.0f } },
    },
};

static TargetCup sTimeAttackTargets[8] = {
    {
        { { 6, 120.0f, 15.0f }, { 4, 120.0f, 20.0f } },
        { { 6, 120.0f, 15.0f }, { 4, 120.0f, 20.0f } },
        { { 9, 90.0f, 15.0f }, { 6, 90.0f, 20.0f } },
    },
    {
        { { 8, 120.0f, 10.0f }, { 4, 120.0f, 20.0f } },
        { { 8, 120.0f, 10.0f }, { 4, 120.0f, 20.0f } },
        { { 9, 90.0f, 10.0f }, { 6, 90.0f, 20.0f } },
    },
    {
        { { 4, 120.0f, 20.0f }, { 4, 120.0f, 30.0f } },
        { { 4, 120.0f, 20.0f }, { 4, 120.0f, 30.0f } },
        { { 6, 90.0f, 20.0f }, { 5, 90.0f, 30.0f } },
    },
    {
        { { 3, 120.0f, 40.0f }, { 3, 120.0f, 50.0f } },
        { { 3, 120.0f, 40.0f }, { 3, 120.0f, 50.0f } },
        { { 4, 100.0f, 40.0f }, { 4, 100.0f, 50.0f } },
    },
    {
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 35.0f } },
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 35.0f } },
        { { 5, 100.0f, 30.0f }, { 5, 100.0f, 35.0f } },
    },
    {
        { { 2, 120.0f, 90.0f }, { 2, 120.0f, 100.0f } },
        { { 2, 120.0f, 90.0f }, { 2, 120.0f, 100.0f } },
        { { 3, 100.0f, 90.0f }, { 3, 100.0f, 100.0f } },
    },
    {
        { { 3, 120.0f, 90.0f }, { 2, 150.0f, 100.0f } },
        { { 3, 120.0f, 90.0f }, { 2, 150.0f, 100.0f } },
        { { 4, 100.0f, 90.0f }, { 3, 150.0f, 100.0f } },
    },
    {
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 30.0f } },
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 30.0f } },
        { { 5, 100.0f, 30.0f }, { 5, 100.0f, 30.0f } },
    },
};

static TargetCup sBattleTargets[8] = {
    {
        { { 6, 120.0f, 15.0f }, { 4, 120.0f, 20.0f } },
        { { 6, 120.0f, 15.0f }, { 4, 120.0f, 20.0f } },
        { { 9, 90.0f, 15.0f }, { 6, 90.0f, 20.0f } },
    },
    {
        { { 8, 120.0f, 10.0f }, { 4, 120.0f, 20.0f } },
        { { 8, 120.0f, 10.0f }, { 4, 120.0f, 20.0f } },
        { { 9, 90.0f, 10.0f }, { 6, 90.0f, 20.0f } },
    },
    {
        { { 4, 120.0f, 20.0f }, { 4, 120.0f, 30.0f } },
        { { 4, 120.0f, 20.0f }, { 4, 120.0f, 30.0f } },
        { { 6, 90.0f, 20.0f }, { 5, 90.0f, 30.0f } },
    },
    {
        { { 3, 120.0f, 40.0f }, { 3, 120.0f, 50.0f } },
        { { 3, 120.0f, 40.0f }, { 3, 120.0f, 50.0f } },
        { { 4, 100.0f, 40.0f }, { 4, 100.0f, 50.0f } },
    },
    {
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 35.0f } },
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 35.0f } },
        { { 5, 100.0f, 30.0f }, { 5, 100.0f, 35.0f } },
    },
    {
        { { 2, 120.0f, 90.0f }, { 2, 120.0f, 100.0f } },
        { { 2, 120.0f, 90.0f }, { 2, 120.0f, 100.0f } },
        { { 3, 100.0f, 90.0f }, { 3, 100.0f, 100.0f } },
    },
    {
        { { 3, 120.0f, 90.0f }, { 2, 150.0f, 100.0f } },
        { { 3, 120.0f, 90.0f }, { 2, 150.0f, 100.0f } },
        { { 4, 100.0f, 90.0f }, { 3, 150.0f, 100.0f } },
    },
    {
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 30.0f } },
        { { 4, 120.0f, 30.0f }, { 4, 120.0f, 30.0f } },
        { { 5, 100.0f, 30.0f }, { 5, 100.0f, 30.0f } },
    },
};
extern TitleCheckFn DetermineTitle_data_806CF220[1];
extern TitleCheckFn DetermineTitle_data_806CF224[1];
extern int g_characterId;
extern unsigned char fn_801D5B8C(PlayerData *p, int a, int b, int c);
extern unsigned char fn_801D59F8(PlayerData *p, int a, int b);
int DetermineNameId(int score, int chara);
unsigned char TitleCheck_NewClearedRecord_Race(void);
unsigned char TaTitle_CheckAllCoursesRecorded(void);
extern long long OSGetTime(void);
extern void OSTicksToCalendarTime(long long t, OSCalendarTime *td);
extern void MemoryManager_TimedFree(void *p);
extern void *TaRecord_GetEntry_Indexed(int a, int b, int c, int d, int e);
extern int wcscmp(const void *a, const void *b);
extern int TitleCheck_NewClearedRecord_Race_rodata_80326B04[8];
extern int TitleCheck_CupCleared_rodata_803269AC[8];
extern int RankLog_rodata_80326ADC[];
extern int g_roundIndex;
extern int g_ccClass;
extern int g_consecutiveWinsTier;

void RankLog_InitStartRace(void *self);

static inline void SetTitle(int id, int param)
{
    g_stagingTitleId = id;
    g_titleParam = param;
}

static inline unsigned char IsLocalSlot(int slot)
{
    if (slot < 0 && slot > 3) {
        return 0;
    }
    if (g_gameMode != 2) {
        return 1;
    }
    if (slot == GetDisplayBufferIndex()) {
        return 1;
    }
    return 0;
}

void RankLog_SetRaceResult(void *self, int slot, void *result, int score)
{
    if (IsLocalSlot(slot) == 1) {
        if (RankLog_bss_806D13EC > 0 && RankLog_bss_806D13EC == RankLog_bss_806D13F0) {
            g_technicalTitleGrade = 1;
        }
        g_raceResult = (int)result;
        g_totalScore = score;
    }
}

void TitleTracker_ResetPerRound(void *self, int slot, int newRound)
{
    if (IsLocalSlot(slot) == 1) {
        if (newRound == 1 && RankLog_bss_806D13EC > 0) {
            if (fn_8024F588()->lapB == fn_8024F588()->lapA) {
                g_technicalTitleGrade = 0;
            }
        }
        lbl_806D1428 = 0;
        lbl_806D1450 = 0;
    }
}

void RankLog_UpdateTechnicalFlag(void *self, int v)
{
    RankLog_bss_806D13EC = v;
    if (v > 0) {
        g_technicalTitleGrade = 2;
    }
}

void TitleStats_AccumDistanceCounter(void *self, int slot, unsigned char moving)
{
    if (IsLocalSlot(slot) == 1) {
        if (moving) {
            if (g_totalDistance < 900) {
                g_totalDistance++;
            }
        } else if (g_totalDistance < 900) {
            g_totalDistance = 0;
        }
    }
}

void RankLog_OnPlayerDefeated(void *self, int slot)
{
    if (IsLocalSlot(slot) == 1) {
        g_defeatCount++;
    }
}

void RankLog_OnMatchEnd(void *self, int slot, KartResult *__restrict a, KartResult *__restrict b)
{
    if (IsLocalSlot(slot) == 1) {
        int ka;
        int kb;
        g_matchCount++;
        ka = a->kind;
        kb = b->kind;
        if (ka != 3 && ka != 9 && (kb == 3 || kb == 9)) {
            g_undefeatedStreak++;
        }
    }
}

void RankLog_OnHit(void *self, int slot)
{
    if (IsLocalSlot(slot) == 1) {
        g_hitCount++;
    }
}

void TitleStats_IncPerfectCount(void *self, int slot)
{
    if (IsLocalSlot(slot) == 1) {
        g_perfectCount++;
    }
}

void RankLog_OnOpponentDefeated(void *self, int slot, int kind)
{
    if (IsLocalSlot(slot) == 1) {
        RankLog_bss_806D1434++;
        if (kind == 5) {
            g_gpLossCount++;
        } else if (kind == 4) {
            g_specificDefeatCount++;
        } else if (kind == 1) {
            g_ghostDefeatCount++;
        }
    }
}

void RankLog_OnPlayerVictory(void *self, int slot, int kind)
{
    if (IsLocalSlot(slot) == 1) {
        g_prevRaceScore++;
        if (kind == 5) {
            g_gpWinCount++;
        }
    }
}

void TitleStats_IncCurrentRaceScore(void *self, int slot)
{
    if (IsLocalSlot(slot) == 1) {
        g_currentRaceScore++;
    }
}

void TitleStats_SetEventFlag_806d1420(void *self, int slot)
{
    if (IsLocalSlot(slot) == 1) {
        lbl_806D1420 = 1;
    }
}

void TitleStats_MarkAllCoursesClearedIfDistance(void *self, int slot, float dist)
{
    if (IsLocalSlot(slot) == 1) {
        if (dist >= lbl_806D4DD0) {
            g_allCoursesCleared = 1;
        }
    }
}

void TitleStats_IncTotalRaces(void *self, int slot)
{
    if (IsLocalSlot(slot) == 1) {
        g_totalRaces++;
    }
}

void RankLog_OnRoundComplete(void)
{
    g_prevPrevRaceResult = g_prevRaceResult;
    g_prevRaceResult = g_raceResult;
    g_roundCount++;
}

void PlayerData_RefreshDerivedStats(void)
{
    fn_801D5DD0(&g_playerData);
}

void TitleStats_CaptureRoundContext(void *self, int v, float f)
{
    RankLog_data_806CF204 = v;
    RankLog_data_806CF208 = f;
    RankLog_bss_806D1404 = g_cupId - 1;
    RankLog_bss_806D1408 = g_longRoundFlag;
    RankLog_bss_806D140C = g_reverseRoundFlag;
}

void Empty_NokoNokoHook(void)
{
}

void race_result_handler(void *self, int result)
{
    PlayerData *pd = &g_playerData;

    g_raceResult = result;
    if (result == 0) {
        if (pd->wins < 999) {
            pd->wins++;
        }
        g_consecutiveWins++;
    } else {
        if (pd->losses < 999) {
            pd->losses++;
        }
        g_consecutiveWins = 0;
    }
    g_scoreThreshold = RaceResult_GetRankEntry(1)->time;
    DetermineTitle(0);
}

void TitleStats_FinalizeRace_PlayCountThenTitle(void)
{
    if (g_totalScore <= 0) {
        g_playCount = 0;
    } else if (g_totalScore <= 3) {
        g_playCount = 1;
    }
    DetermineTitle(0);
}

void TitleStats_FinalizeRace_WithRankSnapshot(void)
{
    if (g_totalScore <= 0) {
        g_playCount = 0;
    } else if (g_totalScore <= 3) {
        g_playCount = 1;
    }
    if (RaceResult_GetRankEntry(1) != 0) {
        g_scoreThreshold = RaceResult_GetRankEntry(1)->time;
    }
    DebugPrintf(lbl_80326B54, g_prevRaceResult, g_raceResult);
    DetermineTitle(0);
}

void TitleTracker_Empty_PreFinalizeHook(void)
{
}

void TitleStats_ResetRaceStagingState(void *self)
{
    RankLog_bss_806D13D0 = 0;
    g_stagingTitleId = 0;
    g_titleParam = 0;
    g_nameId = 0;
    g_rankingPosition = -1;
    RankLog_bss_806D1448 = 0;
    RankLog_bss_806D1449 = 0;
    RankLog_InitStartRace(self);
}

void RankLog_Reset(void *self)
{
    DebugPrintf(lbl_80326B70);
    g_roundCount = 0;
    g_prevRaceResult = -1;
    g_prevPrevRaceResult = 0;
    g_raceResult = -1;
    g_consecutiveWins = 0;
    RankLog_bss_806D13D0 = 0;
    g_stagingTitleId = 0;
    g_titleParam = 0;
    g_nameId = 0;
    g_rankingPosition = -1;
    RankLog_bss_806D1448 = 0;
    RankLog_bss_806D1449 = 0;
    RankLog_InitStartRace(self);
}

extern void __copy(void *, const void *, unsigned long);

void RankLog_InitStartRace(void *self)
{
    DebugPrintf(RankLog_InitStartRace_rodata_80326B84);
    g_raceResult = -1;
    g_totalScore = 0;
    g_playCount = -1;
    RankLog_data_806CF1F4 = -1;
    lbl_806CF1F8 = -1;
    g_totalRaces = 0;
    g_allCoursesCleared = 0;
    RankLog_bss_806D13EC = 0;
    RankLog_bss_806D13F0 = 0;
    g_technicalTitleGrade = -1;
    g_totalDistance = 0;
    g_matchCount = 0;
    g_undefeatedStreak = 0;
    g_defeatCount = 0;
    RankLog_data_806CF204 = -1;
    RankLog_data_806CF208 = lbl_806D4DD4;
    RankLog_bss_806D1404 = 0;
    RankLog_bss_806D1408 = 0;
    RankLog_bss_806D140C = 0;
    lbl_806D1420 = 0;
    RankLog_bss_806D1424 = 0;
    lbl_806D1428 = 0;
    g_currentRaceScore = 0;
    g_prevRaceScore = 0;
    RankLog_bss_806D1434 = 0;
    g_perfectCount = 0;
    g_gpWinCount = 0;
    g_gpLossCount = 0;
    g_specificDefeatCount = 0;
    g_ghostDefeatCount = 0;
    RankLog_data_806CF21C = -1;
    lbl_806D1450 = 0;
    g_hazardPassCount = 0;
    RankLog_data_806CF20C = -1;
    g_maxCoins = -1;
    g_scoreThreshold = -1;
    RankLog_InitStartRace_bss_806D144A = 0;
    g_hitCount = 0;
    {
        PlayerData *__restrict dst = &RankLog_bss_805D2F40;
        const PlayerData *__restrict src = &g_playerData;
        /* Copy the header independently of the remaining snapshot fields. */
        dst->word000 = src->word000;
        dst->word004 = src->word004;
        dst->word008 = src->word008;
        dst->byte00C = src->byte00C;
        dst->byte00D = src->byte00D;
        dst->wins = src->wins;
    }
    {
        /* End these pointer lifetimes at the first byte-array copy. */
        PlayerData *__restrict dst = &RankLog_bss_805D2F40;
        const PlayerData *__restrict src = &g_playerData;
        dst->losses = src->losses;
        dst->word014 = src->word014;
        dst->byte018 = src->byte018;
        dst->byte019 = src->byte019;
        dst->byte01A = src->byte01A;
        dst->w01C = src->w01C;
        dst->w020 = src->w020;
        dst->w024 = src->w024;
        dst->w028 = src->w028;
        dst->w02C = src->w02C;
        dst->w030 = src->w030;
        dst->w034 = src->w034;
        dst->w038 = src->w038;
        dst->w03C = src->w03C;
        dst->w040 = src->w040;
        dst->w044 = src->w044;
        dst->w048 = src->w048;
        dst->w04C = src->w04C;
        dst->w050 = src->w050;
        dst->w054 = src->w054;
        dst->w058 = src->w058;
        dst->w05C = src->w05C;
        dst->w060 = src->w060;
        dst->w064 = src->w064;
        dst->w068 = src->w068;
        dst->w06C = src->w06C;
        dst->w070 = src->w070;
        dst->w074 = src->w074;
        dst->w078 = src->w078;
        dst->w07C = src->w07C;
        dst->w080 = src->w080;
        dst->w084 = src->w084;
        dst->w088 = src->w088;
        dst->w08C = src->w08C;
        dst->w090 = src->w090;
        dst->w094 = src->w094;
        dst->w098 = src->w098;
        dst->w09C = src->w09C;
        dst->w0A0 = src->w0A0;
        dst->w0A4 = src->w0A4;
        __copy(dst->bytes0A8, src->bytes0A8, sizeof(src->bytes0A8));
    }
    __copy(RankLog_bss_805D2F40.bytes121, g_playerData.bytes121, sizeof(g_playerData.bytes121));
    {
        /* The tail has its own non-aliasing copy region after both arrays. */
        const PlayerData *__restrict src = &g_playerData;
        PlayerData *__restrict dst = &RankLog_bss_805D2F40;
        dst->word18C = src->word18C;
        dst->word190 = src->word190;
        dst->word194 = src->word194;
        dst->b198 = src->b198;
        dst->b199 = src->b199;
        dst->b19A = src->b19A;
        dst->b19B = src->b19B;
        dst->b19C = src->b19C;
        dst->b19D = src->b19D;
        dst->b19E = src->b19E;
        dst->b19F = src->b19F;
        dst->b1A0 = src->b1A0;
        dst->word1A4 = src->word1A4;
        dst->byte1A8 = src->byte1A8;
        dst->word1AC = src->word1AC;
        dst->byte1B0 = src->byte1B0;
        dst->byte1B1 = src->byte1B1;
        dst->word1B4 = src->word1B4;
        dst->byte1B8 = src->byte1B8;
        dst->byte1B9 = src->byte1B9;
        dst->words1BA.w1BA = src->words1BA.w1BA;
        dst->words1BA.w1BE = src->words1BA.w1BE;
        dst->words1BA.w1C2 = src->words1BA.w1C2;
        dst->words1BA.w1C6 = src->words1BA.w1C6;
        dst->words1BA.w1CA = src->words1BA.w1CA;
        dst->words1BA.w1CE = src->words1BA.w1CE;
        dst->word1D4 = src->word1D4;
        dst->byte1D8 = src->byte1D8;
        dst->byte1D9 = src->byte1D9;
        dst->byte1DA = src->byte1DA;
    }
}


static inline char *TitleStr(TitleEntry *e, int title)
{
    if (title < 0 || title >= 0xBB) {
        return RankLog_data_806CF1E8;
    }
    if (isJapanese() == 0) {
        return e->en;
    }
    return e->jp;
}

static inline char *NameStr(int name)
{
    if (name < 0 || name >= 0x26) {
        return RankLog_data_806CF1E8;
    }
    if (isJapanese() == 0) {
        return RankLog_data_80411B18[name].en;
    }
    return RankLog_data_80411B18[name].jp;
}

/* The target keeps title * sizeof(TitleEntry) in its own saved register, computed
 * before the range re-check, and adds it to the table at each use. */
static inline TitleEntry *TitleAt(TitleEntry *t, int off)
{
    char *e = (char *)t;

    e += off;
    return (TitleEntry *)e;
}

static inline char *TitleStrAt(TitleEntry *tbl, int off, int title)
{
    if (title < 0 || title >= 0xBB) {
        return RankLog_data_806CF1E8;
    }
    if (isJapanese() == 0) {
        return TitleAt(tbl, off)->en;
    }
    return TitleAt(tbl, off)->jp;
}

char *get_title_name(void *self, int title, unsigned char count, int unused, int name)
{
    unsigned char *pool = RankLog_rodata_80324B98;
    int off;
    TitleEntry *tbl;
    char *tstr;

    if (title < 0 || title >= 0xBB) {
        DebugPrintf((char *)pool + 0x2008, title);
        return lbl_806D4A44;
    }
    if (name < 0 || name >= 0x26) {
        DebugPrintf((char *)pool + 0x2038, name);
        return lbl_806D4A44;
    }
    tbl = (TitleEntry *)(pool + 0x1520);
    off = title * 12;
    tstr = TitleStrAt(tbl, off, title);
    switch (((TitleEntry *)((char *)tbl + off))->type) {
    case 0:
        sprintf(RankLog_bss_805D311C, lbl_806D4DD8, tstr, NameStr(name));
        break;
    case 1:
        sprintf(RankLog_bss_805D311C, tstr);
        break;
    case 2:
        sprintf(RankLog_bss_805D311C, lbl_806D4DE0, count, tstr, NameStr(name));
        break;
    default:
        memset(RankLog_bss_805D311C, 0, 0x200);
        DebugPrintf((char *)pool + 0x2068, title, count, name);
        break;
    }
    return RankLog_bss_805D311C;
}

char *get_title_name_global(void)
{
    char *tstr;
    unsigned char *pool;
    TitleEntry *tbl;
    int title;
    unsigned char count;
    int name;
    int off;

    pool = RankLog_rodata_80324B98;
    title = g_playerData.b19B;
    name = g_playerData.byte1B1;
    count = g_playerData.b19C;

    if (title < 0 || title >= 0xBB) {
        DebugPrintf((char *)pool + 0x2008, title);
        return lbl_806D4A44;
    }
    if (name < 0 || name >= 0x26) {
        DebugPrintf((char *)pool + 0x2038, name);
        return lbl_806D4A44;
    }
    tbl = (TitleEntry *)(pool + 0x1520);
    off = title * 12;
    tstr = TitleStrAt(tbl, off, title);
    switch (((TitleEntry *)((char *)tbl + off))->type) {
    case 0:
        sprintf(RankLog_bss_805D311C, lbl_806D4DD8, tstr, NameStr(name));
        break;
    case 1:
        sprintf(RankLog_bss_805D311C, tstr);
        break;
    case 2:
        sprintf(RankLog_bss_805D311C, lbl_806D4DE0, count, tstr, NameStr(name));
        break;
    default:
        memset(RankLog_bss_805D311C, 0, 0x200);
        DebugPrintf((char *)pool + 0x2068, title, count, name);
        break;
    }
    return RankLog_bss_805D311C;
}

int get_title_result(void *self, int *title, int *param, int *name)
{
    if (RankLog_bss_806D13D0 == 0) {
        DetermineTitle(1);
        RankLog_bss_806D13D0 = 1;
    }
    if (g_stagingTitleId > 0) {
        *title = g_stagingTitleId;
        *param = g_titleParam;
        if (name != 0) {
            *name = g_nameId;
        }
        return 1;
    }
    return 0;
}

typedef struct TitleTracker {
    void **vt;
} TitleTracker;

static inline TitleTracker *tracker(void)
{
    return (TitleTracker *)SINGLETON_INSTANCE(lbl_806D10A0);
}

TitleTracker *TitleTracker_GetOrCreateSingleton(void)
{
    if (tracker() == 0) {
        TitleTracker *t = (TitleTracker *)Alloc(4);
        if (t != 0) {
            t->vt = TitleTracker_data_80411DC0;
            lbl_806D10A0 = t;
            t->vt = TitleTracker_data_80411DB4;
        }
    }
    return tracker();
}


static inline int CurrentNameScore(void)
{
    int j;
    int k;
    int score;
    long i;
    score = 0;
    for (i = 0; i < 2; i++) {
        for (j = 1; j < 9; j++) {
            for (k = 0; k < 8; k++) {
                if (fn_801D5B8C(&g_playerData, i, j, k) == 1) {
                    score++;
                }
            }
        }
    }
    {
        int cup;
        int variant;

        for (cup = 1; cup < 9; cup++) {
            for (variant = 0; variant < 2; variant++) {
                if (fn_801D59F8(&g_playerData, cup, variant) == 1) {
                    score += 4;
                }
            }
        }
    }
    score += g_playerData.wins;
    return score;
}

static inline int CurrentPlayerNameId(int chara)
{
    return DetermineNameId(CurrentNameScore(), chara);
}

void DetermineTitle(unsigned char mode)
{
    unsigned char skip;
    TitleCheckFn *checks = 0;
    int count = 0;
    TitleCheckFn pre = 0;
    int i;
    unsigned char *tbl = (unsigned char *)RankLog_data_80411458;
    unsigned char *pool = RankLog_rodata_80324B98;

    if (lbl_80598A60.mode == 2 || (lbl_80598A60.mode == 1 && lbl_80598A60.flag24 == 0)) {
        g_stagingTitleId = 0;
        g_titleParam = 0;
        g_nameId = 0;
        return;
    }
    g_nameId = CurrentPlayerNameId(g_characterId);
    if (mode == 1) {
        return;
    }
    if (mode != 0) {
        checks = DetermineTitle_data_806CF224;
        count = 1;
    } else {
        switch (g_gameMode) {
        case 0:
            if (g_cupId >= 9) {
                checks = DetermineTitle_data_806CF220;
                count = 1;
            } else {
                checks = (TitleCheckFn *)(tbl + 0x7F0);
                count = 0x20;
                pre = TitleCheck_NewClearedRecord_Race;
            }
            break;
        case 1:
            checks = (TitleCheckFn *)(tbl + 0x870);
            count = 0x10;
            pre = TaTitle_CheckAllCoursesRecorded;
            break;
        case 2:
            checks = (TitleCheckFn *)(tbl + 0x8B0);
            count = 0x28;
            break;
        default:
            DebugPrintf((char *)pool + 0x2084);
            break;
        }
    }
    DebugPrintf((char *)pool + 0x20AC, g_stagingTitleId);
    skip = 0;
    if (pre != 0 && pre() == 1 && g_stagingTitleId > 0 && g_stagingTitleId != g_playerData.b19B) {
        skip = 1;
    }
    DebugPrintf((char *)pool + 0x20C4, g_stagingTitleId);
    if (checks != 0 && !skip) {
        for (i = 0; i < count; i++) {
            if (checks[i]() == 1 && g_stagingTitleId > 0) {
                g_stagingTitleId += 0x2D;
                if (g_stagingTitleId != g_playerData.b19B || g_stagingTitleId == 0x42) {
                    DebugPrintf((char *)pool + 0x20D8, i, g_stagingTitleId);
                    break;
                }
            }
        }
    }
    DebugPrintf((char *)pool + 0x2100, g_stagingTitleId);
}

int DateTitle_GetMonthSeasonIndex(void)
{
    OSCalendarTime td;

    OSTicksToCalendarTime(OSGetTime(), &td);
    if (td.hour < 5 || td.hour >= 22) {
        return 13;
    }
    if (td.hour < 10) {
        return 0;
    }
    if (td.hour < 11) {
        return 1;
    }
    if (td.hour < 12) {
        return 2;
    }
    if (td.hour < 13) {
        return 3;
    }
    if (td.hour < 14) {
        return 4;
    }
    if (td.hour < 15) {
        return 5;
    }
    if (td.hour < 16) {
        return 6;
    }
    if (td.hour < 17) {
        return 7;
    }
    if (td.hour < 18) {
        return 8;
    }
    if (td.hour < 19) {
        return 9;
    }
    if (td.hour < 20) {
        return 10;
    }
    if (td.hour < 21) {
        return 11;
    }
    return 12;
}

TitleTracker *TitleTrackerSingleton_Dtor(TitleTracker *self, short flag)
{
    if (self != 0) {
        self->vt = TitleTracker_data_80411DC0;
        if (flag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}

unsigned char TaTitle_CheckAllCoursesRecorded(void)
{
    int a;
    int b;
    int c;
    int d;
    void *entry;

    for (a = 0; a < 2; a++) {
        for (b = 0; b < 8; b++) {
            for (c = 0; c < 2; c++) {
                for (d = 0; d < 2; d++) {
                    entry = TaRecord_GetEntry_Indexed(0, a + 1, b + 1, c, d);
                    if (wcscmp(&g_playerData, entry) != 0) {
                        return 0;
                    }
                }
            }
        }
    }
    SetTitle(0x2D, 0);
    return 1;
}


unsigned char TitleCheck_NewClearedRecord_Race(void)
{
    PlayerData *pd = &g_playerData;
    int base = pd->b19A == 0 ? 0 : 6;
    int j;
    int cur;
    int prev;
    int mode;

    for (mode = 0; mode < 2; mode++) {
        cur = 0;
        prev = 0;
        for (j = 1; j < 9; j++) {
            if (fn_801D5B8C(pd, mode, j, 3) == 1) {
                cur++;
            }
            if (fn_801D5B8C(&RankLog_bss_805D2F40, mode, j, 3) == 1) {
                prev++;
            }
        }
        if (cur != prev && cur >= 8) {
            g_stagingTitleId = 1 + base + mode;
            return 1;
        }
    }
    for (mode = 0; mode < 2; mode++) {
        cur = 0;
        prev = 0;
        for (j = 1; j < 9; j++) {
            if (fn_801D5B8C(pd, mode, j, 7) == 1) {
                cur++;
            }
            if (fn_801D5B8C(&RankLog_bss_805D2F40, mode, j, 7) == 1) {
                prev++;
            }
        }
        if (cur != prev && cur >= 8) {
            g_stagingTitleId = 3 + base + mode;
            return 1;
        }
    }
    for (mode = 0; mode < 2; mode++) {
        cur = 0;
        prev = 0;
        for (j = 1; j < 9; j++) {
            if (fn_801D59F8(pd, j, mode) == 1) {
                cur++;
            }
            if (fn_801D59F8(&RankLog_bss_805D2F40, j, mode) == 1) {
                prev++;
            }
        }
        if (cur != prev && cur >= 8) {
            g_stagingTitleId = 5 + base + mode;
            return 1;
        }
    }
    {
        int i;

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 8; j++) {
                cur = 0;
                prev = 0;
                if (fn_801D5B8C(pd, i, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 3) == 1) {
                    cur = 1;
                }
                if (fn_801D5B8C(&RankLog_bss_805D2F40, i, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 3) == 1) {
                    prev = 1;
                }
                if (cur != prev && cur >= 1) {
                    g_stagingTitleId = j + 0xD;
                    return 1;
                }
            }
        }
    }
    {
        int i;

        for (i = 0; i < 2; i++) {
            for (j = 0; j < 8; j++) {
                cur = 0;
                prev = 0;
                if (fn_801D5B8C(pd, i, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 7) == 1) {
                    cur = 1;
                }
                if (fn_801D5B8C(&RankLog_bss_805D2F40, i, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 7) == 1) {
                    prev = 1;
                }
                if (cur != prev && cur >= 1) {
                    g_stagingTitleId = j + 0x15;
                    return 1;
                }
            }
        }
    }
    for (j = 0; j < 8; j++) {
        cur = 0;
        prev = 0;
        if (fn_801D59F8(pd, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 0) == 1) {
            cur = 1;
        }
        if (fn_801D59F8(&RankLog_bss_805D2F40, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 0) == 1) {
            prev = 1;
        }
        if (cur != prev && cur >= 1) {
            g_stagingTitleId = j + 0x1D;
            return 1;
        }
    }
    for (j = 0; j < 8; j++) {
        cur = 0;
        prev = 0;
        if (fn_801D59F8(pd, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 1) == 1) {
            cur = 1;
        }
        if (fn_801D59F8(&RankLog_bss_805D2F40, TitleCheck_NewClearedRecord_Race_rodata_80326B04[j], 1) == 1) {
            prev = 1;
        }
        if (cur != prev && cur >= 1) {
            g_stagingTitleId = j + 0x25;
            return 1;
        }
    }
    return 0;
}

static inline int CupSlot(int cup)
{
    int i;

    for (i = 0; i < 8; i++) {
        if (cup == TitleCheck_CupCleared_rodata_803269AC[i]) {
            return i;
        }
    }
    return 0;
}

unsigned char TitleCheck_CupCleared(void)
{
    if (g_gameMode == 1) {
        return 0;
    }
    if (g_raceResult == 0) {
        int lr = g_longRoundFlag == 1;
        int slot = CupSlot(g_cupId);
        SetTitle(0x7E + slot * 2 + lr, 0);
        return 1;
    }
    return 0;
}

#pragma dont_inline on
unsigned char TitleCheck_MidpointMilestone(void)
{
    unsigned char hit = 0;

    if (g_gameMode == 0) {
        if (g_roundIndex == 2 || g_roundIndex == 6) {
            hit = 1;
        }
    } else if (g_gameMode == 2) {
        if (g_roundCount > 0) {
            hit = 1;
        }
    }
    if (hit == 1) {
        g_stagingTitleId = DateTitle_GetMonthSeasonIndex() + 0x70;
        g_titleParam = 0;
        return 1;
    }
    return 0;
}
#pragma dont_inline reset

unsigned char fn_800A7C0C(void)
{
    if (RankLog_bss_805D2F40.wins + RankLog_bss_805D2F40.losses == 0 && g_playerData.wins + g_playerData.losses > 0) {
        SetTitle((g_ccClass == 2) + 0x6E, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_FirstPlayToday_TA(void)
{
    OSCalendarTime td;

    OSTicksToCalendarTime(OSGetTime(), &td);
    if (td.wday == 0 && g_roundCount == 3) {
        SetTitle(0x6D, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_FirstPlayEver(void)
{
    if (g_playCount == 0) {
        SetTitle(0x6C, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A7CF4(void)
{
    if (g_rankingPosition < 0) {
        return 0;
    }
    SetTitle(g_rankingPosition + 0x69, 0);
    return 1;
}

unsigned char fn_800A7D20(void)
{
    if (g_consecutiveWinsTier > 0) {
        SetTitle(RankLog_rodata_80326ADC[g_consecutiveWinsTier - 1], 0);
        return 1;
    }
    return 0;
}


extern int lbl_80677CC8[4];
extern int *fn_8016CB44(void);
extern int g_kartVariant;
extern int GetCoinMilage(PlayerData *p);
extern signed char fn_801D5970(PlayerData *p);
extern int CheckTitle_OriginalKartCoinMilage_rodata_80326A64[13][2];
extern int TitleCheck_NewClearedCountStep_rodata_80326A24[16];
extern int RankLog_rodata_80326A14[4];
extern int RankLog_rodata_803269CC[18];

#include "game/types/Int4.h"
extern Int4 TitleCheck_BattleWinsMilestone_rodata_80326ACC;

unsigned char TitleCheck_AllRecordsCleared(void)
{
    int sum = 0;
    int i;

    for (i = 0; i < 4; i++) {
        sum += lbl_80677CC8[i];
    }

    if (sum == fn_8024F588()->lapB - 1) {
        SetTitle(0x5E, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_TechGradeMax_NoLoss(void)
{
    if (g_technicalTitleGrade == 2 && g_raceResult == 0) {
        SetTitle(0x5D, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_TechGrade1(void)
{
    if (g_technicalTitleGrade == 1) {
        SetTitle(0x5C, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_TechGrade0(void)
{
    if (g_technicalTitleGrade == 0) {
        SetTitle(0x5B, 0);
        return 1;
    }
    return 0;
}

static inline signed char LookupTarget(TargetCup *m)
{
    return m[g_cupId][g_ccClass][g_longRoundFlag].score;
}

static inline int TargetScore(void)
{
    int t;
    int n;

    if (g_gameMode == 0) {
        t = LookupTarget((TargetCup *)RankLog_data_80411458);
    } else if (g_gameMode == 1) {
        t = LookupTarget((TargetCup *)sBattleTargets);
    } else if (g_gameMode == 2) {
        t = LookupTarget((TargetCup *)sTimeAttackTargets);
    } else {
        t = 0;
    }
    n = fn_8016CB44() != 0 ? *fn_8016CB44() : 0;
    return t * n;
}

unsigned char TitleCheck_ScoreOverQuarterTarget(void)
{
    int target = TargetScore();

    if (target <= 0) {
        return 0;
    }
    if (g_currentRaceScore <= target / 4) {
        SetTitle(0x5A, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A7F9C(void)
{
    if (g_hitCount >= 7) {
        SetTitle(0x59, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A7FC8(void)
{
    if (g_currentRaceScore > g_prevRaceScore && g_raceResult >= 4) {
        SetTitle(0x58, 0);
        return 1;
    }
    return 0;
}

unsigned char CheckTitle_EnhancedKartTA(void)
{
    if (g_kartVariant == 3 && g_gameMode == 2 && g_raceResult == 0 &&
        g_totalScore >= g_scoreThreshold + 5) {
        SetTitle(0x57, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A805C(void)
{
    if (g_roundCount > 0 && g_prevRaceResult != 0 && g_raceResult == 0) {
        SetTitle(0x56, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A80A0(void)
{
    if (g_maxCoins >= 180) {
        SetTitle(0x55, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_HeavyLossWithWin(void)
{
    int target = TargetScore();

    if (target <= 0) {
        return 0;
    }
    if (g_gpWinCount > 0 && g_gpLossCount >= 9) {
        SetTitle(0x54, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A8208(void)
{
    if (g_ghostDefeatCount >= 6) {
        SetTitle(0x53, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A8234(void)
{
    if (g_gpWinCount >= 10 && g_gpLossCount == 0) {
        SetTitle(0x52, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A826C(void)
{
    if (g_totalDistance >= 900) {
        SetTitle(0x51, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A8298(void)
{
    if (g_matchCount + g_defeatCount == 0) {
        SetTitle(0x50, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A82C8(void)
{
    if (g_specificDefeatCount >= 6) {
        SetTitle(0x4F, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A82F4(void)
{
    if (g_prevRaceScore == 0) {
        SetTitle(0x4E, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A8320(void)
{
    if (g_totalRaces >= 50) {
        SetTitle(0x4D, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A834C(void)
{
    if (g_playCount == 1) {
        SetTitle(0x4C, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A8378(void)
{
    if (g_allCoursesCleared == 1) {
        SetTitle(0x4B, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A83A4(void)
{
    unsigned char hit = 0;

    if (g_cupId == 5) {
        if (g_hazardPassCount >= 6) {
            hit = 1;
        }
    } else if (g_cupId == 6) {
        if (g_hazardPassCount >= 4) {
            hit = 1;
        }
    }
    if (hit == 1) {
        SetTitle(0x4A, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A840C(void)
{
    if (g_perfectCount >= 3) {
        SetTitle(0x49, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A8438(void)
{
    if (lbl_806CF1F8 >= 0 && lbl_806CF1F8 < 60) {
        if (g_raceResult > 0) {
            SetTitle(0x47, 0);
            return 1;
        }
        if (g_raceResult == 0) {
            SetTitle(0x48, 0);
            return 1;
        }
    }
    return 0;
}

unsigned char TitleCheck_UndefeatedStreak15(void)
{
    if (g_undefeatedStreak >= 15) {
        SetTitle(0x46, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_BattleWinsMilestone(void)
{
    Int4 tbl = TitleCheck_BattleWinsMilestone_rodata_80326ACC;
    int i;

    for (i = 0; i < 4; i++) {
        if (g_roundCount == tbl.v[i]) {
            SetTitle(i + 0x40, 0);
            return 1;
        }
    }
    return 0;
}

unsigned char CheckTitle_OriginalKartCoinMilage(void)
{
    int milage = GetCoinMilage(&g_playerData);
    int id = -1;

    if (milage >= 10000 && milage <= 10100) {
        id = 2;
    }
    if (milage >= 4000 && milage <= 4100) {
        id = 1;
    }
    if (milage >= 1470 && milage <= 1570) {
        id = 0;
    }
    if (id >= 0) {
        SetTitle(id + 0x3C, 0);
        return 1;
    }
    if (g_kartVariant != 2) {
        return 0;
    }
    if (g_characterId < 0 || g_characterId >= 13) {
        return 0;
    }
    if (milage >= CheckTitle_OriginalKartCoinMilage_rodata_80326A64[g_characterId][0] && milage <= CheckTitle_OriginalKartCoinMilage_rodata_80326A64[g_characterId][1]) {
        SetTitle(0x3F, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_NewClearedCountStep(void)
{
    if (g_ccClass == 0) {
        return 0;
    }
    if (g_ccClass == 1) {
        int cur = fn_801D5970(&g_playerData);

        if (cur != fn_801D5970(&RankLog_bss_805D2F40) && (signed char)cur > 0 && cur <= 16) {
            SetTitle(cur + 0x1B, 0);
            return 1;
        }
        return 0;
    } else {
        unsigned char *a = (unsigned char *)&RankLog_bss_805D2F40;
        unsigned char *b = (unsigned char *)&g_playerData;
        int na = 0;
        int nb = 0;
        int i;

        for (i = 0; i < 0x20; a++, b++, i++) {
            if (a[0x48] == 1) {
                na++;
            }
            if (a[0x88] == 1) {
                na++;
            }
            if (b[0x48] == 1) {
                nb++;
            }
            if (b[0x88] == 1) {
                nb++;
            }
        }
        if (na == nb) {
            return 0;
        }
        for (i = 0; i < 16; i++) {
            if (na == TitleCheck_NewClearedCountStep_rodata_80326A24[i]) {
                SetTitle(i + 0x2C, 0);
                return 1;
            }
        }
        return 0;
    }
}

unsigned char fn_800A87E0(void)
{
    PlayerData *pd = &g_playerData;
    int total = pd->wins + pd->losses;
    int i;

    if (total == 0) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        if (total % RankLog_rodata_80326A14[i] == 0) {
            SetTitle(i + 0x18, 0);
            return 1;
        }
    }
    return 0;
}

unsigned char fn_800A8854(void)
{
    if (g_roundCount != 2) {
        return 0;
    }
    if (g_prevPrevRaceResult != 0 && g_prevRaceResult != 0 && g_raceResult == 0) {
        SetTitle(0x17, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_ConsecutiveWins(void)
{
    int wins = g_consecutiveWins;

    if (wins >= 2 && wins <= 4) {
        SetTitle(0x15, wins);
        return 1;
    }
    if (wins >= 5) {
        SetTitle(0x16, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A88FC(void)
{
    int wins = g_playerData.wins;
    int i;

    if (wins == RankLog_bss_805D2F40.wins) {
        return 0;
    }
    for (i = 17; i >= 0; i--) {
        if (wins == RankLog_rodata_803269CC[i]) {
            SetTitle(i + 3, 0);
            return 1;
        }
    }
    return 0;
}

unsigned char fn_800A8974(void)
{
    PlayerData *pd = &g_playerData;
    int losses = pd->losses;

    if (losses == 0) {
        return 0;
    }
    if (RankLog_bss_805D2F40.losses == losses) {
        return 0;
    }
    if (pd->b19B == 0x2E) {
        SetTitle(2, 0);
        return 1;
    }
    return 0;
}

unsigned char fn_800A89D8(void)
{
    PlayerData *pd = &g_playerData;
    int losses = pd->losses;
    int wins = pd->wins;

    if (losses > 0) {
        return 0;
    }
    if (wins == 3) {
        SetTitle(1, 0);
        return 1;
    }
    return 0;
}

unsigned char TitleCheck_AlwaysFalse(void)
{
    return 0;
}

int DetermineNameId(int score, int chara)
{
    unsigned char allB = 0;
    unsigned char allA = 0;
    int na = 0;
    int nb = 0;
    int j;
    int thr;
    int id;
    unsigned char normal;

    for (j = 1; j < 9; j++) {
        if (fn_801D59F8(&g_playerData, j, 0) == 1) {
            na++;
        }
        if (fn_801D59F8(&g_playerData, j, 1) == 1) {
            nb++;
        }
    }
    if (na == 8) {
        allA = 1;
    }
    if (nb == 8) {
        allB = 1;
    }
    if (allB == 1 && score >= 150) {
        return 0x25;
    }
    if (allA == 1) {
        for (thr = 0x80, id = 0x24; thr >= 0x64; thr -= 4, id--) {
            if (thr >= score) {
                return id;
            }
        }
    }
    normal = 1;
    if (chara == 3 || chara == 9) {
        normal = 0;
    }
    for (thr = 0x60, id = 0x1C; thr >= 0x3C; thr -= 4, id--) {
        if (thr <= score) {
            return id;
        }
    }
    if (score >= 0x38) {
        return normal == 1 ? 0x11 : 0x12;
    }
    if (score >= 0x34) {
        return normal == 1 ? 0xF : 0x10;
    }
    if (score >= 0x30) {
        return normal == 1 ? 0xD : 0x0E;
    }
    for (id = 0xA, thr = 0x2C; id >= 0; thr -= 4, id--) {
        if (thr <= score) {
            return id + 2;
        }
    }
    if (score >= 0) {
        return g_gameMode == 1;
    }
    return 0;
}

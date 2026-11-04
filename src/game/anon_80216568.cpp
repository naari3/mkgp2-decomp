/*
 * 0x80216568..0x80218B5C: post-race coin reward calculation, the
 * coin/milestone table lookups and setup, a row of text sprites and the
 * "insert card" prompt tasks.
 */

#include "game/CoinMilestone.h"
#include "game/FadeLogo.h"

typedef struct CoinTimeTable {
    float t[8][2][4];
} CoinTimeTable;

/*
 * Coin reward tables inside the rodata pool at lbl_803C3F50. The original
 * TU owned them as static const arrays (addressed off the pool base), so
 * CalcEarnedCoins does not match until that rodata is split into this TU.
 */
typedef struct CoinRodata {
    char pad000[0x408];
    int winBonus[3];
    int positionGP[4][4];
    int positionVS[3][4];
    int timeBonusA[4];
    int timeBonusB[4];
    int perfectBonus[3];
    float parTime[8][2];
    char pad530[0x7DC - 0x530];
    CoinTimeTable timesFwd;
    char pad8DC[0xAFC - 0x8DC];
    CoinTimeTable timesRev;
} CoinRodata;

extern const CoinRodata lbl_803C3F50;
#define kWinBonus (rd->winBonus)
#define kPositionGP (rd->positionGP)
#define kPositionVS (rd->positionVS)
#define kTimeBonusA (rd->timeBonusA)
#define kTimeBonusB (rd->timeBonusB)
#define kPerfectBonus (rd->perfectBonus)
#define kParTime (rd->parTime)
#define kTimesFwd (rd->timesFwd)
#define kTimesRev (rd->timesRev)

typedef struct RaceResult {
    char pad00;
    unsigned char retired;
    char pad02[0x18 - 0x2];
    int coins;
    int coinGoal;
} RaceResult;

typedef struct RankSlot {
    unsigned char active;
} RankSlot;

typedef struct PlayerData {
    char pad00[0x48];
    unsigned char cleared[8][2][2];
} PlayerData;

extern "C" {

extern const int lbl_803C4440[13];
extern const int lbl_803C4474[10];
extern const int lbl_803C449C[10];
extern const char *lbl_804EDB40[10][2];

extern PlayerData g_playerData;
extern int g_extraCoinsToAdd;
extern int g_coinMilageBeforeRace;
extern int extraBattleBonus;
extern int battleBonus;
extern int positionBonus;
extern int winBonus;
extern int baseCoins;
extern int g_earnedCoins;
extern int g_ccClass;
extern int g_gameMode;
extern int g_cupId;
extern int g_longRoundFlag;
extern int g_reverseRoundFlag;
extern unsigned char g_raceEnded;
extern float g_totalRaceTime;
extern int lbl_806D1ACC;
extern const float lbl_806DAEB0;
extern const float lbl_806DAEB4;
extern const float lbl_806DAEB8;

int GetCoinMilage(void *playerData);
RaceResult *fn_8024F588(void);
RankSlot *RankSlot_GetByIndex(int i);
int isJapanese(void);

static inline int TimeRank(float d) {
    if (d < lbl_806DAEB0) {
        return 0;
    }
    if (d < lbl_806DAEB4) {
        return 1;
    }
    if (d < lbl_806DAEB8) {
        return 2;
    }
    return 3;
}

void CalcEarnedCoins(void) {
    const CoinRodata *rd = &lbl_803C3F50;
    int cc;
    int rank;
    int i;
    int mode;

    g_earnedCoins = 0;
    baseCoins = 0;
    winBonus = 0;
    positionBonus = -1;
    g_extraCoinsToAdd = -1;
    battleBonus = -1;
    extraBattleBonus = -1;
    g_coinMilageBeforeRace = GetCoinMilage(&g_playerData);
    cc = g_ccClass;
    baseCoins = fn_8024F588()->coins;
    winBonus = 0;
    {
        RaceResult *r = fn_8024F588();
        if (r->coins >= r->coinGoal) {
            winBonus = kWinBonus[cc];
        }
    }
    rank = 3;
    for (i = 0; i < 3; i++) {
        if (RankSlot_GetByIndex(i)->active == 1) {
            rank = i;
        }
    }
    mode = g_gameMode;
    if (mode == 0) {
        int c = cc;
        if (cc == 2 && lbl_806D1ACC > 0) {
            c = 3;
        }
        positionBonus = kPositionGP[c][rank];
    } else if (mode == 2) {
        positionBonus = kPositionVS[cc][rank];
    }
    if (mode == 1 && cc == 1) {
        int k = TimeRank(g_totalRaceTime - kParTime[g_cupId - 1][g_longRoundFlag]);
        if (!g_raceEnded) {
            k = 3;
        }
        battleBonus = kTimeBonusA[k];
    }
    if (mode == 1 && cc == 2) {
        CoinTimeTable fwd = kTimesFwd;
        CoinTimeTable rev = kTimesRev;
        float *t;
        int k;
        if (g_reverseRoundFlag != 0) {
            t = rev.t[g_cupId - 1][g_longRoundFlag];
        } else {
            t = fwd.t[g_cupId - 1][g_longRoundFlag];
        }
        k = TimeRank(g_totalRaceTime - t[3]);
        if (!g_raceEnded) {
            k = 3;
        }
        battleBonus = kTimeBonusB[k];
        if (!fn_8024F588()->retired) {
            if (g_playerData.cleared[g_cupId - 1][g_longRoundFlag][g_reverseRoundFlag] == 1) {
                extraBattleBonus = RankSlot_GetByIndex(0)->active ? kPerfectBonus[cc] : 0;
            }
        }
    }
    g_earnedCoins = baseCoins + winBonus;
    if (positionBonus >= 0) {
        g_earnedCoins += positionBonus;
    }
    if (battleBonus >= 0) {
        g_earnedCoins += battleBonus;
    }
    if (extraBattleBonus >= 0) {
        g_earnedCoins += extraBattleBonus;
    }
}

} /* extern "C" */

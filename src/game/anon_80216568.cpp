#include "game/types/text_word.h"
/*
 * 0x80216568..0x80216908: post-race coin reward calculation.
 * The constant pool also supplies the coin display and time trial records.
 */

#include "game/CoinMilestone.h"
#include "game/FadeLogo.h"

struct CoinTimeEntry { int course; const char *file; int frames; float time; };
struct CoinTimeTable { CoinTimeEntry t[8][2]; };
extern "C" {
extern const char lbl_803C452C[16];
extern const char lbl_803C453C[15];
extern const char lbl_803C454C[16];
extern const char lbl_803C455C[15];
extern const char lbl_803C456C[16];
extern const char lbl_803C457C[15];
extern const char lbl_803C458C[16];
extern const char lbl_803C459C[15];
extern const char lbl_803C45AC[16];
extern const char lbl_803C45BC[15];
extern const char lbl_803C45CC[16];
extern const char lbl_803C45DC[15];
extern const char lbl_803C45EC[16];
extern const char lbl_803C46FC[15];
extern const char lbl_803C470C[16];
extern const char lbl_803C471C[16];
extern const char lbl_803C482C[17];
extern const char lbl_803C4840[16];
extern const char lbl_803C4850[17];
extern const char lbl_803C4864[16];
extern const char lbl_803C4874[17];
extern const char lbl_803C4888[16];
extern const char lbl_803C4898[17];
extern const char lbl_803C48AC[16];
extern const char lbl_803C48BC[17];
extern const char lbl_803C48D0[16];
extern const char lbl_803C48E0[17];
extern const char lbl_803C48F4[16];
extern const char lbl_803C4A04[17];
extern const char lbl_803C4A18[16];
extern const char lbl_803C4A28[17];
extern const char lbl_803C4A3C[16];

/* Display colour and coin milestone scale pairs preceding the reward tables. */
extern const float CalcEarnedCoins_rodata_803C3F50[258] = {
    0.0f, 0.0f, 0.0f, 1.0f, 0.699999988079071f, 0.8999999761581421f, 0.0f, 0.0f,
    500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f,
    4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f,
    5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f,
    2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f,
    0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f,
    3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f,
    500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f,
    4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f,
    5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f,
    2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f,
    0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f,
    3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f,
    500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f,
    4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f,
    1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f,
    5000.0f, 66.66667175292969f, 0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f,
    2000.0f, 66.66667175292969f, 3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f,
    0.0f, 0.0f, 500.0f, 66.66667175292969f, 1000.0f, 66.66667175292969f, 2000.0f, 66.66667175292969f,
    3000.0f, 66.66667175292969f, 4000.0f, 66.66667175292969f, 5000.0f, 66.66667175292969f, 0.0f, 0.0f,
    500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f,
    4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f,
    5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f,
    2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f,
    0.0f, 0.0f, 500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f,
    3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f,
    500.0f, 83.33333587646484f, 1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f,
    4000.0f, 83.33333587646484f, 5000.0f, 83.33333587646484f, 0.0f, 0.0f, 500.0f, 83.33333587646484f,
    1000.0f, 83.33333587646484f, 2000.0f, 83.33333587646484f, 3000.0f, 83.33333587646484f, 4000.0f, 83.33333587646484f,
    5000.0f, 83.33333587646484f,
};
static const int kWinBonus[3] = {
    5, 5, 5,
};
static const int kPositionGP[4][4] = {
    10, 8, 6, 5, 10, 8, 6, 5,
    10, 8, 6, 5, 10, 8, 6, 5,
};
static const int kPositionVS[3][4] = {
    20, 15, 12, 10, 20, 15, 12, 10,
    20, 15, 12, 10,
};
static const int kTimeBonusA[4] = {
    20, 15, 12, 10,
};
static const int kTimeBonusB[4] = {
    25, 20, 15, 10,
};
static const int kPerfectBonus[3] = {
    10, 10, 10,
};
static const float kParTime[8][2] = {
    114.0f, 116.0f, 126.0f, 117.0f, 117.0f, 142.0f, 125.0f, 150.0f,
    130.0f, 157.0f, 137.0f, 144.0f, 135.0f, 132.0f, 144.0f, 142.0f,
};
extern const int lbl_803C4440[13] = { 0, 3, 6, 9, 11, 7, 4, 12, 8, 10, 2, 5, 1 };
extern const int lbl_803C4474[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
extern const int lbl_803C449C[10] = { 3140, 3136, 3135, 3137, 3138, 3141, 3143, 3139, 3144, 3142 };
extern const int lbl_803C44C4[3] = { TEXT_WORD(0x82, 0xBF, 0x82, 0xE5), TEXT_WORD(0x82, 0xF1, 0x82, 0xDC), TEXT_WORD(0x82, 0xB0, 0, 0) };
extern const int lbl_803C44D0[4] = { TEXT_WORD(0x83, 'E', 0x83, 'H'), TEXT_WORD(0x83, 0x93, 0x83, 'e'), TEXT_WORD(0x83, 'b', 0x83, 'h'), 0 };
extern const int lbl_803C44E0[3] = { TEXT_WORD(0x82, 0xB0, 0x82, 0xA2), TEXT_WORD(0x82, 0xB5, 0x82, 0xE1), 0 };
extern const int lbl_803C44EC[3] = { TEXT_WORD(0x82, 0xA9, 0x82, 0xA2), TEXT_WORD(0x82, 0xBC, 0x82, 0xAD), 0 };
extern const int lbl_803C44F8[3] = { TEXT_WORD(0x82, 0xAD, 0x82, 0xDC), TEXT_WORD(0x82, 0xBF, 0x82, 0xE1), TEXT_WORD(0x82, 0xF1, 0, 0) };
extern const int lbl_803C4504[3] = { TEXT_WORD(0x83, 'l', 0x83, 'R'), TEXT_WORD(0x83, '~', 0x83, '~'), 0 };
extern const int lbl_803C4510[3] = { TEXT_WORD(0x83, '}', 0x83, 'W'), TEXT_WORD(0x83, 'V', 0x83, 0x83), TEXT_WORD(0x83, 0x93, 0, 0) };
extern const int lbl_803C451C[4] = { TEXT_WORD(0x82, 0xAB, 0x82, 0xE5), TEXT_WORD(0x82, 0xA4, 0x82, 0xE8), TEXT_WORD(0x82, 0xE3, 0x82, 0xA4), 0 };
extern const char lbl_803C452C[16] = "ta_mr_short.bin";
extern const char lbl_803C453C[15] = "ta_mr_long.bin";
extern const char lbl_803C454C[16] = "ta_dk_short.bin";
extern const char lbl_803C455C[15] = "ta_dk_long.bin";
extern const char lbl_803C456C[16] = "ta_wc_short.bin";
extern const char lbl_803C457C[15] = "ta_wc_long.bin";
extern const char lbl_803C458C[16] = "ta_pc_short.bin";
extern const char lbl_803C459C[15] = "ta_pc_long.bin";
extern const char lbl_803C45AC[16] = "ta_kp_short.bin";
extern const char lbl_803C45BC[15] = "ta_kp_long.bin";
extern const char lbl_803C45CC[16] = "ta_rb_short.bin";
extern const char lbl_803C45DC[15] = "ta_rb_long.bin";
extern const char lbl_803C45EC[16] = "ta_yi_short.bin";
static const CoinTimeTable kTimesFwdShort = {{
    { { 0, lbl_803C452C, 7128, 117.0f }, { 1, lbl_803C453C, 7192, 118.0f } },
    { { 6, lbl_803C454C, 6653, 111.0f }, { 6, lbl_803C455C, 6976, 120.0f } },
    { { 2, lbl_803C456C, 7052, 119.0f }, { 2, lbl_803C457C, 8605, 144.0f } },
    { { 8, lbl_803C458C, 7793, 127.0f }, { 8, lbl_803C459C, 8983, 150.0f } },
    { { 4, lbl_803C45AC, 7730, 130.0f }, { 4, lbl_803C45BC, 7086, 119.0f } },
    { { 3, lbl_803C45CC, 8575, 140.0f }, { 10, lbl_803C45DC, 8784, 147.0f } },
    { { 3, lbl_803C45EC, 8575, 140.0f }, { 10, lbl_803C45DC, 8784, 147.0f } },
    { { 3, lbl_803C45CC, 8575, 140.0f }, { 10, lbl_803C45DC, 8784, 147.0f } },
}};
extern const char lbl_803C46FC[15] = "ta_yi_long.bin";
extern const char lbl_803C470C[16] = "ta_dn_short.bin";
extern const char lbl_803C471C[16] = "ta_dn_long.bin";
static const CoinTimeTable kTimesFwd = {{
    { { 0, lbl_803C452C, 7443, 122.0999984741211f }, { 1, lbl_803C453C, 7714, 126.5f } },
    { { 10, lbl_803C454C, 6472, 105.9000015258789f }, { 8, lbl_803C455C, 7686, 126.0999984741211f } },
    { { 2, lbl_803C456C, 7847, 128.6999969482422f }, { 12, lbl_803C457C, 7876, 129.1999969482422f } },
    { { 8, lbl_803C458C, 7373, 120.80000305175781f }, { 9, lbl_803C459C, 8542, 140.3000030517578f } },
    { { 7, lbl_803C45AC, 7400, 121.30000305175781f }, { 3, lbl_803C45BC, 8932, 146.8000030517578f } },
    { { 11, lbl_803C45CC, 9052, 148.8000030517578f }, { 5, lbl_803C45DC, 9548, 154.10000610351562f } },
    { { 4, lbl_803C45EC, 7528, 123.4000015258789f }, { 2, lbl_803C46FC, 8170, 132.0f } },
    { { 0, lbl_803C470C, 7746, 127.0999984741211f }, { 4, lbl_803C471C, 7580, 125.30000305175781f } },
}};
extern const char lbl_803C482C[17] = "ta_mr_shortR.bin";
extern const char lbl_803C4840[16] = "ta_mr_longR.bin";
extern const char lbl_803C4850[17] = "ta_dk_shortR.bin";
extern const char lbl_803C4864[16] = "ta_dk_longR.bin";
extern const char lbl_803C4874[17] = "ta_wc_shortR.bin";
extern const char lbl_803C4888[16] = "ta_wc_longR.bin";
extern const char lbl_803C4898[17] = "ta_pc_shortR.bin";
extern const char lbl_803C48AC[16] = "ta_pc_longR.bin";
extern const char lbl_803C48BC[17] = "ta_kp_shortR.bin";
extern const char lbl_803C48D0[16] = "ta_kp_longR.bin";
extern const char lbl_803C48E0[17] = "ta_rb_shortR.bin";
extern const char lbl_803C48F4[16] = "ta_rb_longR.bin";
static const CoinTimeTable kTimesRevShort = {{
    { { 0, lbl_803C482C, 7146, 117.5f }, { 1, lbl_803C4840, 7316, 118.5f } },
    { { 6, lbl_803C4850, 6748, 112.0f }, { 6, lbl_803C4864, 7067, 119.5f } },
    { { 2, lbl_803C4874, 7143, 118.5f }, { 2, lbl_803C4888, 8652, 142.0f } },
    { { 8, lbl_803C4898, 7727, 127.0f }, { 8, lbl_803C48AC, 9021, 152.0f } },
    { { 4, lbl_803C48BC, 7880, 130.5f }, { 4, lbl_803C48D0, 7216, 118.5f } },
    { { 7, lbl_803C48E0, 8577, 138.5f }, { 5, lbl_803C48F4, 8829, 146.5f } },
    { { 7, lbl_803C48E0, 8577, 138.5f }, { 5, lbl_803C48F4, 8829, 146.5f } },
    { { 7, lbl_803C48E0, 8577, 138.5f }, { 5, lbl_803C48F4, 8829, 146.5f } },
}};
extern const char lbl_803C4A04[17] = "ta_yi_shortR.bin";
extern const char lbl_803C4A18[16] = "ta_yi_longR.bin";
extern const char lbl_803C4A28[17] = "ta_dn_shortR.bin";
extern const char lbl_803C4A3C[16] = "ta_dn_longR.bin";
static const CoinTimeTable kTimesRev = {{
    { { 6, lbl_803C482C, 7503, 123.0999984741211f }, { 1, lbl_803C4840, 7627, 125.0999984741211f } },
    { { 7, lbl_803C4850, 6487, 106.0999984741211f }, { 12, lbl_803C4864, 7626, 125.0999984741211f } },
    { { 6, lbl_803C4874, 7929, 130.10000610351562f }, { 5, lbl_803C4888, 7818, 131.3000030517578f } },
    { { 3, lbl_803C4898, 7526, 123.4000015258789f }, { 10, lbl_803C48AC, 8630, 141.8000030517578f } },
    { { 10, lbl_803C48BC, 7372, 120.80000305175781f }, { 12, lbl_803C48D0, 8836, 145.1999969482422f } },
    { { 9, lbl_803C48E0, 9018, 148.1999969482422f }, { 7, lbl_803C48F4, 9888, 162.6999969482422f } },
    { { 2, lbl_803C4A04, 7558, 123.9000015258789f }, { 4, lbl_803C4A18, 8199, 134.60000610351562f } },
    { { 11, lbl_803C4A28, 7708, 126.4000015258789f }, { 0, lbl_803C4A3C, 7687, 126.0999984741211f } },
}};
} /* extern "C" */
#include "game/types/RaceResult.h"

typedef struct RankSlot {
    unsigned char active;
} RankSlot;

typedef struct PlayerData {
    char pad00[0x48];
    unsigned char cleared[32];
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

static inline int CourseClearIndex(int course, int reverse, int isLong) {
    return isLong + course * 4 + reverse * 2;
}

static inline unsigned char IsCourseCleared(int index) {
    return g_playerData.cleared[index];
}

int CalcEarnedCoins(void) {
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
        const CoinTimeEntry *t;
        int k;
        if (g_reverseRoundFlag == 0) {
            t = &fwd.t[g_cupId - 1][g_longRoundFlag];
        } else {
            t = &rev.t[g_cupId - 1][g_longRoundFlag];
        }
        k = TimeRank(g_totalRaceTime - t->time);
        if (!g_raceEnded) {
            k = 3;
        }
        battleBonus = kTimeBonusB[k];
        if (!fn_8024F588()->retired) {
            if (IsCourseCleared(CourseClearIndex(g_cupId - 1, g_reverseRoundFlag, g_longRoundFlag)) == 1) {
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

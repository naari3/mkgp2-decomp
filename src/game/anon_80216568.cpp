/*
 * 0x80216568..0x802174F8: post-race coin reward calculation, the
 * coin/milestone table lookups and setup, and a row of text sprites.
 */

#include "game/CoinMilestone.h"

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

int fn_80216908(int i) {
    return lbl_803C449C[i];
}

const char *fn_8021691C(int i) {
    return lbl_804EDB40[i][isJapanese()];
}

int fn_80216960(int i) {
    return lbl_803C4440[i];
}

int fn_80216974(int i) {
    return lbl_803C4474[i];
}

int fn_80216988(int mileage) {
    int i;
    for (i = 0; i < 93; i++) {
        if (mileage < lbl_80679748[i].threshold) {
            return i;
        }
    }
    return -1;
}

CoinMilestone *fn_802169F4(int i) {
    if (i < 0) {
        return 0;
    }
    if (i >= 93) {
        return 0;
    }
    return &lbl_80679748[i];
}

/* Fills the milestone table (type 0..4, param = index within the type). */
void fn_80216A28(void) {
    CoinMilestone *m = lbl_80679748;

    m[0].threshold = 30;
    m[0].type = 3;
    m[0].param = 0;
    m[1].threshold = 70;
    m[1].type = 0;
    m[1].param = 0;
    m[2].threshold = 110;
    m[2].type = 1;
    m[2].param = 0;
    m[3].threshold = 150;
    m[3].type = 3;
    m[3].param = 1;
    m[4].threshold = 190;
    m[4].type = 1;
    m[4].param = 1;
    m[5].threshold = 230;
    m[5].type = 1;
    m[5].param = 2;
    m[6].threshold = 270;
    m[6].type = 3;
    m[6].param = 2;
    m[7].threshold = 310;
    m[7].type = 0;
    m[7].param = 1;
    m[8].threshold = 350;
    m[8].type = 1;
    m[8].param = 3;
    m[9].threshold = 390;
    m[9].type = 3;
    m[9].param = 3;
    m[10].threshold = 430;
    m[10].type = 1;
    m[10].param = 4;
    m[11].threshold = 470;
    m[11].type = 1;
    m[11].param = 5;
    m[12].threshold = 510;
    m[12].type = 3;
    m[12].param = 4;
    m[13].threshold = 550;
    m[13].type = 0;
    m[13].param = 2;
    m[14].threshold = 590;
    m[14].type = 1;
    m[14].param = 6;
    m[15].threshold = 630;
    m[15].type = 3;
    m[15].param = 5;
    m[16].threshold = 670;
    m[16].type = 1;
    m[16].param = 7;
    m[17].threshold = 710;
    m[17].type = 1;
    m[17].param = 8;
    m[18].threshold = 750;
    m[18].type = 3;
    m[18].param = 6;
    m[19].threshold = 790;
    m[19].type = 0;
    m[19].param = 3;
    m[20].threshold = 830;
    m[20].type = 1;
    m[20].param = 9;
    m[21].threshold = 870;
    m[21].type = 3;
    m[21].param = 7;
    m[22].threshold = 910;
    m[22].type = 1;
    m[22].param = 10;
    m[23].threshold = 950;
    m[23].type = 1;
    m[23].param = 11;
    m[24].threshold = 990;
    m[24].type = 3;
    m[24].param = 8;
    m[25].threshold = 1030;
    m[25].type = 0;
    m[25].param = 4;
    m[26].threshold = 1070;
    m[26].type = 1;
    m[26].param = 12;
    m[27].threshold = 1110;
    m[27].type = 3;
    m[27].param = 9;
    m[28].threshold = 1150;
    m[28].type = 1;
    m[28].param = 13;
    m[29].threshold = 1190;
    m[29].type = 1;
    m[29].param = 14;
    m[30].threshold = 1230;
    m[30].type = 3;
    m[30].param = 10;
    m[31].threshold = 1270;
    m[31].type = 0;
    m[31].param = 5;
    m[32].threshold = 1310;
    m[32].type = 1;
    m[32].param = 15;
    m[33].threshold = 1350;
    m[33].type = 3;
    m[33].param = 11;
    m[34].threshold = 1390;
    m[34].type = 1;
    m[34].param = 16;
    m[35].threshold = 1430;
    m[35].type = 1;
    m[35].param = 17;
    m[36].threshold = 1470;
    m[36].type = 3;
    m[36].param = 12;
    m[37].threshold = 1510;
    m[37].type = 0;
    m[37].param = 6;
    m[38].threshold = 1550;
    m[38].type = 1;
    m[38].param = 18;
    m[39].threshold = 1590;
    m[39].type = 4;
    m[39].param = 0;
    m[40].threshold = 1630;
    m[40].type = 1;
    m[40].param = 19;
    m[41].threshold = 1670;
    m[41].type = 1;
    m[41].param = 20;
    m[42].threshold = 1710;
    m[42].type = 4;
    m[42].param = 1;
    m[43].threshold = 1750;
    m[43].type = 0;
    m[43].param = 7;
    m[44].threshold = 1790;
    m[44].type = 1;
    m[44].param = 21;
    m[45].threshold = 1830;
    m[45].type = 4;
    m[45].param = 2;
    m[46].threshold = 1870;
    m[46].type = 1;
    m[46].param = 22;
    m[47].threshold = 1910;
    m[47].type = 1;
    m[47].param = 23;
    m[48].threshold = 1950;
    m[48].type = 4;
    m[48].param = 3;
    m[49].threshold = 1990;
    m[49].type = 0;
    m[49].param = 8;
    m[50].threshold = 2030;
    m[50].type = 1;
    m[50].param = 24;
    m[51].threshold = 2070;
    m[51].type = 4;
    m[51].param = 4;
    m[52].threshold = 2110;
    m[52].type = 1;
    m[52].param = 25;
    m[53].threshold = 2150;
    m[53].type = 1;
    m[53].param = 26;
    m[54].threshold = 2190;
    m[54].type = 4;
    m[54].param = 5;
    m[55].threshold = 2230;
    m[55].type = 0;
    m[55].param = 9;
    m[56].threshold = 2270;
    m[56].type = 1;
    m[56].param = 27;
    m[57].threshold = 2310;
    m[57].type = 4;
    m[57].param = 6;
    m[58].threshold = 2350;
    m[58].type = 1;
    m[58].param = 28;
    m[59].threshold = 2390;
    m[59].type = 1;
    m[59].param = 29;
    m[60].threshold = 2430;
    m[60].type = 4;
    m[60].param = 7;
    m[61].threshold = 2470;
    m[61].type = 1;
    m[61].param = 30;
    m[62].threshold = 2510;
    m[62].type = 1;
    m[62].param = 31;
    m[63].threshold = 2550;
    m[63].type = 4;
    m[63].param = 8;
    m[64].threshold = 2590;
    m[64].type = 1;
    m[64].param = 32;
    m[65].threshold = 2630;
    m[65].type = 1;
    m[65].param = 33;
    m[66].threshold = 2670;
    m[66].type = 4;
    m[66].param = 9;
    m[67].threshold = 2710;
    m[67].type = 1;
    m[67].param = 34;
    m[68].threshold = 2750;
    m[68].type = 1;
    m[68].param = 35;
    m[69].threshold = 2790;
    m[69].type = 4;
    m[69].param = 10;
    m[70].threshold = 2830;
    m[70].type = 1;
    m[70].param = 36;
    m[71].threshold = 2870;
    m[71].type = 1;
    m[71].param = 37;
    m[72].threshold = 2910;
    m[72].type = 4;
    m[72].param = 11;
    m[73].threshold = 2950;
    m[73].type = 1;
    m[73].param = 38;
    m[74].threshold = 2990;
    m[74].type = 1;
    m[74].param = 39;
    m[75].threshold = 3030;
    m[75].type = 4;
    m[75].param = 12;
    m[76].threshold = 3070;
    m[76].type = 1;
    m[76].param = 40;
    m[77].threshold = 3110;
    m[77].type = 1;
    m[77].param = 41;
    m[78].threshold = 3150;
    m[78].type = 1;
    m[78].param = 42;
    m[79].threshold = 3190;
    m[79].type = 1;
    m[79].param = 43;
    m[80].threshold = 3230;
    m[80].type = 1;
    m[80].param = 44;
    m[81].threshold = 3270;
    m[81].type = 1;
    m[81].param = 45;
    m[82].threshold = 3310;
    m[82].type = 1;
    m[82].param = 46;
    m[83].threshold = 3350;
    m[83].type = 1;
    m[83].param = 47;
    m[84].threshold = 3390;
    m[84].type = 1;
    m[84].param = 48;
    m[85].threshold = 3430;
    m[85].type = 1;
    m[85].param = 49;
    m[86].threshold = 3470;
    m[86].type = 1;
    m[86].param = 50;
    m[87].threshold = 3510;
    m[87].type = 1;
    m[87].param = 51;
    m[88].threshold = 3550;
    m[88].type = 1;
    m[88].param = 52;
    m[89].threshold = 3590;
    m[89].type = 1;
    m[89].param = 53;
    m[90].threshold = 3630;
    m[90].type = 1;
    m[90].param = 54;
    m[91].threshold = 3670;
    m[91].type = 1;
    m[91].param = 55;
    m[92].threshold = 4000;
    m[92].type = 2;
    m[92].param = 0;
}

} /* extern "C" */

/* ---- text sprite row ---- */

void *operator new(unsigned long size);
void operator delete(void *p) throw();

/* 0x230-byte text sprite (ctor TexMgr_Init). */
struct TextSprite {
    char pad000[0x8];
    float width;
    char pad00C[0x18 - 0xC];
    int visible;
    char pad01C[0x20 - 0x1C];
    unsigned int color;
    char pad024[0x22C - 0x24];
    float spacing;
    TextSprite();
};

extern "C" {
void PtrVec_InsertFill(void *v, void *pos, int n, const void *val);
void TexMgr_SetTexture(TextSprite *t, const char *fmt, ...);
void fn_801F93EC(TextSprite *t, float x, float y);
void fn_801F93D0(TextSprite *t, float sx, float sy);
void fn_801F8FCC(TextSprite *t, int mode);
void fn_801F8E90(TextSprite *t);
void *fn_801F8E58(void);
void fn_801F8A34(void *list, TextSprite *t, int layer);
extern const float lbl_806DAEC0;
extern const float lbl_806DAEC4;
extern const float lbl_806DAEC8;
extern const float lbl_806DAECC;
extern const float lbl_806DAED0;
}

template <class T> struct PtrVecData {
    int cap;
    int count;
    T *data;
    PtrVecData() : cap(0), count(0), data(0) {}
    ~PtrVecData() {
        if (data) {
            operator delete(data);
        }
    }
};

template <class T> struct PtrVecBase : PtrVecData<T> {
    PtrVecBase() {}
    ~PtrVecBase() {}
};

template <class T> struct PtrVec : PtrVecBase<T> {
    PtrVec() {}
    ~PtrVec() {}
    T *begin() { return this->data; }
    T *end() { return this->data + this->count; }
    void push_back(const T &v) { PtrVec_InsertFill(this, end(), 1, &v); }
};

static inline unsigned int PackColor(int r, int g, int b, int a) {
    return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

struct TextRow {
    PtrVec<TextSprite *> sprites;
    int layer;
    int align;
    int visible;
    unsigned char alpha;
    float x;
    float y;
    float sx;
    float sy;
    unsigned char dirty;
    ~TextRow();
};

extern "C" void fn_802170F0(TextRow *row, unsigned char alpha) {
    row->alpha = alpha;
    for (TextSprite **it = row->sprites.begin(); it != row->sprites.end(); it++) {
        (*it)->color = PackColor((*it)->color >> 24, (*it)->color >> 16, (*it)->color >> 8, row->alpha);
    }
}

extern "C" void fn_8021713C(TextRow *row) {
    float gap;
    float width = lbl_806DAEC0;
    float x = row->x;
    TextSprite **it;
    if (row->visible == 0) {
        gap = lbl_806DAEC4;
    } else {
        gap = lbl_806DAEC8;
    }
    row->dirty = 0;
    for (it = row->sprites.begin(); it != row->sprites.end(); it++) {
        (*it)->visible = row->visible;
        fn_801F8FCC(*it, 2);
        fn_801F8E90(*it);
        width += (*it)->width;
    }
    if (row->align == 1) {
        x -= lbl_806DAECC * width;
    } else if (row->align == 2) {
        x -= width;
    }
    for (it = row->sprites.begin(); it != row->sprites.end(); it++) {
        fn_801F8FCC(*it, 0);
        fn_801F93EC(*it, x, row->y);
        x += (gap - (*it)->width) + (*it)->spacing;
        fn_801F8E90(*it);
    }
}

extern "C" void fn_80217298(TextRow *row, const char *text, unsigned char r, unsigned char g, unsigned char b, float spacing) {
    row->dirty = 1;
    TextSprite *t = new TextSprite;
    TexMgr_SetTexture(t, text);
    t->color = PackColor(r, g, b, row->alpha);
    fn_801F93EC(t, row->x, row->y);
    fn_801F93D0(t, row->sx, row->sy);
    t->visible = row->visible;
    fn_801F8FCC(t, row->align);
    t->spacing = spacing;
    row->sprites.push_back(t);
}

extern "C" void fn_80217390(TextRow *row) {
    void *list = fn_801F8E58();
    for (TextSprite **it = row->sprites.begin(); it != row->sprites.end(); it++) {
        fn_801F8A34(list, *it, row->layer);
    }
}

TextRow::~TextRow() {
    for (TextSprite **it = sprites.begin(); it != sprites.end(); it++) {
        if (*it != 0) {
            delete *it;
        }
    }
}

extern "C" TextRow *fn_802174A8(TextRow *row) {
    row->sprites.cap = 0;
    row->sprites.count = 0;
    row->sprites.data = 0;
    row->layer = 6;
    row->align = 0;
    row->visible = 1;
    row->alpha = 0xFF;
    row->dirty = 0;
    row->x = row->y = lbl_806DAEC0;
    row->sx = row->sy = lbl_806DAED0;
    return row;
}

extern "C" void fn_802174F4(void) {
}

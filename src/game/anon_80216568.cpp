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
void fn_801F93D0(TextSprite *t, float sx, float sy);
void *fn_801F8E58(void);
void fn_801F8A34(void *list, TextSprite *t, int layer);
extern const float lbl_806DAEC0;
extern const float lbl_806DAEC4;
extern const float lbl_806DAEC8;
extern const float lbl_806DAECC;
extern const float lbl_806DAED0;
}

/* FlowScene.h declares these on TextManager; same object. */
static inline void SetText(TextSprite *t, const char *s) {
    TexMgr_SetTexture((TextManager *)t, s);
}
static inline void SetPos(TextSprite *t, float x, float y) {
    fn_801F93EC((TextManager *)t, x, y);
}
static inline void SetAlign(TextSprite *t, int mode) {
    fn_801F8FCC((TextManager *)t, mode);
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
        SetAlign(*it, 2);
        fn_801F8E90((TextManager *)*it);
        width += (*it)->width;
    }
    if (row->align == 1) {
        x -= lbl_806DAECC * width;
    } else if (row->align == 2) {
        x -= width;
    }
    for (it = row->sprites.begin(); it != row->sprites.end(); it++) {
        SetAlign(*it, 0);
        SetPos(*it, x, row->y);
        x += (gap - (*it)->width) + (*it)->spacing;
        fn_801F8E90((TextManager *)*it);
    }
}

extern "C" void fn_80217298(TextRow *row, const char *text, unsigned char r, unsigned char g, unsigned char b, float spacing) {
    row->dirty = 1;
    TextSprite *t = new TextSprite;
    SetText(t, text);
    t->color = PackColor(r, g, b, row->alpha);
    SetPos(t, row->x, row->y);
    fn_801F93D0(t, row->sx, row->sy);
    t->visible = row->visible;
    SetAlign(t, row->align);
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


/* ---- "insert card" prompt ---- */

struct FadeKeyBase {
    virtual ~FadeKeyBase();
    int dur;
    FadeKeyBase(int d) : dur(d) {}
};

struct FadeKey : FadeKeyBase {
    float from;
    float to;
    VHolder<FadeKey> next;
    FadeKey(int d, float f, float t) : FadeKeyBase(d), from(f), to(t) {}
    ~FadeKey();
    void Append(int dur, float to);
};

struct FadeSeq {
    virtual ~FadeSeq();
    virtual bool Done();
    virtual void Update();
    bool loop;
    FadeKey *head;
    FadeKey *cur;
    FlowFaderF *tween;
    FadeSeq(FadeKey *h, bool l);
};

extern "C" {
extern const float lbl_803C4B90[6];
extern const float lbl_806DAED8;
extern const float lbl_806DAEDC;
extern const float lbl_806DAEE0;
extern const float lbl_806DAEE4;
extern const float lbl_806DAEE8;
extern const float lbl_806DAEEC;
extern const float lbl_806DAEF0;
extern const float lbl_806DAEF4;
extern const float lbl_806DAEF8;
extern const float lbl_806DAEFC;
extern const float lbl_806DAF00;
extern const float lbl_806DAF04;
extern const float lbl_806DAF08;
extern const float lbl_806DAF0C;
extern const float lbl_806DAF10;
extern const float lbl_806DAF14;
extern const float lbl_806DAF18;
extern const float lbl_806DAF1C;
extern const float lbl_806DAF20;
extern const float lbl_806DAF24;
extern const float lbl_806DAF28;
extern int g_cupId;
unsigned char IsCardValid(void);
void PreloadResource(int res);
void fn_8011FAFC(ResCtrl *ctrl, int layer);
void fn_80121E10(ResCtrl *ctrl);
}

static inline unsigned int PackGray(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    return (r << 24) | (g << 16) | (b << 8) | a;
}

static inline int PromptRes() {
    return IsCardValid() == 1 ? 0xB1A : 0xCD7;
}

/* Card logo that zooms in, pulses and then glows (vtable lbl_804EDBB0). */
struct CardPrompt : PopupTask {
    int layer;
    int state;
    FlowFaderI *alpha;
    FlowFaderF *scale;
    CardPrompt(int layer_, int id_);
    ~CardPrompt();
    void Finish();
    void Update();
    void Draw();
    void Intro();
    void Hold();
};

void CardPrompt::Draw() {
}

void CardPrompt::Update() {
    switch (state) {
    case 0:
        Intro();
        break;
    case 1:
        Hold();
        break;
    }
}

void CardPrompt::Hold() {
    float sx = scale[0].Value();
    float sy = scale[1].Value();
    int a0 = alpha[0].Value();
    int a1 = alpha[1].Value();
    ResCtrl rc;
    rc.resId = PromptRes();
    rc.SetScaleXY(sx, sy);
    rc.Show(lbl_803C4B90[0], lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(a0 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    rc.mode = 3;
    rc.SetColor(a1 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    float gx = scale[2].Value();
    float gy = scale[3].Value();
    float off = scale[4].Value();
    unsigned char g = alpha[2].Value();
    fn_80121E10(&rc);
    rc.resId = PromptRes();
    rc.SetScaleXY(gx, gy);
    rc.tail[0] = 1;
    rc.tail[1] = 1;
    rc.tail[2] = 1;
    rc.Show(lbl_803C4B90[0] + off, lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(PackGray(g, g, g, 0xFF));
    fn_8011FAFC(&rc, layer);
    rc.Show(lbl_803C4B90[0] - off, lbl_803C4B90[1], lbl_806DAED8);
    fn_8011FAFC(&rc, layer);
    alpha[0].Step();
    alpha[1].Step();
    scale[0].Step();
    scale[1].Step();
    alpha[2].Step();
    scale[2].Step();
    scale[3].Step();
    scale[4].Step();
    if (scale[2].Done()) {
        if (scale[2].Value() == lbl_806DAEDC) {
            alpha[0].Set(0, 0, 1);
            alpha[1].Set(0, 0, 1);
            alpha[2].Set(0, 0xFF, 10);
            scale[2].Set(lbl_806DAEDC, lbl_806DAEE0, 10);
            scale[3].Set(lbl_806DAEE4, lbl_806DAEE8, 10);
            scale[4].Set(lbl_806DAEEC, lbl_806DAEF0, 10);
        } else {
            field0C = 1;
        }
    }
}

void CardPrompt::Intro() {
    float sx = scale[0].Value();
    float sy = scale[1].Value();
    int a0 = alpha[0].Value();
    int a1 = alpha[1].Value();
    ResCtrl rc;
    rc.resId = PromptRes();
    rc.SetScaleXY(sx, sy);
    rc.Show(lbl_803C4B90[0], lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(a0 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    rc.mode = 3;
    rc.SetColor(a1 | 0xFFFFFF00);
    fn_8011FAFC(&rc, layer);
    float gs = scale[2].Value();
    unsigned char g = alpha[2].Value();
    fn_80121E10(&rc);
    rc.resId = PromptRes();
    rc.SetScaleXY(gs, gs);
    rc.tail[0] = 1;
    rc.tail[1] = 1;
    rc.tail[2] = 1;
    rc.Show(lbl_803C4B90[0], lbl_803C4B90[1], lbl_806DAED8);
    rc.SetColor(PackGray(g, g, g, 0xFF));
    fn_8011FAFC(&rc, layer);
    alpha[2].Step();
    scale[2].Step();
    if (scale[2].Done()) {
        float v = scale[2].Value();
        if (lbl_806DAEF4 == v) {
            alpha[2].Set(0xFF, 0x7F, 6);
            scale[2].Set(lbl_806DAEF4, lbl_806DAEF8, 6);
        } else if (lbl_806DAEF8 == v) {
            alpha[2].Set(0x7F, 0, 5);
            scale[2].Set(lbl_806DAEF8, lbl_806DAEFC, 5);
        }
    }
    alpha[0].Step();
    alpha[1].Step();
    scale[0].Step();
    scale[1].Step();
    if (scale[0].Done()) {
        float v = scale[0].Value();
        if (lbl_806DAF00 == v) {
            scale[0].Set(lbl_806DAF00, lbl_806DAF04, 9);
            scale[1].Set(lbl_806DAF00, lbl_806DAF04, 9);
            alpha[0].Set(0, 0xFF, 9);
        } else if (lbl_806DAF04 == v) {
            scale[0].Set(lbl_806DAED8, lbl_806DAF08, 3);
            scale[1].Set(lbl_806DAED8, lbl_806DAF08, 3);
        } else if (lbl_806DAF08 == v) {
            scale[0].Set(lbl_806DAF08, lbl_806DAED8, 3);
            scale[1].Set(lbl_806DAF08, lbl_806DAED8, 3);
        } else if (lbl_806DAED8 == v) {
            scale[0].Set(lbl_806DAED8, lbl_806DAF0C, 0x4F);
            scale[1].Set(lbl_806DAED8, lbl_806DAF0C, 0x4F);
            alpha[1].Set(0xFF, 0, 14);
        } else {
            scale[0].Set(lbl_806DAED8, lbl_806DAEDC, 5);
            scale[1].Set(lbl_806DAED8, lbl_806DAEE4, 5);
            alpha[1].Set(0, 0xFF, 5);
            alpha[2].Set(0, 0, 5);
            scale[2].Set(lbl_806DAEDC, lbl_806DAEDC, 5);
            scale[3].Set(lbl_806DAEE4, lbl_806DAEE4, 5);
            scale[4].Set(lbl_806DAEEC, lbl_806DAEEC, 5);
            state = 1;
        }
    }
}

extern "C" void fn_80217E9C(void) {
    if (IsCardValid() == 1) {
        PreloadResource(0xB1A);
    } else {
        PreloadResource(0xCD7);
    }
}

CardPrompt::~CardPrompt() {
    delete[] scale;
    delete[] alpha;
}

CardPrompt::CardPrompt(int layer_, int id_) : PopupTask(id_), layer(layer_), state(0) {
    alpha = new FlowFaderI[4];
    scale = new FlowFaderF[5];
    alpha[0].Set(0, 0, 6);
    alpha[1].Set(0xFF, 0xFF, 6);
    scale[0].Set(lbl_806DAF00, lbl_806DAF00, 6);
    scale[1].Set(lbl_806DAF00, lbl_806DAF00, 6);
    alpha[2].Set(0, 0xFF, 12);
    scale[2].Set(lbl_806DAF00, lbl_806DAEF4, 12);
    alpha[3].Set(0, 0, 1);
    scale[3].Set(lbl_806DAED8, lbl_806DAED8, 1);
    scale[4].Set(lbl_806DAEEC, lbl_806DAEEC, 1);
}

/* Task list host that runs one CardLogo (vtable lbl_804EDBDC). */
struct CardLogoScene : PopupTask {
    VHolder<TaskListImpl> list;
    CardLogoScene(int layer_, int id_);
    ~CardLogoScene();
    void Finish();
    void Update();
    void Draw();
};

/* Card logo bouncing in (vtable lbl_804EDC08). */
struct CardLogo : PopupTask {
    int layer;
    VHolder<FadeKey> key1;
    VHolder<FadeSeq> seq1;
    VHolder<FadeKey> key2;
    VHolder<FadeSeq> seq2;
    VHolder<FadeKey> key3;
    VHolder<FadeSeq> seq3;
    CardLogo(int layer_, int id_);
    ~CardLogo();
    void Finish();
    void Update();
    void Draw();
};

void CardLogoScene::Draw() {
}

void CardLogoScene::Update() {
    if (list.p->entries.count <= 0) {
        field0C = 1;
    }
    list.p->Update();
    list.p->Draw();
}

extern "C" void fn_8021819C(void) {
    if (g_cupId == 14) {
        PreloadResource(0x14B6);
    } else if (IsCardValid() == 1) {
        PreloadResource(0xB1B);
    } else {
        PreloadResource(0xCD8);
    }
}

CardLogoScene::~CardLogoScene() {
}

CardLogoScene::CardLogoScene(int layer_, int id_) : PopupTask(id_), list(new TaskListImpl) {
    TaskListImpl *l = list.p;
    l->Add(new CardLogo(layer_, 0), 0);
}

void CardLogo::Draw() {
}

void CardLogo::Update() {
    ResCtrl rc;
    if (g_cupId == 14) {
        rc.resId = 0x14B6;
    } else if (IsCardValid() == 1) {
        rc.resId = 0xB1B;
    } else {
        rc.resId = 0xCD8;
    }
    rc.Show(lbl_806DAF10, seq1.p->tween->Value(), lbl_806DAED8);
    rc.SetScaleXY(seq2.p->tween->Value(), seq3.p->tween->Value());
    fn_8011FAFC(&rc, layer);
    seq1.p->Update();
    seq2.p->Update();
    seq3.p->Update();
    if (seq1.p->Done()) {
        field0C = 1;
    }
}

void CardLogo::Finish() {
    delete this;
}

CardLogo::~CardLogo() {
}

CardLogo::CardLogo(int layer_, int id_) : PopupTask(id_), layer(layer_) {
    key1.Reset(new FadeKey(11, lbl_806DAF14, lbl_806DAF18));
    key1.p->Append(8, lbl_806DAF1C);
    key1.p->Append(7, lbl_806DAF18);
    key1.p->Append(0x5A, lbl_806DAF18);
    key2.Reset(new FadeKey(11, lbl_806DAED8, lbl_806DAF20));
    key2.p->Append(8, lbl_806DAF24);
    key2.p->Append(7, lbl_806DAED8);
    key2.p->Append(0x5A, lbl_806DAED8);
    key3.Reset(new FadeKey(11, lbl_806DAED8, lbl_806DAF28));
    key3.p->Append(8, lbl_806DAEF8);
    key3.p->Append(7, lbl_806DAED8);
    key3.p->Append(0x5A, lbl_806DAED8);
    seq1.Reset(new FadeSeq(key1.p, false));
    seq2.Reset(new FadeSeq(key2.p, false));
    seq3.Reset(new FadeSeq(key3.p, false));
}

void CardPrompt::Finish() {
    delete this;
}

void CardLogoScene::Finish() {
    delete this;
}

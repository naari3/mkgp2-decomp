/*
 * Credit manager: coin/credit banner, queries and acceptor polling,
 * 0x80081184..0x8008299C.
 */

#include "game/types/CoinCounters.h"

typedef struct CreditCfg {
    unsigned char pad00[0x0C];
    unsigned int coinsSeen; /* 0x0C */
    unsigned int creditsSeen; /* 0x10 */
    unsigned char pad14[0x13];
    unsigned char bannerAltLayout; /* 0x27 */
    unsigned char pad28[0x28];
    unsigned char freeVs2P; /* 0x50 */
    unsigned char freeVs3P; /* 0x51 */
    unsigned char freeVs4P; /* 0x52 */
} CreditCfg;

typedef struct CoinStatus {
    int credits; /* 0x00 */
    int coins; /* 0x04 */
    unsigned int coinsPerCredit; /* 0x08 */
    unsigned char pad0C[0x34];
} CoinStatus;

typedef struct CoinConfig {
    unsigned char pad00[0x08];
    unsigned char mode; /* 0x08 */
    unsigned char pad09[0x02];
    unsigned char divisor; /* 0x0B */
    unsigned char perSlot[0x14]; /* 0x0C */
} CoinConfig;

extern CreditCfg lbl_80598A60;
extern int CreditMgr_bss_806D1180; /* active slot */
extern int CreditMgr_bss_806D1184; /* last queried slot */
extern unsigned char lbl_806D117C;
extern unsigned char lbl_806D117D; /* polling disabled */

unsigned int fn_80288CC8(int ch);
int fn_80288F6C(int ch, int kind);
unsigned int fn_80289040(int ch, int alt);
void fn_80289A90(CoinCounters *out);
void fn_80289B04(CoinStatus *out);
void fn_80289B7C(CoinConfig *out);
void PlayStats_IncCoinInserted(void);
void PlayStats_IncCreditAdded(void);
void PlayStats_PublishCoinCreditShadow(void);
void PlayStats_IncSinglePlayJoin(void);
void PlayStats_IncVs2PJoin(void);
void PlayStats_IncVs2PlusJoin(void);
void PlayStats_IncVs3PlusJoin(void);
void PlayStats_IncVs4PJoin(void);
void PlayStats_BeginPlaySession(void);
void SoundMgr_Play(int id);
int CreditMgr_GetCreditCount(int slot);

double fmod(double x, double y);
int isJapanese(void);

void CreditMgr_PollInsertAndPlay(unsigned char silent);
int CreditMgr_GetCoinCount(unsigned char noClamp);

#pragma exceptions on
#pragma cplusplus on

/* Sprite draw request (ResCtrl_Init / dtor_80082960). */
struct ResCtrl {
    ResCtrl();
    ~ResCtrl() {}
    int resId;
    int field4;
    int mode;
    int fieldc;
    unsigned char flag;
    unsigned char pad11[3];
    float x;
    float y;
    float z;
    float width;
    float height;
    float rot;
    float scaleX;
    float scaleY;
    unsigned int colors[4];
    unsigned char flipX;
    unsigned char flipY;
    unsigned char pad46[2];
    int tail[4];
    void Show(float px, float py, float pz) {
        flag = 1;
        x = px;
        y = py;
        z = pz;
    }
    void SetColor(unsigned int col) {
        colors[0] = col;
        colors[1] = col;
        colors[2] = col;
        colors[3] = col;
    }
};

extern "C" void fn_80121E10(ResCtrl *ctrl);
extern "C" void fn_8011FAFC(ResCtrl *ctrl, int layer);


static inline void DrawBannerSprite(int id, float x, float y, unsigned int color) {
    ResCtrl ctrl;
    fn_80121E10(&ctrl);
    ctrl.resId = id;
    ctrl.Show(x, y, 1.0f);
    ctrl.SetColor(color);
    fn_8011FAFC(&ctrl, 6);
}

/* Same body as CreditMgr_GetPlayState below. */
static inline int BannerPlayState(int alt) {
    int state = 2;
    unsigned int s;

    if (fn_80288CC8(0) != 0) {
        int k = 0;
        if (alt == 1) {
            k = 1;
        }
        s = fn_80289040(0, k);
        if (s == 0) {
            state = 0;
        }
        if (s == 1) {
            state = 1;
        }
        if (s == 2) {
            state = 2;
        }
    } else {
        state = 3;
    }
    return state;
}

/* Same body as CreditMgr_GetCoinCount(0) below. */
static inline int BannerCoinCount(void) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return 99;
    }
    fn_80289B7C(&cfg);
    if (cfg.mode > 1) {
        n = st.credits;
    } else {
        n = st.coins + st.credits * st.coinsPerCredit;
    }
    if (n > 99) {
        n = 99;
    }
    return n;
}

extern "C" void CreditMgr_DrawCoinCreditBanner(int slot, unsigned int color, int frame) {
    static unsigned char sLatched = 0;
    static unsigned char sBlinkOn = 1;
    unsigned char showIdle = 0;
    int state;

    state = BannerPlayState(slot);
    if (state < 2) {
        if (CreditMgr_GetCreditCount(slot) <= 0) {
            showIdle = 1;
        }
    } else {
        showIdle = 1;
    }

    if (frame > 1) {
        if ((color & 0xFF) < 4) {
            if (sLatched == 0) {
                sLatched = 1;
                sBlinkOn = sBlinkOn != 1;
            }
        } else {
            sLatched = 0;
        }
    } else {
        sBlinkOn = 0;
        sLatched = 0;
    }

    if (isJapanese() == 0) {
        if (showIdle) {
            if (sBlinkOn) {
                DrawBannerSprite(frame + 0x1B54, 226.0f, 345.0f, color);
                DrawBannerSprite(0x1B53, 333.0f, 345.0f, color);
            } else {
                DrawBannerSprite(0x1B4E, 320.0f, 345.0f, color);
            }
            return;
        }
        int credits = CreditMgr_GetCreditCount(slot);
        int tens = credits / 10 + 0x1B54;
        int ones = credits % 10 + 0x1B54;
        if (lbl_80598A60.bannerAltLayout == 0) {
            if (BannerCoinCount() == 0) {
                if (sBlinkOn) {
                    DrawBannerSprite(frame + 0x1B54, 226.0f, 345.0f, color);
                    DrawBannerSprite(0x1B53, 333.0f, 345.0f, color);
                } else {
                    DrawBannerSprite(0x1B4F, 215.0f, 345.0f, color);
                    if (tens != 0x1B54) {
                        DrawBannerSprite(tens, 275.0f, 345.0f, color);
                    }
                    DrawBannerSprite(ones, 291.0f, 345.0f, color);
                    DrawBannerSprite(0x1B51, 395.0f, 345.0f, color);
                }
            } else {
                DrawBannerSprite(0x1B4F, 189.0f, 345.0f, color);
                DrawBannerSprite(0x1B50, 265.0f, 345.0f, color);
                if (tens != 0x1B54) {
                    DrawBannerSprite(tens, 301.0f, 345.0f, color);
                }
                DrawBannerSprite(ones, 317.0f, 345.0f, color);
                DrawBannerSprite(0x1B51, 421.0f, 345.0f, color);
            }
        } else {
            if (BannerCoinCount() == 0) {
                if (sBlinkOn) {
                    DrawBannerSprite(frame + 0x1B54, 226.0f, 345.0f, color);
                    DrawBannerSprite(0x1B53, 333.0f, 345.0f, color);
                } else {
                    if (tens != 0x1B54) {
                        DrawBannerSprite(tens, 208.0f, 345.0f, color);
                    }
                    DrawBannerSprite(ones, 224.0f, 345.0f, color);
                    DrawBannerSprite(0x1B52, 347.0f, 345.0f, color);
                }
            } else {
                DrawBannerSprite(0x1B50, 199.0f, 345.0f, color);
                if (tens != 0x1B54) {
                    DrawBannerSprite(tens, 235.0f, 345.0f, color);
                }
                DrawBannerSprite(ones, 251.0f, 345.0f, color);
                DrawBannerSprite(0x1B52, 374.0f, 345.0f, color);
            }
        }
    } else {
        if (showIdle) {
            if (sBlinkOn) {
                DrawBannerSprite(frame + 0x3BA, 184.0f, 345.0f, color);
                DrawBannerSprite(0x3B9, 332.0f, 345.0f, color);
            } else {
                DrawBannerSprite(0x3B5, 322.0f, 346.0f, color);
            }
            return;
        }
        int jpCredits = CreditMgr_GetCreditCount(slot);
        int jpTens = jpCredits / 10 + 0x3BA;
        int jpOnes = jpCredits % 10 + 0x3BA;
        if (BannerCoinCount() == 0) {
            if (sBlinkOn) {
                DrawBannerSprite(frame + 0x3BA, 184.0f, 345.0f, color);
                DrawBannerSprite(0x3B9, 332.0f, 345.0f, color);
            } else {
                DrawBannerSprite(0x3B8, 269.0f, 346.0f, color);
                if (jpTens != 0x3BA) {
                    DrawBannerSprite(jpTens, 355.0f, 346.0f, color);
                }
                DrawBannerSprite(jpOnes, 371.0f, 346.0f, color);
                DrawBannerSprite(0x3B6, 421.0f, 346.0f, color);
            }
        } else {
            DrawBannerSprite(0x3B8, 237.0f, 346.0f, color);
            DrawBannerSprite(0x3B7, 344.0f, 346.0f, color);
            if (jpTens != 0x3BA) {
                DrawBannerSprite(jpTens, 388.0f, 346.0f, color);
            }
            DrawBannerSprite(jpOnes, 404.0f, 346.0f, color);
            DrawBannerSprite(0x3B6, 454.0f, 346.0f, color);
        }
    }
}

#pragma cplusplus reset

/* The rest of the unit is code-generated deferred: CW emits deferred
 * functions back to front, so they are written in reverse address order,
 * and the weak ResCtrl destructor lands after them as in the target. */
#pragma defer_codegen on

int CreditMgr_ResetState(void) {
    lbl_806D117C = 0;
    lbl_806D117D = 0;
    CreditMgr_bss_806D1180 = 0;
    CreditMgr_bss_806D1184 = 0;
    CreditMgr_PollInsertAndPlay(1);
    return 1;
}

void CreditMgr_PollInsertAndPlay(unsigned char silent) {
    CoinCounters cnt;
    CreditCfg *cfg;
    int event = 0;
    unsigned char sound = 1;
    int coins;
    int per;

    if (lbl_806D117D == 1) {
        return;
    }
    if (fn_80288CC8(0) == 0) {
        sound = 0;
    }
    cfg = &lbl_80598A60;
    fn_80289A90(&cnt);
    while (cfg->coinsSeen != cnt.totalCoins) {
        PlayStats_IncCoinInserted();
        event = 1;
        cfg->coinsSeen++;
    }
    while (cfg->creditsSeen != cnt.serviceCredits) {
        PlayStats_IncCreditAdded();
        event = 2;
        cfg->creditsSeen++;
    }
    if (silent) {
        return;
    }
    if (event == 1) {
        coins = CreditMgr_GetCoinCount(1);
        per = CreditMgr_GetCoinsPerCredit(CreditMgr_bss_806D1184);
        if (per == -1) {
            event = 2;
        } else if (coins % per == 0) {
            event = 2;
        }
    }
    if (sound && event > 0) {
        if (event == 1) {
            SoundMgr_Play(1);
        } else if (event == 2) {
            SoundMgr_Play(2);
        }
    }
    if (event != 0) {
        PlayStats_PublishCoinCreditShadow();
    }
}

int CreditMgr_GetPlayState(int alt) {
    int state = 2;
    unsigned int s;

    if (fn_80288CC8(0) != 0) {
        int k = 0;
        if (alt == 1) {
            k = 1;
        }
        s = fn_80289040(0, k);
        if (s == 0) {
            state = 0;
        }
        if (s == 1) {
            state = 1;
        }
        if (s == 2) {
            state = 2;
        }
    } else {
        state = 3;
    }
    return state;
}

int CreditMgr_AcceptorIsAbsent(void) {
    return fn_80288CC8(0) == 0;
}

int CreditMgr_PollAcceptor(void) {
    return fn_80288CC8(0);
}

int CreditMgr_SetActiveSlot(int slot) {
    if (slot == CreditMgr_bss_806D1180) {
        return 0;
    }
    CreditMgr_bss_806D1180 = slot;
    CreditMgr_bss_806D1184 = slot;
    return 1;
}

int CreditMgr_GetCreditCount(int slot) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;
    int count;
    int r;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return -1;
    }
    if (slot == 2 && lbl_80598A60.freeVs2P == 1) {
        return 0;
    }
    if (slot == 3 && lbl_80598A60.freeVs3P == 1) {
        return 0;
    }
    if (slot == 4 && lbl_80598A60.freeVs4P == 1) {
        return 0;
    }
    fn_80289B7C(&cfg);
    if (slot == -1) {
        slot = CreditMgr_bss_806D1180;
    }
    CreditMgr_bss_806D1184 = slot;
    if ((unsigned int)st.credits >= cfg.perSlot[slot]) {
        return 0;
    }
    n = st.credits;
    count = 0;
    while (n < cfg.perSlot[slot]) {
        n += cfg.mode;
        count++;
    }
    if (st.coinsPerCredit == 1) {
        if (fmod(count, cfg.divisor) == 0.0) {
            r = count / cfg.divisor;
        } else {
            r = count / cfg.divisor + 1;
        }
    } else {
        r = st.coinsPerCredit * count - st.coins;
    }
    if (r > 99) {
        r = 99;
    }
    return r;
}

int CreditMgr_GetCoinsPerCredit(int slot) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return -1;
    }
    if (slot == 2 && lbl_80598A60.freeVs2P == 1) {
        return 0;
    }
    if (slot == 3 && lbl_80598A60.freeVs3P == 1) {
        return 0;
    }
    if (slot == 4 && lbl_80598A60.freeVs4P == 1) {
        return 0;
    }
    fn_80289B7C(&cfg);
    if (slot == -1) {
        slot = CreditMgr_bss_806D1180;
    }
    CreditMgr_bss_806D1184 = slot;
    if (cfg.mode > 1) {
        n = cfg.perSlot[slot];
    } else {
        n = st.coinsPerCredit * cfg.perSlot[slot];
    }
    if (n > 99) {
        n = 99;
    }
    return n;
}

int CreditMgr_GetCoinCount(unsigned char noClamp) {
    CoinConfig cfg;
    CoinStatus st;
    unsigned int ok;
    int n;

    ok = fn_80288CC8(0);
    fn_80289B04(&st);
    if (ok == 0) {
        return 99;
    }
    fn_80289B7C(&cfg);
    if (cfg.mode > 1) {
        n = st.credits;
    } else {
        n = st.coins + st.credits * st.coinsPerCredit;
    }
    if (!noClamp && n > 99) {
        n = 99;
    }
    return n;
}

int CreditMgr_TryConfirmPlay(int mode) {
    int kind;

    if (mode == 0) {
        kind = 0;
    } else if (mode == 1) {
        kind = 1;
    } else if (mode == 2) {
        kind = 2;
    } else if (mode == 3) {
        kind = 3;
    } else {
        kind = 4;
    }

    if (mode == 2 && lbl_80598A60.freeVs2P == 1) {
        PlayStats_IncVs2PJoin();
        PlayStats_IncVs2PlusJoin();
        return 1;
    }
    if (mode == 3 && lbl_80598A60.freeVs3P == 1) {
        PlayStats_IncVs2PlusJoin();
        PlayStats_IncVs3PlusJoin();
        return 1;
    }
    if (mode == 4 && lbl_80598A60.freeVs4P == 1) {
        PlayStats_IncVs4PJoin();
        PlayStats_IncVs3PlusJoin();
        return 1;
    }

    if (fn_80288F6C(0, kind) == 0) {
        return 0;
    }
    if (mode == 0) {
        PlayStats_IncSinglePlayJoin();
        PlayStats_BeginPlaySession();
    }
    if (mode == 1) {
        PlayStats_IncSinglePlayJoin();
    }
    if (mode == 2) {
        PlayStats_IncVs2PJoin();
        PlayStats_IncVs2PlusJoin();
    }
    if (mode == 3) {
        PlayStats_IncVs2PlusJoin();
        PlayStats_IncVs3PlusJoin();
    }
    if (mode == 4) {
        PlayStats_IncVs4PJoin();
        PlayStats_IncVs3PlusJoin();
    }
    return 1;
}

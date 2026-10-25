/*
 * Continue (insert coin) flow scene @ 0x8024D764..0x8024E338.
 *
 * ContinueScene derives from FlowScene (vtable lbl_804EF000). CoinCounter
 * (0x10 bytes) is defined first so CW auto-inlines its methods into the
 * scene; its out-of-line copies are the functions at the end of the range.
 */

#include "game/FlowScene.h"

struct CoinWindow {
    int state;
    char pad04[0x1C];
    unsigned char visible;
    char pad21[0x47];
    CoinWindow();
};

struct CoinPrompt {
    char body[0x20];
    CoinPrompt(int a, int b, int c, int d, int e);
};

struct CoinPopupDetail {
    int pad00[4];
    int state;
    int pad14;
    int mode;
    char pad1C[0x8C - 0x1C];
    CoinPopupDetail(int a, int b, int c);
};

struct ItemMsgWnd {
    char body[0x5C];
    ItemMsgWnd();
};

struct MsgParam {
    int a;
    int b;
    const char *c;
    const char *d;
    const char *e;
    int f;
    int g;
};

struct RoundResult {
    unsigned char pad00[2];
    unsigned char pending;
    unsigned char pad03;
    int cup;
    int round;
    char pad0C[8];
    unsigned char done;
};

struct ItemDisplay;
struct RankLog;

extern "C" {
extern ItemMsgWnd *lbl_806D1A88;
extern const int lbl_806D1AB8;
extern unsigned char lbl_806D17F0;
extern unsigned char lbl_806D17F1;
extern unsigned char lbl_806D17F2;
extern int lbl_806D12C0;
extern RankLog *lbl_806D10A0;
extern int g_gameMode;
extern int g_cupId;
extern int g_ccClass;
extern int g_roundIndex;
extern char g_playerData[];
extern const char lbl_806DC020[4];
extern const char lbl_803F0848[];
extern const char lbl_803F0860[];
extern const char lbl_803EFEA0[];
extern const char *lbl_806D0970[2];
extern unsigned char lbl_80598A60[];
extern const float lbl_806DC024;
extern const float lbl_806DC028;
extern const float lbl_806DC02C;
extern const float lbl_806DC030;
extern const float lbl_806DC014;
extern const float lbl_806DC010;
extern const float lbl_806DC00C;
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
bool CreditMgr_TryConfirmPlay(int slot);
void fn_801D9F88(CoinWindow *p, int flag);
void fn_801D9A2C(CoinWindow *p);
void fn_801D9B70(CoinWindow *p, bool on);
void fn_801D8DF8(CoinWindow *p, const char *text, int line);
void fn_801D919C(CoinWindow *p);
void fn_801D92D0(CoinWindow *p, MsgParam *param);
void fn_8023CFE0(CoinPrompt *p, int flag);
void fn_8023CEB4(CoinPrompt *p);
void fn_8023CD3C(CoinPrompt *p, float a, float b);
void fn_8023CCF8(CoinPrompt *p, float a, float b);
void fn_8023CD24(CoinPrompt *p, float a, float b);
void fn_8023CCCC(CoinPrompt *p, float a, float b);
void fn_80232284(ItemMsgWnd *wnd, float t);
void fn_801618CC(CoinPopupDetail *p, int a, int b);
void fn_80161F28(CoinPopupDetail *p, int flag);
void fn_80161888(CoinPopupDetail *p);
void fn_8020A7CC(FlowFaderI *f, int a, int b, int c);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void fn_8020AAD4(ItemDisplay *d);
void fn_801FE27C(int t);
void TitleStats_ResetRaceStagingState(RankLog *log);
void RankLog_OnRoundComplete(RankLog *log);
RoundResult *fn_8024F588(void);
void DebugPrintf(const char *fmt, ...);
int sprintf(char *buf, const char *fmt, ...);
unsigned char fn_801D5C88(void *data, int cc);
unsigned char fn_801D5B8C(void *data, int cc, int cup, int mode);
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline RankLog *GetRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}

static inline bool IsNoCredit() {
    if (CreditMgr_GetPlayState(0) == 3) {
        return 1;
    }
    if (CreditMgr_GetCreditCount(1) == 0) {
        return 1;
    }
    return 0;
}

struct CoinPromptHolder {
    CoinPrompt *p;
    CoinPromptHolder(CoinPrompt *q) : p(q) {}
    ~CoinPromptHolder() throw() { fn_8023CFE0(p, 1); }
};

struct CoinCounter {
    int slot;
    int timer;
    unsigned char done;
    CoinWindow *window;
    CoinCounter(int s);
    ~CoinCounter();
    void Update();
    void Draw();
    void Show();
};

CoinCounter::CoinCounter(int s) : slot(s), timer(0), done(1), window(0) {
    InputState *in;
    window = new CoinWindow;
    window->visible = 1;
    in = GetInput();
    in->enabled = 1;
    in->held = 0;
    in->edge = 0;
}

CoinCounter::~CoinCounter() {
    if (window) {
        fn_801D9F88(window, 1);
    }
}

void CoinCounter::Show() {
    MsgParam param;
    timer = 0xB4;
    done = 0;
    param.a = -1;
    param.b = 0x1CFE;
    param.c = lbl_806DC020;
    param.d = lbl_803F0848;
    param.e = lbl_806DC020;
    param.f = 0;
    param.g = 0;
    fn_801D92D0(window, &param);
}

void CoinCounter::Draw() {
    const char *base = lbl_803EFEA0;
    char buf[0x80];
    int idx;
    int credits = CreditMgr_GetCreditCount(slot);
    fn_801D9B70(window, GetInput()->held == 1);
    if (done != 1) {
        idx = lbl_80598A60[0x27] != 0;
        if (isJapanese() == 0) {
            sprintf(buf, lbl_806D0970[idx], credits);
            fn_801D8DF8(window, buf, 1);
            fn_801D8DF8(window, base + 0x984, 2);
        } else {
            sprintf(buf, base + 0x998, credits);
            fn_801D8DF8(window, base + 0x768, 1);
            fn_801D8DF8(window, buf, 2);
        }
        if (credits <= 0 || window->state == 0) {
            fn_801D919C(window);
            done = 1;
        }
    }
}

void CoinCounter::Update() {
    fn_801D9A2C(window);
    if (done == 1) {
        return;
    }
}

struct ContinueScene : FlowScene {
    int retries;
    int coins;
    unsigned char noCredit;
    unsigned char started;
    CoinCounter *counter;
    CoinPopupDetail *detail;
    CoinPromptHolder prompt;
    ContinueScene(int id);
    ~ContinueScene();
    virtual void _key4();
    void Update();
    void Confirm();
    void Cancel();
};

ContinueScene::ContinueScene(int id)
    : FlowScene(id), retries(0), coins(CreditMgr_GetCoinCount(0, -1)), noCredit(0), started(0),
      counter(0), detail(0), prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 3)) {
    state = 0;
    timer = lbl_806D1AB8 + 1;
    detail = new CoinPopupDetail(0, 0, 7);
    fn_8020A7CC(fader.p, 0, 0x1E, 0x1E);
    state = 1;
    CreditMgr_SetActiveSlot(1);
    counter = new CoinCounter(1);
    fn_80232284(ItemMsg_Get(), (float)timer / lbl_806DC024);
    fn_8023CD3C(prompt.p, lbl_806DC028, lbl_806DC02C);
    fn_8023CCF8(prompt.p, lbl_806DC014, lbl_806DC010);
    fn_8023CD24(prompt.p, lbl_806DC030, lbl_806DC010);
    fn_8023CCCC(prompt.p, lbl_806DC00C, lbl_806DC010);
    fn_8023CEB4(prompt.p);
}

ContinueScene::~ContinueScene() {
    CreditMgr_SetActiveSlot(0);
    delete counter;
    if (detail) {
        fn_80161F28(detail, 1);
    }
}

#pragma dont_inline on
extern "C" ContinueScene *fn_8024DD04(int id) {
    return new ContinueScene(id);
}
#pragma dont_inline reset

extern "C" void fn_8024DCCC(VObject *obj) {
    delete obj;
}

void ContinueScene::Update() {
    bool noCred;
    InputState *in;
    bool active;
    int mode;
    int c;
    in = GetInput();
    mode = detail->state < 2 ? 2 : detail->mode;
    active = mode != 0;

    cursor += in->dir;
    if (cursor < 0) {
        cursor = 0;
    } else if (cursor > 1) {
        cursor = 1;
    }
    c = CreditMgr_GetCoinCount(0, -1);
    if (coins != c) {
        timer = lbl_806D1AB8 + 1;
    }
    coins = c;
    noCred = IsNoCredit();
    if (timer > 0) {
        timer--;
    }
    fn_80232284(ItemMsg_Get(), (float)timer / lbl_806DC024);
    fn_801FE27C(timer);
    if (noCred && noCredit != noCred && !started && cursor > 0) {
        fn_8020A7CC(fader.p, 0, 0xF, 0xF);
        started = 1;
        state = 3;
    }
    if (in->held == 1) {
        if (cursor == 0) {
            if (noCred) {
                if (CreditMgr_TryConfirmPlay(1)) {
                    goto confirmed;
                }
            } else if (!noCred) {
                lbl_806D17F0 = 0;
                state = 5;
                counter->Show();
                if (!active) {
                    if (retries < 1) {
                        retries++;
                        timer = lbl_806D1AB8 + 1;
                    }
                    fn_801618CC(detail, 0, 0);
                }
            }
        } else {
            lbl_806D17F0 = 0;
            state = 7;
            {
                RankLog *log = GetRankLog();
                if (log) {
                    TitleStats_ResetRaceStagingState(log);
                }
            }
        }
    }
    if (timer <= 0) {
        lbl_806D17F0 = 0;
        if (cursor == 0) {
            fn_8020A7CC(fader.p, 0, 0xF, 0xF);
            state = 4;
        } else {
            state = 7;
            fn_80161888(detail);
        }
        {
            RankLog *log = GetRankLog();
            if (log) {
                TitleStats_ResetRaceStagingState(log);
            }
        }
    }
    noCredit = noCred;
    return;

confirmed:
    fn_80161888(detail);
    lbl_806D17F0 = 1;
    {
        RoundResult *res = fn_8024F588();
        if (g_gameMode == 0) {
            int cup;
            bool clear;
            cup = g_cupId;
            clear = 0;
            DebugPrintf(lbl_803F0860, ++lbl_806D12C0, 0x244);
            if (!res->done && cup >= 1 && cup <= 8) {
                unsigned char all = fn_801D5C88(g_playerData, g_ccClass);
                int m = 3;
                if (all == 1) {
                    m = 7;
                }
                if (!fn_801D5B8C(g_playerData, g_ccClass, g_cupId, m)) {
                    clear = 1;
                }
            }
            if (clear == 1 && !lbl_806D17F2) {
                int round = g_roundIndex;
                res->pending = 1;
                res->cup = cup;
                res->round = round;
            }
        } else if (g_gameMode == 2) {
            lbl_806D17F1 = 1;
        }
    }
    state = 7;
    {
        RankLog *log = GetRankLog();
        if (log) {
            RankLog_OnRoundComplete(log);
            TitleStats_ResetRaceStagingState(log);
        }
    }
    fn_8020AAD4(ItemDisplay_GetOrCreate());
}

void ContinueScene::Cancel() {
    fn_801618CC(detail, 0, 0);
    fader.p->Step();
    if (fader.p->Done()) {
        cursor = 0;
        state = 2;
    }
}

void ContinueScene::Confirm() {
    fn_801618CC(detail, 1, 0);
    fn_80161888(detail);
    fader.p->Step();
    if (fader.p->Done()) {
        cursor = 1;
        state = 7;
    }
    fn_8020AAD4(ItemDisplay_GetOrCreate());
}

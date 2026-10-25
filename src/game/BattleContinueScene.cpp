/*
 * Network battle continue scene @ 0x8024E344..0x8024F400.
 *
 * BattleContinueScene derives from FlowScene (vtable lbl_804EF054). It
 * reuses CoinCounter from ContinueScene.cpp out of line and waits for the
 * host PCB through a SyncWaiter (ctor fn_8021BA20).
 */

#include "game/FlowScene.h"

typedef long long OSTime;
extern "C" OSTime OSGetTime(void);
#define OS_BUS_CLOCK (*(unsigned long *)0x800000F8)
#define OS_TIMER_CLOCK (OS_BUS_CLOCK / 4)
#define OSTicksToMilliseconds(ticks) ((ticks) / (OS_TIMER_CLOCK / 1000))

struct CoinPrompt {
    char body[0x20];
    CoinPrompt(int a, int b, int c, int d, int e);
};

struct CoinCounter {
    int slot;
    int timer;
    unsigned char done;
    void *window;
    CoinCounter(int s);
};

struct Sprite {
    char pad00[0xC];
    float x;
    float y;
};

struct CoinPopupDetail {
    int pad00;
    char list04[0xC];
    int state;
    int pad14;
    int mode;
    float rect[4];
    char pad2C[0x24];
    char list50[0x10];
    Sprite *center;
    char pad64[8];
    float offs[8];
    CoinPopupDetail(int a, int b, int c);
    void SetRect(float x0, float y0, float x1, float y1);
    unsigned char Closed() { return state == 6; }
};

struct ItemMsgWnd {
    char body[0x5C];
    ItemMsgWnd();
};

struct SyncWaiter {
    char pad00[0x14];
    virtual ~SyncWaiter();
    virtual void v0C();
    virtual void v10();
    virtual void Update();
    virtual void Draw();
    char pad18[0x4C - 0x18];
    SyncWaiter();
};

struct InputPlayer {
    virtual void v0();
    virtual void v1();
    virtual float v2();
    virtual void v3();
    virtual float StickRight();
    virtual float StickLeft();
    virtual unsigned char Pressed(int mask);
    virtual unsigned char Held(int mask);
    virtual unsigned int Released(int mask);
};

struct Panel {
    int kind;
    int timer;
    ResCtrl frame;
    ResCtrl labels[2];
    Panel();
};

struct PcbMode {
    char pad00[8];
    int mode;
};

struct ItemDisplay;
struct RankLog;

extern "C" {
extern ItemMsgWnd *lbl_806D1A88;
extern unsigned char lbl_806D17F0;
extern unsigned char lbl_806D17F1;
extern int lbl_806D11A8;
extern RankLog *lbl_806D10A0;
extern int g_localPcbRole;
extern const char lbl_803F0A18[];
extern const float lbl_806DC038;
extern const float lbl_806DC03C;
extern const float lbl_806DC040;
extern const float lbl_806DC044;
extern const float lbl_806DC048;
extern const float lbl_806DC04C;
extern const float lbl_806DC050;
extern const float lbl_806DC054;
extern const float lbl_806DC058;
extern const float lbl_806DC05C;
extern const float lbl_806DC060;
extern const float lbl_806DC064;
extern const float lbl_806DC068;
extern const float lbl_806DC06C;
extern const float lbl_806DC070;
extern const float lbl_806DC074;
extern const float lbl_806DC078;
extern const float lbl_806DC07C;
extern const float lbl_806DC080;
int CreditMgr_GetPlayState(int slot);
int CreditMgr_GetCreditCount(int slot);
int CreditMgr_GetCoinsPerCredit(int slot);
bool CreditMgr_TryConfirmPlay(int slot);
void fn_8023CFE0(CoinPrompt *p, int flag);
void fn_8023CEB4(CoinPrompt *p);
void fn_8023CD3C(CoinPrompt *p, float a, float b);
void fn_8023CCF8(CoinPrompt *p, float a, float b);
void fn_8023CD24(CoinPrompt *p, float a, float b);
void fn_8023CCCC(CoinPrompt *p, float a, float b);
void fn_8023CD54(CoinPrompt *p);
void fn_8023CDA8(CoinPrompt *p);
void fn_8023CFD4(CoinPrompt *p);
void fn_8023CFC8(CoinPrompt *p);
void fn_80232284(ItemMsgWnd *wnd, float t);
void fn_802321D4(ItemMsgWnd *wnd);
void fn_801618CC(CoinPopupDetail *p, int a, int b);
void fn_80161888(CoinPopupDetail *p);
void fn_80161F28(CoinPopupDetail *p, int flag);
void fn_8016039C(CoinPopupDetail *p);
void fn_80160588(CoinPopupDetail *p, int dir, int b);
void **fn_80146000(void *list, int index);
void fn_8020A7CC(FlowFaderI *f, int a, int b, int c);
ItemDisplay *ItemDisplay_GetOrCreate(void);
void fn_8020AAD4(ItemDisplay *d);
void fn_801FE27C(int t);
void fn_801FE348(void);
void TitleStats_ResetRaceStagingState(RankLog *log);
void RankLog_OnRoundComplete(RankLog *log);
void DebugPrintf(const char *fmt, ...);
void fn_8024E244(CoinCounter *p, int flag);
void fn_8024E094(CoinCounter *p);
void fn_8024E05C(CoinCounter *p);
void fn_8024E1DC(CoinCounter *p);
PcbMode *fn_801DAEC0(void);
void fn_801D1684(Panel *p);
void fn_8011FAFC(ResCtrl *r, int mode);
void SetLocalPcbRole(int role);
void SetSyncTarget(int target);
float PcbSyncTable_LookupValueByState(int state);
void SetPcbScratchFlag_806d11a4(void);
unsigned char PCBComm_ConfirmHostBattle(void);
int fn_8021B568(SyncWaiter *w);
void fn_8021B5D4(SyncWaiter *w);
void *GetInputManager(void);
InputPlayer *InputMgr_GetPlayer(void *mgr, int index);
}

static inline ItemMsgWnd *ItemMsg_Get() {
    return lbl_806D1A88 ? lbl_806D1A88 : (lbl_806D1A88 = new ItemMsgWnd);
}

static inline RankLog *GetRankLog() {
    return lbl_806D10A0 == 0 ? (RankLog *)0 : lbl_806D10A0;
}

static inline void SetPcbMode(int mode) {
    PcbMode *m = fn_801DAEC0();
    m->mode = mode;
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

static inline float ElapsedMs(OSTime start) {
    return (float)OSTicksToMilliseconds(OSGetTime() - start);
}

struct CoinPromptHolder {
    CoinPrompt *p;
    CoinPromptHolder(CoinPrompt *q) : p(q) {}
    ~CoinPromptHolder() throw() { fn_8023CFE0(p, 1); }
};

inline Panel::Panel() : kind(3), timer(0) {
    frame.mode = 2;
    frame.SetSize(lbl_806DC038, lbl_806DC03C);
    frame.Show(lbl_806DC040, lbl_806DC044, lbl_806DC048);
    labels[0].resId = 0x1B12;
    labels[0].Show(lbl_806DC040, lbl_806DC044, lbl_806DC048);
    labels[1].resId = 0x1B13;
    labels[1].Show(lbl_806DC040, lbl_806DC068, lbl_806DC048);
    frame.SetColor(0);
    labels[0].SetColor(0xFFFFFF00);
    labels[1].SetColor(0xFFFFFF00);
}

static inline void SetXY(Sprite *s, float x, float y) {
    s->x = x;
    s->y = y;
}

inline void CoinPopupDetail::SetRect(float x0, float y0, float x1, float y1) {
    rect[0] = x0;
    rect[1] = y0;
    rect[2] = x1;
    rect[3] = y1;
    SetXY((Sprite *)*fn_80146000(list04, 0), rect[0], rect[1]);
    SetXY((Sprite *)*fn_80146000(list04, 1), rect[2], rect[3]);
    fn_801F93EC((TextManager *)*fn_80146000(list50, 0), rect[0] + offs[0], rect[1] + offs[1]);
    fn_801F93EC((TextManager *)*fn_80146000(list50, 1), rect[0] + offs[2], rect[1] + offs[3]);
    fn_801F93EC((TextManager *)*fn_80146000(list50, 2), rect[2] + offs[4], rect[3] + offs[5]);
    fn_801F93EC((TextManager *)*fn_80146000(list50, 3), rect[2] + offs[6], rect[3] + offs[7]);
    SetXY(center, 0.5f * (rect[2] - rect[0]) + rect[0], 0.5f * (rect[3] - rect[1]) + rect[1]);
}

struct BattleContinueScene : FlowScene {
    float timeLeft;
    int field2C;
    int coins;
    unsigned char noCredit;
    unsigned char started;
    int field38;
    int waiting;
    unsigned char autoQuit;
    OSTime waitStart;
    unsigned char confirmed;
    SyncWaiter *waiter;
    CoinCounter *counter;
    CoinPopupDetail *detail;
    CoinPromptHolder prompt;
    VHolder<Panel> panel;
    BattleContinueScene(int id);
    ~BattleContinueScene();
    virtual void _key4();
    void Update();
    void Draw();
    void Select();
    void Confirm();
    void Cancel();
};

BattleContinueScene::BattleContinueScene(int id)
    : FlowScene(id), field2C(0), coins(CreditMgr_GetCoinCount(0, -1)), noCredit(0), started(0),
      field38(0), waiting(0), autoQuit(0), confirmed(0), waiter(0), counter(0), detail(0),
      prompt(new CoinPrompt(0x74, 0x4A, 0x1874, 0x1875, 3)), panel(new Panel) {
    SetLocalPcbRole(5);
    cursor = 0;
    state = 0;
    timeLeft = PcbSyncTable_LookupValueByState(g_localPcbRole);
    autoQuit = 1;
    detail = new CoinPopupDetail(0, 0, 8);
    detail->SetRect(lbl_806DC06C, lbl_806DC070, lbl_806DC074, lbl_806DC070);
    fn_8020A7CC(fader.p, 0, 0x1E, 0x1E);
    state = 1;
    CreditMgr_SetActiveSlot(1);
    waiter = new SyncWaiter;
    counter = new CoinCounter(1);
    fn_8023CD3C(prompt.p, lbl_806DC078, lbl_806DC07C);
    fn_8023CCF8(prompt.p, lbl_806DC054, lbl_806DC050);
    fn_8023CD24(prompt.p, lbl_806DC080, lbl_806DC050);
    fn_8023CCCC(prompt.p, lbl_806DC04C, lbl_806DC050);
    fn_8023CEB4(prompt.p);
}

BattleContinueScene::~BattleContinueScene() {
    SetPcbMode(1);
    CreditMgr_SetActiveSlot(0);
    if (detail) {
        fn_80161F28(detail, 1);
        detail = 0;
    }
    if (waiter) {
        delete waiter;
        waiter = 0;
    }
    if (counter) {
        fn_8024E244(counter, 1);
        counter = 0;
    }
}

#pragma dont_inline on
extern "C" BattleContinueScene *fn_8024EDC4(int id) {
    return new BattleContinueScene(id);
}
#pragma dont_inline reset

extern "C" void fn_8024ED8C(VObject *obj) {
    delete obj;
}

void BattleContinueScene::Select() {
    InputState *in;
    bool noCred;
    bool active;
    int mode;
    int c;

    if (confirmed == 1) {
        return;
    }
    in = GetInput();
    mode = detail->state < 2 ? 2 : detail->mode;
    active = mode != 0;
    cursor += in->dir;
    if (cursor < 0) {
        cursor = 0;
    } else if (cursor > 1) {
        cursor = 1;
    }
    if (timeLeft > lbl_806DC05C) {
        c = CreditMgr_GetCoinCount(0, -1);
        if (coins != c) {
            if (coins < CreditMgr_GetCoinsPerCredit(-1)) {
                lbl_806D11A8 = 1;
            }
            if (coins == CreditMgr_GetCoinsPerCredit(-1) - 1) {
                fn_80160588(detail, 0, 0);
                fn_801618CC(detail, 0, 0);
                CreditMgr_TryConfirmPlay(1);
                goto confirmed_;
            }
        }
    }
    coins = CreditMgr_GetCoinCount(0, -1);
    noCred = IsNoCredit();
    timeLeft = PcbSyncTable_LookupValueByState(g_localPcbRole);
    fn_801FE27C((int)timeLeft);
    fn_80232284(ItemMsg_Get(), timeLeft);
    if (timeLeft > lbl_806DC05C && noCred && noCredit != noCred && !started && cursor > 0) {
        fn_8020A7CC(fader.p, 0, 0xF, 0xF);
        started = 1;
        state = 4;
    }
    if (in->held == 1) {
        if (cursor == 0) {
            if (noCred) {
                if (timeLeft > lbl_806DC05C) {
                    if (CreditMgr_TryConfirmPlay(1)) {
                        goto confirmed_;
                    }
                }
            } else if (!noCred) {
                lbl_806D17F0 = 0;
                fn_8024E1DC(counter);
                state = 6;
                if (!active) {
                    fn_801618CC(detail, 0, 0);
                }
            }
        } else {
            lbl_806D17F0 = 0;
            SetLocalPcbRole(0);
            SetSyncTarget(0x34);
            state = 9;
            cursor = 1;
            {
                RankLog *log = GetRankLog();
                if (log) {
                    TitleStats_ResetRaceStagingState(log);
                }
            }
        }
    }
    if (autoQuit && timeLeft <= lbl_806DC064) {
        cursor = 1;
        lbl_806D17F0 = 0;
        SetLocalPcbRole(0);
        SetSyncTarget(0x34);
        fn_801618CC(detail, 1, 0);
        fn_80160588(detail, 0, 0);
        fn_80161888(detail);
        state = 9;
        {
            RankLog *log = GetRankLog();
            if (log) {
                TitleStats_ResetRaceStagingState(log);
            }
        }
    }
    noCredit = noCred;
    return;

confirmed_:
    cursor = 0;
    fn_801618CC(detail, 0, 1);
    DebugPrintf(lbl_803F0A18);
    {
        Panel *p = panel.p;
        if (p->kind == 3) {
            p->kind = 0;
            p->timer = 0;
        }
    }
    confirmed = 1;
    state = 3;
    SetSyncTarget(0x32);
}

#pragma auto_inline off
void BattleContinueScene::Cancel() {
    fn_801618CC(detail, 0, 0);
    fader.p->Step();
    if (fader.p->Done()) {
        cursor = 0;
        state = 2;
    }
}

void BattleContinueScene::Confirm() {
    fn_801618CC(detail, 1, 0);
    fn_80161888(detail);
    SetLocalPcbRole(0);
    fader.p->Step();
    if (fader.p->Done()) {
        cursor = 1;
        state = 9;
    }
}

#pragma auto_inline reset

void BattleContinueScene::Update() {
    InputState *in = GetInput();
    if (in->held == 1) {
        SetPcbMode(4);
    } else {
        SetPcbMode(1);
    }
    switch (state) {
    case 1:
        fader.p->Step();
        if (fader.p->Done()) {
            coins = CreditMgr_GetCoinCount(0, -1);
            noCredit = IsNoCredit();
            state = 2;
            fn_8023CFD4(prompt.p);
        }
        break;
    case 2:
        Select();
        break;
    case 3:
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Released(0x2000)) {
            SetPcbScratchFlag_806d11a4();
        }
        timeLeft = PcbSyncTable_LookupValueByState(g_localPcbRole);
        fn_801FE27C((int)timeLeft);
        fn_80232284(ItemMsg_Get(), timeLeft);
        if (fn_8021B568(waiter) == 0 && waiting == 0) {
            waiting = 1;
            field38 = 0;
            waitStart = OSGetTime();
            fn_8021B5D4(waiter);
        }
        if (waiting > 0) {
            if ((float)OSTicksToMilliseconds(OSGetTime() - waitStart) / lbl_806DC058 >= lbl_806DC05C) {
                if (PCBComm_ConfirmHostBattle() == 1) {
                    Panel *p = panel.p;
                    if (p->kind == 0 || p->kind == 1) {
                        p->kind = 2;
                        p->timer = 0;
                    }
                    lbl_806D17F0 = 1;
                    fn_801FE348();
                    lbl_806D17F1 = g_localPcbRole != 0;
                    state = 8;
                    waitStart = OSGetTime();
                    {
                        RankLog *log = GetRankLog();
                        if (log) {
                            RankLog_OnRoundComplete(log);
                            TitleStats_ResetRaceStagingState(log);
                        }
                    }
                }
            }
        }
        break;
    case 4:
        Cancel();
        break;
    case 5:
        Confirm();
        break;
    case 6:
        fn_8024E094(counter);
        if (counter->done == 1) {
            state = 2;
        }
        break;
    case 8:
        if ((float)OSTicksToMilliseconds(OSGetTime() - waitStart) / lbl_806DC058 >= lbl_806DC060) {
            fn_8021B5D4(waiter);
            state = 9;
        }
        break;
    case 9:
        fn_80161888(detail);
        fn_8023CFC8(prompt.p);
        fn_802321D4(ItemMsg_Get());
        fn_8020AAD4(ItemDisplay_GetOrCreate());
        state = 10;
        break;
    case -1:
    case 0:
    case 7:
        break;
    case 10:
        if (list.p->entries.count <= 0 && detail->Closed() == 1) {
            field0C = 1;
            state = -1;
        }
        break;
    }
    waiter->Update();
    list.p->Update();
    fn_8023CDA8(prompt.p);
    if (detail) {
        if (state == 6) {
            fn_80160588(detail, 0, 0);
        } else {
            fn_80160588(detail, in->dir, 0);
        }
    }
    fn_8024E094(counter);
    fn_801D1684(panel.p);
}

void BattleContinueScene::Draw() {
    waiter->Draw();
    list.p->Draw();
    fn_8023CD54(prompt.p);
    if (detail) {
        fn_8016039C(detail);
    }
    if (counter) {
        fn_8024E05C(counter);
    }
    {
        Panel *p = panel.p;
        if (p->kind != 3) {
            fn_8011FAFC(&p->frame, 6);
            fn_8011FAFC(&p->labels[0], 6);
            fn_8011FAFC(&p->labels[1], 6);
        }
    }
}

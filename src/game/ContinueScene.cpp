#include "game/ContinueScene_private.h"
/* --- owned .rodata 0x803F0860..0x803F08B4 (tools/own_data.py) --- */
#pragma force_active on
extern "C" const char ContinueScene_rodata_803F0860[84] = { 71, 80, 67, 111, 110, 116, 105, 110, 117, 101, 32, 58, 32, 37, 100, 44, 32, 105, 109, 97, 109, 117, 114, 97, 47, 82, 115, 67, 111, 110, 116, 105, 110, 117, 101, 48, 48, 46, 99, 112, 112, 32, 45, 32, 37, 100, 10, 0, 99, 108, 89, 84, 97, 115, 107, 77, 97, 110, 97, 103, 101, 114, 60, 99, 108, 77, 110, 84, 97, 115, 107, 73, 110, 116, 101, 114, 102, 97, 99, 101, 62, 0, 0, 0 };
#pragma force_active reset
extern "C" 
inline CoinCounter::CoinCounter(int s) : slot(s), timer(0), done(1), window(0) {
    InputState *in;
    window = new CoinWindow;
    window->visible = 1;
    in = GetInput();
    in->enabled = 1;
    in->held = 0;
    in->edge = 0;
}

inline CoinCounter::~CoinCounter() {
    if (window) {
        fn_801D9F88(window, 1);
    }
}

inline void CoinCounter::Show() {
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

void ContinueScene::Cancel() {
    fn_801618CC(detail, 0, 0);
    fader.p->Step();
    if (fader.p->Done()) {
        cursor = 0;
        state = 2;
    }
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
            DebugPrintf(ContinueScene_rodata_803F0860, ++lbl_806D12C0, 0x244);
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

extern "C" void fn_8024DCCC(VObject *obj) {
    delete obj;
}

#pragma dont_inline on
extern "C" ContinueScene *fn_8024DD04(int id) {
    return new ContinueScene(id);
}
#pragma dont_inline reset

ContinueScene::~ContinueScene() {
    CreditMgr_SetActiveSlot(0);
    delete counter;
    if (detail) {
        fn_80161F28(detail, 1);
    }
}

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

void CoinCounter::Update() {
    fn_801D9A2C(window);
    if (done == 1) {
        return;
    }
}

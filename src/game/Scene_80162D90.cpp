#include "game/Scene_80162D90Private.h"

static inline unsigned char HasNoCredits(const CreditPanel162 *panel) {
    return panel->credits <= 0;
}

int CreditPanel162::Tick() {
    CreditPanel162 *s = this;
    int oldCredits = s->credits;
    s->credits = CreditMgr_GetCreditCount(1);
    if (oldCredits != s->credits) {
        s->changed = 1;
        fn_80147574(s, 1200);
    }
    unsigned char noCredits = HasNoCredits(s);
    int state = 0;
    unsigned char pressed = 0;
    if (InputState()) state = InputState()->state;
    if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x100) ||
        InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x2000)) pressed = 1;
    if (!fn_80147530(s)) {
        fn_80147470(s, 1);
    } else {
        if (fn_80147468(s) == 0) {
            if (s->credits > 0) {
                if (pressed) {
                    SetRumbleMode(0, 1, 1);
                    fn_801474FC(s, 0);
                    if (!s->confirmed) {
                        s->confirmed = 1;
                        fn_80147574(s, 1200);
                    }
                }
            } else if (pressed) {
                SetRumbleMode(0, 4, 10);
                goto finish;
            }
            if (state == 1) fn_80147470(s, 1);
        } else {
            if (pressed) {
                SetRumbleMode(0, 4, 10);
                goto finish;
            }
            if (state == -1) {
                fn_80147470(s, 0);
            } else if (noCredits && noCredits != s->noCredits && !s->expired) {
                s->expired = 1;
                fn_80147470(s, 0);
            }
        }
        s->noCredits = noCredits;
        return 0;
    }
finish:
    if (fn_80147468(s) == 0) {
        if (s->credits <= 0 && CreditMgr_TryConfirmPlay(1)) {
            lbl_806D17F0 = 1;
            void *t = TitleTracker();
            if (t) {
                TitleStats_ResetRaceStagingState(t);
                RankLog_OnRoundComplete(t);
            }
        } else {
            fn_80147470(s, 1);
        }
    }
    return 1;
}

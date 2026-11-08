#include "game/FlowCardCheckPages_private.h"

static inline void ClearPage(clFlowCCInterface **pages, const int &index) {
    clFlowCCInterface *page = pages[index];
    if (page != 0) {
        delete page;
        pages[index] = 0;
    }
}

int clFlowCardCheck::Update() {
    InputState *in = input_state();
    switch (state) {
    case 0:
        state = 1;
        break;
    case 1:
        pages[0] = new clFlowCCDate();
        pages[page]->Open(18);
        state = 2;
        fn_801699D8(0, 1);
        fn_801699D8(1, 1);
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Stick() >= lbl_806DB7A0) {
            stickLatch = 1;
        }
        break;
    case 2:
        if (in->cardState == 3) {
            SetRumbleMode(1, 1, 1);
            fn_801FE390();
            if (prevPage < 0) {
                prevPage = page;
                pages[page]->Close(18);
                if (++page >= 8) {
                    page = 0;
                }
                if (pages[page] == 0) {
                    switch (page) {
                    case 0:
                        pages[page] = new clFlowCCDate();
                        break;
                    case 1:
                        pages[page] = new clFlowCCItem();
                        break;
                    case 2:
                        pages[page] = new clFlowCCCharaItem(0);
                        break;
                    case 3:
                        pages[page] = new clFlowCCCharaItem(1);
                        break;
                    case 4:
                        pages[page] = new clFlowCCGP(0);
                        break;
                    case 5:
                        pages[page] = new clFlowCCGP(1);
                        break;
                    case 6:
                        pages[page] = new clFlowCCGP(2);
                        break;
                    case 7:
                        pages[page] = new clFlowCCBattle();
                        break;
                    }
                }
                pages[page]->Open(18);
                timer = 18;
            }
        }
        if (prevPage >= 0) {
            clFlowCCInterface *p = pages[prevPage];
            if (p != 0) {
                if (p->active == 0) {
                    ClearPage(pages, prevPage);
                    prevPage = -1;
                }
            } else {
                prevPage = -1;
            }
        }
        {
            void *mgr = GetInputManager();
            if (InputMgr_GetPlayer(mgr, 0)->Stick() < lbl_806DB7A0) {
                stickLatch = 0;
            }
            if (InputMgr_GetPlayer(mgr, 0)->Held(0x2000) ||
                (InputMgr_GetPlayer(mgr, 0)->Stick() >= lbl_806DB7A0 && stickLatch == 0) || bright <= 0.0f) {
                bright = -1.0f;
                fn_801FE348();
                state = 3;
                fn_801699D8(0, 0);
                fn_801699D8(1, 0);
            }
        }
        break;
    case 3:
        state = 0;
        result = 11;
        break;
    }
    for (int i = 0; i < 8; i++) {
        clFlowCCInterface *p = pages[i];
        if (p != 0 && p->active == 1) {
            p->Update();
        }
    }
    fn_8023CDA8(indicator);
    bright -= lbl_806DB7AC;
    if (bright < 0.0f) {
        bright = -1.0f;
    }
    SetScreenBrightness(bright);
    fn_801B7EF8();
    return result;
}

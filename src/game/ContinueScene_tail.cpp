#include "game/ContinueScene_private.h"

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

CoinCounter::~CoinCounter() {
    if (window) {
        fn_801D9F88(window, 1);
    }
}

CoinCounter::CoinCounter(int s) : slot(s), timer(0), done(1), window(0) {
    InputState *in;
    window = new CoinWindow;
    window->visible = 1;
    in = GetInput();
    in->enabled = 1;
    in->held = 0;
    in->edge = 0;
}

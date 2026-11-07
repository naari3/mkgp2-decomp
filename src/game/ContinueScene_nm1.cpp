#include "game/ContinueScene_private.h"

void CoinCounter::Draw() {
    const char *base = lbl_803EFEA0;
    char buf[0x80];
    int idx;
    int credits = CreditMgr_GetCreditCount(slot);
    fn_801D9B70(window, GetInput()->held == 1);
    if (done != 1) {
        idx = lbl_80598A60[0x27] ? 1 : 0;
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

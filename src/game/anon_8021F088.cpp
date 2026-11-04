#include "game/anon_8021F088_private.h"

#pragma auto_inline off
void clCSSceneCoinMilage::StateNext() {
    if (timer == 1) {
        int i = fn_80216988(milage);
        if (i >= 0) {
            unsigned char found = 0;
            MilageItem *e;
            for (;;) {
                e = fn_802169F4(i);
                if (e == 0) {
                    break;
                }
                if (e->type != 1) {
                    found = 1;
                    break;
                }
                if (fn_80209338(g_characterId) > 0) {
                    found = 1;
                    break;
                }
                i++;
            }
            if (found == 1) {
                DebugPrintf(lbl_803C6C2C, e->coins - milage, e->coins, milage);
                next->Start(e->coins - milage);
            }
        }
    }
    if (next->state == 0) {
        int s = 7;
        timer = 0;
        wait = 0;
        if (g_gameMode == 2) {
            s = 6;
        }
        state = s;
    }
}
#pragma auto_inline reset

void NextWnd::Start(int n) {
    if (n > 0) {
        value = n;
        timer = 0;
        state = 1;
        for (int i = 0; i < 3; i++) {
            fn_80121E10(&digits[i]);
            digits[i].SetColor(0xFFFFFF00);
        }
        digits[0].resId = value % 10 + 0x1931;
        digits[1].resId = value / 10 % 10 + 0x1931;
        digits[2].resId = value / 100 % 10 + 0x1931;
        if (value < 100) {
            if (isJapanese() == 0) {
                digits[0].Show(lbl_806DB19C, lbl_806DB1A0, lbl_806DB194);
                digits[1].Show(lbl_806DB1A4, lbl_806DB1A0, lbl_806DB194);
            } else {
                digits[0].Show(lbl_806DB1A8, lbl_806DB1AC, lbl_806DB194);
                digits[1].Show(lbl_806DB1B0, lbl_806DB1AC, lbl_806DB194);
            }
            fn_80121E10(&digits[2]);
            digits[2].resId = 0x1ECD;
        } else if (isJapanese() == 0) {
            digits[0].Show(lbl_806DB1B4, lbl_806DB1A0, lbl_806DB194);
            digits[1].Show(lbl_806DB1B8, lbl_806DB1A0, lbl_806DB194);
            digits[2].Show(lbl_806DB1BC, lbl_806DB1A0, lbl_806DB194);
        } else {
            digits[0].Show(lbl_806DB1C0, lbl_806DB1AC, lbl_806DB194);
            digits[1].Show(lbl_806DB1C4, lbl_806DB1AC, lbl_806DB194);
            digits[2].Show(lbl_806DB1C8, lbl_806DB1AC, lbl_806DB194);
        }
    }
}

#pragma auto_inline off
void clCSSceneCoinMilage::StateItems() {
    if (wnd->state == 0) {
        unsigned char end = 0;
        if (itemIndex != fn_80216988(milage)) {
            MilageItem *e = fn_802169F4(itemIndex);
            if (e != 0) {
                wnd->Setup(e->coins, e);
                itemIndex++;
                SoundMgr_Play(0x22);
            } else {
                DebugPrintf(lbl_803C6C58);
                end = 1;
            }
        } else {
            DebugPrintf(lbl_803C6C70);
            end = 1;
        }
        if (end == 1) {
            timer = 0;
            wait = 0;
            if (fn_802169F4(fn_80216988(milage)) == 0) {
                int s = 7;
                if (g_gameMode == 2) {
                    s = 6;
                }
                state = s;
            } else {
                state = 5;
            }
        }
    }
}
#pragma auto_inline reset

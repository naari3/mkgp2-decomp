#define COIN_RESCTRL_IMPLICIT_PADDING
#include "game/anon_8021F088_private.h"

void clGetCoinSum::Layout() {
    float px = tracks[3].value;
    float py = tracks[4].value;
    int n = 1;
    Int5 d = lbl_803C6B70;
    d.v[0] = value % 10;
    d.v[1] = value / 10 % 10;
    d.v[2] = value / 100 % 10;
    d.v[3] = value / 1000 % 10;
    d.v[4] = value / 10000 % 10;
    if (d.v[4] != 0) {
        n = 5;
    } else if (d.v[3] != 0) {
        n = 4;
    } else if (d.v[2] != 0) {
        n = 3;
    } else if (d.v[1] != 0) {
        n = 2;
    }
    float x = lbl_806DB200 + px;
    float y = lbl_806DB314 + py;
    for (int i = 0; i < 5; i++) {
        fn_80121E10(&digits[i]);
        digits[i].Show(x, y, lbl_806DB194);
        digits[i].scaleX = lbl_806DB318;
        digits[i].scaleY = lbl_806DB318;
        digits[i].resId = i >= n ? 0x1ECD : d.v[i] + 0x14BA;
        x -= lbl_806DB31C;
    }
    if (flash == 1) {
        int a = 0;
        if (timer <= 20) {
            a = 0;
        } else if (timer <= 40) {
            a = (int)(lbl_806DB260 * ((timer - 20) / lbl_806DB288));
        } else if (timer <= 60) {
            a = (int)(lbl_806DB260 * (lbl_806DB194 - (timer - 40) / lbl_806DB288));
        }
        if (a > 0xFF) {
            a = 0xFF;
        }
        for (int i = 0; i < 5; i++) {
            glow[i] = digits[i];
            glow[i].mode = 3;
            glow[i].SetColor(PackColor(0xFF, 0xFF, 0xFF, a));
        }
        if (timer >= 110) {
            timer = 0;
            flash = 0;
            done = 1;
        }
    }
}

#include "game/anon_8021F088_private.h"

void ItemWnd::Open() {
    switch (sub) {
    case 0: {
        int a = (int)(lbl_806DB284 * (timer / lbl_806DB250));
        fade.SetColor((unsigned char)a);
        if (timer >= 10) {
            sub++;
            timer = 0;
            spr[0]->alpha = lbl_806DB194;
            spr[0]->sx = lbl_806DB190;
            spr[0]->sy = lbl_806DB190;
        }
        return;
    }
    case 1: {
        float f = timer / lbl_806DB294;
        float c = lbl_806DB194 - (float)cos(lbl_806DB1D8 * (lbl_806DB28C * f));
        c = c * c;
        spr[0]->sx = c;
        spr[0]->sy = c;
        spr[0]->alpha = f * f;
        if (timer >= 15) {
            sub = 0;
            timer = 0;
            state = 2;
            if (spr[2] != 0) {
                delete spr[2];
                spr[2] = 0;
            }
            spr[2] = new Sprite(0x14A, 1, 0);
            spr[2]->SetPos(lbl_806DB1E8, lbl_806DB2AC);
            spr[2]->layer = 5;
            spr[2]->alpha = lbl_806DB190;
            spr[2]->SetAnimParam(0x1931, 0x1ECD);
            spr[2]->SetAnimParam(0x1932, 0x1ECD);
            spr[2]->SetAnimParam(0x1933, 0x1ECD);
            spr[2]->SetAnimParam(0x1934, 0x1ECD);
            int d[4];
            struct Digits4 { int v[4]; };
            *(struct Digits4 *)d = *(const struct Digits4 *)lbl_803C6BC4;
            d[0] = coins % 10;
            d[1] = coins / 10 % 10;
            d[2] = coins / 100 % 10;
            d[3] = coins / 1000 % 10;
            if (d[3] == 0) {
                d[3] = -1;
            }
            if (d[2] == 0 && d[3] < 0) {
                d[2] = -1;
            }
            int row = 0;
            if (isJapanese() == 1) {
                if (d[3] < 0) {
                    row = 1;
                } else {
                    row = 2;
                }
            }
            const float *xs = lbl_803C6BD4[row];
            for (int i = 0; i < 4; i++) {
                fn_80121E10(&digits[i]);
                if (d[i] < 0) {
                    digits[i].resId = 0x1ECD;
                } else {
                    digits[i].resId = (short)(d[i] + 0x1931);
                }
                digits[i].Show(xs[i], lbl_806DB2B0, lbl_806DB194);
                digits[i].SetColor(0xFFFFFF00);
            }
        }
        break;
    }
    }
}

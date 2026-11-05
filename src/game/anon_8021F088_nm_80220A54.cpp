#define COIN_RESCTRL_IMPLICIT_PADDING
#include "game/anon_8021F088_private.h"


void clGetCoinLine::Layout(float y) {
    int a = (int)(lbl_806DB24C * ((timer - 70) / lbl_806DB250));
    if (timer < 70) {
        a = 0;
    }
    for (int i = 0; i < 3; i++) {
        fn_80121E10(&digits[i]);
        digits[i].scaleX = lbl_806DB1F0;
        digits[i].scaleY = lbl_806DB1F0;
        digits[i].SetColor(PackColor(0xFF, 0xFF, 0xFF, a));
    }
    int h = value / 100 % 10;
    digits[2].resId = h != 0 ? (short)(h + 0x14BA) : 0x1ECD;
    digits[2].Show(lbl_806DB254, y - lbl_806DB194, lbl_806DB194);
    int t = value / 10 % 10;
    unsigned char blank = 0;
    if (t == 0 && h == 0) {
        blank = 1;
    }
    digits[1].resId = !blank ? (short)(t + 0x14BA) : 0x1ECD;
    digits[1].Show(lbl_806DB258, y - lbl_806DB194, lbl_806DB194);
    digits[0].resId = (short)(value % 10 + 0x14BA);
    digits[0].Show(lbl_806DB1FC, y - lbl_806DB194, lbl_806DB194);
    if (flash == 1) {
        if (flashTimer < 12) {
            a = 0;
        } else if (flashTimer <= 19) {
            float f = (flashTimer - 12) / lbl_806DB25C;
            int v = (int)(lbl_806DB260 * f);
            if (v > 0xFF) {
                v = 0xFF;
            }
            a = v & 255;
            float s = lbl_806DB20C * f + lbl_806DB1F0;
            digits[0].scaleX = s;
            digits[0].scaleY = s;
            digits[1].scaleX = s;
            digits[1].scaleY = s;
            digits[2].scaleX = s;
            digits[2].scaleY = s;
        } else if (flashTimer <= 23) {
            a = 0xFF;
            digits[0].scaleX = lbl_806DB264;
            digits[0].scaleY = lbl_806DB264;
            digits[1].scaleX = lbl_806DB264;
            digits[1].scaleY = lbl_806DB264;
            digits[2].scaleX = lbl_806DB264;
            digits[2].scaleY = lbl_806DB264;
        } else if (flashTimer <= 30) {
            float f = lbl_806DB194 - (flashTimer - 23) / lbl_806DB25C;
            int v = (int)(lbl_806DB260 * f);
            if (v > 0xFF) {
                v = 0xFF;
            }
            a = v & 255;
            float s = lbl_806DB1F8 * f + lbl_806DB1F0;
            digits[0].scaleX = s;
            digits[0].scaleY = s;
            digits[1].scaleX = s;
            digits[1].scaleY = s;
            digits[2].scaleX = s;
            digits[2].scaleY = s;
        }
        if (flashTimer == 19) {
            value += add;
            add = 0;
        }
        if (flashTimer >= 30) {
            flash = 0;
        }
        for (int i = 0; i < 3; i++) {
            glow[i] = digits[i];
            glow[i].mode = 3;
            glow[i].SetColor(PackColor(0xFF, 0xFF, 0xFF, a));
        }
    }
}

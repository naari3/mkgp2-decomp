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
            a = (unsigned char)v;
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
            a = (unsigned char)v;
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

#pragma auto_inline off
void clCSSceneCoinMilage::StateCoins() {
    unsigned char end = 0;
    if (timer == 1) {
        SoundMgr_Play(0x72);
    }
    int landed = 0;
    for (int i = 0; i < numCoins; i++) {
        Coin *c = &coins[i];
        if (c->y >= lbl_806DB224) {
            landed++;
        } else {
            c->x += c->vx;
            c->y += c->vy;
            c->rot += c->vrot;
            c->vy += lbl_806DB1F0;
            if (c->rot > lbl_806DB270) {
                c->rot -= lbl_806DB270;
            }
            if (c->rot < lbl_806DB190) {
                c->rot += lbl_806DB270;
            }
            if (c->bounced == 0 && c->y >= lbl_806DB274) {
                c->bounced = 1;
                c->vy = lbl_806DB20C * -c->vy;
                c->vx = rand() % 2 ? lbl_806DB278 : lbl_806DB27C;
            }
        }
    }
    if (--wait < 0) {
        if (numCoins < 30) {
            numCoins++;
            wait = rand() % 2 + 2;
        } else {
            wait = 0;
            if (landed == 30) {
                end = 1;
            }
        }
    }
    if (GetInput()->held == 1) {
        end = 1;
    }
    if (end == 1) {
        fn_80192688(0x72, 1);
        timer = 0;
        sub = 0;
        wait = 0;
        state = 2;
        fn_8013D634(model, lbl_806DB190, lbl_806DB190, lbl_806DB190);
        fn_8013D59C(model, lbl_806DB190, lbl_806DB190, lbl_806DB190);
    }
}
#pragma auto_inline reset

void clCSSceneCoinMilage::Draw() {
    fn_8011FAB8();
    fn_801A1280();
    if (state == 4) {
        wnd->Draw();
    }
    if (state == 5) {
        next->Draw();
    }
    for (FadeObj **it = nodes.begin(); it != nodes.end(); it++) {
        (*it)->Render();
    }
    if (state == 1) {
        for (int i = 0; i < numCoins; i++) {
            fn_8013D634(model, lbl_806DB190, lbl_806DB190, coins[i].z);
            fn_8013D660(model, coins[i].x, coins[i].y);
            fn_8013D59C(model, lbl_806DB190, lbl_806DB1D8 * coins[i].rot, lbl_806DB190);
            model->Draw();
        }
    }
}

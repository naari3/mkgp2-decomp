#include "game/anon_8021F088_private.h"

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
            c->vy += 0.8f;
            if (c->rot > 360.0f) {
                c->rot -= 360.0f;
            }
            if (c->rot < lbl_806DB190) {
                c->rot += 360.0f;
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


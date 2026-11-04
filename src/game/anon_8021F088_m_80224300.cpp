#define COIN_LINE_DRAW_OUTLINE
#include "game/anon_8021F088_private.h"

void clGetCoinLine::Draw() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        spr.p->SetPos(x, y);
        fn_801A0004(spr.p);
        fn_8011F994(1);
        if (model != 0) {
            fn_8013D660(model, x - lbl_806DB2E0, lbl_806DB2E4 + y);
            fn_8013D634(model, lbl_806DB190, lbl_806DB190, lbl_806DB248);
            fn_8013D59C(model, lbl_806DB190, lbl_806DB1D8 * rot, lbl_806DB190);
            fn_8013D608(model, lbl_806DB2E8, lbl_806DB2E8, lbl_806DB2E8);
            model->Draw();
        }
        Layout(y);
        for (int i = 0; i < 3; i++) {
            fn_8011FAFC(&digits[i], 1);
        }
        if (flash) {
            for (int i = 0; i < 3; i++) {
                fn_8011FAFC(&glow[i], 1);
            }
        }
        void *mgr = fn_801F8E58();
        fn_801F93EC(&text, x - lbl_806DB2EC, y - lbl_806DB2F0);
        fn_801F8A34(mgr, &text, 1);
    }


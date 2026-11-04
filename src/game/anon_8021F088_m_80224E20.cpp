#include "game/anon_8021F088_private.h"

void clGetCoinSum::Draw() {
        fn_801A0004(spr.p);
        if (isJapanese() == 0) {
            fn_8011FAFC(&r[0], 1);
        } else {
            fn_801F8A34(fn_801F8E58(), &text, 1);
        }
        fn_8011FAFC(&r[1], 1);
        for (int i = 0; i < 5; i++) {
            fn_8011FAFC(&digits[i], 1);
            fn_8011FAFC(&glow[i], 1);
        }
    }

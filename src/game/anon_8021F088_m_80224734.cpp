#include "game/anon_8021F088_private.h"

void clCoinPerfect::Update() {
        int a = (int)(lbl_806DB24C * tracks[0].value);
        text.color = PackColor(0xE0, 0x20, 0x20, a);
        unsigned int c = PackColor(0xFF, 0x55, 0x55, a);
        r[0].SetColor(c);
        r[1].SetColor(c);
        r[2].SetColor(c);
    }

void clCoinPerfect::Draw() {
        fn_801F8A34(fn_801F8E58(), &text, 1);
        for (int i = 0; i < 3; i++) {
            fn_8011FAFC(&r[i], 1);
        }
    }

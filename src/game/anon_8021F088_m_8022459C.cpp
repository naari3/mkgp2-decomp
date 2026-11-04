#define COIN_LINE_DRAW_OUTLINE
#define COIN_LINE_DTOR_INLINE
#include "game/anon_8021F088_private.h"

void clGetSumLine::Draw() {
        float x = tracks[3].value;
        float y = tracks[4].value;
        clGetCoinLine::Draw();
        if (perfect) {
            bar.p->SetPos(x - lbl_806DB288, y - lbl_806DB2F4);
        } else {
            bar.p->SetPos(x - lbl_806DB288, y - lbl_806DB2F8);
        }
        fn_801A0004(bar.p);
        if (isJapanese() == 0) {
            label.Show(lbl_806DB2FC + x, y - lbl_806DB194, lbl_806DB194);
        } else {
            label.Show(lbl_806DB300 + x, y - lbl_806DB194, lbl_806DB194);
        }
        fn_8011FAFC(&label, 1);
    }

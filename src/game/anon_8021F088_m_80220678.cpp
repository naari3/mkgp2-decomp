#include "game/anon_8021F088_private.h"

clGetSumLine::clGetSumLine(int n, unsigned char p, float y)
    : clGetCoinLine(lbl_806DB220, n, y, 0), perfect(p), bar(new Sprite(0x140, 1, 0)) {
    bar.p->SetPos(lbl_806DB224, lbl_806DB228);
    bar.p->layer = 1;
    fn_80121E10(&label);
    label.resId = 0x16D7;
    if (isJapanese() == 0) {
        label.Show(lbl_806DB22C, lbl_806DB230, lbl_806DB194);
    } else {
        label.Show(lbl_806DB234, lbl_806DB238, lbl_806DB194);
    }
}


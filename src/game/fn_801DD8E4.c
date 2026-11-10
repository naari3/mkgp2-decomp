#include "game/types/Entry_804E2404.h"

extern Entry_804E2404 lbl_804E2404[];
extern const float FLOAT_defaultBonus;

float fn_801DD8E4(int idx) {
    if (idx < 0) {
        return FLOAT_defaultBonus;
    }
    return lbl_804E2404[idx].f10;
}

int fn_801DD90C(int idx) {
    if (idx < 0) {
        return 0;
    }
    return lbl_804E2404[idx].fC;
}

#include "game/PlayerDataProgressPrivate.h"
void fn_801D676C(PlayerProgress *self) {
    int index = g_longRoundFlag + ((g_cupId - 1) * 4 + g_reverseRoundFlag * 2);
    int cc = g_ccClass;
    if (cc <= 0) return;
    if (cc > 2) return;
    if (self->completed[cc - 1][index] == 0) {
        unsigned char *flags = fn_8024F588();
        flags[1] = 1;
        self->completed[cc - 1][index] = 1;
    }
}

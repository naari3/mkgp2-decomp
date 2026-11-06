#include "game/PlayerDataProgressPrivate.h"
void fn_801D676C(PlayerProgress *self) {
    int index = g_longRoundFlag + ((g_cupId - 1) * 4 + g_reverseRoundFlag * 2);
    int cc = g_ccClass;
    if (cc <= 0) return;
    if (cc > 2) return;
    self = (PlayerProgress *)((unsigned char *)self + (cc - 1) * 32);
    self = (PlayerProgress *)((unsigned char *)self + index);
    if (self->completed[0][0] == 0) {
        unsigned char *flags = fn_8024F588();
        flags[1] = 1;
        self->completed[0][0] = 1;
    }
}

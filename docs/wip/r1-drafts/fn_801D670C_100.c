#include "game/PlayerDataProgressPrivate.h"
void fn_801D670C(PlayerProgress *self) {
    int index = g_longRoundFlag + (g_cupId - 1) * 4 + g_reverseRoundFlag * 2;
    int cc = g_ccClass;
    if (cc <= 0 || cc > 2) return;
    self = (PlayerProgress *)((unsigned char *)self + (cc - 1) * 32);
    self = (PlayerProgress *)((unsigned char *)self + index);
    if (self->visited[0][0] == 0) {
        self->visited[0][0] = 1;
    }
}

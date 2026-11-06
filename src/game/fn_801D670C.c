#include "game/PlayerDataProgressPrivate.h"
static inline void Mark(PlayerProgress *self, int cc, int index) {
    if (cc <= 0) return;
    if (cc > 2) return;
    self = (PlayerProgress *)((unsigned char *)self + (cc - 1) * 32);
    self = (PlayerProgress *)((unsigned char *)self + index);
    if (self->visited[0][0] == 0) {
        self->visited[0][0] = 1;
    }
}
void fn_801D670C(PlayerProgress *self) {
    int index = (g_cupId - 1) * 4 + g_reverseRoundFlag * 2;
    index += g_longRoundFlag;
    Mark(self, g_ccClass, index);
}

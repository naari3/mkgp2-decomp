#include "game/PlayerDataProgressPrivate.h"

int fn_801D5C88(PlayerDataRecord *p, int cc) {
    int i;
    if (cc < 0 || cc > 2) return 0;
    for (i = 0; i < 8; i++) {
        if (p->cupRank[cc][i] < 4) return 0;
    }
    return 1;
}

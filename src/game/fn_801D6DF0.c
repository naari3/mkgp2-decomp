#include "game/PlayerDataProgressPrivate.h"
extern unsigned char lbl_806D12E4[3];
static inline unsigned char RankReached(PlayerDataRecord *p, int cc, int cup) {
    if (cc < 0 || cc > 2) return 0;
    if (cup < 1 || cup >= 17) return 0;
    if (cup >= 9) cup -= 9; else cup -= 1;
    { int rank = p->cupRank[cc][cup];
    if (rank >= 4) return 1; }
    return 0;
}
static inline unsigned char AllCupsComplete(PlayerDataRecord *self, int cc) {
    unsigned char all = 1;
    int cup;
    for (cup = 1; cup <= 8; cup++) {
        if (cup != 6 && RankReached(self, cc, cup) == 0) { all = 0; break; }
    }
    return all;
}
void fn_801D6DF0(PlayerDataRecord *self) {
    int cc;
    for (cc = 0; cc < 3; cc++) {
        if (AllCupsComplete(self, cc) == 1) lbl_806D12E4[cc] = 1;
    }
}

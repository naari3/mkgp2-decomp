#include "game/PlayerDataResetPrivate.h"
extern int lbl_806D09C8;
extern PlayerDataRecord g_playerData;
extern unsigned char lbl_806D12E4[3];
extern unsigned char lbl_80598A60[];
extern void PlayStats_IncAllCupsCleared3rdMilestone(void);
extern void PlayStats_IncAllCupsClearedFinalMilestone(void);

static inline int CompletionStage(void) {
    int stage = 0;
    int count = 0;
    int i;
    for (i = 0; i < 8; i++) {
        int rank = g_playerData.cupRank[g_ccClass][i];
        if (rank >= 4) count++;
    }
    if (count == 8) stage = 1;
    count = 0;
    for (i = 0; i < 8; i++) {
        int rank = g_playerData.cupRank[g_ccClass][i];
        if (rank >= 9) count++;
    }
    if (count == 8) stage = 2;
    return stage;
}
static inline unsigned char RankReached(PlayerDataRecord *p, int cc, int cup) {
    int rank;
    if (cc < 0 || cc > 2) return 0;
    if (cup < 1 || cup >= 17) return 0;
    if (cup >= 9) cup -= 9; else cup -= 1;
    rank = p->cupRank[cc][cup];
    if (rank >= 4) return 1;
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
void fn_801D680C(PlayerDataRecord *self, int cup, int round, unsigned char update) {
    lbl_806D09C8 = -1;
    if (update) {
        PlayerDataRecord old = *self;
        int award = -1;
        int cc = g_ccClass;
        if (round <= 3) {
            if (self->cupRank[cc][cup] < round + 1) self->cupRank[cc][cup] = round + 1;
        } else {
            if (self->cupRank[cc][cup] < round + 2) self->cupRank[cc][cup] = round + 2;
        }
        if (old.cupRank[cc][cup] != self->cupRank[cc][cup]) {
            *fn_8024F588() = 1;
            if (cc == 1) award = 2;
            else if (cc == 2) award = 4;
            else award = 0;
            if ((signed char)lbl_80598A60[0x20] == 2 ||
                ((signed char)lbl_80598A60[0x20] == 1 && lbl_80598A60[0x24] == 0)) {
                if (round == 3) {
                    if (CompletionStage() == 1) PlayStats_IncAllCupsCleared3rdMilestone();
                } else if (round == 7) {
                    award++;
                    if (CompletionStage() == 2) PlayStats_IncAllCupsClearedFinalMilestone();
                } else award = -1;
            } else if (cup + 1 == 6) {
                if (round == 3) PlayStats_IncAllCupsCleared3rdMilestone();
                else if (round == 7) {
                    PlayStats_IncAllCupsClearedFinalMilestone();
                    award++;
                } else award = -1;
            } else award = -1;
        }
        if (award >= 0) {
            lbl_806D09C8 = award;
            *(int *)(fn_8024F588() + 0x10) = award;
        }
        if (AllCupsComplete(self, cc) == 1) lbl_806D12E4[cc] = 1;
        ((PlayerDataReset *)self)->field1D4 = cc;
        ((PlayerDataReset *)self)->field1D8 = round >= 4;
    }
}

#include "game/PlayerDataProgressPrivate.h"
extern int lbl_806D09C8;
void fn_801D6558(PlayerDataRecord *self, int cup, int mode, unsigned char update) {
    int pending = lbl_806D09C8;
    unsigned char *flags = fn_8024F588();
    *(int *)(flags + 0x10) = pending;
    lbl_806D09C8 = -1;
    if (update) {
        PlayerDataRecord old = *self;
        int normalized = cup;
        int cc = g_ccClass;
        if (cup >= 9 && cup <= 16) normalized = cup - 8;
        if (mode == 0) {
            if (CupRank(&old, cc, normalized) < 5) {
                unsigned char *p = fn_8024F588(); p[0] = 1;
            }
            if (self->cupRank[cc][normalized - 1] < 5) self->cupRank[cc][normalized - 1] = 5;
        } else {
            if (CupRank(&old, cc, normalized) < 10) {
                unsigned char *p = fn_8024F588(); p[0] = 1;
            }
            if (self->cupRank[cc][normalized - 1] < 10) self->cupRank[cc][normalized - 1] = 10;
        }
    }
}

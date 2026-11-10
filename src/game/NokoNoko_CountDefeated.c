#include "game/types/NokoNoko.h"

extern unsigned char g_nokonokoEnable;
extern NokoNoko *g_nokonokoHead;

int NokoNoko_CountDefeated(void) {
    int count;
    NokoNoko *p;

    if (g_nokonokoEnable == 0) {
        return 0;
    }
    count = 0;
    for (p = g_nokonokoHead; p != 0; p = p->next) {
        if (p->state >= 4) {
            count = count + 1;
        }
    }
    return count;
}

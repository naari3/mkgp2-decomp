#include "game/types/NokoNoko.h"

extern unsigned char g_nokonokoEnable;
extern NokoNoko *g_nokonokoHead;
extern const float lbl_806D9324;

extern void NokoNoko_Update(NokoNoko *p);

void NokoNoko_StopAllAlive(void) {
    NokoNoko *p;
    float fVar1;

    if (g_nokonokoEnable == 0) {
        return;
    }
    p = g_nokonokoHead;
    fVar1 = lbl_806D9324;
    for (; p != 0; p = p->next) {
        if (p->state < 4) {
            p->state = 0;
            p->model = 0;
            p->timer = -1;
            p->speed = fVar1;
            p->radius = fVar1;
        }
    }
}

void NokoNoko_UpdateAll(void) {
    NokoNoko *p;

    if (g_nokonokoEnable == 0) {
        return;
    }
    for (p = g_nokonokoHead; p != 0; p = p->next) {
        NokoNoko_Update(p);
    }
}

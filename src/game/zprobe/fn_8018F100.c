#include "game/types/ZProbe.h"

extern ZProbe *lbl_806D16A0;

void fn_8018F100(ZProbe *p) {
    ZProbe *it;
    p->next = 0;
    p->active = 0;
    p->x = 0;
    p->y = 0;
    p->z = 0;
    if (lbl_806D16A0 == 0) {
        lbl_806D16A0 = p;
        return;
    }
    for (it = lbl_806D16A0; it->next != 0; it = it->next) {
    }
    it->next = p;
}

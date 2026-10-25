#include "game/miyazakiconsole/miyazakiconsole.h"

/* 0x80180B34: draw the debug menus. The open submenu is drawn beside the
 * cursor line of its parent, which scrolls in a 9-line window. */

extern "C" {
extern Menu *lbl_806D1658;
extern Menu *lbl_806D165C;
extern Menu *lbl_806D1660;
extern int lbl_806D166C;
extern int lbl_806D1670;
extern unsigned char lbl_806CFBA0;
extern unsigned char lbl_806CFBA1;
void fn_801807E0(Menu *m, int x, int y, int dim);
}

extern "C" void fn_80180B34(void) {
    Menu *m;
    if (lbl_806D1658 == 0) {
        return;
    }
    if (lbl_806CFBA1 != 0) {
        if (lbl_806D1660 != 0) {
            fn_801807E0(lbl_806D165C, lbl_806D166C, lbl_806D1670, 0);
            if (lbl_806CFBA0 != 0) {
                unsigned int n = lbl_806D165C->count;
                int line;
                if (n < 9) {
                    line = lbl_806D165C->cursor;
                } else if (lbl_806D165C->cursor < 4) {
                    line = lbl_806D165C->cursor;
                } else if (lbl_806D165C->cursor > n - 4) {
                    line = 9 - (n - lbl_806D165C->cursor);
                } else {
                    line = 4;
                }
                fn_801807E0(lbl_806D1660, lbl_806D166C + 2, lbl_806D1670 + line + 3, 1);
            } else {
                fn_801807E0(lbl_806D1660, lbl_806D166C + 2, lbl_806D1670 + 2, 1);
            }
        } else {
            fn_801807E0(lbl_806D165C, lbl_806D166C, lbl_806D1670, 1);
        }
    }
    for (m = lbl_806D1658; m != 0; m = (Menu *)m->x4) {
        if (m->callback != 0) {
            m->callback(4, m->user, m->cursor, (unsigned char)(m == lbl_806D165C), 0);
        }
    }
}

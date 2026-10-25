#include "game/miyazakiconsole/miyazakiconsole.h"

extern "C" {
extern Menu *lbl_806D1658;
extern Menu *lbl_806D165C;
extern Menu *lbl_806D1660;
extern int lbl_806D1664;
extern unsigned char lbl_806CFBA1;
int fn_80180C80(Menu *m);
}

extern "C" void fn_80181144(void) {
    if (lbl_806D1658 == 0) {
        return;
    }
    if (++lbl_806D1664 > 30) {
        lbl_806D1664 = 0;
    }
    if (lbl_806CFBA1 != 0) {
        if (lbl_806D1660 != 0) {
            switch (fn_80180C80(lbl_806D1660)) {
            case 1: {
                unsigned int sel = lbl_806D1660->cursor;
                delete lbl_806D1660;
                lbl_806D1660 = 0;
                Menu *m = lbl_806D165C;
                if (m->callback != 0) {
                    m->callback(1, m->user, m->cursor, 1, sel);
                }
                break;
            }
            case 11:
                delete lbl_806D1660;
                lbl_806D1660 = 0;
                break;
            }
            return;
        }
        unsigned int key = fn_80180C80(lbl_806D165C);
        if (key != 0) {
            Menu *m = lbl_806D165C;
            if (m->callback != 0) {
                m->callback(0, m->user, m->cursor, 1, key);
            }
        }
    }
    Menu *m = lbl_806D165C;
    if (m->callback != 0) {
        m->callback(3, m->user, m->cursor, 1, 0);
    }
}

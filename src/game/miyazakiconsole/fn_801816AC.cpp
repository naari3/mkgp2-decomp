#include "game/miyazakiconsole/miyazakiconsole.h"

extern "C" {
extern Menu *lbl_806D1658;
extern Menu *lbl_806D165C;
}

extern "C" Menu *fn_801816AC(const char *name) {
    Menu *m = new Menu(name);
    if (lbl_806D1658 != 0) {
        lbl_806D165C->x4 = (int)m;
        m->x0 = (int)lbl_806D165C;
        lbl_806D165C = m;
    } else {
        lbl_806D1658 = m;
        lbl_806D165C = m;
    }
    return m;
}

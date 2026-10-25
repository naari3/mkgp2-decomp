#include "game/miyazakiconsole/miyazakiconsole.h"

extern "C" {
extern Menu *lbl_806D1658;
extern Menu *lbl_806D165C;
extern Menu *lbl_806D1660;
void fn_801801CC(Menu *m);
}

extern "C" void fn_801814C8(void) {
    if (lbl_806D1660 != 0) {
        delete lbl_806D1660;
        lbl_806D1660 = 0;
    }
    if (lbl_806D165C != lbl_806D1658) {
        lbl_806D165C = (Menu *)lbl_806D165C->x0;
        delete (Menu *)lbl_806D165C->x4;
        lbl_806D165C->x4 = 0;
    } else {
        fn_801801CC(lbl_806D1658);
        delete lbl_806D1658;
        lbl_806D1658 = 0;
        lbl_806D165C = 0;
    }
}

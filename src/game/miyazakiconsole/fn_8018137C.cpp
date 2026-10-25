#include "game/miyazakiconsole/miyazakiconsole.h"

extern "C" {
extern Menu *lbl_806D1658;
extern Menu *lbl_806D165C;
extern Menu *lbl_806D1660;
void fn_801801CC(Menu *m);
}

extern "C" void fn_8018137C(void) {
    if (lbl_806D1660 != 0) {
        delete lbl_806D1660;
        lbl_806D1660 = 0;
    }
    if (lbl_806D1658 != 0) {
        fn_801801CC(lbl_806D1658);
        delete lbl_806D1658;
        lbl_806D1658 = 0;
        lbl_806D165C = 0;
    }
}

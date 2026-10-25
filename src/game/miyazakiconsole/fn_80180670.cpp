#include "game/miyazakiconsole/miyazakiconsole.h"

extern "C" {
extern unsigned int lbl_806D1658;
extern Menu *lbl_806D1660;
extern unsigned char lbl_806CFBA0;
}

extern "C" Menu *fn_80180670(const char *name, unsigned char flag) {
    if (lbl_806D1658 == 0) {
        return 0;
    }
    if (lbl_806D1660 != 0) {
        delete lbl_806D1660;
        lbl_806D1660 = 0;
    }
    lbl_806D1660 = new Menu(name);
    lbl_806CFBA0 = flag;
    return lbl_806D1660;
}

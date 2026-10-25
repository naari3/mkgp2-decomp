#include "game/miyazakiconsole/miyazakiconsole.h"

extern "C" void fn_801801CC(Menu *m) {
    if ((Menu *)m->x4 != 0) {
        fn_801801CC((Menu *)m->x4);
        delete (Menu *)m->x4;
        m->x4 = 0;
    }
}

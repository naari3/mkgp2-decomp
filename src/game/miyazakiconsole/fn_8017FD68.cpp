#include "game/miyazakiconsole/console_create_private.h"

extern "C" MiyazakiMode *fn_8017FD68() {
    const char *s=lbl_80376220;
    return new MiyazakiMode(s);
}

#include "game/types/Obj.h"

extern void PathCursor_SetIndex(int, int);

void fn_801DBA60(void *p0, int index) {
    PathCursor_SetIndex(((Obj *)p0)->f_C, index);
}

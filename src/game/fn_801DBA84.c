#include "game/types/Obj.h"

extern void Waypoint_Advance(int);

void fn_801DBA84(void *p0) {
    Waypoint_Advance(((Obj *)p0)->f_C);
}

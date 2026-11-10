#include "game/types/Obj.h"

extern void Waypoint_FindNearest(int, int);

void fn_801DB99C(void *p0, int p1) {
    Waypoint_FindNearest(((Obj *)p0)->f_C, 0);
}

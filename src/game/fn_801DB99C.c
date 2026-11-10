#include "game/types/Obj.h"

extern int Waypoint_FindNearest(int, float *, float, float, float, float);

int fn_801DB99C(void *p0, float x, float y, float z, float maxDist) {
    return Waypoint_FindNearest(((Obj *)p0)->f_C, 0, x, y, z, maxDist);
}

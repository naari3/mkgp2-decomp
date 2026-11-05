/* Waypoint_FindNearest @ 0x80046680 (0x1D8).
 * Keep squared distance in the dx web so the sqrt input and return share
 * the target FPR, while the first two squared terms use a scratch register.
 * Private copies leave the already-matched PathCursor family unchanged.
 */
#include "game/PathCursor.h"

static inline float Nearest_CursorDistance(PathCursor *path, float x, float y, float z)
{
    Waypoint *p;
    float dx;
    float dy;
    float dz;

    if (path->points == 0) {
        return lbl_806D2678;
    }
    p = &path->points[path->cursor];
    dx = p->x - x;
    dy = p->y - y;
    dz = p->z - z;
    dx = dx * dx + dy * dy + dz * dz;
    return PathCursor_sqrtf(dx);
}

static inline float Nearest_OffsetDistance(PathCursor *path, int step, float x, float y, float z)
{
    Waypoint *p;
    float dx;
    float dy;
    float dz;

    if (path->points == 0) {
        return lbl_806D2678;
    }
    p = &path->points[PathCursor_Wrap(path, step)];
    dx = p->x - x;
    dy = p->y - y;
    dz = p->z - z;
    dx = dx * dx + dy * dy + dz * dz;
    return PathCursor_sqrtf(dx);
}

#pragma exceptions on
int Waypoint_FindNearest(PathCursor *path, float *outDist, float x, float y, float z,
                         float maxDist)
{
    int i;
    int saved;
    int best;
    float bestDist;
    float dist;

    if (path->points == 0) {
        return -1;
    }
    saved = path->cursor;
    bestDist = maxDist;
    best = -1;
    path->cursor = 0;
    for (i = 0; path->points[i].flag >= 0; i++) {
        dist = Nearest_CursorDistance(path, x, y, z);
        if (dist < maxDist && dist < bestDist) {
            best = i;
            bestDist = dist;
        }
        path->cursor++;
    }
    path->cursor = saved;
    if (outDist != 0) {
        *outDist = Nearest_OffsetDistance(path, 4, x, y, z);
    }
    return best;
}
#pragma exceptions reset

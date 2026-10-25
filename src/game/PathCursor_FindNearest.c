/*
 * Waypoint_FindNearest @ 0x80046680 (0x1D8), NonMatching.
 *
 * Instruction stream matches; only FPR numbering in the loop differs: the
 * squared distance / sqrt result web lands in f7 (dz) instead of f9 (dx).
 * Tried: all dx/dy/dz declaration orders, an explicit sum local, a nested
 * block, and four association orders of the sum. The int locals are
 * already pinned (i before saved gives target r7/r8).
 */
#include "game/PathCursor.h"

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
        dist = PathCursor_CursorDistance(path, x, y, z);
        if (dist < maxDist && dist < bestDist) {
            best = i;
            bestDist = dist;
        }
        path->cursor++;
    }
    path->cursor = saved;
    if (outDist != 0) {
        *outDist = PathCursor_OffsetDistance(path, 4, x, y, z);
    }
    return best;
}
#pragma exceptions reset

/*
 * Waypoint path cursor, 0x800461F0..0x80046680.
 *
 * Path layout: count, cursor index, waypoint array of 16-byte entries
 * (flag >= 0 marks a live entry, then x/y/z).
 */

#include "game/PathCursor.h"

#pragma exceptions on
int Path_CountWaypointsAndSnapGround(Waypoint *list)
{
    Waypoint *points = list;
    int count = 0;
    float zero = lbl_806D2660;

    while (points->flag >= 0) {
        float height = points->y;
        Vec3 pos = lbl_802EAF00;

        pos.x = points->x;
        pos.y = points->y;
        pos.z = points->z;
        if (Terrain_GetGroundHeightWithPenetration(&pos, &height, 0, 0, lbl_806D2664) == 1) {
            points->y = height;
            zero = lbl_806D2660;
        } else {
            points->y = zero;
        }
        count++;
        points++;
    }
    return count;
}
#pragma exceptions reset

int PathManager_HasPathLoaded(PathCursor *path)
{
    return path->points != 0;
}

int PathIndex_AdvanceCircular(PathCursor *path, int delta)
{
    return PathCursor_Wrap(path, delta);
}

int Path_GetCurrentIndex(PathCursor *path)
{
    return path->cursor;
}

int Path_GetTotalCount(PathCursor *path)
{
    return path->count;
}

Waypoint *Path_GetWaypointPtr(PathCursor *path, int index)
{
    if (path->points == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (index >= path->count) {
        return 0;
    }
    return &path->points[index];
}

Waypoint *PathCursor_SetIndex(PathCursor *path, int index)
{
    if (path->points == 0) {
        return 0;
    }
    if (index < 0) {
        return 0;
    }
    if (index >= path->count) {
        return 0;
    }
    path->cursor = index;
    return &path->points[index];
}

Waypoint *Waypoint_Advance(PathCursor *path)
{
    path->cursor = (path->cursor + 1) % path->count;
    return &path->points[path->cursor];
}

static inline float PathCursor_ProjectAlongSegment(PathCursor *path, int step, float x, float z)
{
    Vec3 dir;
    Vec3 to;
    float dist;
    float dot;
    int a;
    int b;

    if (path->points == 0) {
        return lbl_806D2678;
    }
    a = PathCursor_Wrap(path, step);
    b = PathCursor_Wrap(path, step - 1);
    dir.x = path->points[b].x - path->points[a].x;
    dir.y = lbl_806D2660;
    dir.z = path->points[b].z - path->points[a].z;
    to.x = x - path->points[a].x;
    to.y = lbl_806D2660;
    to.z = z - path->points[a].z;
    dist = Vec3_Magnitude(&to);
    Vec3_Normalize(&dir, &dir);
    Vec3_Normalize(&to, &to);
    dot = Vec3_Dot(&to, &dir);
    if (dot < lbl_806D2660) {
        return lbl_806D2678;
    }
    return dist * dot;
}

#pragma exceptions on
int Waypoint_FindBestAhead(PathCursor *path, float x, float y, float z,
                           int start, int from, int to, float *outDist)
{
    int best;
    int saved;
    int step;
    float dist;

    if (path->points == 0) {
        return -1;
    }
    if (start < 0) {
        return -1;
    }
    if (start >= path->count) {
        return -1;
    }
    if (from >= to) {
        return -1;
    }
    saved = path->cursor;
    step = from;
    dist = lbl_806D2678;
    best = -1;
    path->cursor = start;
    for (; step <= to; step++) {
        dist = PathCursor_ProjectAlongSegment(path, step, x, z);
        if (dist >= lbl_806D2660) {
            best = PathCursor_Wrap(path, step);
            break;
        }
    }
    if (saved != -1) {
        path->cursor = saved;
    }
    if (outDist != 0) {
        *outDist = dist;
    }
    return best;
}
#pragma exceptions reset

#ifndef GAME_PATHCURSOR_H
#define GAME_PATHCURSOR_H

typedef struct Vec3 {
    float x, y, z;
} Vec3;

typedef struct Waypoint {
    int flag;
    float x, y, z;
} Waypoint;

typedef struct PathCursor {
    int count;
    int cursor;
    unsigned char pad_08[4];
    Waypoint *points;
} PathCursor;

extern Vec3 lbl_802EAF00;
extern const float lbl_806D2660;
extern const float lbl_806D2664;
extern const double lbl_806D2668;
extern const double lbl_806D2670;
extern const float lbl_806D2678;

extern unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *pos, float *height,
                                                            int a, int b, float range);
extern float Vec3_Magnitude(Vec3 *v);
extern void Vec3_Normalize(Vec3 *src, Vec3 *dst);
extern float Vec3_Dot(Vec3 *a, Vec3 *b);

static inline int PathCursor_Wrap(PathCursor *path, int delta)
{
    int index = path->cursor + delta;

    if (delta >= 0) {
        while (index >= path->count) {
            index -= path->count;
        }
    } else {
        while (index < 0) {
            index += path->count;
        }
    }
    return index;
}

static inline float PathCursor_sqrtf(float x)
{
    volatile float y;

    if (x > lbl_806D2660) {
        double guess = __frsqrte(x);
        guess = lbl_806D2668 * guess * (lbl_806D2670 - x * (guess * guess));
        guess = lbl_806D2668 * guess * (lbl_806D2670 - x * (guess * guess));
        guess = lbl_806D2668 * guess * (lbl_806D2670 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline float PathCursor_CursorDistance(PathCursor *path, float x, float y, float z)
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
    return PathCursor_sqrtf(dx * dx + dy * dy + dz * dz);
}

static inline float PathCursor_OffsetDistance(PathCursor *path, int step, float x, float y, float z)
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
    return PathCursor_sqrtf(dx * dx + dy * dy + dz * dz);
}

#endif

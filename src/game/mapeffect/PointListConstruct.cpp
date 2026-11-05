struct Vec { float x, y, z;
    Vec &operator=(const Vec &v) { x=v.x; y=v.y; z=v.z; return *this; }
    void Set(float a, float b, float c) { x=a; y=b; z=c; }
};
typedef struct SpawnPoint { float x, y, z; int tag; } SpawnPoint;
struct PointList { int count; Vec *pts; PointList(SpawnPoint *); };
extern "C" {
extern const float lbl_806D8B00, lbl_806D8B04;
extern char lbl_8036D540[], lbl_8036D564[];
extern float PSVECSquareMag(const Vec *);
extern unsigned char IsSpawnTableTerminator(const SpawnPoint *);
extern void DebugPrintf(const char *, ...);
extern void *FUN_8003b120(int);
}
#pragma exceptions on
PointList::PointList(SpawnPoint *spawn) {
    PointList *l = this;
    Vec points[20];
    Vec delta;
    int j, n, i, k;
    SpawnPoint *cur;
    l->count = 0;
    l->pts = 0;
    if (!spawn) return;
    cur = spawn;
    n = 0;
    while (!IsSpawnTableTerminator(cur)) {
        for (j = 0; j < n; ++j) {
            delta.Set(points[j].x-cur->x, lbl_806D8B00, points[j].z-cur->z);
            if (PSVECSquareMag(&delta) < lbl_806D8B04) break;
        }
        if (j >= n) {
            points[n].x = cur->x;
            points[n].y = lbl_806D8B00;
            points[n].z = cur->z;
            if (++n >= 20) break;
        }
        ++cur;
    }
    if (n <= 0) return;
    DebugPrintf(lbl_8036D540, n);
    l->count = n;
    l->pts = (Vec *)FUN_8003b120(l->count * sizeof(Vec));
    if (!l->pts) {
        l->count = 0;
        l->pts = 0;
        return;
    }
    for (i = 0; i < l->count; ++i) {
        l->pts[i] = points[i];
    }
    for (k = 0; k < l->count; ++k) DebugPrintf(lbl_8036D564, l->pts[k].x, l->pts[k].y, l->pts[k].z);
    return;
}

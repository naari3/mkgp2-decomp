/* Wall list vs. XZ segment test, 0x80036278..0x800364C8. */

typedef struct TerrainWall {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    float x0;
    float z0;
    float x1;
    float z1;
} TerrainWall;

typedef struct TerrainWallList {
    unsigned char pad_00[8];
    TerrainWall *walls;
    int count;
} TerrainWallList;

typedef struct TerrainWallHit {
    unsigned char pad_00[0x30];
    float normal[3];
    float point[3];
} TerrainWallHit;

extern const float lbl_806D2384;
extern const float lbl_806D2388;
extern const double lbl_806D23A0;
extern const double lbl_806D23A8;

extern unsigned char Math_SegmentIntersection2D(void *self, float ax, float az, float bx, float bz, float cx,
                                                float cz, float dx, float dz, float *out);

#pragma exceptions on
unsigned char Terrain_WallSegmentTest(TerrainWallHit *hit, TerrainWallList *list, float *seg)
{
    float loZ;
    float loX;
    float hiX;
    float hiZ;
    int i;

    if (list == 0) {
        return 0;
    }
    if (list->count <= 0) {
        return 0;
    }
    if (seg[1] > seg[3]) {
        loZ = seg[3];
        hiZ = seg[1];
    } else {
        loZ = seg[1];
        hiZ = seg[3];
    }
    if (seg[0] > seg[2]) {
        loX = seg[2];
        hiX = seg[0];
    } else {
        loX = seg[0];
        hiX = seg[2];
    }
    for (i = 0; i < list->count; i++) {
        TerrainWall *wall = &list->walls[i];

        if (loZ <= wall->maxZ && hiZ >= wall->minZ && loX <= wall->maxX && hiX >= wall->minX) {
            if (Math_SegmentIntersection2D(hit, seg[0], seg[1], seg[2], seg[3], wall->x0, wall->z0, wall->x1,
                                           wall->z1, hit->point) == 1) {
                float len;
                float inv;

                hit->normal[0] = -(wall->z1 - wall->z0);
                hit->normal[1] = lbl_806D2384;
                hit->normal[2] = wall->x1 - wall->x0;
                len = hit->normal[0] * hit->normal[0] + hit->normal[1] * hit->normal[1] +
                      hit->normal[2] * hit->normal[2];
                if (len > lbl_806D2384) {
                    double guess = __frsqrte(len);
                    volatile float y;

                    guess = lbl_806D23A0 * guess * (lbl_806D23A8 - len * (guess * guess));
                    guess = lbl_806D23A0 * guess * (lbl_806D23A8 - len * (guess * guess));
                    guess = lbl_806D23A0 * guess * (lbl_806D23A8 - len * (guess * guess));
                    y = (float)(len * guess);
                    len = y;
                }
                inv = lbl_806D2388 / len;
                hit->normal[0] *= inv;
                hit->normal[1] *= inv;
                hit->normal[2] *= inv;
                return 1;
            }
        }
    }
    return 0;
}
#pragma exceptions reset

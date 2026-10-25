/*
 * Course ground-height queries, 0x80035268..0x80035AE4.
 * NonMatching (both functions). Terrain_GetGroundHeightWithPenetration differs
 * in register coloring and load order: the target keeps x/z in f0/f1 and
 * reloads the zero constant where CW keeps it live.
 * Terrain_GetGroundHeight: the target keeps the parameters in r28..r31 in order and
 * reloads the edge-test zero (lbl_806D2384) inside the triangle loop; CW
 * hoists it here, same as Terrain_FindTriangleAtPosition.
 */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
}

typedef struct TerrainTri {
    float minX;
    float minZ;
    float maxX;
    float maxZ;
    float v[3][3];
    float edgeNormal[3][3];
    unsigned int wallEdges;
    unsigned char pad_5C[4];
    float plane[4];
} TerrainTri;

typedef struct TerrainCell {
    TerrainTri *tris;
    int triCount;
    void *walls;
    int wallCount;
} TerrainCell;

typedef struct TerrainGrid {
    int width;
    int height;
    float cellWidth;
    float cellDepth;
    unsigned char pad_10[0x10];
    float offsetX;
    float offsetZ;
    TerrainCell *cells;
} TerrainGrid;

extern "C" {
extern TerrainGrid *lbl_806CED58;
extern float lbl_806D2384;
extern const float lbl_806D2388;
extern const float lbl_806D238C;
extern const float lbl_806D2398;
extern const float lbl_806D239C;

}

class ScopedTimer {
public:
    inline ScopedTimer(int slot)
    {
        m_slot = slot;
        m_startTick = OSGetTick();
    }

    inline ~ScopedTimer()
    {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D238C);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};

static inline int Terrain_EdgeSide(TerrainTri *tri, int e, float x, float z)
{
    float a = -tri->edgeNormal[e][2] * (x - tri->v[e][0]);
    float b = tri->edgeNormal[e][0] * (z - tri->v[e][2]);

    return a + b > lbl_806D2384;
}

static inline int Terrain_OutsideEdges(TerrainTri *tri, float x, float z)
{
    int outside;

    outside = 3;
    if (!Terrain_EdgeSide(tri, 0, x, z)) {
        outside = 2;
        if (!Terrain_EdgeSide(tri, 1, x, z)) {
            outside = 1;
            if (!Terrain_EdgeSide(tri, 2, x, z)) {
                outside = 0;
            }
        }
    }
    return outside;
}

static inline float Terrain_PlaneSide(TerrainTri *tri, float x, float y, float z)
{
    return tri->plane[2] * (z - tri->v[0][2]) + (tri->plane[0] * (x - tri->v[0][0]) + tri->plane[1] * (y - tri->v[0][1]));
}

static inline float Terrain_PlaneHeight(TerrainTri *tri, float x, float y, float z)
{
    float b = tri->plane[1];
    float inv = b;

    if (lbl_806D2384 != b) {
        inv = lbl_806D2388 / b;
    }
    return inv * (tri->plane[3] + (tri->plane[2] * z + (tri->plane[0] * x + b * y)));
}

extern "C" unsigned char Terrain_GetGroundHeightWithPenetration(float *pos, float *outHeight, float *outNormal,
                                                                unsigned int *outAttr, float penetration)
{
    ScopedTimer timer(0x10);
    TerrainGrid *grid;
    float x;
    int col;
    int row;
    TerrainCell *cell;
    TerrainTri *tri;
    int count;
    int i;
    unsigned char found;
    unsigned char haveBest;
    float best;
    float bestHeight;
    float bestNormal[3];
    unsigned int bestAttr;

    if (lbl_806CED58 == 0) {
        return 0;
    }
    x = pos[0];
    *outHeight = lbl_806D2398;
    grid = lbl_806CED58;
    col = (x + grid->offsetX) / grid->cellWidth;
    row = (pos[2] + grid->offsetZ) / grid->cellDepth;
    if (col < 0 || row < 0 || col >= grid->width || row >= grid->height) {
        return 0;
    }
    cell = &grid->cells[row * grid->width + col];
    best = lbl_806D239C;
    found = 0;
    haveBest = 0;
    tri = cell->tris;
    count = cell->triCount;
    for (i = 0; i < count; i++, tri++) {
        if (tri->minX <= x && tri->maxX >= x && tri->minZ <= pos[2] && tri->maxZ >= pos[2]) {
            float z = pos[2];
            if (Terrain_OutsideEdges(tri, x, z) == 0) {
                float y = pos[1] + penetration;
                float d = Terrain_PlaneSide(tri, x, y, z);
                float h = Terrain_PlaneHeight(tri, x, y, z);

                y = y - h;
                if (d >= lbl_806D2384 && *outHeight <= y) {
                    *outHeight = y;
                    if (outNormal != 0) {
                        outNormal[0] = tri->plane[0];
                        outNormal[1] = tri->plane[1];
                        outNormal[2] = tri->plane[2];
                    }
                    if (outAttr != 0) {
                        *outAttr = *(unsigned int *)tri->pad_5C;
                    }
                    found = 1;
                } else {
                    float a = __fabs(h);
                    if (best >= a) {
                        best = a;
                        bestNormal[0] = tri->plane[0];
                        bestHeight = y;
                        bestNormal[1] = tri->plane[1];
                        bestNormal[2] = tri->plane[2];
                        haveBest = 1;
                        bestAttr = *(unsigned int *)tri->pad_5C;
                    }
                }
            }
        }
    }
    if (!found && haveBest == 1) {
        *outHeight = bestHeight;
        if (outNormal != 0) {
            outNormal[0] = bestNormal[0];
            outNormal[1] = bestNormal[1];
            outNormal[2] = bestNormal[2];
        }
        if (outAttr != 0) {
            *outAttr = bestAttr;
        }
        found = 1;
    }
    return found;
}

extern "C" unsigned char Terrain_GetGroundHeight(float *pos, float *outHeight, float *outNormal, unsigned int *outAttr)
{
    ScopedTimer timer(0x10);
    TerrainGrid *grid = lbl_806CED58;
    int col;
    int row;
    TerrainCell *cell;
    TerrainTri *tri;
    int count;
    int i;

    if (grid == 0) {
        return 0;
    }
    col = (pos[0] + grid->offsetX) / grid->cellWidth;
    row = (pos[2] + grid->offsetZ) / grid->cellDepth;
    if (col < 0 || row < 0 || col >= grid->width || row >= grid->height) {
        return 0;
    }
    cell = &grid->cells[row * grid->width + col];
    tri = cell->tris;
    count = cell->triCount;
    for (i = 0; i < count; i++, tri++) {
        if (tri->minX <= pos[0] && tri->maxX >= pos[0] && tri->minZ <= pos[2] && tri->maxZ >= pos[2]) {
            if (Terrain_OutsideEdges(tri, pos[0], pos[2]) == 0) {
                float y;
                float b = tri->plane[1];
                float inv = b;
                float h;

                if (0.0f != b) {
                    inv = lbl_806D2388 / b;
                }
                y = pos[1];
                h = inv * (tri->plane[3] + (tri->plane[2] * pos[2] + (tri->plane[0] * pos[0] + b * y)));
                *outHeight = y - h;
                if (outNormal != 0) {
                    outNormal[0] = tri->plane[0];
                    outNormal[1] = tri->plane[1];
                    outNormal[2] = tri->plane[2];
                }
                if (outAttr != 0) {
                    *outAttr = *(unsigned int *)tri->pad_5C;
                }
                return 1;
            }
        }
    }
    return 0;
}

#pragma cplusplus off

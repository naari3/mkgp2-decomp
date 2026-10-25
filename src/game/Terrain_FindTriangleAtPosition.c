/*
 * Course collision grid lookup, 0x80035ED4..0x80036154.
 * NonMatching: CW hoists the edge-test zero (lbl_806D2384) out of the
 * triangle loop, while the target reloads it every iteration; the rest
 * (including the plane height solve) is instruction-exact.
 */

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

typedef struct TerrainSample {
    TerrainCell *cell;
    TerrainTri *triangle;
    float x;
    float y;
    float z;
    unsigned char onTriangle;
    unsigned char pad_15[3];
} TerrainSample;

typedef struct TerrainStepper {
    TerrainSample samples[2];
    unsigned char pad_30[0x18];
    int index;
} TerrainStepper;

extern TerrainGrid *lbl_806CED58;
extern const float lbl_806D2384;
extern const float lbl_806D2388;

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

#pragma exceptions on
unsigned char Terrain_FindTriangleAtPosition(TerrainStepper *stepper, float x, float y, float z)
{
    int col = (x + lbl_806CED58->offsetX) / lbl_806CED58->cellWidth;
    int row = (z + lbl_806CED58->offsetZ) / lbl_806CED58->cellDepth;
    TerrainTri *tri;
    int count;
    int i;

    stepper->samples[stepper->index].cell = 0;
    stepper->samples[stepper->index].triangle = 0;
    if (col < 0 || row < 0 || col >= lbl_806CED58->width || row >= lbl_806CED58->height) {
        return 0;
    }
    stepper->samples[stepper->index].cell = &lbl_806CED58->cells[row * lbl_806CED58->width + col];
    tri = lbl_806CED58->cells[row * lbl_806CED58->width + col].tris;
    count = lbl_806CED58->cells[row * lbl_806CED58->width + col].triCount;
    for (i = 0; i < count; i++, tri++) {
        if (tri->minX <= x && tri->maxX >= x && tri->minZ <= z && tri->maxZ >= z) {
            if (Terrain_OutsideEdges(tri, x, z) == 0) {
                float b = tri->plane[1];
                float inv = b;

                if (0.0f != b) {
                    inv = lbl_806D2388 / b;
                }
                {
                    float h = inv * (tri->plane[3] + (tri->plane[2] * z + (tri->plane[0] * x + b * y)));

                    stepper->samples[stepper->index].x = x;
                    stepper->samples[stepper->index].y = y - h;
                }
                stepper->samples[stepper->index].z = z;
                stepper->samples[stepper->index].triangle = tri;
                return 1;
            }
        }
    }
    stepper->samples[stepper->index].triangle = 0;
    return 0;
}
#pragma exceptions reset

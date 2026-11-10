/*
 * Course collision grid lookup, 0x80035ED4..0x80036154.
 * Indexed triangle traversal preserves the array base and the target count
 * register. The three-edge countdown loop preserves the target zero reload
 * and floating-point temporaries.
 */

#include "game/types/TerrainTri.h"

#include "game/types/TerrainCell.h"

#include "game/types/TerrainGrid.h"

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
extern const float lbl_806D2388;

static inline int Terrain_EdgeSide(TerrainTri *tri, int e, float x, float z)
{
    float a = -tri->edgeNormal[e][2] * (x - tri->v[e][0]);
    float b = tri->edgeNormal[e][0] * (z - tri->v[e][2]);

    return a + b > 0.0f;
}

static inline int Terrain_OutsideEdges(TerrainTri *tri, float x, float z)
{
    int outside;
    int edge;

    for (outside = 3, edge = 0; outside > 0; --outside, ++edge) {
        if (Terrain_EdgeSide(tri, edge, x, z)) {
            break;
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
    TerrainTri *triangles;
    int count;
    int i;

    stepper->samples[stepper->index].cell = 0;
    stepper->samples[stepper->index].triangle = 0;
    if (col < 0 || row < 0 || col >= lbl_806CED58->width || row >= lbl_806CED58->height) {
        return 0;
    }
    stepper->samples[stepper->index].cell = &lbl_806CED58->cells[row * lbl_806CED58->width + col];
    triangles = lbl_806CED58->cells[row * lbl_806CED58->width + col].tris;
    count = lbl_806CED58->cells[row * lbl_806CED58->width + col].triCount;
    for (i = 0; i < count; i++) {
        tri = &triangles[i];
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

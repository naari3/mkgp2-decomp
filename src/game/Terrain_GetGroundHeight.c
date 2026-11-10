/*
 * Penetrating ground-height query, 0x80035268..0x80035700.
 * NonMatching: only initial sentinel/X and grid/Z load scheduling differs.
 * Indexed cell and triangle traversal preserves the original array bases.
 */
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
}

#include "game/types/TerrainTri.h"

#include "game/types/TerrainCell.h"

#include "game/types/TerrainGrid.h"

extern "C" {
extern TerrainGrid *g_collisionData;
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

static inline float Terrain_PlaneSide(TerrainTri *tri, float x, float y, float z)
{
    return tri->plane[2] * (z - tri->v[0][2]) + (tri->plane[0] * (x - tri->v[0][0]) + tri->plane[1] * (y - tri->v[0][1]));
}


static inline float Terrain_InitHeight(float x, float *height)
{
    *height = lbl_806D2398;
    return x;
}

extern "C" unsigned char Terrain_GetGroundHeightWithPenetration(float *pos, float *outHeight, float *outNormal,
                                                                unsigned int *outAttr, float penetration)
{
    ScopedTimer timer(0x10);
    TerrainGrid *grid;
    float x;
    int col;
    int row;
    TerrainTri *tri;
    TerrainTri *triangles;
    int count;
    int i;
    unsigned char found;
    unsigned char haveBest;
    float best;
    float bestHeight;
    float bestNormal[3];
    unsigned int bestAttr;

    if (g_collisionData == 0) {
        return 0;
    }
    x = Terrain_InitHeight(pos[0], outHeight);
    grid = g_collisionData;
    col = (x + grid->offsetX) / grid->cellWidth;
    row = (pos[2] + grid->offsetZ) / grid->cellDepth;
    if (col < 0 || row < 0 || col >= grid->width || row >= grid->height) {
        return 0;
    }
    best = lbl_806D239C;
    found = 0;
    haveBest = 0;
    triangles = grid->cells[row * grid->width + col].tris;
    count = grid->cells[row * grid->width + col].triCount;
    for (i = 0; i < count; i++) {
        tri = &triangles[i];
        if (tri->minX <= x && tri->maxX >= x && tri->minZ <= pos[2] && tri->maxZ >= pos[2]) {
            float z = pos[2];
            if (Terrain_OutsideEdges(tri, x, z) == 0) {
                float y = pos[1] + penetration;
                float d = Terrain_PlaneSide(tri, x, y, z);
                float b = tri->plane[1];
                float inv = b;
                float h;

                if (0.0f != b) {
                    inv = lbl_806D2388 / b;
                }
                h = inv * (tri->plane[3] + (tri->plane[2] * z + (tri->plane[0] * x + b * y)));

                y = y - h;
                if (d >= 0.0f && *outHeight <= y) {
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

#pragma cplusplus off

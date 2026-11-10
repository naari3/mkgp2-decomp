/*
 * Ground-height query, 0x80035700..0x80035AE4.
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


extern "C" unsigned char Terrain_GetGroundHeight(float *pos, float *outHeight, float *outNormal, unsigned int *outAttr)
{
    ScopedTimer timer(0x10);
    TerrainGrid *grid = g_collisionData;
    int col;
    int row;
    TerrainTri *tri;
    TerrainTri *triangles;
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
    triangles = grid->cells[row * grid->width + col].tris;
    count = grid->cells[row * grid->width + col].triCount;
    for (i = 0; i < count; i++) {
        tri = &triangles[i];
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

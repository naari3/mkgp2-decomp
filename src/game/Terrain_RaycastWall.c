#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * Wall raycast between two positions, 0x80035AE4..0x80035ED4: special-face
 * mesh first, then the terrain grid stepper.
 * The input ranges are independent. The first triangle query belongs to
 * the stepper constructor so exception cleanup starts after it completes.
 */
C_REGION_END
#pragma cplusplus on
extern "C" {
unsigned int OSGetTick(void);
void Profiler_RecordFrame(int slot, float value);
}

#include "game/types/Vec3.h"

typedef struct TerrainSample {
    void *cell;
    void *triangle;
    float x;
    float y;
    float z;
    unsigned char onTriangle;
    unsigned char pad_15[3];
} TerrainSample;

struct TerrainStepper;
extern "C" unsigned char Terrain_FindTriangleAtPosition(TerrainStepper *, float, float, float);

struct TerrainStepper {
    TerrainSample samples[2];
    Vec3 normal;
    Vec3 pos;
    int index;
    unsigned char pad_4C[4];
    float delta[3];

    TerrainStepper(float x, float y, float z)
    {
        index = 0;
        samples[0].x = x;
        samples[0].y = y;
        samples[0].z = z;
        samples[0].cell = 0;
        samples[0].triangle = 0;
        samples[1].x = x;
        samples[1].y = y;
        samples[1].z = z;
        samples[1].cell = 0;
        samples[1].triangle = 0;
        samples[index].onTriangle = Terrain_FindTriangleAtPosition(this, x, y, z);
    }

    void Advance(float x, float y, float z)
    {
        index++;
        index &= 1;
        samples[index].x = x;
        samples[index].y = y;
        samples[index].z = z;
        samples[index].onTriangle = Terrain_FindTriangleAtPosition(this, x, y, z);
    }

    ~TerrainStepper() {} /* out of line: dtor_80036988 */
};

struct SpecialFaceMesh;

extern "C" {
extern SpecialFaceMesh *lbl_806D1138;
extern const float lbl_806D2384;
extern const float lbl_806D2388;
extern const float lbl_806D238C;
unsigned char SpecialFaceMesh_RaycastThunk(SpecialFaceMesh *mesh, Vec3 *from, Vec3 *to, float *outPos, float *outNormal);
unsigned char Terrain_GetGroundHeightWithPenetration(float *pos, float *outHeight, float *outNormal,
                                                     unsigned int *outAttr, float penetration);
unsigned char Terrain_FindTriangleAtPosition(TerrainStepper *st, float x, float y, float z);
unsigned char Terrain_WallEdgeTest(TerrainStepper *st);
unsigned char Terrain_StepAndResolve(TerrainStepper *st);
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

static inline SpecialFaceMesh *SpecialFaceMesh_Get(void)
{
    SpecialFaceMesh *m = lbl_806D1138;
    if (m == 0) {
        return 0;
    }
    return m;
}

extern "C" unsigned char Terrain_RaycastWall(float *__restrict from, float *__restrict to, float *outPos, float *outNormal)
{
    ScopedTimer timer(0x10);
    SpecialFaceMesh *mesh = SpecialFaceMesh_Get();

    if (mesh != 0) {
        Vec3 a = *(Vec3 *)from;
        Vec3 b = *(Vec3 *)to;

        a.y += lbl_806D2388;
        b.y += lbl_806D2388;
        if (SpecialFaceMesh_RaycastThunk(mesh, &a, &b, outPos, outNormal) == 1) {
            Terrain_GetGroundHeightWithPenetration(outPos, &outPos[1], 0, 0, lbl_806D2384);
            return 1;
        }
    }
    {
        TerrainStepper st(from[0], from[1], from[2]);
        float *xs = &st.samples[0].x;
        float *ys = &st.samples[0].y;
        float *zs = &st.samples[0].z;
        float x = to[0], y = to[1], z = to[2];
        st.index++;
        st.index &= 1;
        *(float *)((char *)xs + st.index * 0x18) = x;
        *(float *)((char *)ys + st.index * 0x18) = y;
        *(float *)((char *)zs + st.index * 0x18) = z;
        st.samples[st.index].onTriangle = Terrain_FindTriangleAtPosition(&st, x, y, z);
        if (st.samples[st.index].onTriangle == 1) {
            return 0;
        }
        if (!Terrain_WallEdgeTest(&st)) {
            return 0;
        }
        if (!Terrain_StepAndResolve(&st)) {
            return 0;
        }
        outPos[0] = st.pos.x;
        outPos[1] = st.pos.y;
        outPos[2] = st.pos.z;
        outNormal[0] = st.normal.x;
        outNormal[1] = st.normal.y;
        outNormal[2] = st.normal.z;
        Terrain_GetGroundHeightWithPenetration(outPos, &outPos[1], 0, 0, lbl_806D2384);
        return 1;
    }
}

#pragma cplusplus off

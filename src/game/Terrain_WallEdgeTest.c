/*
 * Terrain_WallEdgeTest, 0x80036710..0x80036988.
 * NonMatching (98%): the prologue schedules the segment copy against
 * different volatile registers and the loop index add lands in r0
 * instead of r3; FPR/GPR coloring otherwise exact.
 */

typedef struct TerrainVertex {
    float x;
    float y;
    float z;
} TerrainVertex;

typedef struct TerrainTriangle {
    unsigned char pad_00[0x10];
    TerrainVertex verts[3];
    unsigned char pad_34[0x24];
    unsigned int wallEdges;
} TerrainTriangle;

typedef struct TerrainSegment {
    float ax;
    float az;
    float bx;
    float bz;
} TerrainSegment;

typedef struct TerrainSample {
    void *walls;
    TerrainTriangle *triangle;
    float x;
    float y;
    float z;
    unsigned char onTriangle;
    unsigned char pad_15[3];
} TerrainSample;

typedef struct TerrainStepper {
    TerrainSample samples[2];
    float normal[3];
    float x;
    float pad_40;
    float z;
    int index;
    unsigned char pad_4C[4];
    float delta[3];
} TerrainStepper;

extern const float lbl_806D2380;
extern const float lbl_806D2384;
extern const float lbl_806D2388;
extern const double lbl_806D23A0;
extern const double lbl_806D23A8;

extern const TerrainSegment lbl_802E9828;

extern unsigned char Math_SegmentIntersection2D(void *self, float ax, float az, float bx, float bz, float cx,
                                                float cz, float dx, float dz, float *out);
extern unsigned char Terrain_WallSegmentTest(TerrainStepper *stepper, void *walls, TerrainSegment *seg);
extern unsigned char Terrain_FindTriangleAtPosition(TerrainStepper *stepper, float x, float y, float z);

static inline int Terrain_OtherIndex(int index)
{
    return (index + 1) & 1;
}

#pragma exceptions on
unsigned char Terrain_WallEdgeTest(TerrainStepper *stepper)
{
    int index = stepper->index;
    TerrainSegment seg = { 0.0f, 0.0f, 0.0f, 0.0f };
    TerrainSample *from = &stepper->samples[(index + 1) & 1];
    TerrainSample *to = &stepper->samples[index];
    int e;
    unsigned int edges;
    TerrainTriangle *tri;
    TerrainVertex *v;
    int k;
    TerrainSample *sample;
    unsigned char hit;

    seg.ax = from->x;
    seg.az = from->z;
    seg.bx = to->x;
    seg.bz = to->z;
    for (k = 0; k < 2; k++) {
        sample = &stepper->samples[(k + stepper->index + 1) & 1];
        tri = sample->triangle;
        if (tri == 0) {
            hit = 0;
        } else {
            edges = tri->wallEdges;
            if (edges == 0) {
                hit = 0;
            } else {
                for (e = 0, v = (TerrainVertex *)tri; e < 3; e++, v++) {
                    if ((edges >> e) & 1) {
                        int next = (e + 1) % 3;

                        if (Math_SegmentIntersection2D(stepper, seg.ax, seg.az, seg.bx, seg.bz, ((float *)v)[4], ((float *)v)[6], tri->verts[next].x, tri->verts[next].z,
                                                       &stepper->x) == 1) {
                            float len;
                            float inv;

                            stepper->normal[0] = -(tri->verts[next].z - tri->verts[e].z);
                            stepper->normal[1] = 0.0f;
                            stepper->normal[2] = tri->verts[next].x - tri->verts[e].x;
                            len = stepper->normal[0] * stepper->normal[0] +
                                  stepper->normal[1] * stepper->normal[1] +
                                  stepper->normal[2] * stepper->normal[2];
                            if (len > 0.0f) {
                                double guess = __frsqrte(len);
                                volatile float y;

                                guess = lbl_806D23A0 * guess * (lbl_806D23A8 - len * (guess * guess));
                                guess = lbl_806D23A0 * guess * (lbl_806D23A8 - len * (guess * guess));
                                guess = lbl_806D23A0 * guess * (lbl_806D23A8 - len * (guess * guess));
                                y = (float)(len * guess);
                                len = y;
                            }
                            inv = lbl_806D2388 / len;
                            stepper->normal[0] *= inv;
                            stepper->normal[1] *= inv;
                            stepper->normal[2] *= inv;
                            hit = 1;
                            goto tested;
                        }
                    }
                }
                hit = 0;
            }
        }
tested:
        if (hit == 1) {
            return 1;
        }
        if (Terrain_WallSegmentTest(stepper, sample->walls, &seg) == 1) {
            return 1;
        }
    }
    return 0;
}
#pragma exceptions reset

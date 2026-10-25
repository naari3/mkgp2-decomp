/* Two-sample position stepping against the course terrain, 0x800364D8..0x80036710. */

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

static inline float Terrain_sqrtf(float x)
{
    volatile float y;

    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = lbl_806D23A0 * guess * (lbl_806D23A8 - x * (guess * guess));
        guess = lbl_806D23A0 * guess * (lbl_806D23A8 - x * (guess * guess));
        guess = lbl_806D23A0 * guess * (lbl_806D23A8 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

static inline int Terrain_OtherIndex(int index)
{
    return (index + 1) & 1;
}

#pragma exceptions on
unsigned char Terrain_StepAndResolve(TerrainStepper *stepper)
{
    int prev = (stepper->index + 1) & 1;
    TerrainSample *from = &stepper->samples[prev];
    TerrainSample *to = &stepper->samples[stepper->index];
    float dx = from->x - to->x;
    float dz = from->z - to->z;
    float lenSq = dx * dx + dz * dz;
    float inv;
    unsigned char hit;

    if (lenSq <= 0.0f) {
        stepper->x = 0.0f;
        stepper->z = 0.0f;
        stepper->delta[0] = 0.0f;
        stepper->delta[1] = 0.0f;
        stepper->delta[2] = 0.0f;
        return 0;
    }
    inv = lbl_806D2388 / Terrain_sqrtf(lenSq);
    dx *= inv;
    dz *= inv;
    stepper->x += lbl_806D2380 * dx;
    stepper->z += lbl_806D2380 * dz;
    stepper->delta[0] = stepper->x - stepper->samples[stepper->index].x;
    stepper->delta[1] = 0.0f;
    stepper->delta[2] = stepper->z - stepper->samples[stepper->index].z;
    stepper->samples[stepper->index].x = stepper->x;
    stepper->samples[stepper->index].z = stepper->z;
    hit = Terrain_FindTriangleAtPosition(stepper, stepper->samples[stepper->index].x,
                                         stepper->samples[stepper->index].y, stepper->samples[stepper->index].z);
    if (!hit) {
        stepper->samples[stepper->index].x = from->x;
        stepper->samples[stepper->index].y = stepper->samples[prev].y;
        stepper->samples[stepper->index].z = from->z;
        stepper->delta[0] = 0.0f;
        stepper->delta[1] = 0.0f;
        stepper->delta[2] = 0.0f;
        hit = Terrain_FindTriangleAtPosition(stepper, stepper->samples[stepper->index].x,
                                             stepper->samples[stepper->index].y,
                                             stepper->samples[stepper->index].z);
    }
    stepper->samples[stepper->index].onTriangle = hit;
    return hit;
}

#pragma exceptions reset

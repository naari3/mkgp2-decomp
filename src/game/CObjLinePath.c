/* Minimal field view reconstructed from the complete wrapper instructions. */
typedef struct LinePoint { float x, y, z; } LinePoint;
typedef struct CObjLinePathView {
    unsigned char pad00[4];
    void *camera;
    unsigned char recording, pad09, mode, pad0B;
    float angle, radius;
    LinePoint offset;
    float angleAux;
    int count;
    unsigned int ready;
    unsigned char pad2C[8];
    LinePoint points[1024];
} CObjLinePathView;

extern void HSD_CObjSetInterest(void *, const LinePoint *);
extern void HSD_CObjSetEyePosition(void *, const LinePoint *);
extern void C_MTXMultVec(const float *, const LinePoint *, LinePoint *);
extern double sin(double);
extern double cos(double);
extern void DebugTextOutput(int, const char *, ...);
extern const char lbl_802E96B8[12];
extern const float lbl_806D2310, lbl_806D2314, lbl_806D2318;
extern const char lbl_806D2334[4], lbl_806D2338[2];
/* Inlined camera setters mirror CObjViewport.c's defensive wrappers. */
static inline int CObj_ApplyViewport(CObjLinePathView *self, const LinePoint *value) {
    if (self->ready == 0) return 0;
    HSD_CObjSetInterest(self->camera, value);
    return 1;
}

static inline int CObj_LoadIntoGX(CObjLinePathView *self, const LinePoint *value) {
    if (self->ready == 0) return 0;
    HSD_CObjSetEyePosition(self->camera, value);
    return 1;
}

/* MSL sqrtf: three Newton refinements and a single-precision spill. */
static inline float LinePath_sqrtf(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

int CObj_LinePath_Step(CObjLinePathView *self, const float *matrix,
                      float height, float y, float z) {
    volatile LinePoint vector;
    /* Preserve ordered component reads while assembling camera vectors. */
    const volatile float *translation = matrix;
    const char *formats = lbl_802E96B8;
    float x = 0.0f;
    if (self->ready == 0) return 0;
    vector.x = translation[3];
    vector.y = translation[7] + height;
    vector.z = translation[11];
    CObj_ApplyViewport(self, (const LinePoint *)&vector);

    if (self->mode == 1) {
        float a;
        double radians;
        x = -(self->radius * (float)sin((float)(0.017453292519943295 * self->angle)));
        z = self->radius * (float)cos((float)(0.017453292519943295 * self->angle));
        a = 280.0f + self->angle;
        if (a >= 360.0f) a -= 360.0f;
        radians = 0.017453292519943295 * a;
        self->offset.x = -(13.0f * (float)sin((float)radians));
        self->offset.y = y - 5.0f;
        self->offset.z = 13.0f * (float)cos((float)radians);
        a = lbl_806D2310 + self->angle;
        if (a >= 360.0f) a -= 360.0f;
        self->angleAux = lbl_806D2314 - a;
        a = self->angle + lbl_806D2318;
        self->angle = a;
        if (a >= 360.0f) self->angle -= 360.0f;
    } else self->radius = z;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    if (self->mode == 1) {
        float tx = (float)(double)x;
        float ty = (float)(double)y;
        float tz = (float)(double)z;
        vector.x = tx + translation[3];
        vector.y = ty + translation[7];
        vector.z = tz + translation[11];
    } else C_MTXMultVec(matrix, (const LinePoint *)&vector, (LinePoint *)&vector);
    CObj_LoadIntoGX(self, (const LinePoint *)&vector);

    if (self->recording == 1 && self->count > 10) {
        float dz = matrix[11] - self->points[1].z;
        float dx = matrix[3] - self->points[1].x;
        float distance = LinePath_sqrtf(dx * dx + dz * dz);
        if (distance < 100.0f) {
            int i;
            DebugTextOutput(1, formats + 0x70);
            for (i = 1; i < self->count; ++i)
                DebugTextOutput(1, formats + 0x88, self->points[i].x, self->points[i].y, self->points[i].z);
            DebugTextOutput(1, formats + 0xAC, self->count - 1);
            DebugTextOutput(1, lbl_806D2334);
            DebugTextOutput(1, lbl_806D2338);
            self->recording = 0;
        }
    }
    if (self->recording == 1) {
        float dx = matrix[3] - self->points[self->count - 1].x;
        float dz = matrix[11] - self->points[self->count - 1].z;
        float distance = LinePath_sqrtf(dx * dx + dz * dz);
        if (self->count < 1024 && distance >= 100.0f) {
            self->points[self->count].x = matrix[3];
            self->points[self->count].y = matrix[7];
            self->points[self->count].z = matrix[11];
            ++self->count;
        }
    } else {
        self->points[0].x = matrix[3];
        self->points[1].y = matrix[3];
        self->points[2].z = matrix[3];
    }
    return 1;
}

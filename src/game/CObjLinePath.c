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

extern void fn_802C72AC(void *, const LinePoint *);
extern void fn_802C7384(void *, const LinePoint *);
extern void fn_8025DEAC(const float *, const LinePoint *, LinePoint *);
extern double fn_8027E9E8(double);
extern double fn_8027E480(double);
extern void DebugTextOutput(int, const char *, ...);
extern const char lbl_802E96B8[12];
extern const char lbl_806D2334[4], lbl_806D2338[2];
extern const float lbl_806D22F4, lbl_806D2300, lbl_806D2304;
extern const float lbl_806D2308, lbl_806D230C, lbl_806D2310;
extern const float lbl_806D2314, lbl_806D2318, lbl_806D2330;
extern const double lbl_806D22F8, lbl_806D2320, lbl_806D2328;

/* MSL sqrtf: three Newton refinements and a single-precision spill. */
static inline float LinePath_sqrtf(float x) {
    volatile float y;
    if (x > lbl_806D22F4) {
        double guess = __frsqrte(x);
        guess = lbl_806D2320 * guess * (lbl_806D2328 - x * (guess * guess));
        guess = lbl_806D2320 * guess * (lbl_806D2328 - x * (guess * guess));
        guess = lbl_806D2320 * guess * (lbl_806D2328 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

int CObj_LinePath_Step(CObjLinePathView *self, const float *matrix,
                      float height, float y, float z) {
    volatile LinePoint vector;
    const char *formats = lbl_802E96B8;
    float x = lbl_806D22F4;
    if (self->ready == 0) return 0;
    vector.x = matrix[3];
    vector.y = matrix[7] + height;
    vector.z = matrix[11];
    if (self->ready != 0) fn_802C72AC(self->camera, (const LinePoint *)&vector);

    if (self->mode == 1) {
        float a;
        double radians;
        x = -(self->radius * (float)fn_8027E9E8((float)(lbl_806D22F8 * self->angle)));
        z = self->radius * (float)fn_8027E480((float)(lbl_806D22F8 * self->angle));
        a = lbl_806D2300 + self->angle;
        if (a >= lbl_806D2304) a -= lbl_806D2304;
        radians = lbl_806D22F8 * a;
        self->offset.x = -(lbl_806D2308 * (float)fn_8027E9E8((float)radians));
        self->offset.y = y - lbl_806D230C;
        self->offset.z = lbl_806D2308 * (float)fn_8027E480((float)radians);
        a = lbl_806D2310 + self->angle;
        if (a >= lbl_806D2304) a -= lbl_806D2304;
        self->angleAux = lbl_806D2314 - a;
        a = self->angle + lbl_806D2318;
        self->angle = a;
        if (a >= lbl_806D2304) self->angle -= lbl_806D2304;
    } else self->radius = z;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    if (self->mode == 1) {
        float tx = (float)(double)x;
        float ty = (float)(double)y;
        float tz = (float)(double)z;
        vector.x = tx + matrix[3];
        vector.y = ty + matrix[7];
        vector.z = tz + matrix[11];
    } else fn_8025DEAC(matrix, (const LinePoint *)&vector, (LinePoint *)&vector);
    if (self->ready != 0) fn_802C7384(self->camera, (const LinePoint *)&vector);

    if (self->recording == 1 && self->count > 10) {
        float dz = matrix[11] - self->points[1].z;
        float dx = matrix[3] - self->points[1].x;
        float distance = LinePath_sqrtf(dx * dx + dz * dz);
        if (distance < lbl_806D2330) {
            int i;
            LinePoint *point;
            DebugTextOutput(1, formats + 0x70);
            for (i = 1, point = &self->points[1]; i < self->count; ++i, ++point)
                DebugTextOutput(1, formats + 0x88, point->x, point->y, point->z);
            DebugTextOutput(1, formats + 0xAC, self->count - 1);
            DebugTextOutput(1, lbl_806D2334);
            DebugTextOutput(1, lbl_806D2338);
            self->recording = 0;
        }
    }
    if (self->recording == 1) {
        float dz = matrix[11] - self->points[self->count - 1].z;
        float dx = matrix[3] - self->points[self->count - 1].x;
        float distance = LinePath_sqrtf(dx * dx + dz * dz);
        if (self->count < 1024 && distance >= lbl_806D2330) {
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

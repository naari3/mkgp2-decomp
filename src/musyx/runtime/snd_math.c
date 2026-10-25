typedef struct SND_FVECTOR {
    float x;
    float y;
    float z;
} SND_FVECTOR;

typedef struct SND_FMATRIX {
    float m[3][3];
    float t[3];
} SND_FMATRIX;

extern const float lbl_806DCAF0;
extern const double lbl_806DCAF8;
extern const double lbl_806DCB00;
extern const float lbl_806DCB08;

static inline float sqrtf(float x) {
    volatile float y;
    if (x > lbl_806DCAF0) {
        double guess = __frsqrte((double)x);
        guess = lbl_806DCAF8 * guess * (lbl_806DCB00 - guess * guess * x);
        guess = lbl_806DCAF8 * guess * (lbl_806DCB00 - guess * guess * x);
        guess = lbl_806DCAF8 * guess * (lbl_806DCB00 - guess * guess * x);
        y = (float)(x * guess);
        return y;
    }
    return x;
}

void salApplyMatrix(const SND_FMATRIX* mat, const SND_FVECTOR* in, SND_FVECTOR* out) {
    out->x = mat->m[0][0] * in->x + mat->m[0][1] * in->y + mat->m[0][2] * in->z + mat->t[0];
    out->y = mat->m[1][0] * in->x + mat->m[1][1] * in->y + mat->m[1][2] * in->z + mat->t[1];
    out->z = mat->m[2][0] * in->x + mat->m[2][1] * in->y + mat->m[2][2] * in->z + mat->t[2];
}

float salNormalizeVector(SND_FVECTOR* vec) {
    float l = sqrtf(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
    vec->x /= l;
    vec->y /= l;
    vec->z /= l;
    return l;
}

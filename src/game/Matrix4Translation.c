/* Complete column-major multiplication through a temporary preserves out == in. */
extern const float lbl_806D592C;
extern const float lbl_806D5930;

#if 0
/* Approach C: the natural inline helper composition preserves initialization
 * stores but loses coefficient forwarding/unrolling. Kept as complete evidence. */
static inline void InitializeIdentity(float *m)
{
    m[0] = lbl_806D5930; m[1] = lbl_806D592C;
    m[2] = lbl_806D592C; m[3] = lbl_806D592C;
    m[4] = lbl_806D592C; m[5] = lbl_806D5930;
    m[6] = lbl_806D592C; m[7] = lbl_806D592C;
    m[8] = lbl_806D592C; m[9] = lbl_806D592C;
    m[10] = lbl_806D5930; m[11] = lbl_806D592C;
    m[12] = lbl_806D592C; m[13] = lbl_806D592C;
    m[14] = lbl_806D592C; m[15] = lbl_806D5930;
}

static inline void SetTranslation(float *m, float x, float y, float z)
{
    m[12] = x; m[13] = y; m[14] = z;
}

static inline void Multiply(float *result, const float *t, const float *in)
{
    int i;
    for (i = 0; i < 4; ++i) {
        float a = in[4*i] * t[0];
        float b = in[4*i] * t[1];
        float c = in[4*i] * t[2];
        float d = in[4*i] * t[3];
        a = t[4] * in[4*i+1] + a;
        b = t[5] * in[4*i+1] + b;
        c = t[6] * in[4*i+1] + c;
        d = t[7] * in[4*i+1] + d;
        a = t[8] * in[4*i+2] + a;
        b = t[9] * in[4*i+2] + b;
        c = t[10] * in[4*i+2] + c;
        d = t[11] * in[4*i+2] + d;
        result[4*i] = t[12] * in[4*i+3] + a;
        result[4*i+1] = t[13] * in[4*i+3] + b;
        result[4*i+2] = t[14] * in[4*i+3] + c;
        result[4*i+3] = t[15] * in[4*i+3] + d;
    }
}

void Matrix4_PreMultiplyTranslation(float *out, const float *in,
                                   float x, float y, float z)
{
    struct { float result[16]; float translation[16]; } scratch;
    int i;
    InitializeIdentity(scratch.translation);
    SetTranslation(scratch.translation, x, y, z);
    Multiply(scratch.result, scratch.translation, in);
    for (i = 0; i < 16; ++i) out[i] = scratch.result[i];
}
#endif

/* Best bounded draft (approach B): complete, not accepted as matching. */
void Matrix4_PreMultiplyTranslation(float *out, const float *in,
                                   float x, float y, float z)
{
    float result[16];
    float translation[16];
    int i;
    for (i = 0; i < 16; ++i) translation[i] = lbl_806D592C;
    translation[0] = lbl_806D5930;
    translation[5] = lbl_806D5930;
    translation[10] = lbl_806D5930;
    translation[15] = lbl_806D5930;
    translation[12] = x;
    translation[13] = y;
    translation[14] = z;
    for (i = 0; i < 4; ++i) {
        result[4*i] = in[4*i] * translation[0]
                    + translation[4] * in[4*i+1]
                    + translation[8] * in[4*i+2]
                    + translation[12] * in[4*i+3];
        result[4*i+1] = in[4*i] * translation[1]
                      + translation[5] * in[4*i+1]
                      + translation[9] * in[4*i+2]
                      + translation[13] * in[4*i+3];
        result[4*i+2] = in[4*i] * translation[2]
                      + translation[6] * in[4*i+1]
                      + translation[10] * in[4*i+2]
                      + translation[14] * in[4*i+3];
        result[4*i+3] = in[4*i] * translation[3]
                      + translation[7] * in[4*i+1]
                      + translation[11] * in[4*i+2]
                      + translation[15] * in[4*i+3];
    }
    for (i = 0; i < 16; ++i) out[i] = result[i];
}

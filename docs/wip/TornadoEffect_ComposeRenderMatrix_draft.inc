/* TornadoEffect_ComposeRenderMatrix @ 0x80057A8C (size 0xA84). */

extern double cos(double);
extern double sin(double);

typedef union { float m[4][4]; float f[16]; } TEMtx;

static inline void TE_MtxIdentity(TEMtx *a)
{
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            a->m[i][j] = 0.0f;
        }
    }
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1.0f;
}

static inline void TE_MtxMul(TEMtx *a, const TEMtx *b)
{
    float t[16];
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            float s = a->f[i * 4 + 0] * b->f[0 * 4 + j];
            s += a->f[i * 4 + 1] * b->f[1 * 4 + j];
            s += a->f[i * 4 + 2] * b->f[2 * 4 + j];
            s += a->f[i * 4 + 3] * b->f[3 * 4 + j];
            t[i * 4 + j] = s;
        }
    }
    a->f[0] = t[0]; a->f[1] = t[1]; a->f[2] = t[2]; a->f[3] = t[3];
    a->f[4] = t[4]; a->f[5] = t[5]; a->f[6] = t[6]; a->f[7] = t[7];
    a->f[8] = t[8]; a->f[9] = t[9]; a->f[10] = t[10]; a->f[11] = t[11];
    a->f[12] = t[12]; a->f[13] = t[13]; a->f[14] = t[14]; a->f[15] = t[15];
}

void TornadoEffect_ComposeRenderMatrix(void *e, const TEMtx *src, TEMtx *out)
{
    void *st;
    TEMtx a;
    TEMtx r;
    float ang;
    float sx;
    float sy;
    float sz;

    TE_MtxIdentity(out);
    sx = 1.2f * TE_F(e, 0xEC);
    sy = 1.2f * TE_F(e, 0xF0);
    sz = 1.2f * TE_F(e, 0xF4);
    out->m[0][0] *= sx;
    out->m[1][1] *= sy;
    out->m[2][2] *= sz;
    TE_MtxMul(out, src);

    st = TE_PTR(TE_PTR(e, 0xC), 0x304);
    TE_MtxIdentity(&a);
    ang = 0.017453292519943295 * Saturate_Double(TE_F(e, 0x120), -10.0f, 10.0f);
    TE_MtxIdentity(&r);
    {
        float c = cos(ang);
        float s = sin(ang);
        r.m[0][0] = c;
        r.m[0][1] = s;
        r.m[1][1] = c;
        r.m[1][0] = -s;
    }
    TE_MtxMul(&r, &a);
    a = r;
    TE_MtxMul(&a, out);
    *out = a;

    if (TE_StateHasFlagLo(st, 0x10) == 1 || TE_StateHasFlagLo(st, 0x8) == 1) {
        float k = TE_F(e, 0x10C);
        if (TE_StateHasFlagLo(TE_PTR(TE_PTR(e, 0xC), 0x304), 0x10) == 1) {
            k *= 1.0f + (1.0f - (float)__fabs((float)sin(TE_F(e, 0x114))));
        }
        out->m[3][1] += TE_F(e, 0x18) * (k - 1.0f);
    }
    {
        float x = TE_F(st, 0x30);
        float y = TE_F(st, 0x34);
        float z = TE_F(st, 0x38);
        out->m[3][0] += x;
        out->m[3][1] += y;
        out->m[3][2] += z;
    }
}

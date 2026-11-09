/* TornadoEffect_ComposeRenderMatrix @ 0x80057A8C (size 0xA84). */

extern double cos(double);
extern double sin(double);

typedef struct { float x, y, z; } TEVec3c;
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

static inline void TE_MtxMul(TEMtx *a, const TEMtx *b, float *t)
{
    const float *row = a->f;
    const float *column;
    float *output = t;
    const float *right = b->f;
    int n = 0;
    int i;
    int j;
    for (i = 0; i < 4; i++) {
        column = right;
        for (j = 0; j < 4; j++, column++) {
            float value = row[0] * column[0];
            value += row[1] * column[4];
            value += row[2] * column[8];
            value += row[3] * column[12];
            output[n + j] = value;
        }
        row += 4;
        n += 4;
    }
    for (i = 0; i < 16; ++i) {
        a->f[i] = t[i];
    }
}

#pragma push
#pragma use_lmw_stmw on
void TornadoEffect_ComposeRenderMatrix(void *e, const TEMtx *src, TEMtx *out)
{
    void *st;
    TEMtx a;
    TEMtx *ap = &a;
    float t1[16];
    TEMtx r;
    TEMtx *rp;
    float t3[16];
    float t2[16];
    float ang;
    int k;
    float sx;
    float sy;
    float sz;

    sx = 1.2f * TE_F(e, 0xEC);
    sy = 1.2f * TE_F(e, 0xF0);
    sz = 1.2f * TE_F(e, 0xF4);
    TE_MtxIdentity(out);
    out->m[0][0] *= sx;
    out->m[1][1] *= sy;
    out->m[2][2] *= sz;
    TE_MtxMul(out, src, t1);

    st = TE_PTR(TE_PTR(e, 0xC), 0x304);
    TE_MtxIdentity(&a);
    ang = 0.017453292519943295 * Saturate_Double(TE_F(e, 0x120), -10.0f, 10.0f);
    rp = &r;
    TE_MtxIdentity(&r);
    {
        float c = cos(ang);
        float s = sin(ang);
        r.m[0][0] = c;
        r.m[0][1] = s;
        r.m[1][1] = c;
        r.m[1][0] = -s;
    }
    TE_MtxMul(rp, &a, t2);
    a = r;
    TE_MtxMul(ap, out, t3);
    for (k = 0; k < 16; k++) {
        out->f[k] = (float)(double)ap->f[k];
    }

    if (TE_StateHasFlagLo(st, 0x10) == 1 || TE_StateHasFlagLo(st, 0x8) == 1) {
        float k = TE_F(e, 0x10C);
        if (TE_StateHasFlagLo(TE_PTR(TE_PTR(e, 0xC), 0x304), 0x10) == 1) {
            k *= 1.0f + (1.0f - (float)__fabs((float)sin(TE_F(e, 0x114))));
        }
        out->m[3][1] += TE_F(e, 0x18) * (k - 1.0f);
    }
    {
        TEVec3c p = *(TEVec3c *)((char *)st + 0x30);
        out->m[3][0] += p.x;
        out->m[3][1] += p.y;
        out->m[3][2] += p.z;
    }
}
#pragma pop

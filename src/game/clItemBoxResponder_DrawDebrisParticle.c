/* Row-major debris transform, composed in the same order as Matrix4 helpers. */
extern double cos(double);
extern double sin(double);
extern void Mtx4x4_TransposeTo4x3(const void *, void *);
extern void GXChannel_PushTransform(void *, const void *);
extern void *clItemBox_bss_806D10B8;

#include "game/ItemBoxDebrisParticlePrivate.h"

static inline void Identity(Matrix *m)
{
    int i;
    for (i = 0; i < 16; ++i) m->v[i] = 0.0f;
    m->v[0] = m->v[5] = m->v[10] = m->v[15] = 1.0f;
}

static inline void Concat(Matrix *out, const Matrix *a, const Matrix *b)
{
    float tmp[16];
    float *m;
    int k, i, j;
    if (out == a || out == b) m = tmp;
    else m = out->v;
    k = 0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j) {
            float sum = a->v[k] * b->v[j];
            sum += a->v[k + 1] * b->v[4 + j];
            sum += a->v[k + 2] * b->v[8 + j];
            sum += a->v[k + 3] * b->v[12 + j];
            m[k + j] = sum;
        }
        k += 4;
    }
    if (out == a || out == b) {
        for (i = 0; i < 16; ++i) out->v[i] = tmp[i];
    }
}

static inline float Cosine(float angle) { return (float)cos(angle); }
static inline float Sine(float angle) { return (float)sin(angle); }

static inline void RotateY(Matrix *out, const Matrix *in, float angle)
{
    Matrix rot;
    float c, s;
    Identity(&rot);
    c = Cosine(angle);
    s = Sine(angle);
    rot.v[0] = c; rot.v[8] = s; rot.v[10] = c; rot.v[2] = -s;
    Concat(&rot, &rot, in);
    *out = rot;
}

static inline void RotateX(Matrix *out, const Matrix *in, float angle)
{
    Matrix rot;
    float c, s;
    Identity(&rot);
    c = Cosine(angle);
    s = Sine(angle);
    rot.v[10] = c; rot.v[6] = s; rot.v[5] = c; rot.v[9] = -s;
    Concat(&rot, &rot, in);
    *out = rot;
}

static inline void SetTranslation(Matrix *m, float x, float y, float z)
{
    m->v[12] = x; m->v[13] = y; m->v[14] = z;
}

#pragma use_lmw_stmw on
void clItemBoxResponder_DrawDebrisParticle(DebrisParticle *particle)
{
    float transform[3][4];
    Matrix m;
    Identity(&m);
    RotateY(&m, &m, particle->yaw);
    RotateX(&m, &m, particle->pitch);
    SetTranslation(&m, particle->position[0], particle->position[1], particle->position[2]);
    m.v[0] *= particle->scale; m.v[4] *= particle->scale; m.v[8] *= particle->scale;
    m.v[1] *= particle->scale; m.v[5] *= particle->scale; m.v[9] *= particle->scale;
    m.v[2] *= particle->scale; m.v[6] *= particle->scale; m.v[10] *= particle->scale;
    Mtx4x4_TransposeTo4x3(&m, transform);
    GXChannel_PushTransform(clItemBox_bss_806D10B8, transform);
}
#pragma use_lmw_stmw reset

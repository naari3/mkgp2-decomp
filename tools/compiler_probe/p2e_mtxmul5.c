/* volatile-out variant of m1.
 * Phase 2e probe: flavor-5 4x4 mtx-multiply loop SR coalescing
 * (CarObject_MainUpdate 0x8004DA44..0x8004DC58).
 * Target loop per iteration (2 iterations, ctr):
 *   - row ptr r26 walks A (const offsets 0x0..0x1c, addi r26,r26,0x20)
 *   - out index k in r5 kept INTEGER: slwi r0,k,2 + stfsx f8,r6,r0
 *     (r6 = &out materialized once); k+1..k+3 addi temps in r3; k+=4 twice
 *   - dead counter i in r4: init `mr r4,r5` (phase-2c splice family),
 *     `addi r4,r4,1` once per iteration, never read
 *   - B matrix read from caller stack slots 0x80..0xbc(r1) with const offsets
 * Hypothesis: the loop is spliced from a static inline MtxMul(out, a, b);
 * param-based out/a defeat the SR coalescing seen in all 5 direct forms,
 * and the spliced i web (init copy from k) escapes const-prop AND DCE.
 */

#pragma exceptions off

extern void Consume(void *m, float *a);
extern const float F_ZERO, F_ONE;

typedef struct Scratch {
    float qx, qy, qz, qw;
    float axis[3];
    float colY[3];
    float up[3];
    float mOut[16];
    float mB[16];
    float mA[16];
} Scratch;

typedef struct MvView { char pad[0x98]; float mtx[16]; } MvView;
typedef struct SelfView { char pad[0x28]; MvView *movement; } SelfView;

/* m1: helper, 2-iteration loop, k integer index, i control via `i < 2`,
 * init spelled k = 0; i = k (mr family). */
static inline void MtxMul_m1(volatile float *out, const float *a, const float *b) {
    int k;
    int i;
    for (i = 0, k = i; i < 2; i++) {
        out[k] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
        out[k + 1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
        out[k + 2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
        out[k + 3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
        k += 4;
        out[k] = a[4] * b[0] + a[5] * b[4] + a[6] * b[8] + a[7] * b[12];
        out[k + 1] = a[4] * b[1] + a[5] * b[5] + a[6] * b[9] + a[7] * b[13];
        out[k + 2] = a[4] * b[2] + a[5] * b[6] + a[6] * b[10] + a[7] * b[14];
        out[k + 3] = a[4] * b[3] + a[5] * b[7] + a[6] * b[11] + a[7] * b[15];
        k += 4;
        a += 8;
    }
}

void m1_wrap(SelfView *self) {
    Scratch s;
    MvView *m = self->movement;
    int j;
    for (j = 0; j < 16; j++) {
        s.mA[j] = m->mtx[j];
        s.mB[j] = F_ZERO;
    }
    s.mB[0] = F_ONE;
    s.mB[5] = F_ONE;
    s.mB[10] = F_ONE;
    s.mB[15] = F_ONE;
    MtxMul_m1(s.mOut, s.mA, s.mB);
    Consume(self->movement, s.mA);
}

/* m2: same helper body but 4-iteration single-row loop (backend unroll x2?) */
static inline void MtxMul_m2(float *out, const float *a, const float *b) {
    int k;
    int i;
    for (i = 0, k = i; i < 4; i++) {
        out[k] = a[0] * b[0] + a[1] * b[4] + a[2] * b[8] + a[3] * b[12];
        out[k + 1] = a[0] * b[1] + a[1] * b[5] + a[2] * b[9] + a[3] * b[13];
        out[k + 2] = a[0] * b[2] + a[1] * b[6] + a[2] * b[10] + a[3] * b[14];
        out[k + 3] = a[0] * b[3] + a[1] * b[7] + a[2] * b[11] + a[3] * b[15];
        k += 4;
        a += 4;
    }
}

void m2_wrap(SelfView *self) {
    Scratch s;
    MvView *m = self->movement;
    int j;
    for (j = 0; j < 16; j++) {
        s.mA[j] = m->mtx[j];
        s.mB[j] = F_ZERO;
    }
    s.mB[0] = F_ONE;
    s.mB[5] = F_ONE;
    s.mB[10] = F_ONE;
    s.mB[15] = F_ONE;
    MtxMul_m2(s.mOut, s.mA, s.mB);
    Consume(self->movement, s.mA);
}

/* m3: direct loop in the wrapper (known-negative baseline, draft form 5) */
void m3_direct(SelfView *self) {
    Scratch s;
    MvView *m = self->movement;
    int j;
    int k;
    int i;
    float *pa;
    float *out;
    for (j = 0; j < 16; j++) {
        s.mA[j] = m->mtx[j];
        s.mB[j] = F_ZERO;
    }
    s.mB[0] = F_ONE;
    s.mB[5] = F_ONE;
    s.mB[10] = F_ONE;
    s.mB[15] = F_ONE;
    k = 0;
    i = 0;
    pa = s.mA;
    out = s.mOut;
    do {
        out[k] = pa[0] * s.mB[0] + pa[1] * s.mB[4] + pa[2] * s.mB[8] + pa[3] * s.mB[12];
        out[k + 1] = pa[0] * s.mB[1] + pa[1] * s.mB[5] + pa[2] * s.mB[9] + pa[3] * s.mB[13];
        out[k + 2] = pa[0] * s.mB[2] + pa[1] * s.mB[6] + pa[2] * s.mB[10] + pa[3] * s.mB[14];
        out[k + 3] = pa[0] * s.mB[3] + pa[1] * s.mB[7] + pa[2] * s.mB[11] + pa[3] * s.mB[15];
        k += 4;
        out[k] = pa[4] * s.mB[0] + pa[5] * s.mB[4] + pa[6] * s.mB[8] + pa[7] * s.mB[12];
        out[k + 1] = pa[4] * s.mB[1] + pa[5] * s.mB[5] + pa[6] * s.mB[9] + pa[7] * s.mB[13];
        out[k + 2] = pa[4] * s.mB[2] + pa[5] * s.mB[6] + pa[6] * s.mB[10] + pa[7] * s.mB[14];
        out[k + 3] = pa[4] * s.mB[3] + pa[5] * s.mB[7] + pa[6] * s.mB[11] + pa[7] * s.mB[15];
        k += 4;
        pa += 8;
        i += 1;
    } while (i < 2);
    Consume(self->movement, s.mA);
}

#pragma exceptions reset

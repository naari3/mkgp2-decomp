/* Phase 2e probe: helper under #pragma optimization_level 2, caller at O4.
 * Theory: target mtx loop = O2-style body (stfsx, no SR, unmerged k+=4,
 * live-but-naive i web) spliced into an O4 caller whose late backend passes
 * (ctr conversion, scheduling, regalloc) then run on it, orphaning the i
 * init+increment without a DCE rerun.
 */

#pragma exceptions off
#pragma inline_max_size(1024)

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

#pragma optimization_level 2

/* n1 helper: O2 island */
static inline void MtxMul_n1(float *out, const float *a, const float *b) {
    int k;
    int i;
    k = 0;
    for (i = k; i < 2; i++) {
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

#pragma optimization_level reset

void n1_wrap(SelfView *self) {
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
    MtxMul_n1(s.mOut, s.mA, s.mB);
    Consume(self->movement, s.mA);
}

#pragma exceptions reset

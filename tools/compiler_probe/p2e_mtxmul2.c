/* Phase 2e probe: what does the OPTIMIZED CALLEE of a MtxMul(out,a,b) helper
 * look like standalone, with explicit row locals (a0..a3)? Target evidence:
 * a-row loads CSEd into f7/f5/f3/f1 (source row locals), b loads fresh per
 * product (param, aliasing), out stores NEVER SR'd (slwi+stfsx each), k
 * integer web kept, dead i counter kept with `mr` init.
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

/* s1: standalone helper, row locals */
void s1_standalone(float *out, const float *a, const float *b) {
    int k;
    int i;
    float a0, a1, a2, a3;
    for (i = 0, k = i; i < 2; i++) {
        a0 = a[0];
        a1 = a[1];
        a2 = a[2];
        a3 = a[3];
        out[k] = a0 * b[0] + a1 * b[4] + a2 * b[8] + a3 * b[12];
        out[k + 1] = a0 * b[1] + a1 * b[5] + a2 * b[9] + a3 * b[13];
        out[k + 2] = a0 * b[2] + a1 * b[6] + a2 * b[10] + a3 * b[14];
        out[k + 3] = a0 * b[3] + a1 * b[7] + a2 * b[11] + a3 * b[15];
        k += 4;
        a0 = a[4];
        a1 = a[5];
        a2 = a[6];
        a3 = a[7];
        out[k] = a0 * b[0] + a1 * b[4] + a2 * b[8] + a3 * b[12];
        out[k + 1] = a0 * b[1] + a1 * b[5] + a2 * b[9] + a3 * b[13];
        out[k + 2] = a0 * b[2] + a1 * b[6] + a2 * b[10] + a3 * b[14];
        out[k + 3] = a0 * b[3] + a1 * b[7] + a2 * b[11] + a3 * b[15];
        k += 4;
        a += 8;
    }
}

/* s2: identical body as static inline + wrapper (splice shape) */
static inline void MtxMul_s2(float *out, const float *a, const float *b) {
    int k;
    int i;
    float a0, a1, a2, a3;
    for (i = 0, k = i; i < 2; i++) {
        a0 = a[0];
        a1 = a[1];
        a2 = a[2];
        a3 = a[3];
        out[k] = a0 * b[0] + a1 * b[4] + a2 * b[8] + a3 * b[12];
        out[k + 1] = a0 * b[1] + a1 * b[5] + a2 * b[9] + a3 * b[13];
        out[k + 2] = a0 * b[2] + a1 * b[6] + a2 * b[10] + a3 * b[14];
        out[k + 3] = a0 * b[3] + a1 * b[7] + a2 * b[11] + a3 * b[15];
        k += 4;
        a0 = a[4];
        a1 = a[5];
        a2 = a[6];
        a3 = a[7];
        out[k] = a0 * b[0] + a1 * b[4] + a2 * b[8] + a3 * b[12];
        out[k + 1] = a0 * b[1] + a1 * b[5] + a2 * b[9] + a3 * b[13];
        out[k + 2] = a0 * b[2] + a1 * b[6] + a2 * b[10] + a3 * b[14];
        out[k + 3] = a0 * b[3] + a1 * b[7] + a2 * b[11] + a3 * b[15];
        k += 4;
        a += 8;
    }
}

void s2_wrap(SelfView *self) {
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
    MtxMul_s2(s.mOut, s.mA, s.mB);
    Consume(self->movement, s.mA);
}

#pragma exceptions reset

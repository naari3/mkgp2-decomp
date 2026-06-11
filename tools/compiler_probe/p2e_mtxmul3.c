/* Phase 2e probe: mtx loop counter survival via opaque init.
 * Target (MainUpdate 0x8004DA44): i init `mr r4,r5` (copy from k), test was
 * presumably on i; hypothesis: the spliced copy hides i's init value from the
 * early up->down loop rewrite, so i stays live (cmp) until late ctr
 * conversion, which orphans init+addi without a DCE rerun.
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

/* m4: helper; k = 0; i = k; test on i; row locals + accumulator chains */
static inline void MtxMul_m4(float *out, const float *a, const float *b) {
    int k;
    int i;
    float a0, a1, a2, a3;
    float f;
    k = 0;
    for (i = k; i < 2; i++) {
        a0 = a[0];
        a1 = a[1];
        a2 = a[2];
        a3 = a[3];
        f = a0 * b[0];
        f += a1 * b[4];
        f += a2 * b[8];
        f += a3 * b[12];
        out[k] = f;
        f = a0 * b[1];
        f += a1 * b[5];
        f += a2 * b[9];
        f += a3 * b[13];
        out[k + 1] = f;
        f = a0 * b[2];
        f += a1 * b[6];
        f += a2 * b[10];
        f += a3 * b[14];
        out[k + 2] = f;
        f = a0 * b[3];
        f += a1 * b[7];
        f += a2 * b[11];
        f += a3 * b[15];
        out[k + 3] = f;
        k += 4;
        a0 = a[4];
        a1 = a[5];
        a2 = a[6];
        a3 = a[7];
        f = a0 * b[0];
        f += a1 * b[4];
        f += a2 * b[8];
        f += a3 * b[12];
        out[k] = f;
        f = a0 * b[1];
        f += a1 * b[5];
        f += a2 * b[9];
        f += a3 * b[13];
        out[k + 1] = f;
        f = a0 * b[2];
        f += a1 * b[6];
        f += a2 * b[10];
        f += a3 * b[14];
        out[k + 2] = f;
        f = a0 * b[3];
        f += a1 * b[7];
        f += a2 * b[11];
        f += a3 * b[15];
        out[k + 3] = f;
        k += 4;
        a += 8;
    }
}

void m4_wrap(SelfView *self) {
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
    MtxMul_m4(s.mOut, s.mA, s.mB);
    Consume(self->movement, s.mA);
}

#pragma exceptions reset

/* fp-scratch register NUMBERING probes (Phase 2a).
 * Target rule under test: simultaneously-live scratch fp webs are numbered
 * DESCENDING (later-first-use -> lower reg); CW 1.3.2 numbers ASCENDING by
 * def order. Each fn below is classified independently:
 *   load-block offset direction (a/d/m) + load-block register direction.
 * TARGET signature for the *_asc fns: offsets ascending, regs DESCENDING.
 */

void sink(float *p);

/* primary minimal repro: 8 temps loaded then stored (PerFrameStep rows 36-59 shape) */
void c8_asc(float *dst, float *src) {
    float t0, t1, t2, t3, t4, t5, t6, t7;
    t0 = src[0];
    t1 = src[1];
    t2 = src[2];
    t3 = src[3];
    t4 = src[4];
    t5 = src[5];
    t6 = src[6];
    t7 = src[7];
    dst[0] = t0;
    dst[1] = t1;
    dst[2] = t2;
    dst[3] = t3;
    dst[4] = t4;
    dst[5] = t5;
    dst[6] = t6;
    dst[7] = t7;
}

/* reverse def order, same use order */
void c8_desc(float *dst, float *src) {
    float t0, t1, t2, t3, t4, t5, t6, t7;
    t7 = src[7];
    t6 = src[6];
    t5 = src[5];
    t4 = src[4];
    t3 = src[3];
    t2 = src[2];
    t1 = src[1];
    t0 = src[0];
    dst[0] = t0;
    dst[1] = t1;
    dst[2] = t2;
    dst[3] = t3;
    dst[4] = t4;
    dst[5] = t5;
    dst[6] = t6;
    dst[7] = t7;
}

/* ascending defs, reversed use order */
void c8_revuse(float *dst, float *src) {
    float t0, t1, t2, t3, t4, t5, t6, t7;
    t0 = src[0];
    t1 = src[1];
    t2 = src[2];
    t3 = src[3];
    t4 = src[4];
    t5 = src[5];
    t6 = src[6];
    t7 = src[7];
    dst[7] = t7;
    dst[6] = t6;
    dst[5] = t5;
    dst[4] = t4;
    dst[3] = t3;
    dst[2] = t2;
    dst[1] = t1;
    dst[0] = t0;
}

/* temps as array elements (SROA path) */
void c8_arr(float *dst, float *src) {
    float t[8];
    t[0] = src[0];
    t[1] = src[1];
    t[2] = src[2];
    t[3] = src[3];
    t[4] = src[4];
    t[5] = src[5];
    t[6] = src[6];
    t[7] = src[7];
    dst[0] = t[0];
    dst[1] = t[1];
    dst[2] = t[2];
    dst[3] = t[3];
    dst[4] = t[4];
    dst[5] = t[5];
    dst[6] = t[6];
    dst[7] = t[7];
}

/* register storage class */
void c8_reg(float *dst, float *src) {
    register float t0, t1, t2, t3, t4, t5, t6, t7;
    t0 = src[0];
    t1 = src[1];
    t2 = src[2];
    t3 = src[3];
    t4 = src[4];
    t5 = src[5];
    t6 = src[6];
    t7 = src[7];
    dst[0] = t0;
    dst[1] = t1;
    dst[2] = t2;
    dst[3] = t3;
    dst[4] = t4;
    dst[5] = t5;
    dst[6] = t6;
    dst[7] = t7;
}

/* web-count thresholds */
void c2_asc(float *dst, float *src) {
    float t0, t1;
    t0 = src[0];
    t1 = src[1];
    dst[0] = t0;
    dst[1] = t1;
}

void c4_asc(float *dst, float *src) {
    float t0, t1, t2, t3;
    t0 = src[0];
    t1 = src[1];
    t2 = src[2];
    t3 = src[3];
    dst[0] = t0;
    dst[1] = t1;
    dst[2] = t2;
    dst[3] = t3;
}

void c6_asc(float *dst, float *src) {
    float t0, t1, t2, t3, t4, t5;
    t0 = src[0];
    t1 = src[1];
    t2 = src[2];
    t3 = src[3];
    t4 = src[4];
    t5 = src[5];
    dst[0] = t0;
    dst[1] = t1;
    dst[2] = t2;
    dst[3] = t3;
    dst[4] = t4;
    dst[5] = t5;
}

/* PerFrameStep full shape: escaping local struct + 8-deep software pipeline
 * over a 16-float copy. Ascending defs (= target emission order). */
typedef struct M16 {
    float m[16];
} M16;

void c16_pipe(float *src) {
    M16 x;
    float t0, t1, t2, t3, t4, t5, t6, t7;
    t0 = src[0];
    t1 = src[1];
    t2 = src[2];
    t3 = src[3];
    t4 = src[4];
    t5 = src[5];
    t6 = src[6];
    t7 = src[7];
    x.m[0] = t0;
    t0 = src[8];
    x.m[1] = t1;
    t1 = src[9];
    x.m[2] = t2;
    t2 = src[10];
    x.m[3] = t3;
    t3 = src[11];
    x.m[4] = t4;
    t4 = src[12];
    x.m[5] = t5;
    t5 = src[13];
    x.m[6] = t6;
    t6 = src[14];
    x.m[7] = t7;
    t7 = src[15];
    x.m[8] = t0;
    x.m[9] = t1;
    x.m[10] = t2;
    x.m[11] = t3;
    x.m[12] = t4;
    x.m[13] = t5;
    x.m[14] = t6;
    x.m[15] = t7;
    sink(x.m);
}

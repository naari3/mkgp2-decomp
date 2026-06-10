void sink(float *p);
typedef struct F16 { float m[16]; } F16;
typedef struct MV { char pad[0x58]; float mtx[16]; } MV;

/* two 8-copy halves; does the scheduler interleave half-2 loads with
 * half-1 stores (target rows 45-59 alternation)? */
void s16_split(MV *mv) {
    F16 x;
    x.m[0] = mv->mtx[0];
    x.m[1] = mv->mtx[1];
    x.m[2] = mv->mtx[2];
    x.m[3] = mv->mtx[3];
    x.m[4] = mv->mtx[4];
    x.m[5] = mv->mtx[5];
    x.m[6] = mv->mtx[6];
    x.m[7] = mv->mtx[7];
    x.m[8] = mv->mtx[8];
    x.m[9] = mv->mtx[9];
    x.m[10] = mv->mtx[10];
    x.m[11] = mv->mtx[11];
    x.m[12] = mv->mtx[12];
    x.m[13] = mv->mtx[13];
    x.m[14] = mv->mtx[14];
    x.m[15] = mv->mtx[15];
    sink(x.m);
}

/* same but with f8..f31 pressure: doubles live across the block */
extern double gA, gB, gC2, gD, gE, gF, gG, gH;
double s16_pressure(MV *mv) {
    F16 x;
    double a = gA, b = gB, c = gC2, d = gD, e = gE, f = gF, g = gG, h = gH;
    x.m[0] = mv->mtx[0];
    x.m[1] = mv->mtx[1];
    x.m[2] = mv->mtx[2];
    x.m[3] = mv->mtx[3];
    x.m[4] = mv->mtx[4];
    x.m[5] = mv->mtx[5];
    x.m[6] = mv->mtx[6];
    x.m[7] = mv->mtx[7];
    x.m[8] = mv->mtx[8];
    x.m[9] = mv->mtx[9];
    x.m[10] = mv->mtx[10];
    x.m[11] = mv->mtx[11];
    x.m[12] = mv->mtx[12];
    x.m[13] = mv->mtx[13];
    x.m[14] = mv->mtx[14];
    x.m[15] = mv->mtx[15];
    sink(x.m);
    return a + b + c + d + e + f + g + h;
}

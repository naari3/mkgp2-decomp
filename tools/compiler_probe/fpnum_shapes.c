void sink(float *p);
extern float gC;

typedef struct MV { char pad[0x17c]; float velX, velY, velZ; } MV;
typedef struct V3 { float x, y, z; } V3;
typedef struct G5 { V3 nb, na, vb, pos, scaled; } G5;

/* na-block shape, appendix style: NAMED temps ax/ay/az (current 97.87% form) */
void na_named(MV *mv) {
    G5 G;
    float zero, ax, ay, az;
    zero = gC;
    ax = mv->velX;
    ay = mv->velY;
    az = mv->velZ;
    G.na.x = ax;
    G.na.y = ay;
    G.na.z = az;
    G.na.y = zero;
    sink(&G.nb.x);
}

/* na-block shape, direct member-to-member (no named value temps) */
void na_direct(MV *mv) {
    G5 G;
    float zero;
    zero = gC;
    G.na.x = mv->velX;
    G.na.y = mv->velY;
    G.na.z = mv->velZ;
    G.na.y = zero;
    sink(&G.nb.x);
}

/* 2-web tie-break: member load vs const load, both used after */
void tie_named(MV *mv, float *out) {
    float vx, c;
    vx = mv->velX;
    c = gC;
    out[0] = vx * vx;
    out[1] = c * c;
    out[2] = vx * c;
}

void tie_direct(MV *mv, float *out) {
    out[0] = mv->velX * mv->velX;
    out[1] = gC * gC;
    out[2] = mv->velX * gC;
}

/* 8-copy direct with later read-back across the call (PerFrameStep reads m[4..6]) */
typedef struct F16 { float m[16]; } F16;
float s8_readback(const F16 *src) {
    F16 x;
    x.m[0] = src->m[0];
    x.m[1] = src->m[1];
    x.m[2] = src->m[2];
    x.m[3] = src->m[3];
    x.m[4] = src->m[4];
    x.m[5] = src->m[5];
    x.m[6] = src->m[6];
    x.m[7] = src->m[7];
    sink(x.m);
    return x.m[4] * src->m[4] + x.m[5] * src->m[5] + x.m[6] * src->m[6];
}

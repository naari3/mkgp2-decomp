void sink(float *p);

typedef struct F16 { float m[16]; } F16;

/* 16 direct member copies, no named temps */
void s16_member(const F16 *src) {
    F16 x;
    x.m[0] = src->m[0];
    x.m[1] = src->m[1];
    x.m[2] = src->m[2];
    x.m[3] = src->m[3];
    x.m[4] = src->m[4];
    x.m[5] = src->m[5];
    x.m[6] = src->m[6];
    x.m[7] = src->m[7];
    x.m[8] = src->m[8];
    x.m[9] = src->m[9];
    x.m[10] = src->m[10];
    x.m[11] = src->m[11];
    x.m[12] = src->m[12];
    x.m[13] = src->m[13];
    x.m[14] = src->m[14];
    x.m[15] = src->m[15];
    sink(x.m);
}

/* same but src is a struct member pointer chain like the real fn (mv->mtx) */
typedef struct MV { char pad[0x58]; float mtx[16]; } MV;
typedef struct SELF { char pad[0x28]; MV *movement; } SELF;

void s16_member_chain(SELF *self) {
    F16 x;
    MV *mv = self->movement;
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

/* struct-copy lowering probes: does CW's built-in block-copy expansion
 * number fp scratch webs DESCENDING (target shape)? */

void sink(float *p);

typedef struct F16 {
    float m[16];
} F16;

typedef struct F8 {
    float m[8];
} F8;

typedef struct V3 {
    float x, y, z;
} V3;

/* 64-byte struct assignment, both pointers */
void s16_p2p(F16 *dst, const F16 *src) {
    *dst = *src;
}

/* 64-byte struct assignment into escaping local (PerFrameStep shape) */
void s16_local(const F16 *src) {
    F16 x;
    x = *src;
    sink(x.m);
}

/* 32-byte struct assignment into escaping local */
void s8_local(const F8 *src) {
    F8 x;
    x = *src;
    sink(x.m);
}

/* 12-byte Vec3 copy (known canonical lwz/stw word copy under defaults) */
void s3_local(const V3 *src) {
    V3 x;
    x = *src;
    sink(&x.x);
}

/* member-wise float copy through a struct (no block assign) */
void s8_member(const F8 *src) {
    F8 x;
    x.m[0] = src->m[0];
    x.m[1] = src->m[1];
    x.m[2] = src->m[2];
    x.m[3] = src->m[3];
    x.m[4] = src->m[4];
    x.m[5] = src->m[5];
    x.m[6] = src->m[6];
    x.m[7] = src->m[7];
    sink(x.m);
}

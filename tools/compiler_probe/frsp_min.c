/* frsp_min.c -- Phase 2b: class-2 "frsp store-forward interleave" probes.
 *
 * Target shape (ItemEffect_Dispatch 0x80050410 kind14 branch, CW 1.3.2 -O4,p):
 *   - 16x raw lfs+stfs matrix copy into a stack scratch struct (NO frsp
 *     feeding the stfs; the stored registers are the raw lfs results)
 *   - the 6 consumed values are READ BACK from the scratch slots:
 *     5 of them (m0,m1,m12,m13,m14) appear as `frsp fN, fM` register copies
 *     where fM is the still-live lfs result (store-to-load forwarding with
 *     conservative re-rounding), and 1 (m2) is a REAL stack reload because
 *     its register (f7) was reused for the posZ load before the use point.
 *   - the d[] stores (fsubs results) are dead stores, never read back.
 *
 * Plain-C ledger (docs/notes/cw132-frsp-store-forward-negative-probes.md):
 * 6 forms negative. This file probes the C++ axis (compile with -lang=c++)
 * plus two C-compatible escape forms the ledger did not cover (pointer-param
 * inline helper, Vec-pointer dot).
 *
 * Classifier: probe_frsp.py  Runner: run_frsp_axis*.py
 */

#ifdef __cplusplus
#define XC extern "C"
#else
#define XC
#endif

typedef struct KartMov {
    unsigned char pad[0x58];
    float transform[16]; /* +0x58 */
} KartMov;

typedef struct ItemObj {
    unsigned char pad[0xa0];
    float posX, posY, posZ; /* +0xa0 */
} ItemObj;

typedef struct Lane {
    unsigned char pad[0x10];
    int mode;    /* +0x10 */
    float blend; /* +0x14 */
} Lane;

typedef struct Scratch {
    float dir[3]; /* frame +0x8 in target */
    float d[3];   /* +0x14 */
    float mtx[16];/* +0x20 */
} Scratch;

extern float kZero; /* lbl_806D26EC */
extern float kNeg;  /* lbl_806D26E4 */
extern float kPos;  /* lbl_806D26FC */

#define COPY16(d, s) \
    d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = s[3]; \
    d[4] = s[4]; d[5] = s[5]; d[6] = s[6]; d[7] = s[7]; \
    d[8] = s[8]; d[9] = s[9]; d[10] = s[10]; d[11] = s[11]; \
    d[12] = s[12]; d[13] = s[13]; d[14] = s[14]; d[15] = s[15];

/* consumed values are named locals initialized from scratch READ-BACKS;
 * d/dir stores are dead (matches target asm: d slots never reloaded). */
#define CONSUME_RB(lane, obj, s) \
    { \
        float dir0 = s.mtx[0]; \
        float dir1 = s.mtx[1]; \
        float dir2 = s.mtx[2]; \
        float dx = (obj)->posX - s.mtx[12]; \
        float dy = (obj)->posY - s.mtx[13]; \
        float dz = (obj)->posZ - s.mtx[14]; \
        float dot; \
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz; \
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2; \
        dot = (dx * dir0 + dy * dir1) + dz * dir2; \
        if (dot < kZero) { (lane)->blend = kNeg; } else { (lane)->blend = kPos; } \
    }

/* ---- f0: control (= plain-C ledger probe 1). Expect DSE / raw. ---- */
XC void f0_plain(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    CONSUME_RB(lane, obj, s)
}

/* ---- f7: C-compatible, pointer-param static inline helpers (untried in
 * plain-C ledger; ledger probe 5 used float params, not a struct pointer) */
static void sc_copy(Scratch *s, const float *src) {
    COPY16(s->mtx, src)
}
static float sc_dot(Scratch *s, const ItemObj *obj) {
    float dir0 = s->mtx[0];
    float dir1 = s->mtx[1];
    float dir2 = s->mtx[2];
    float dx = obj->posX - s->mtx[12];
    float dy = obj->posY - s->mtx[13];
    float dz = obj->posZ - s->mtx[14];
    s->d[0] = dx; s->d[1] = dy; s->d[2] = dz;
    s->dir[0] = dir0; s->dir[1] = dir1; s->dir[2] = dir2;
    return (dx * dir0 + dy * dir1) + dz * dir2;
}
XC void f7_ptrhelper(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    sc_copy(&s, mov->transform);
    if (sc_dot(&s, obj) < kZero) {
        lane->blend = kNeg;
    } else {
        lane->blend = kPos;
    }
}

/* ---- f12: C-compatible, Vec-pointer dot over the scratch arrays ---- */
typedef struct Vec3 { float x, y, z; } Vec3;
static float vec_dot(const Vec3 *a, const Vec3 *b) {
    return (a->x * b->x + a->y * b->y) + a->z * b->z;
}
XC void f12_vecdot(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    s.dir[0] = s.mtx[0];
    s.dir[1] = s.mtx[1];
    s.dir[2] = s.mtx[2];
    s.d[0] = obj->posX - s.mtx[12];
    s.d[1] = obj->posY - s.mtx[13];
    s.d[2] = obj->posZ - s.mtx[14];
    if (vec_dot((Vec3 *)s.d, (Vec3 *)s.dir) < kZero) {
        lane->blend = kNeg;
    } else {
        lane->blend = kPos;
    }
}

/* ---- f15: pun read-back inline (no helper) -- bisect helper boundary ---- */
XC void f15_inlinepun(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    s.dir[0] = s.mtx[0];
    s.dir[1] = s.mtx[1];
    s.dir[2] = s.mtx[2];
    s.d[0] = obj->posX - s.mtx[12];
    s.d[1] = obj->posY - s.mtx[13];
    s.d[2] = obj->posZ - s.mtx[14];
    {
        Vec3 *a = (Vec3 *)s.d;
        Vec3 *b = (Vec3 *)s.dir;
        float dot = (a->x * b->x + a->y * b->y) + a->z * b->z;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f16: same-type float* read-back -- does the pun matter? ---- */
XC void f16_floatptr(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    s.dir[0] = s.mtx[0];
    s.dir[1] = s.mtx[1];
    s.dir[2] = s.mtx[2];
    s.d[0] = obj->posX - s.mtx[12];
    s.d[1] = obj->posY - s.mtx[13];
    s.d[2] = obj->posZ - s.mtx[14];
    {
        float *a = s.d;
        float *b = s.dir;
        float dot = (a[0] * b[0] + a[1] * b[1]) + a[2] * b[2];
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f17: FULL target shape -- consumed mtx values read back through
 * punned Vec3 views (axis row 0, translation row 3), separate-statement
 * dot temps (target has fmuls/fadds, no fmadds). Expect ~6 frsp. ---- */
XC void f17_fullpun(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        Vec3 *axis = (Vec3 *)&s.mtx[0];
        Vec3 *trans = (Vec3 *)&s.mtx[12];
        float dir0 = axis->x;
        float dir1 = axis->y;
        float dir2 = axis->z;
        float dx = obj->posX - trans->x;
        float dy = obj->posY - trans->y;
        float dz = obj->posZ - trans->z;
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f18: write punned, read direct (inverse direction) ---- */
XC void f18_punwrite(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    {
        Vec3 *axis = (Vec3 *)&s.mtx[0];
        Vec3 *trans = (Vec3 *)&s.mtx[12];
        axis->x = t[0]; axis->y = t[1]; axis->z = t[2]; s.mtx[3] = t[3];
        s.mtx[4] = t[4]; s.mtx[5] = t[5]; s.mtx[6] = t[6]; s.mtx[7] = t[7];
        s.mtx[8] = t[8]; s.mtx[9] = t[9]; s.mtx[10] = t[10]; s.mtx[11] = t[11];
        trans->x = t[12]; trans->y = t[13]; trans->z = t[14]; s.mtx[15] = t[15];
    }
    CONSUME_RB(lane, obj, s)
}

/* ---- f19: union pun -- float array written, Vec3 view read ---- */
typedef union ScratchU {
    float f[22];
    struct { Vec3 dir; Vec3 d; Vec3 axis; float pad[6]; Vec3 trans; float m15; } v;
} ScratchU;
XC void f19_unionpun(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchU s;
    float *t = mov->transform;
    s.f[6] = t[0];  s.f[7] = t[1];  s.f[8] = t[2];  s.f[9] = t[3];
    s.f[10] = t[4]; s.f[11] = t[5]; s.f[12] = t[6]; s.f[13] = t[7];
    s.f[14] = t[8]; s.f[15] = t[9]; s.f[16] = t[10]; s.f[17] = t[11];
    s.f[18] = t[12]; s.f[19] = t[13]; s.f[20] = t[14]; s.f[21] = t[15];
    {
        float dir0 = s.v.axis.x;
        float dir1 = s.v.axis.y;
        float dir2 = s.v.axis.z;
        float dx = obj->posX - s.v.trans.x;
        float dy = obj->posY - s.v.trans.y;
        float dz = obj->posZ - s.v.trans.z;
        float t0, t1, sum, t2, dot;
        s.f[3] = dx; s.f[4] = dy; s.f[5] = dz;
        s.f[0] = dir0; s.f[1] = dir1; s.f[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f20: Mtx (float[4][4]) scratch, Vec3 row views -- SDK-idiomatic ---- */
typedef float Mtx44[4][4];
XC void f20_mtx44(Lane *lane, ItemObj *obj, KartMov *mov) {
    struct { float dir[3]; float d[3]; Mtx44 m; } s;
    float *t = mov->transform;
    s.m[0][0] = t[0];  s.m[0][1] = t[1];  s.m[0][2] = t[2];  s.m[0][3] = t[3];
    s.m[1][0] = t[4];  s.m[1][1] = t[5];  s.m[1][2] = t[6];  s.m[1][3] = t[7];
    s.m[2][0] = t[8];  s.m[2][1] = t[9];  s.m[2][2] = t[10]; s.m[2][3] = t[11];
    s.m[3][0] = t[12]; s.m[3][1] = t[13]; s.m[3][2] = t[14]; s.m[3][3] = t[15];
    {
        Vec3 *axis = (Vec3 *)s.m[0];
        Vec3 *trans = (Vec3 *)s.m[3];
        float dir0 = axis->x;
        float dir1 = axis->y;
        float dir2 = axis->z;
        float dx = obj->posX - trans->x;
        float dy = obj->posY - trans->y;
        float dz = obj->posZ - trans->z;
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f22: f15 mechanics + named-local reads (expression theory test) ---- */
XC void f22_punlocals(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    s.dir[0] = s.mtx[0];
    s.dir[1] = s.mtx[1];
    s.dir[2] = s.mtx[2];
    s.d[0] = obj->posX - s.mtx[12];
    s.d[1] = obj->posY - s.mtx[13];
    s.d[2] = obj->posZ - s.mtx[14];
    {
        Vec3 *a = (Vec3 *)s.d;
        Vec3 *b = (Vec3 *)s.dir;
        float ax = a->x;
        float ay = a->y;
        float az = a->z;
        float bx = b->x;
        float by = b->y;
        float bz = b->z;
        float dot = (ax * bx + ay * by) + az * bz;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f23: f17 shape but pointers formed by array DECAY (+offset) ---- */
XC void f23_decaypun(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        Vec3 *axis = (Vec3 *)(s.mtx);
        Vec3 *trans = (Vec3 *)(s.mtx + 12);
        float dir0 = axis->x;
        float dir1 = axis->y;
        float dir2 = axis->z;
        float dx = obj->posX - trans->x;
        float dy = obj->posY - trans->y;
        float dz = obj->posZ - trans->z;
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f24: f15 shape but pointers formed by &s.d[0] (address-of) ---- */
XC void f24_addrofpun(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    s.dir[0] = s.mtx[0];
    s.dir[1] = s.mtx[1];
    s.dir[2] = s.mtx[2];
    s.d[0] = obj->posX - s.mtx[12];
    s.d[1] = obj->posY - s.mtx[13];
    s.d[2] = obj->posZ - s.mtx[14];
    {
        Vec3 *a = (Vec3 *)&s.d[0];
        Vec3 *b = (Vec3 *)&s.dir[0];
        float dot = (a->x * b->x + a->y * b->y) + a->z * b->z;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f25: full-target recipe attempt: all 6 consumed reads through
 * decay-formed Vec3 views of s.mtx ---- */
XC void f25_fullrecipe(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        Vec3 *axis = (Vec3 *)(s.mtx);
        Vec3 *trans = (Vec3 *)(s.mtx + 12);
        float dir0 = axis->x;
        float dir1 = axis->y;
        float dir2 = axis->z;
        float dx = obj->posX - trans->x;
        float dy = obj->posY - trans->y;
        float dz = obj->posZ - trans->z;
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f26: Vec3 LOCALS initialized by struct-assign from punned mtx views.
 * Theory: struct-copy loads bypass scalar copy-prop -> backend frsp-forward,
 * locals SROA'd to the frsp regs (target stores frsp'd regs to dir slots). */
XC void f26_vec3assign(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        Vec3 av = *(Vec3 *)(s.mtx);
        Vec3 tv = *(Vec3 *)(s.mtx + 12);
        float dx = obj->posX - tv.x;
        float dy = obj->posY - tv.y;
        float dz = obj->posZ - tv.z;
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = av.x; s.dir[1] = av.y; s.dir[2] = av.z;
        t0 = dx * av.x;
        t1 = dy * av.y;
        sum = t0 + t1;
        t2 = dz * av.z;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f27: struct-assign directly INTO the dir slots, then read them ---- */
XC void f27_vec3slots(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        Vec3 tv;
        *(Vec3 *)s.dir = *(Vec3 *)(s.mtx);
        tv = *(Vec3 *)(s.mtx + 12);
        {
            float dx = obj->posX - tv.x;
            float dy = obj->posY - tv.y;
            float dz = obj->posZ - tv.z;
            float t0, t1, sum, t2, dot;
            s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
            t0 = dx * s.dir[0];
            t1 = dy * s.dir[1];
            sum = t0 + t1;
            t2 = dz * s.dir[2];
            dot = t2 + sum;
            if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
        }
    }
}

/* ---- f28: f24 mechanics but pointers into the MTX slots (slot identity
 * test: is it dir/d-slot specific or any embedded pun read?) ---- */
XC void f28_mtxptr(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        Vec3 *axis = (Vec3 *)&s.mtx[0];
        Vec3 *trans = (Vec3 *)&s.mtx[12];
        float dx = obj->posX - trans->x;
        float dy = obj->posY - trans->y;
        float dz = obj->posZ - trans->z;
        float dot = (dx * axis->x + dy * axis->y) + dz * axis->z;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = axis->x; s.dir[1] = axis->y; s.dir[2] = axis->z;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f29: copy block written through a POINTER variable (inlined
 * MTXCopy-style dst[i]=src[i]), consumed via DIRECT member read-backs ---- */
XC void f29_ptrwrite(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    float *dst = s.mtx;
    COPY16(dst, t)
    CONSUME_RB(lane, obj, s)
}

/* ---- f30: pointer write + pointer read (different pointer vars) ---- */
XC void f30_ptrboth(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    float *dst = s.mtx;
    COPY16(dst, t)
    {
        Vec3 *axis = (Vec3 *)&s.mtx[0];
        Vec3 *trans = (Vec3 *)&s.mtx[12];
        float dir0 = axis->x;
        float dir1 = axis->y;
        float dir2 = axis->z;
        float dx = obj->posX - trans->x;
        float dy = obj->posY - trans->y;
        float dz = obj->posZ - trans->z;
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f31: copy via inlined helper (pointer param), direct reads ---- */
static void mtx_copy16(float *d, const float *src) {
    COPY16(d, src)
}
XC void f31_helpercopy(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    mtx_copy16(s.mtx, mov->transform);
    CONSUME_RB(lane, obj, s)
}

/* ---- f32: manual copy + LOOP consume (variable-index read-backs) ---- */
XC void f32_loopconsume(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    int i;
    COPY16(s.mtx, t)
    for (i = 0; i < 3; i++) {
        s.dir[i] = s.mtx[i];
        s.d[i] = (&obj->posX)[i] - s.mtx[12 + i];
    }
    {
        float t0 = s.d[0] * s.dir[0];
        float t1 = s.d[1] * s.dir[1];
        float sum = t0 + t1;
        float t2 = s.d[2] * s.dir[2];
        float dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f33: LOOP copy + LOOP consume ---- */
XC void f33_loopboth(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    int i;
    for (i = 0; i < 16; i++) {
        s.mtx[i] = t[i];
    }
    for (i = 0; i < 3; i++) {
        s.dir[i] = s.mtx[i];
        s.d[i] = (&obj->posX)[i] - s.mtx[12 + i];
    }
    {
        float t0 = s.d[0] * s.dir[0];
        float t1 = s.d[1] * s.dir[1];
        float sum = t0 + t1;
        float t2 = s.d[2] * s.dir[2];
        float dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f34: LOOP copy + direct consume ---- */
XC void f34_loopcopy(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    int i;
    for (i = 0; i < 16; i++) {
        s.mtx[i] = t[i];
    }
    CONSUME_RB(lane, obj, s)
}

/* ---- f35: RECIPE form -- loop copy + separate-statement dot temps
 * (target has fmuls/fadds, not fmadds) ---- */
XC void f35_recipe(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    int i;
    for (i = 0; i < 16; i++) {
        s.mtx[i] = t[i];
    }
    {
        float dir0 = s.mtx[0];
        float dir1 = s.mtx[1];
        float dir2 = s.mtx[2];
        float dx = obj->posX - s.mtx[12];
        float dy = obj->posY - s.mtx[13];
        float dz = obj->posZ - s.mtx[14];
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f36: pointer-walk copy loop ---- */
XC void f36_ptrwalk(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *src = mov->transform;
    float *dst = s.mtx;
    int n;
    for (n = 0; n < 16; n++) {
        *dst++ = *src++;
    }
    CONSUME_RB(lane, obj, s)
}

/* ---- f37: loop copy via 2D Mtx-style [4][4] indices ---- */
XC void f37_loop2d(Lane *lane, ItemObj *obj, KartMov *mov) {
    struct { float dir[3]; float d[3]; float m[4][4]; } s;
    float (*src)[4] = (float (*)[4])mov->transform;
    int r, c;
    for (r = 0; r < 4; r++) {
        for (c = 0; c < 4; c++) {
            s.m[r][c] = src[r][c];
        }
    }
    {
        float dir0 = s.m[0][0];
        float dir1 = s.m[0][1];
        float dir2 = s.m[0][2];
        float dx = obj->posX - s.m[3][0];
        float dy = obj->posY - s.m[3][1];
        float dz = obj->posZ - s.m[3][2];
        float t0, t1, sum, t2, dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        t0 = dx * dir0;
        t1 = dy * dir1;
        sum = t0 + t1;
        t2 = dz * dir2;
        dot = t2 + sum;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

#ifdef __cplusplus
/* =================== C++-only forms =================== */

/* ---- f1: const reference param view of the source matrix ---- */
struct Mtx16R { float m[16]; };
static void copy_from_cref(Scratch &s, const Mtx16R &src) {
    COPY16(s.mtx, src.m)
}
XC void f1_constref(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    copy_from_cref(s, *(const Mtx16R *)mov->transform);
    CONSUME_RB(lane, obj, s)
}

/* ---- f2: read-backs through const float& locals ---- */
XC void f2_reflocal(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        const float &m0 = s.mtx[0];
        const float &m1 = s.mtx[1];
        const float &m2 = s.mtx[2];
        const float &m12 = s.mtx[12];
        const float &m13 = s.mtx[13];
        const float &m14 = s.mtx[14];
        float dx = obj->posX - m12;
        float dy = obj->posY - m13;
        float dz = obj->posZ - m14;
        float dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = m0; s.dir[1] = m1; s.dir[2] = m2;
        dot = (dx * m0 + dy * m1) + dz * m2;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f3: member functions (this-pointer escape of the scratch) ---- */
struct ScratchM {
    float dir[3];
    float d[3];
    float mtx[16];
    void copyFrom(const float *src) {
        COPY16(mtx, src)
    }
    float dot3(const ItemObj *obj) {
        float dir0 = mtx[0];
        float dir1 = mtx[1];
        float dir2 = mtx[2];
        float dx = obj->posX - mtx[12];
        float dy = obj->posY - mtx[13];
        float dz = obj->posZ - mtx[14];
        d[0] = dx; d[1] = dy; d[2] = dz;
        dir[0] = dir0; dir[1] = dir1; dir[2] = dir2;
        return (dx * dir0 + dy * dir1) + dz * dir2;
    }
};
XC void f3_member(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchM s;
    s.copyFrom(mov->transform);
    if (s.dot3(obj) < kZero) {
        lane->blend = kNeg;
    } else {
        lane->blend = kPos;
    }
}

/* ---- f4: reference-return accessor ---- */
struct ScratchA {
    float v[22]; /* dir@0, d@3, mtx@6 */
    float &at(int i) { return v[i]; }
};
XC void f4_accessor(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchA s;
    float *t = mov->transform;
    s.at(6) = t[0];  s.at(7) = t[1];  s.at(8) = t[2];  s.at(9) = t[3];
    s.at(10) = t[4]; s.at(11) = t[5]; s.at(12) = t[6]; s.at(13) = t[7];
    s.at(14) = t[8]; s.at(15) = t[9]; s.at(16) = t[10]; s.at(17) = t[11];
    s.at(18) = t[12]; s.at(19) = t[13]; s.at(20) = t[14]; s.at(21) = t[15];
    {
        float dir0 = s.at(6);
        float dir1 = s.at(7);
        float dir2 = s.at(8);
        float dx = obj->posX - s.at(18);
        float dy = obj->posY - s.at(19);
        float dz = obj->posZ - s.at(20);
        float dot;
        s.at(3) = dx; s.at(4) = dy; s.at(5) = dz;
        s.at(0) = dir0; s.at(1) = dir1; s.at(2) = dir2;
        dot = (dx * dir0 + dy * dir1) + dz * dir2;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f5: default operator= (memberwise) of a 16-float struct ---- */
struct Mtx16C { float m[16]; };
struct ScratchC {
    float dir[3];
    float d[3];
    Mtx16C mtx;
};
XC void f5_opassign(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchC s;
    s.mtx = *(const Mtx16C *)mov->transform;
    {
        float dir0 = s.mtx.m[0];
        float dir1 = s.mtx.m[1];
        float dir2 = s.mtx.m[2];
        float dx = obj->posX - s.mtx.m[12];
        float dy = obj->posY - s.mtx.m[13];
        float dz = obj->posZ - s.mtx.m[14];
        float dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        dot = (dx * dir0 + dy * dir1) + dz * dir2;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f9: copy constructor of a 16-float struct ---- */
XC void f9_copyctor(Lane *lane, ItemObj *obj, KartMov *mov) {
    Mtx16C local(*(const Mtx16C *)mov->transform);
    Scratch s;
    {
        float dir0 = local.m[0];
        float dir1 = local.m[1];
        float dir2 = local.m[2];
        float dx = obj->posX - local.m[12];
        float dy = obj->posY - local.m[13];
        float dz = obj->posZ - local.m[14];
        float dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        dot = (dx * dir0 + dy * dir1) + dz * dir2;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f6: non-const references aliasing the consumed slots ---- */
XC void f6_mutref(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    float *t = mov->transform;
    float &r0 = s.mtx[0];
    float &r1 = s.mtx[1];
    float &r2 = s.mtx[2];
    float &r12 = s.mtx[12];
    float &r13 = s.mtx[13];
    float &r14 = s.mtx[14];
    r0 = t[0]; r1 = t[1]; r2 = t[2]; s.mtx[3] = t[3];
    s.mtx[4] = t[4]; s.mtx[5] = t[5]; s.mtx[6] = t[6]; s.mtx[7] = t[7];
    s.mtx[8] = t[8]; s.mtx[9] = t[9]; s.mtx[10] = t[10]; s.mtx[11] = t[11];
    r12 = t[12]; r13 = t[13]; r14 = t[14]; s.mtx[15] = t[15];
    {
        float dir0 = r0;
        float dir1 = r1;
        float dir2 = r2;
        float dx = obj->posX - r12;
        float dy = obj->posY - r13;
        float dz = obj->posZ - r14;
        float dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        dot = (dx * dir0 + dy * dir1) + dz * dir2;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f8: float wrapper class with operator float() / operator= ---- */
class F32W {
public:
    float v;
    F32W &operator=(float f) { v = f; return *this; }
    operator float() const { return v; }
};
struct ScratchW {
    F32W dir[3];
    F32W d[3];
    F32W mtx[16];
};
XC void f8_wrapclass(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchW s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    {
        float dir0 = s.mtx[0];
        float dir1 = s.mtx[1];
        float dir2 = s.mtx[2];
        float dx = obj->posX - s.mtx[12];
        float dy = obj->posY - s.mtx[13];
        float dz = obj->posZ - s.mtx[14];
        float dot;
        s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
        s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
        dot = (dx * dir0 + dy * dir1) + dz * dir2;
        if (dot < kZero) { lane->blend = kNeg; } else { lane->blend = kPos; }
    }
}

/* ---- f11: reference-param static helpers (C++ twin of f7) ---- */
static void rcopy(Scratch &s, const float *src) {
    COPY16(s.mtx, src)
}
static float rdot(Scratch &s, const ItemObj *obj) {
    float dir0 = s.mtx[0];
    float dir1 = s.mtx[1];
    float dir2 = s.mtx[2];
    float dx = obj->posX - s.mtx[12];
    float dy = obj->posY - s.mtx[13];
    float dz = obj->posZ - s.mtx[14];
    s.d[0] = dx; s.d[1] = dy; s.d[2] = dz;
    s.dir[0] = dir0; s.dir[1] = dir1; s.dir[2] = dir2;
    return (dx * dir0 + dy * dir1) + dz * dir2;
}
XC void f11_refhelper(Lane *lane, ItemObj *obj, KartMov *mov) {
    Scratch s;
    rcopy(s, mov->transform);
    if (rdot(s, obj) < kZero) {
        lane->blend = kNeg;
    } else {
        lane->blend = kPos;
    }
}

/* ---- f13: scratch with an EMPTY inline destructor (EH scope, no call) ---- */
struct ScratchD {
    float dir[3];
    float d[3];
    float mtx[16];
    ~ScratchD() {}
};
XC void f13_inldtor(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchD s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    CONSUME_RB(lane, obj, s)
}

/* ---- f14: scratch with an OPAQUE (extern) destructor ----
 * Diagnostic only: the dtor call itself is absent in the target, but if this
 * form yields frsp store-forwarding it confirms the liveness mechanism. */
struct ScratchX {
    float dir[3];
    float d[3];
    float mtx[16];
    ~ScratchX();
};
XC void f14_extdtor(Lane *lane, ItemObj *obj, KartMov *mov) {
    ScratchX s;
    float *t = mov->transform;
    COPY16(s.mtx, t)
    CONSUME_RB(lane, obj, s)
}

#endif /* __cplusplus */

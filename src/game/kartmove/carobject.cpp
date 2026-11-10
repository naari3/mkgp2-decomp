/* Car object / speed curve code, .text 0x8019E1A8..0x8019F5BC.
 * This span's extabindex is not in ascending order, so dtk can't split it
 * further; all functions are defined, with remaining mismatches kept NonMatching. */

typedef struct { float v; float k; } CurveKey;
typedef struct { float k; float v; } CurveKeyKV;

extern "C" {
extern void MemoryManager_TimedFree(void *p);
int fn_8019F1C4(CurveKeyKV *keys, int n, float t, float *out);
int fn_8019F3C0(CurveKey *keys, int n, float t, float *out);
}

#include "game/kartmove/carobject_init_private.h"

CarObject::~CarObject() {}
CarTrivial::~CarTrivial() {}

extern "C" {
extern double cos(double);
extern double sin(double);
extern int g_gameMode;
extern float lbl_804963F8[];
extern const float lbl_806D96D0, lbl_806D96D4;
extern float lbl_806D971C, lbl_806D97CC, lbl_806D97D0, lbl_806D973C, lbl_806D9728;
extern double lbl_806D96F0;
extern unsigned char Terrain_GetGroundHeightWithPenetration(Vec3 *, float *, int, int, float);
}

static inline void MatrixIdentity(Matrix44 *a) {
    for (int i = 0; i < 4; i++) for (int j = 0; j < 4; j++) a->m[i][j] = 0.0f;
    a->m[0][0] = a->m[1][1] = a->m[2][2] = a->m[3][3] = 1.0f;
}

static inline void AccumulateProduct(float &value, float right, float left) {
    value += left * right;
}

static inline void MatrixMultiply(Matrix44 *a, const Matrix44 *b) {
    float out[16];
    int i, k;
    for (k = 0, i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = a->m[i][0] * b->m[0][j];
            AccumulateProduct(sum, b->m[1][j], a->m[i][1]);
            AccumulateProduct(sum, b->m[2][j], a->m[i][2]);
            AccumulateProduct(sum, b->m[3][j], a->m[i][3]);
            out[k + j] = sum;
        }
        k += 4;
    }
    for (int i = 0; i < 16; i++) ((float *)a)[i] = out[i];
}

struct SpeedCurveTbl {
    CurveKey *keys;
    int n;
    float maxSpeed;
    float accel;
    float limit;
    float offset;
};

struct SpeedCurve {
    int idx;
    float speed;
    float prog;
    float x0C;
    float x10;
    float x14;
    unsigned char capped;
    char pad19;
    unsigned char clamp;
    char pad1b;
    SpeedCurveTbl *tbl;
};

extern "C" {

float fn_8019E9C0(Vec3 *a, const Vec3 *b) {
    float x = b->y * a->z - b->z * a->y;
    float y = b->z * a->x - b->x * a->z;
    float z = b->x * a->y - b->y * a->x;
    a->x = x;
    a->y = y;
    a->z = z;
    return x + y + z;
}

extern "C" {
extern double __frsqrte(double x);

static inline float Car_sqrtf(float x) {
    volatile float y;
    if (x > 0.0f) {
        double guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        guess = 0.5 * guess * (3.0 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

float fn_8019EA08(const Vec3 *v) {
    volatile float y;
    float len = v->x * v->x + v->y * v->y + v->z * v->z;
    if (len > 0.0f) {
        double guess = __frsqrte(len);
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        y = (float)(len * guess);
        len = y;
    }
    return len;
}

float fn_8019EA8C(Vec3 *v) {
    float len = v->x * v->x + v->y * v->y + v->z * v->z;
    if (len > 0.0f) {
        volatile float y;
        double guess = __frsqrte(len);
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        guess = 0.5 * guess * (3.0 - len * (guess * guess));
        y = (float)(len * guess);
        len = y;
    }
    if (len <= 0.0f) {
        v->x = v->y = v->z = 0.0f;
        return 0.0f;
    } else {
        float inv = 1.0f / len;
        v->x *= inv;
        v->y *= inv;
        v->z *= inv;
    }
    return len;
}
}

float SpeedCurve_LookupFromProgress(SpeedCurve *s, float t);
float SpeedCurve_LookupFromSpeed(SpeedCurve *s, float t);

void fn_8019EB9C(const Matrix44 *__restrict a, Vec3 *out, const Vec3 *__restrict v) {
    float vx = v->x;
    float vy = v->y;
    float vz = v->z;
    out->x = a->m[0][0] * vx + vy * a->m[1][0] + vz * a->m[2][0] + a->m[3][0];
    out->y = a->m[0][1] * vx + vy * a->m[1][1] + vz * a->m[2][1] + a->m[3][1];
    out->z = vx * a->m[0][2] + vy * a->m[1][2] + vz * a->m[2][2] + a->m[3][2];
}

#include "game/types/Mtx44S.h"

/* Alias-safe 4x4 product (out may be a or b), result through a scratch buffer. */
static inline void Mtx44S_Mul(Mtx44S *out, const Mtx44S *a, const Mtx44S *b) {
    float tmp[16];
    float *m;
    int k;
    int i;
    int j;

    if (out == a || out == b) {
        m = tmp;
    } else {
        m = out->v;
    }
    k = 0;
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            float sum = a->v[k + 0] * b->v[0 * 4 + j];
            sum += a->v[k + 1] * b->v[1 * 4 + j];
            sum += a->v[k + 2] * b->v[2 * 4 + j];
            sum += a->v[k + 3] * b->v[3 * 4 + j];
            m[k + j] = sum;
        }
        k += 4;
    }
    if (out == a || out == b) {
        for (i = 0; i < 16; i++) {
            out->v[i] = tmp[i];
        }
    }
}

void fn_8019EC18(Matrix44 *a, float angle) {
    Mtx44S rot;
    Mtx44S *dst = (Mtx44S *)a;
    float c;
    float s;
    int i;

    for (i = 0; i < 16; i++) {
        rot.v[i] = 0.0f;
    }
    rot.v[0] = rot.v[5] = rot.v[10] = rot.v[15] = 1.0f;
    c = (float)cos(angle);
    s = (float)sin(angle);
    rot.v[0] = c;
    rot.v[8] = s;
    rot.v[10] = c;
    rot.v[2] = -s;
    Mtx44S_Mul(&rot, &rot, dst);
    *dst = rot;
}

void SpeedCurve_UpdateSpeedCap(SpeedCurve *s, float v) {
    float x0C = s->x0C;
    if (x0C <= s->tbl[s->idx].limit && s->x10 <= 0.0f) {
        s->capped = 0;
        if (v <= 0.0) {
            s->prog = 0.0f;
            s->speed = 0.0f;
        } else {
            s->prog = v / 3.6f - s->tbl[s->idx].offset;
            if (s->prog < 0.0f) s->prog = 0.0f;
            s->speed = SpeedCurve_LookupFromSpeed(s, s->prog);
        }
    } else {
        float target;
        float a;
        float maxSpeed;
        float x10 = s->x10;
        s->capped = 1;
        a = s->x14 * s->tbl[s->idx].accel;
        maxSpeed = s->tbl[s->idx].maxSpeed;
        target = x0C * maxSpeed;
        x10 *= a;
        s->speed = s->speed - x10;
        if (s->speed < 0.0f) s->speed = 0.0f;
        if (s->speed > target) {
            s->speed -= a;
            if (s->speed < target) s->speed = target;
        } else if (s->speed < target) {
            s->speed += a;
            if (s->speed > target) s->speed = target;
        }
        if (s->speed > maxSpeed) s->speed = maxSpeed;
        s->prog = SpeedCurve_LookupFromProgress(s, s->speed);
    }
}

float SpeedCurve_LookupFromProgress(SpeedCurve *s, float t) {
    float out;
    fn_8019F1C4((CurveKeyKV *)s->tbl[s->idx].keys, s->tbl[s->idx].n, t, &out);
    return out;
}


float SpeedCurve_LookupFromSpeed(SpeedCurve *s, float t) {
    float out;
    fn_8019F3C0(s->tbl[s->idx].keys, s->tbl[s->idx].n, t, &out);
    if (s->clamp == 1 && out >= 55.555557f) out = 55.555557f;
    return out;
}


static inline float CurveHead(const CurveKey *p, float u) {
    float u2 = u * u;
    return p[0].v * (0.5f * u2 + -1.5f * u + 1.0f) + p[1].v * (-1.0f * u2 + 2.0f * u) + p[2].v * (0.5f * u2 + -0.5f * u);
}

static inline float CurveTail(const CurveKey *p, float u) {
    float u2 = u * u;
    return p[0].v * (0.5f * u2 + -0.5f * u) + p[1].v * (-1.0f * u2 + 1.0f) + p[2].v * (0.5f * u2 + 0.5f * u);
}

static inline float CurveMid(const CurveKey *p, float u) {
    float u2 = u * u;
    float u3 = u * u2;
    return p[0].v * (-0.5f * u3 + u2 + -0.5f * u) + p[1].v * (1.5f * u3 + -2.5f * u2 + 1.0f) + p[2].v * (-1.5f * u3 + 2.0f * u2 + 0.5f * u) + p[3].v * (0.5f * u3 + -0.5f * u2);
}

int fn_8019F3C0(CurveKey *p, int n, float t, float *out) {
    int i;
    if (n < 4) return 0;
    if (t <= 0.0f) {
        *out = 0.0f;
        return 0;
    }
    if (p[1].k > t) {
        *out = CurveHead(p, (t - p[0].k) / (p[1].k - p[0].k));
    } else if (p[n - 1].k < t) {
        *out = p[n - 1].v;
    } else if (p[n - 2].k < t) {
        float u = (t - p[n - 2].k) / (p[n - 1].k - p[n - 2].k);
        *out = CurveTail(&p[n - 3], u);
    } else {
        i = 1;
        do {
            if (p[i].k > t) goto found;
            i++;
        } while (i < n);
        *out = 0.0f;
        return 0;
    found:
        i--;
        *out = CurveMid(&p[i - 1], (t - p[i].k) / (p[i + 1].k - p[i].k));
    }
    return 1;
}

static inline float CurveHeadKV(const CurveKeyKV *p, float u) {
    float u2 = u * u;
    return p[0].v * (0.5f * u2 + -1.5f * u + 1.0f) + p[1].v * (-1.0f * u2 + 2.0f * u) + p[2].v * (0.5f * u2 + -0.5f * u);
}

static inline float CurveTailKV(const CurveKeyKV *p, float u) {
    float u2 = u * u;
    return p[0].v * (0.5f * u2 + -0.5f * u) + p[1].v * (-1.0f * u2 + 1.0f) + p[2].v * (0.5f * u2 + 0.5f * u);
}

static inline float CurveMidKV(const CurveKeyKV *p, float u) {
    float u2 = u * u;
    float u3 = u * u2;
    return p[0].v * (-0.5f * u3 + u2 + -0.5f * u) + p[1].v * (1.5f * u3 + -2.5f * u2 + 1.0f) + p[2].v * (-1.5f * u3 + 2.0f * u2 + 0.5f * u) + p[3].v * (0.5f * u3 + -0.5f * u2);
}

int fn_8019F1C4(CurveKeyKV *p, int n, float t, float *out) {
    int i;
    if (n < 4) return 0;
    if (t <= 0.0f) {
        *out = 0.0f;
        return 0;
    }
    if (p[1].k > t) {
        *out = CurveHeadKV(p, (t - p[0].k) / (p[1].k - p[0].k));
    } else if (p[n - 1].k < t) {
        *out = p[n - 1].v;
    } else if (p[n - 2].k < t) {
        float u = (t - p[n - 2].k) / (p[n - 1].k - p[n - 2].k);
        *out = CurveTailKV(&p[n - 3], u);
    } else {
        i = 1;
        do {
            if (p[i].k > t) goto found;
            i++;
        } while (i < n);
        *out = 0.0f;
        return 0;
    found:
        i--;
        *out = CurveMidKV(&p[i - 1], (t - p[i].k) / (p[i + 1].k - p[i].k));
    }
    return 1;
}

}

static inline int IsSpecialMovementMode() { return g_gameMode == 2 ? 1 : 0; }

inline CarTrivial::CarTrivial() {}

inline MovementState::MovementState(float a, float b) : scale(a), value(b) {
    vector.x = 0.0f;
    vector.y = 0.0f;
    vector.z = 0.0f;
}

inline MovementSettings::MovementSettings(int a, int b, bool special) {
    field22 = special;
    field24 = a;
    field28 = b;
    field0c = 0.0f;
    field14 = 0.0f;
    field10 = 0.0f;
    field08 = 0;
    field18 = 0.0f;
    field1c = 1.0f;
    field20 = 1;
    field21 = 0;
}

CarMovementInit::CarMovementInit(void *o, unsigned char *cfg, void *context, float x, float z, float angle)
    : owner(o), config(cfg), settings(*(int *)(config + 0xf0), *(int *)(config + 0xf4), IsSpecialMovementMode()),
      state(1.5f, 0.95f)
{
    field320 = context;
    field38 = *(float *)(config + 0x28);
    field3c = *(float *)(config + 0x40);
    pos.Set(x, 0.0f, z);
    prev.Set(pos.x, pos.y, pos.z);
    yaw = angle;
    MatrixIdentity(&orientation);
    Matrix44 rotation;
    MatrixIdentity(&rotation);
    float radians = (float)(0.017453292519943295 * yaw);
    float c = (float)cos(radians);
    float sn = (float)sin(radians);
    rotation.m[0][0] = c; rotation.m[2][0] = sn;
    rotation.m[2][2] = c; rotation.m[0][2] = -sn;
    MatrixMultiply(&rotation, &orientation);
    orientation = rotation;
    for (int i = 0; i < 16; i++) ((float *)&previous)[i] = ((float *)&orientation)[i];
    MatrixIdentity(&matrixD8);
    v158.Set(0.0f, 0.0f, 0.0f);
    v164.Set(0.0f, 0.0f, 0.0f);
    v170.Set(0.0f, 0.0f, 0.0f);
    v17c.Set(0.0f, 0.0f, 0.0f);
    v188.Set(0.0f, 0.0f, 0.0f);
    v194.Set(0.0f, 0.0f, 0.0f);
    field1cc = 0.0f; field1d0 = yaw;
    field1d8 = 0.0f; field1dc = 0.0f; field1e0 = 0.0f; field1e4 = 0.0f; field1e8 = 0.0f;
    v1ec.Set(0.0f, 0.0f, 0.0f);
    v1f8.Set(0.0f, 0.0f, 0.0f);
    MatrixIdentity(&matrix204);
    field244 = 0; field245 = 0; field246 = 0; field248 = 0; field24c = 1.0f; field250 = 0.0f;
    field1c0 = 0.0f; field2be = 0;
    v1a0.Set(0.0f, 1.0f, 0.0f);
    flags[0] = 1; wheelValues[0] = lbl_804963F8[1];
    flags[1] = 1; wheelValues[1] = lbl_804963F8[1];
    flags[2] = 1; wheelValues[2] = lbl_804963F8[7];
    flags[3] = 1; wheelValues[3] = lbl_804963F8[7];
    v298.Set(0.0f, 0.0f, 0.0f);
    v2a4.Set(0.0f, 0.0f, 0.0f);
    field2bc = 0; field2bd = 0;
    field2c0 = 1; field2c4 = 1; field2c8 = 1;
    field2d4 = 35.0f; field2d8 = 1.0f; field2dc = 0;
    field2e0 = 0.0f; field2f4 = 1.0f; field2f0 = 1.0f;
    field2fc = 0; field2fd = 0; field2fe = 0;
    field2e4 = 0.0f; field2e8 = 0.0f; field2ec = 0.0f;
    field2f8 = 1.0f; field300 = 1.0f;
    v310.Set(0.0f, 0.0f, 0.0f);
    GroundHeight ground;
    if (Terrain_GetGroundHeightWithPenetration(&pos, &ground.value, 0, 0, 10.0f) == 1) {
        pos.y = ground.value; prev.y = ground.value;
    }
    field2c = 0.7f; field30 = 0;
}

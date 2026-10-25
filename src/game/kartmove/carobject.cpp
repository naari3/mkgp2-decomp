/* Car object / speed curve code, .text 0x8019E1A8..0x8019F5BC.
 * This span's extabindex is not in ascending order, so dtk can't split it
 * further; it stays one NonMatching TU and gains functions as they match. */

typedef struct { float v; float k; } CurveKey;
typedef struct { float k; float v; } CurveKeyKV;

extern "C" {
extern void MemoryManager_TimedFree(void *p);
int fn_8019F1C4(CurveKeyKV *keys, int n, float t, float *out);
int fn_8019F3C0(CurveKey *keys, int n, float t, float *out);
}

struct CarElem {
    ~CarElem();
    char pad[0xc];
};

struct CarObject {
    char pad[0x258];
    CarElem elems[4];
    ~CarObject();
};

CarObject::~CarObject() {}

struct CarTrivial {
    ~CarTrivial();
};

CarTrivial::~CarTrivial() {}

typedef struct { float x, y, z; } Vec3;

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

float fn_8019EA08(Vec3 *v) {
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
        float x10 = s->x10;
        float a;
        float target;
        float maxSpeed;
        float d;
        s->capped = 1;
        a = s->x14 * s->tbl[s->idx].accel;
        maxSpeed = s->tbl[s->idx].maxSpeed;
        target = x0C * maxSpeed;
        d = x10 * a;
        s->speed = s->speed - d;
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

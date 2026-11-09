#include "game/kartmove/speed_private.h"

extern "C" const float lbl_806D9710, lbl_806D9714;

static inline float KartVec_Sqrt(float x) {
    volatile float y;
    if (x > lbl_806D96D0) {
        register double g = __frsqrte(x);
        { g = g * lbl_806D96E0 * (lbl_806D96E8 - x * (g * g)); }
        { g = lbl_806D96E0 * g * (lbl_806D96E8 - x * (g * g));
        g = lbl_806D96E0 * g * (lbl_806D96E8 - x * (g * g)); }
        y = (float)(g * x);
        return y;
    }
    return x;
}

struct KartVec {
    float x, y, z;
    KartVec() {}
    ~KartVec() {}
    KartVec(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    float Dot(const KartVec &o) const {
        float xx = x * o.x;
        float yy = y * o.y;
        float zz = z * o.z;
        return zz + (xx + yy);
    }
    float Length() const { float d = Dot(*this); KART_SPEED_ROOT(d); return d; }
    void Normalize() {
        float len = Length();
        if (len <= lbl_806D96D0) {
            z = lbl_806D96D0;
            y = lbl_806D96D0;
            x = lbl_806D96D0;
        } else {
            float s = lbl_806D96D4 / len;
            x *= s;
            y *= s;
            z *= s;
        }
    }
};

extern "C" void fn_8019ADF4(KartForceState *k, Vec3 *input) {
    register float _t476 = input->z;
    KartVec v(input->x, input->y, _t476);
    v.y = lbl_806D96D0;
    if (v.Length() <= lbl_806D96D0) return;
    KartVec n(k->forward.x, lbl_806D96D0, k->forward.z);
    { n.Normalize(); }
    float dot;
    { dot = n.Dot(v); }
    float _t172;
    _t172 = v.y;
    v.x += lbl_806D9710 * (n.x * dot);
    { v.z += lbl_806D9710 * (dot * n.z);
    k->impulse.x += v.x; }
    k->impulse.y += _t172;
    { k->impulse.z += v.z; }
    float len = KartVec_Sqrt(k->impulse.z * k->impulse.z +
                             (k->impulse.x * k->impulse.x + k->impulse.y * k->impulse.y));
    if (len > lbl_806D9714) {
        register float s = lbl_806D9714 / len;
        k->impulse.x *= s;
        { k->impulse.y *= s; }
        k->impulse.z *= s;
    }
}

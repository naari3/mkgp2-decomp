#include "game/kartmove/speed_private.h"

extern "C" const float lbl_806D9710, lbl_806D9714;

static inline float KartVec_Sqrt(float x) {
    volatile float y;
    if (x > lbl_806D96D0) {
        double g = __frsqrte(x);
        g = lbl_806D96E0 * g * (lbl_806D96E8 - x * (g * g));
        g = lbl_806D96E0 * g * (lbl_806D96E8 - x * (g * g));
        g = lbl_806D96E0 * g * (lbl_806D96E8 - x * (g * g));
        y = (float)(x * g);
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
    KartVec v(input->x, input->y, input->z);
    v.y = lbl_806D96D0;
    if (v.Length() <= lbl_806D96D0) return;
    KartVec n(k->forward.x, lbl_806D96D0, k->forward.z);
    n.Normalize();
    float dot = n.Dot(v);
    v.x += lbl_806D9710 * (n.x * dot);
    v.z += lbl_806D9710 * (n.z * dot);
    k->impulse.x += v.x;
    k->impulse.y += v.y;
    k->impulse.z += v.z;
    float len = KartVec_Sqrt(k->impulse.z * k->impulse.z +
                             (k->impulse.x * k->impulse.x + k->impulse.y * k->impulse.y));
    if (len > lbl_806D9714) {
        float s = lbl_806D9714 / len;
        k->impulse.x *= s;
        k->impulse.y *= s;
        k->impulse.z *= s;
    }
}

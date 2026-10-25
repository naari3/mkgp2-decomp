/*
 * 0x80173F5C..0x80173FA4: float clamp and wrap helpers.
 */

extern "C" {

float fn_80173F5C(float v, float lo, float hi) {
    if (v > hi) {
        return hi;
    }
    if (v < lo) {
        return lo;
    }
    return v;
}

float fn_80173F7C(float v, float lo, float hi) {
    float range = hi - lo;

    for (;;) {
        if (v > hi) {
            v -= range;
        } else if (v < lo) {
            v += range;
        } else {
            return v;
        }
    }
}

}

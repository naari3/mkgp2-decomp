/* Needs a GC/2.5+ compiler (2.5, 2.6 and 2.7 all match; 2.7 chosen) plus
 * __restrict: only that pairing sinks the prologue stores below the vector
 * loads. GC/1.3.2 keeps them at the top. */
extern const float lbl_806D592C;
extern const double lbl_806D5940;
extern const double lbl_806D5948;
extern double atan2(double, double);

static inline float Vec3_sqrtf(float x) {
    volatile float y;
    if (x > lbl_806D592C) {
        double guess = __frsqrte(x);
        guess = lbl_806D5940 * guess * (lbl_806D5948 - x * (guess * guess));
        guess = lbl_806D5940 * guess * (lbl_806D5948 - x * (guess * guess));
        guess = lbl_806D5940 * guess * (lbl_806D5948 - x * (guess * guess));
        y = (float)(x * guess);
        return y;
    }
    return x;
}

#pragma exceptions on
float Vec3_ToPitch(float *__restrict v) {
    return atan2(-v[1], Vec3_sqrtf(v[0] * v[0] + v[2] * v[2]));
}

float Vec3_HorizontalMagnitude(float *__restrict v) {
    return Vec3_sqrtf(v[0] * v[0] + v[2] * v[2]);
}
#pragma exceptions reset

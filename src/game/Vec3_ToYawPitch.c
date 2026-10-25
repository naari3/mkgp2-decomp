/* Same compiler setup as Vec3_ToPitch.c: GC/2.7 plus __restrict. */
extern const float lbl_806D592C;
extern const double lbl_806D5940;
extern const double lbl_806D5948;
extern double Atan2(double, double);

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
void Vec3_ToYawPitch(float *__restrict v, float *__restrict outPitch, float *__restrict outYaw) {
    float horizontal = Vec3_sqrtf(v[0] * v[0] + v[2] * v[2]);
    float up = -v[1];

    *outYaw = Atan2(v[0], v[2]);
    *outPitch = Atan2(up, horizontal);
}
#pragma exceptions reset

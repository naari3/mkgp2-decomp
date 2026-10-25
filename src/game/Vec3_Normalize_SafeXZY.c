extern float Vec3_Magnitude(float *);

#pragma exceptions on
void Vec3_Normalize_SafeXZY(float *dst, float *src) {
    float mag = Vec3_Magnitude(src);

    if (0.0001f < mag) {
        dst[0] = src[0] / mag;
        dst[1] = src[1] / mag;
        dst[2] = src[2] / mag;
    } else {
        dst[0] = 0.0f;
        dst[1] = 0.0f;
        dst[2] = 1.0f;
    }
}

#pragma exceptions reset

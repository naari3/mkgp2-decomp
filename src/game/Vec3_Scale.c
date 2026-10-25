typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void PSVECScale(const Vec3 *src, Vec3 *dst, float scale);

void Vec3_Scale(Vec3 *dst, const Vec3 *src, float scale) {
    PSVECScale(src, dst, scale);
}

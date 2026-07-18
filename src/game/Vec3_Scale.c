typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

extern void fn_8025E2AC(const Vec3 *src, Vec3 *dst, float scale);

void Vec3_Scale(Vec3 *dst, const Vec3 *src, float scale) {
    fn_8025E2AC(src, dst, scale);
}

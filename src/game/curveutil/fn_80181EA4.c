typedef struct Vec3f {
    float x, y, z;
} Vec3f;

void fn_80181EA4(const Vec3f *p0, const Vec3f *p1, const Vec3f *p2, Vec3f *out, float t) {
    float u = 1.0f - t;
    float uu = u * u;
    float b1 = 2.0f * t * u;
    float tt = t * t;
    out->x = p0->x * uu + p1->x * b1 + p2->x * tt;
    out->y = p0->y * uu + p1->y * b1 + p2->y * tt;
    out->z = p0->z * uu + p1->z * b1 + p2->z * tt;
}

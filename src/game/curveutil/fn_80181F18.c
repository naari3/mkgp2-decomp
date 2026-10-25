typedef struct Vec3f {
    float x, y, z;
} Vec3f;

extern const float lbl_80491988[];
extern void Vec3_Subtract(const Vec3f *a, const Vec3f *b, Vec3f *out);
extern void PSVECScale(const Vec3f *src, Vec3f *dst, float scale);
extern void PSVECAdd(const Vec3f *a, const Vec3f *b, Vec3f *out);

void fn_80181F18(const Vec3f *a, const Vec3f *b, const Vec3f *c, Vec3f *out, float t) {
    Vec3f dir;
    Vec3f side;
    Vec3f mid;
    Vec3_Subtract(c, a, &dir);
    PSVECScale(&dir, &mid, 0.5f);
    PSVECAdd(a, &mid, &mid);
    Vec3_Subtract(b, &mid, &side);
    PSVECScale(&dir, &dir, t);
    PSVECScale(&side, &side, lbl_80491988[(int)(11.377778f * (57.29578f * (3.1415927f * t))) & 0xFFF]);
    PSVECAdd(a, &dir, out);
    PSVECAdd(out, &side, out);
}

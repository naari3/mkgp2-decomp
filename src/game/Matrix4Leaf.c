/* Contiguous observed Matrix4/Vec3 leaf operations. Shared constants stay external. */
extern const float lbl_806D592C;
extern const float lbl_806D5930;

void Matrix4_Identity(float *matrix)
{
    matrix[0] = lbl_806D5930;
    matrix[1] = lbl_806D592C;
    matrix[2] = lbl_806D592C;
    matrix[3] = lbl_806D592C;
    matrix[4] = lbl_806D592C;
    matrix[5] = lbl_806D5930;
    matrix[6] = lbl_806D592C;
    matrix[7] = lbl_806D592C;
    matrix[8] = lbl_806D592C;
    matrix[9] = lbl_806D592C;
    matrix[10] = lbl_806D5930;
    matrix[11] = lbl_806D592C;
    matrix[12] = lbl_806D592C;
    matrix[13] = lbl_806D592C;
    matrix[14] = lbl_806D592C;
    matrix[15] = lbl_806D5930;
}

void Matrix4_Copy(float *destination, const float *source)
{
    int i;
    for (i = 0; i < 16; ++i) destination[i] = source[i];
}

/* Bounded best C draft: not counted as genuine matching. */
#if 0
void Vec3_Lerp(float *out, const float *first, const float *second, float t)
{
    float complement = lbl_806D5930 - t;
    float x = first[0] * t + second[0] * complement;
    float y = first[1] * t + second[1] * complement;
    float z = first[2] * t + second[2] * complement;
    out[0] = x;
    out[1] = y;
    out[2] = z;
}
#endif

/* Exact assembly fallback; Identity and Copy above are genuine C. */
asm void Vec3_Lerp(float *out, const float *first, const float *second, float t)
{
    nofralloc
    lfs f0, lbl_806D5930(r2)
    lfs f3, 0(r5)
    fsubs f7, f0, f1
    lfs f2, 4(r5)
    lfs f0, 8(r5)
    lfs f6, 0(r4)
    fmuls f5, f3, f7
    lfs f4, 4(r4)
    fmuls f3, f2, f7
    lfs f2, 8(r4)
    fmuls f0, f0, f7
    fmadds f5, f6, f1, f5
    fmadds f3, f4, f1, f3
    fmadds f0, f2, f1, f0
    stfs f5, 0(r3)
    stfs f3, 4(r3)
    stfs f0, 8(r3)
    blr
}
